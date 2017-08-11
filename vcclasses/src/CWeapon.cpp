#include "vcclasses.h"
#include "vcversion.h"

bool &CWeapon::bPhotographHasBeenTaken = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10AF4));
