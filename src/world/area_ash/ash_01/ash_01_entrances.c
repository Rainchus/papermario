#include "ash_01.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_ash_01_EntryEast]    { -65,0,0, 270.000000 },
    [ENTRY_ash_01_EntryWest]    { -2403,-1,424, 45.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};