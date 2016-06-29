#include "CRendererHack.h"
#include "Globals.h"
#include "vcversion.h"

bool CRendererHack::initialise()
{
	// disable backface culling from The Hero's SkyGfx - temporary
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9E5F)) = 1;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9F08)) = 1;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004C9F5D)) = 1;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004CA157)) = 1;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x004CA199)) = 1;
	return true;
}
