#include "ash_02.h"

#include "mapfs/ash_01_shape.h"
#include "mapfs/ash_01_hit.h"

#include "mapfs/ash_03_shape.h"
#include "mapfs/ash_03_hit.h"

extern EvtScript N(EVS_Main);

extern char wMapHitName[0x18];
extern char wMapShapeName[0x18];
extern char wMapTexName[0x18];
extern char wMapBgName[0x18];

s32 N(map_init)(void) {
    sprintf(wMapHitName, "%s", "ash_02_hit");
    sprintf(wMapShapeName, "%s", "ash_02_shape");
    sprintf(wMapBgName, "%s", "arn_bg");
    sprintf(wMapTexName, "%s", "sbk_tex");
    return FALSE;
}

EvtScript N(EVS_ExitWalk_West_ash_02) = EVT_EXIT_WALK(60, ENTRY_ash_02_EntryWest, "ash_01", ENTRY_ash_01_EntryEast);
//EvtScript N(EVS_ExitWalk_West_ash_01) = EVT_EXIT_WALK(60, ENTRY_ash_01_EntryWest, "ash_03", ENTRY_ash_01_EntryWest);

EvtScript N(EVS_BindExitTriggers) = {
    EVT_BIND_TRIGGER(EVT_PTR(N(EVS_ExitWalk_West_ash_02)), TRIGGER_FLOOR_ABOVE, COLLIDER_ash_02_LZWest, 1, 0)
    //EVT_BIND_TRIGGER(EVT_PTR(N(EVS_ExitWalk_West_ash_01)), TRIGGER_FLOOR_ABOVE, COLLIDER_ash_01_LZWest, 1, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Main) = {
    EVT_SET(GB_WorldLocation, LOCATION_TESTING)
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    EVT_SET(LVar0, EVT_PTR(N(EVS_BindExitTriggers)))
    EVT_EXEC(EnterWalk)
    EVT_WAIT(1)
    EVT_RETURN
    EVT_END
};
