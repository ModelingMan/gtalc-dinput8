#include "CWantedHack.h"
#include "CRunningScriptHack.h"
#include "vcversion.h"

bool CWantedHack::initialise()
{
	if (!(CRunningScriptHack::debugMode & DEBUG_VICECITY)) {
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D2126))  = 3200; // level 6
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D2156))  = 1600; // level 5
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D2186))  =  800; // level 4
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D21B6))  =  400; // level 3
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004D21E3))  =  200; // level 2
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004D220A)) =   40; // level 1
	}
	return true;
}
