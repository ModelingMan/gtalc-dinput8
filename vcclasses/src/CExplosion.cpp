#include "vcclasses.h"
#include "vcversion.h"

CExplosion *CExplosion::explosions = reinterpret_cast<CExplosion *>(vcversion::AdjustOffset(0x00780C88));
