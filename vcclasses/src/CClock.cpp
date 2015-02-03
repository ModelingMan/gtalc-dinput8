#include "vcclasses.h"
#include "vcversion.h"

unsigned char& CClock::ms_nGameClockHours = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10B6B));
unsigned char& CClock::ms_nGameClockMinutes = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10B92));
unsigned short& CClock::ms_nGameClockSeconds = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A3C));