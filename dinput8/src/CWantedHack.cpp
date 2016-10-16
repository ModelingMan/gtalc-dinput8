#include "CWantedHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include <Windows.h>

bool CWantedHack::initialise()
{
	if (!GetPrivateProfileInt("Misc", "UseVCWantedSystem", 0, "./gta-lc.ini")) {
		// level updater
		Patch<unsigned int>(0x004D2126, 3200); // level 6
		Patch<unsigned int>(0x004D2156, 1600); // level 5
		Patch<unsigned int>(0x004D2186,  800); // level 4
		Patch<unsigned int>(0x004D21B6,  400); // level 3
		Patch<unsigned int>(0x004D21E3,  200); // level 2
		Patch<unsigned char>(0x004D220A,  40); // level 1

		// max level
		Patch<unsigned int>(0x004D1EAC,  120); // level 1
		Patch<unsigned int>(0x004D1EC5,  300); // level 2
		Patch<unsigned int>(0x004D1EDB,  600); // level 3
		Patch<unsigned int>(0x004D1EF1, 1200); // level 4
		Patch<unsigned int>(0x004D1F07, 2400); // level 5
		Patch<unsigned int>(0x004D1F1D, 4800); // level 6

		// second helicopter
		Patch<unsigned int>(0x004D1E0F, 2);
	}
	return true;
}
