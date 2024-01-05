#include "don_06.h"

extern EvtScript N(EVS_Main);

extern char wMapHitName[0x18];
extern char wMapShapeName[0x18];
extern char wMapTexName[0x18];
extern char wMapBgName[0x18];

s32 N(map_init)(void) {
    sprintf(wMapHitName, "%s", "don_06_hit");
    sprintf(wMapShapeName, "%s", "don_06_shape");
    sprintf(wMapBgName, "%s", "nok_bg");
    sprintf(wMapTexName, "%s", "don_tex");
    return FALSE;
}

EvtScript N(EVS_Main) = {
    EVT_SET(GB_WorldLocation, LOCATION_TESTING)
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    EVT_RETURN
    EVT_END
};
