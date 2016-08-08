#include "vcclasses.h"
#include "vcversion.h"

CProjectileInfo::ProjectileInfo *CProjectileInfo::projectiles = reinterpret_cast<CProjectileInfo::ProjectileInfo *>(vcversion::AdjustOffset(0x007DB888));
