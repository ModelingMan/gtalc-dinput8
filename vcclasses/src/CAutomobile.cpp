#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CAutomobile::m_sAllTaxiLights = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10ABB));
