#include "vcclasses.h"
#include "vcversion.h"

int &CCranes::carsCollectedMilitaryCrane = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6CE4));
int &CCranes::numCranes = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C34));
CCrane *CCranes::cranes = reinterpret_cast<CCrane *>(vcversion::AdjustOffset(0x007E4040));
