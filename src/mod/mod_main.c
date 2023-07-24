#include "common.h"


#define mainMenu 0
#define maxPageEntries 8
void* memcpy(void* s1, const void* s2, size_t n);

char testTextMainMenu[] = "Mapss";
char testTextMainMenu2[] = "Mapss2";

char testTextMainMenu3[] = "Mapss3";
char testTextMainMenu4[] = "Mapss4";

char testTextIndex0[] = "Index0";
char testTextIndex1[] = "Index1";

typedef struct CursorPosition {
    s32 xPos;
    s32 yPos;
} CursorPosition;

typedef struct PageEntry {
    char* entryText[maxPageEntries][maxPageEntries];
    s32 textPositions[maxPageEntries][maxPageEntries];
} PageEntry;

typedef struct PageInfo { //max of 8 entries per page
    PageEntry entries; //currently just 1
} PageInfo;

PageInfo mainPage = {
    .entries = {
        .entryText = {
            //x0, x1, (null)
            {testTextMainMenu, testTextMainMenu2, 0, 0, 0, 0, 0, 0},
            //y0, y1, (null)
            {testTextMainMenu3, testTextMainMenu4, 0, 0, 0, 0, 0, 0} },
        .textPositions = {
            {0, 0, 0, 0, 0, 0, 0, 0}, //x Positions
            {0, 12, 24, 36, 48, 60, 72, 84} // Y positions
        }, 
    },
};

PageInfo pageIndex1 = {
    .entries = {
        .entryText = {
            {testTextMainMenu, testTextMainMenu2, 0, 0, 0, 0, 0, 0}, 
            {testTextMainMenu, testTextMainMenu2, 0, 0, 0, 0, 0, 0}},
        .textPositions = {
            {0, 0, 0, 0, 0, 0, 0, 0}, //x Positions
            {0, 12, 24, 36, 48, 60, 72, 84} // Y positions
        }, 
    },
};

PageInfo* pages[] = {
    &mainPage,
    &pageIndex1,
};

s32 debugMenuBool = 0;
s32 debugCurMenu = 0;
CursorPosition debugCursorPosition = {0, 0};

char testString[] = "Maps";

void convertAsciiToMsg(char* msgText, char* asciiText) {
    while (*asciiText != 0) {
        *msgText++ = (*asciiText - 0x20);
        asciiText++;
    }

    *msgText = '\xFD';
}

typedef struct MessagePositions {
    s32 xPos;
    s32 yPos;
} MessagePositions;

MessagePositions messagePos[4] = {
    {12, 223},
    {80, 223},
    {165, 223},
    {230, 223},
};

typedef struct BoxInfo {
    s32 flags;
    WindowStyle style;
    s32 xPos;
    s32 yPos;
    s32 width;
    s32 height;
    u8 opacity;
} BoxInfo;

void draw_box_wrapper(BoxInfo box) {

    draw_box(box.flags, box.style, box.xPos, box.yPos, 0, box.width, box.height, box.opacity, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, NULL,
            NULL, box.width, box.height, NULL);
}

void drawDebugMenuText(BoxInfo debugBox) { //debugBox defines root position
    char msgCommandsSizeCTextWhiteColor[] = "\xFF\x0D\x0C\x0C\xFF\x05\x00";
    char msgCommandsSizeCTextYellowColor[] = "\xFF\x0D\x0C\x0C\xFF\x05\x05";
    char msgCommandsBuffer[sizeof(msgCommandsSizeCTextYellowColor)];
    char areaBufferAscii[90];
    s32 xPos, yPos;
    s32 i, j;

    // xPos = debugBox.xPos + 8;
    // yPos = debugBox.yPos + 4;

    switch (debugCurMenu) {
        case mainMenu:
            for (i = 0; i < ARRAY_COUNT(pages); i++) {
                for (j = 0; pages[i]->entries.entryText[i][j] != 0; j++) {
                    bzero(msgCommandsBuffer, sizeof(msgCommandsBuffer));
                    if (j == debugCursorPosition.yPos) { //color yellow if current entry, white otherwise
                        memcpy(msgCommandsBuffer, msgCommandsSizeCTextYellowColor, sizeof(msgCommandsBuffer));
                    } else {
                        memcpy(msgCommandsBuffer, msgCommandsSizeCTextWhiteColor, sizeof(msgCommandsBuffer));
                    }

                    xPos = debugBox.xPos + 8 + pages[i]->entries.textPositions[j][0];
                    yPos = debugBox.yPos + 4 + pages[i]->entries.textPositions[j][1];

                    // Copy the prefix sequence into the buffer
                    memcpy(areaBufferAscii, msgCommandsBuffer, sizeof(msgCommandsBuffer) -1);
                    
                    // Convert the ASCII message and copy it after the msg prefix
                    convertAsciiToMsg((areaBufferAscii + sizeof(msgCommandsBuffer) -1), pages[i]->entries.entryText[i][j]);

                    draw_msg((s32)areaBufferAscii, xPos, yPos, 0xFF, 0, DRAW_MSG_STYLE_MENU);
                }
      
            }

            break;

    }
}

void drawDebugMain(void) {
    BoxInfo debugBox;
    debugBox.flags = 0;
    debugBox.style = (WindowStyle)WINDOW_STYLE_4;
    debugBox.xPos = 16;
    debugBox.yPos = 60;
    debugBox.width = 60;
    debugBox.height = 120;
    debugBox.opacity = 255;

    draw_box_wrapper(debugBox);
    drawDebugMenuText(debugBox);
}

void mod_main_func(void) {
    char asciiBuffer[0x28];
    char msgCommands[] = "\xFF\x0D\x0C\x0C";
    char* mapStrings[] = {wMapHitName, wMapShapeName, wMapTexName, wMapBgName};
    char msg[4][sizeof(asciiBuffer) + 1]; // Array of 4 message buffers
    int i, j;
    s32 xPos, yPos;
    char areaBufferAscii[30];
    char areaBufferMsg[sizeof(areaBufferAscii + 1)];

    for (i = 0; i < ARRAY_COUNT(mapStrings); i++) {
        // Copy the prefix sequence into the buffer
        memcpy(msg[i], msgCommands, sizeof(msgCommands) -1);
        
        // Convert the ASCII message and copy it after the msg prefix
        convertAsciiToMsg(msg[i] + sizeof(msgCommands) -1, mapStrings[i]);
        
        // Draw message in pm64 text format
        draw_msg((s32)msg[i], messagePos[i].xPos, messagePos[i].yPos, 0xFF, 0, DRAW_MSG_STYLE_MENU);        
    }

    //gAreas[i].maps[j].id;
    
    
    //prints all map names at once
    // xPos = 0;
    // yPos = 0;
    // for (i = 0; i < ARRAY_COUNT(gAreas); i++) {
    //     for (j = 0; j < gAreas[i].mapCount; j++) {
    //         // Copy the prefix sequence into the buffer
    //         memcpy(areaBufferAscii, msgCommands, sizeof(msgCommands) -1);
            
    //         // Convert the ASCII message and copy it after the msg prefix
    //         convertAsciiToMsg((areaBufferAscii + sizeof(msgCommands) -1), gAreas[i].maps[j].id);

    //         draw_msg(areaBufferAscii, xPos, yPos, 0xFF, 0, DRAW_MSG_STYLE_MENU);
    //         yPos += 12;
    //     }
    // }

    if (gGameStatus.currentButtons[0] & BUTTON_R && gGameStatus.pressedButtons[0] & BUTTON_D_UP ) {
        debugMenuBool ^= 1;
    }

    if (gGameStatus.currentButtons[0] & BUTTON_R && gGameStatus.pressedButtons[0] & BUTTON_D_RIGHT ) {
        debugCurMenu++;
        if (debugCurMenu > ARRAY_COUNT(pages)) {
            debugCurMenu = ARRAY_COUNT(pages);
        }
    } else if (gGameStatus.currentButtons[0] & BUTTON_R && gGameStatus.pressedButtons[0] & BUTTON_D_LEFT ) {
        debugCurMenu--;
        if (debugCurMenu <= 0) {
            debugCurMenu = 0;
        }
    }

    if (debugMenuBool) {
        if (gGameStatus.pressedButtons[0] & BUTTON_D_UP) {
            if (--debugCursorPosition.yPos <= 0) {
                debugCursorPosition.yPos = 0;
            }
        } else if (gGameStatus.pressedButtons[0] & BUTTON_D_LEFT) {
            if (--debugCursorPosition.xPos <= 0) {
                debugCursorPosition.xPos = 0;
            }
        } else if (gGameStatus.pressedButtons[0] & BUTTON_D_RIGHT) {
            if (pages[debugCurMenu]->entries.entryText[debugCursorPosition.xPos + 1][debugCursorPosition.yPos] != 0) {
                debugCursorPosition.xPos++;
            }
        } else if (gGameStatus.pressedButtons[0] & BUTTON_D_DOWN) {
            if (pages[debugCurMenu]->entries.entryText[debugCursorPosition.xPos][debugCursorPosition.yPos + 1] != 0) {
                debugCursorPosition.yPos++;
            }
        }

        drawDebugMain();
    }
}

