#include "don_02.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_don_02_EntryEast]    { -590,0,-840, 135.000000 },
    [ENTRY_don_02_EntryWest]    { -250,0,640, 0.000000 },
    [ENTRY_don_02_EntryIntro]    { -310,-50,-250, 0.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};