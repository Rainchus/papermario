#include "ash_04.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_ash_04_Entry0]    { -484,0,5, 90.000000 },
    [ENTRY_ash_04_Entry1]    { 2,0,-479, 180.000000 },
    [ENTRY_ash_04_Entry2]    { 365,35,90, 180.000000 },
    [ENTRY_ash_04_Entry3]    { 0,0,-60, 0.000000 },
    [ENTRY_ash_04_Entry4]    { -360,0,-50, 90.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};