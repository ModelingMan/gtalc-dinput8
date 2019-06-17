#include "vcclasses.h"
#include "vcversion.h"

int &CCranes::CarsCollectedMilitaryCrane = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B6CE4));
int &CCranes::NumCranes = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C34));
CCrane *CCranes::aCranes = reinterpret_cast<CCrane *>(vcversion::AdjustOffset(0x007E4040));
