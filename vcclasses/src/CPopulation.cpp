#include "vcclasses.h"
#include "vcversion.h"

bool &CPopulation::ms_bGivePedsWeapons = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10AB3));
