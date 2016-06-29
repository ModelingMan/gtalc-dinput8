#include "vcclasses.h"
#include "vcversion.h"

CCranes::Crane *CCranes::cranes = reinterpret_cast<CCranes::Crane *>(vcversion::AdjustOffset(0x007E4040));
int *CCranes::numCranes = reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C34));
