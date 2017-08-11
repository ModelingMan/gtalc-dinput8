#include "vcclasses.h"
#include "vcversion.h"

PedType **CPedType::ms_apPedType = reinterpret_cast<PedType **>(vcversion::AdjustOffset(0x00A0DA64));
