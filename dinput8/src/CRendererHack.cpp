#include "CRendererHack.h"
#include "vcversion.h"
#include <Windows.h>

bool CRendererHack::initialise()
{
	if (GetPrivateProfileInt("Misc", "DisableCulling", 1, "./gta-lc.ini")) {
		// disable backface culling from aap's skygfx_vc - temporary
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9E5F)) = 1;
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9F08)) = 1;
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9F5D)) = 1;
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004CA157)) = 1;
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004CA199)) = 1;
	}
	return true;
}
