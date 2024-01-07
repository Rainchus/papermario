#include "don_01.h"
#include "common.h"

extern EvtScript N(EVS_Main);

extern char wMapHitName[0x18];
extern char wMapShapeName[0x18];
extern char wMapTexName[0x18];
extern char wMapBgName[0x18];

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_StartTexPanners) = {
    //uv panner 1
    EVT_CALL(SetTexPanner, MODEL_don_01_WaterRearTop, TEX_PANNER_1)
    EVT_CALL(EnableTexPanning, MODEL_don_01_WaterRearTop, TRUE)

    //uv panner 2
    EVT_CALL(SetTexPanner, MODEL_don_01_Waterfall, TEX_PANNER_2)
    EVT_CALL(EnableTexPanning, MODEL_don_01_Waterfall, TRUE)

    EVT_CALL(SetTexPanner, MODEL_don_01_WaterForeTop, TEX_PANNER_2)
    EVT_CALL(EnableTexPanning, MODEL_don_01_WaterForeTop, TRUE)

    EVT_CALL(SetTexPanner, MODEL_don_01_WaterForeBottom, TEX_PANNER_2)
    EVT_CALL(EnableTexPanning, MODEL_don_01_WaterForeBottom, TRUE)

    EVT_CALL(SetTexPanner, MODEL_don_01_WaterRearBottom, TEX_PANNER_2)
    EVT_CALL(EnableTexPanning, MODEL_don_01_WaterRearBottom, TRUE)
    
    //uv panner 3
    EVT_CALL(SetTexPanner, MODEL_don_01_WaterfallRear, TEX_PANNER_3)
    EVT_CALL(EnableTexPanning, MODEL_don_01_WaterfallRear, TRUE)
    
    EVT_THREAD
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(-100,    0,  1000,   0)
        TEX_PAN_PARAMS_FREQ(   1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        EVT_EXEC(N(EVS_UpdateTexturePan))
    EVT_END_THREAD
    EVT_THREAD
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(-400,    0,  -400,   0)
        TEX_PAN_PARAMS_FREQ(   1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        EVT_EXEC(N(EVS_UpdateTexturePan))
    EVT_END_THREAD
    EVT_THREAD
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP(   0,  200,    0, 3000)
        TEX_PAN_PARAMS_FREQ(   0,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        EVT_EXEC(N(EVS_UpdateTexturePan))
    EVT_END_THREAD
    EVT_RETURN
    EVT_END
};


s32 N(map_init)(void) {
    sprintf(wMapHitName, "%s", "don_01_hit");
    sprintf(wMapShapeName, "%s", "don_01_shape");
    sprintf(wMapBgName, "%s", "nok_bg");
    sprintf(wMapTexName, "%s", "don_tex");
    return FALSE;
}

EvtScript N(EVS_Main) = {
    EVT_SET(GB_StoryProgress, 0x5C)
    EVT_SET(GB_WorldLocation, LOCATION_TOAD_TOWN)
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    EVT_EXEC(N(EVS_StartTexPanners))
    EVT_RETURN
    EVT_END
};
