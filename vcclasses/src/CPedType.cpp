#include "vcclasses.h"
#include "vcversion.h"

CPedType **CPedType::ms_apPedType = reinterpret_cast<CPedType **>(vcversion::AdjustOffset(0x00A0DA64));
