#include "common.h"
#include "nu/nusys.h"
#include "game_modes.h"

// TODO move these somewhere else...
u8 nuYieldBuf[NU_GFX_YIELD_BUF_SIZE] ALIGNED(16);
OSThread __osThreadSave;
u8 nuBootStack[0x2000] ALIGNED(8);

// used in effects/gfx/flame.c
unsigned char D_800B32E0[0x800] ALIGNED(16);
unsigned char D_800B3AE0[0x800] ALIGNED(16);

s16 D_80074010 = 8; // might be an array, could be size 1-8

void gfxRetrace_Callback(s32);
void gfxPreNMI_Callback(void);
void appendGfx_reset_tile_pattern(void);

void gfx_draw_frame(void);
void gfx_init_state(void);

void create_audio_system(void);
void load_engine_data(void);

enum {
    RESET_STATE_NONE    = 0,
    RESET_STATE_INIT    = 1,
    RESET_STATE_FADE    = 2,
};

// TODO try uniting these two split files
extern s32 ResetGameState;
extern u16* ResetSavedFrameImg;
extern s16 D_80073E08;
extern s16 D_80073E0A;
extern IMG_BIN ResetTilesImg[];

#if defined(SHIFT) || VERSION_IQUE
#define shim_create_audio_system_obfuscated create_audio_system
#define shim_load_engine_data_obfuscated load_engine_data
#endif

u16* ResetFrameBufferArray;
u16* nuGfxZBuffer;

void boot_main(void* data) {
#if VERSION_JP
    if (osTvType == OS_TV_NTSC) {
        nuGfxDisplayOff();
        osViSetMode(&osViModeNtscLan1);
        osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_ON | OS_VI_DITHER_FILTER_ON);
        nuGfxDisplayOff();
    } else {
        PANIC();
    }
#else // not VERSION_JP
    if (osTvType == OS_TV_NTSC) {
        osViSetMode(&osViModeNtscLan1);
        osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_ON | OS_VI_DITHER_FILTER_ON);
    } else if (osTvType == OS_TV_MPAL) {
        osViSetMode(&osViModeMpalLan1);
        osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_ON | OS_VI_DITHER_FILTER_ON);
    } else {
        PANIC();
    }

    nuGfxDisplayOff();
    crash_screen_init();
#endif

#if !VERSION_IQUE
    is_debug_init();
#endif
    nuGfxInit();
    gGameStatusPtr->contBitPattern = nuContInit();

#if !VERSION_IQUE
    load_obfuscation_shims();
#endif
    shim_create_audio_system_obfuscated();
    shim_load_engine_data_obfuscated();

    nuGfxFuncSet((NUGfxFunc) gfxRetrace_Callback);
    nuGfxPreNMIFuncSet(gfxPreNMI_Callback);
    gRandSeed += osGetCount();
    nuGfxDisplayOn();

    while (TRUE) {}
}

void gfxRetrace_Callback(s32 gfxTaskNum) {
    if (ResetGameState != RESET_STATE_NONE) {
        if (ResetGameState == RESET_STATE_INIT) {
            nuGfxTaskAllEndWait();
            if (gfxTaskNum == 0) {
                u16* fb = (u16*) osViGetCurrentFramebuffer();
                u16** bufferSet = &ResetFrameBufferArray;

                bufferSet[2] = fb;
                bufferSet[1] = fb;
                bufferSet[0] = fb;
                ResetSavedFrameImg = fb;
                nuGfxSetCfb(&ResetFrameBufferArray, 3);
                osViSwapBuffer(ResetFrameBufferArray);
                ResetGameState = RESET_STATE_FADE;
            }
        }
        if (ResetGameState == RESET_STATE_FADE) {
            appendGfx_reset_tile_pattern();
        }
    } else {
        D_80073E0A ^= 1;
        if (D_80073E0A == 0) {
            step_game_loop();
            D_80073E08 = 1;

            if (gfxTaskNum < 3) {
                D_80073E08 = 0;
                gfx_task_background();
                gfx_draw_frame();
            }
        }
    }
}

// on reset, draw a series of animated triangular black tiles emanating from the center of the screen
void appendGfx_reset_tile_pattern(void) {
    s16 t;
    s16 i;
    s16 j;
    u16* frozenFrame;

    gMatrixListPos = 0;
    gDisplayContext = &D_80164000[gCurrentDisplayContextIndex];
    gMainGfxPos = gDisplayContext->mainGfx;
    frozenFrame = ResetSavedFrameImg;
    gfx_init_state();

    gDPSetDepthImage(gMainGfxPos++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(frozenFrame));
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    gDPSetCombineMode(gMainGfxPos++, PM_CC_RESET_TILES, PM_CC_RESET_TILES);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 127);
    gDPLoadTextureTile_4b(gMainGfxPos++, ResetTilesImg, G_IM_FMT_I, 128, 8, 0, 0, 127, 7, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 15; j++) {
            s32 s4 = i + 14;
            t = (33 - (s4 - j)) / 2 + 15 - D_80074010;
            if (t >= 16) {
                continue;
            }
            if (t < 0) {
                continue;
            }
            gSPTextureRectangle(gMainGfxPos++, ((i * 8) + 160) * 4,
                                                 ((j * 8)) * 4,
                                                 ((i * 8) + 168) * 4,
                                                 ((j * 8) + 8) * 4,
                                                 G_TX_RENDERTILE,
                                                 (t * 8) * 32, 0, 0x0400, 0x0400);
            gSPTextureRectangle(gMainGfxPos++, ((i * 8) + 160) * 4,
                                                 (232 - (j * 8)) * 4,
                                                 ((i * 8) + 168) * 4,
                                                 (240 - (j * 8)) * 4,
                                                 G_TX_RENDERTILE,
                                                 (t * 8) * 32, 7 * 32, 0x0400, -0x0400);
            gSPTextureRectangle(gMainGfxPos++, (152 - (i * 8)) * 4,
                                                 ((j * 8)) * 4,
                                                 (160 - (i * 8)) * 4,
                                                 ((j * 8) + 8) * 4,
                                                 G_TX_RENDERTILE,
                                                 (t * 8 + 7) * 32, 0, -0x0400, 0x0400);
            gSPTextureRectangle(gMainGfxPos++, (152 - (i * 8)) * 4,
                                                 (232 - (j * 8)) * 4,
                                                 (160 - (i * 8)) * 4,
                                                 (240 - (j * 8)) * 4,
                                                 G_TX_RENDERTILE,
                                                 (t * 8 + 7) * 32, 7 * 32, -0x0400, -0x0400);
        }
    }

    D_80074010++;
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);
    nuGfxTaskStart(gDisplayContext->mainGfx, (u32)(gMainGfxPos - gDisplayContext->mainGfx) * 8, NU_GFX_UCODE_F3DEX, NU_SC_TASK_LODABLE);
    gCurrentDisplayContextIndex ^= 1;
}

#if VERSION_IQUE
NOP_FIX
#endif

void gfxPreNMI_Callback(void) {
    ResetGameState = RESET_STATE_INIT;
    nuContRmbForceStop();
}

typedef struct HeapInfo {
	u32 bytesUsed;
	u32 capacity;
} HeapInfo;
// typedef struct HeapNode {
//     /* 0x00 */ struct HeapNode* next;
//     /* 0x04 */ u32 length;
//     /* 0x08 */ u16 allocated;
//     /* 0x0A */ u16 entryID;
//     /* 0x0C */ u32 capacity;
// } HeapNode; // size = 0x10
extern HeapNode heap_generalHead;
void GetHeapUsage(HeapNode* heap, HeapInfo* heapInfo) {
	u32 bytesAllocated = 0;
    HeapNode* next;
    HeapNode* cur = heap;
    u32 length = 0;
    u16 allocated;
    if (heap == NULL) {
        //debug_printf("Heap pointer passed to function was NULL\n");
        heapInfo->bytesUsed = -1;
        heapInfo->capacity = -1;
        return;
    }
	//walk the nodes
	while (1) {
        bytesAllocated += sizeof(HeapNode); //account for header
        next = cur->next;
        length = cur->length;
        allocated = cur->allocated;
        if (allocated) {
            bytesAllocated += length;
        }
        if (next == NULL) {
            break;
        }
        cur = cur->next;
    }
    heapInfo->bytesUsed = bytesAllocated;
    heapInfo->capacity = cur->capacity;
}

int style = 1;

u8 dx_ascii_char_to_msg(u8 in) {
    switch (in) {
        case '\0': return MSG_CHAR_READ_END;
        case ' ': case '\t': return MSG_CHAR_READ_SPACE;
        case '\n': return MSG_CHAR_READ_ENDL;
        default:
            if (in < 0x20) {
                return MSG_CHAR_NOTE;
            }
            return in - 0x20;
    }
}

void ConvertAsciiToMesg(char* outputBuf, char* inputBuf) {
    s32 i;
    for (i = 0; inputBuf[i] != 0; i++) {
        outputBuf[i] = dx_ascii_char_to_msg(inputBuf[i]);
    }
    outputBuf[i] = 0xFD;
}

void goto_map_custom(char* map, s32 entry) {
    s16 mapID;
    s16 areaID;
    s16 mapTransitionEffect = TRANSITION_STANDARD;
    get_map_IDs_by_name(map, &areaID, &mapID);
    gGameStatusPtr->areaID = areaID;
    gGameStatusPtr->mapID = mapID;
    gGameStatusPtr->entryID = entry;
    set_map_transition_effect(mapTransitionEffect);
    set_game_mode(GAME_MODE_CHANGE_MAP);
}

int displayWorldHeapBar = FALSE;

void PrintWorldHeapUsage(void) {
    HeapInfo worldHeapInfo;
    s32 posX = 15;
    s32 posY = 25;
    s32 baseWidth = 275;
    s32 height = 15;
    f32 heapPercentage;
    char buf[20];
    char buf2[20];
    s32 i;
    if (gGameStatus.pressedButtons[0] & U_JPAD) {
        displayWorldHeapBar ^= 1;
    }
    if (gGameStatus.pressedButtons[0] & D_JPAD) {
        goto_map_custom("kmr_03", 1);
        gPlayerData.hammerLevel = 0;
        gPlayerData.curPartner = 5;
        gCurrentSaveFile.globalBytes[0] = STORY_CH0_LEFT_THE_PLAYGROUND;
    }
    if (displayWorldHeapBar) { 
        GetHeapUsage(&heap_generalHead, &worldHeapInfo);
        heapPercentage = ((f32)worldHeapInfo.bytesUsed / (f32)GENERAL_HEAP_SIZE) * 100;
        sprintf(buf, "%.2f%%", heapPercentage);
        ConvertAsciiToMesg(buf2, buf);
        draw_msg((s32)buf2, 130, 40, 255, 0, 0);
        bzero(buf, sizeof(buf));
        bzero(buf2, sizeof(buf2));
        sprintf(buf, "%d / %d", worldHeapInfo.bytesUsed, GENERAL_HEAP_SIZE);
        ConvertAsciiToMesg(buf2, buf);
        draw_msg((s32)buf2, 130, 54, 255, 0, 0);
        draw_box(0, (WindowStyle)4, posX, posY, 0, baseWidth, height, 255, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0, NULL,
                    SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
        draw_box(0, WINDOW_STYLE_20, posX, posY, 0, heapPercentage * 2.75, height, 255, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0, NULL,
                    SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
    }
}
