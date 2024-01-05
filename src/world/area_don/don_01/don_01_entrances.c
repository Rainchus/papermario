#include "don_01.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_don_01_EntryWest]    { -700,-30,-30, 405.000000 },
    [ENTRY_don_01_EntryNorth]    { 536,60,-860, 225.000000 },
    [ENTRY_don_01_EntryEast]    { 890,-40,301, 270.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};