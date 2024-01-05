#include "don_06.h"

extern EvtScript N(EVS_Main);

EntryList N(Entrances) = {
    [ENTRY_don_06_Entry0]    { 0,100,5, 90.000000 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    //.tattle = { MSG_MapTattle },
};