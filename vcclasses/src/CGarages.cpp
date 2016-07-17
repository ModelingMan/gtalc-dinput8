#include "vcclasses.h"
#include "vcversion.h"

int *CGarages::carsCollected = reinterpret_cast<int *>(vcversion::AdjustOffset(0x007D52F8));
int &CGarages::bankVansCollected = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978714));
int &CGarages::policeCarsCollected = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D8B8));
CGarage *CGarages::garages = reinterpret_cast<CGarage *>(vcversion::AdjustOffset(0x00812668));

static unsigned long g_TriggerMessage = vcversion::AdjustOffset(0x0042EDE0);
static unsigned long g_IsEntityEntirelyInside3D = vcversion::AdjustOffset(0x00430630);
static unsigned long g_IsEntityEntirelyOutside = vcversion::AdjustOffset(0x00430430);
static unsigned long g_IsAnyOtherCarTouchingGarage = vcversion::AdjustOffset(0x0042FDB0);

__declspec(naked) void CGarages::TriggerMessage(char *, short, unsigned short, short)
{
	__asm jmp g_TriggerMessage;
}

__declspec(naked) bool CGarage::IsEntityEntirelyInside3D(CEntity *, float)
{
	__asm jmp g_IsEntityEntirelyInside3D;
}

__declspec(naked) bool CGarage::IsEntityEntirelyOutside(CEntity *, float)
{
	__asm jmp g_IsEntityEntirelyOutside;
}

__declspec(naked) bool CGarage::IsAnyOtherCarTouchingGarage(CVehicle *)
{
	__asm jmp g_IsAnyOtherCarTouchingGarage;
}
