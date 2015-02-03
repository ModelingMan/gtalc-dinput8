#include "vcclasses.h"
#include "vcversion.h"

CPlayerInfo *CWorld::Players = reinterpret_cast<CPlayerInfo *>(vcversion::AdjustOffset(0x0094AD28));