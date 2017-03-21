#include "vcclasses.h"
#include "vcversion.h"

CObject **CProjectileInfo::ms_apProjectile = reinterpret_cast<CObject **>(vcversion::AdjustOffset(0x0094B708));
