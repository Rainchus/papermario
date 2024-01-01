#include "ash_03.h"

extern EvtScript N(EVS_Main);

extern char wMapHitName[0x18];
extern char wMapShapeName[0x18];
extern char wMapTexName[0x18];
extern char wMapBgName[0x18];

s32 N(map_init)(void) {
    sprintf(wMapHitName, "%s", "ash_03_hit");
    sprintf(wMapShapeName, "%s", "ash_03_shape");
    sprintf(wMapBgName, "%s", "arn_bg");
    sprintf(wMapTexName, "%s", "sbk_tex");
    return FALSE;
}

EvtScript N(EVS_Main) = {
    EVT_SET(GB_WorldLocation, LOCATION_TESTING)
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    EVT_RETURN
    EVT_END
};