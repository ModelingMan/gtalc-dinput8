#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetActualPickupIndex = vcversion::AdjustOffset(0x0043D360);
static unsigned long g_GenerateNewOne = vcversion::AdjustOffset(0x004418C0);
CPickup *CPickups::pickups = reinterpret_cast<CPickup *>(vcversion::AdjustOffset(0x00945D30));

__declspec(naked) int CPickups::GetActualPickupIndex(int)
{
	__asm jmp g_GetActualPickupIndex;
}

__declspec(naked) int CPickups::GenerateNewOne(CVector, unsigned int, unsigned int, unsigned int, unsigned char, unsigned char, char *)
{
	__asm jmp g_GenerateNewOne;
}
