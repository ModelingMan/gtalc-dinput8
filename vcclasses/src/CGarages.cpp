#include "vcclasses.h"
#include "vcversion.h"

int *CGarages::carsCollected = reinterpret_cast<int *>(vcversion::AdjustOffset(0x007D52F8));
CGarage *CGarages::garages = reinterpret_cast<CGarage *>(vcversion::AdjustOffset(0x00812668));

static unsigned long g_TriggerMessage = vcversion::AdjustOffset(0x0042EDE0);
static unsigned long g_IsEntityEntirelyInside3D = vcversion::AdjustOffset(0x00430630);

__declspec(naked) void CGarages::TriggerMessage(char *, short, unsigned short, short)
{
	__asm jmp g_TriggerMessage;
}

__declspec(naked) bool CGarage::IsEntityEntirelyInside3D(unsigned long, float)
{
	__asm jmp g_IsEntityEntirelyInside3D;
}
