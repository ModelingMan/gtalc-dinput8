#include "vcclasses.h"
#include "vcversion.h"

CExplosion::Explosion *CExplosion::explosions = reinterpret_cast<CExplosion::Explosion *>(vcversion::AdjustOffset(0x00780C88));
