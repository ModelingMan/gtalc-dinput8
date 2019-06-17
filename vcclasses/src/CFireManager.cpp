#include "vcclasses.h"
#include "vcversion.h"

CFire *CFireManager::fires = reinterpret_cast<CFire *>(vcversion::AdjustOffset(0x0097F8A0));
