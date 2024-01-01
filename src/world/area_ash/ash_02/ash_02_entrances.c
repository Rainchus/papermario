#include "ash_02.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_ash_02_EntryEast]    { 136,0,150, 270.000000 },
    [ENTRY_ash_02_EntryWest]    { -1580,0,0, 90.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};