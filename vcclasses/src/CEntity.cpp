#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetDistanceFromCentreOfMassToBaseOfModel = vcversion::AdjustOffset(0x00487D10);
static unsigned long g_UpdateRwFrame = vcversion::AdjustOffset(0x00489360);
static unsigned long g_RegisterReference = vcversion::AdjustOffset(0x004C6AC0);

__declspec(naked) float CEntity::GetDistanceFromCentreOfMassToBaseOfModel(void)
{
	__asm jmp g_GetDistanceFromCentreOfMassToBaseOfModel;
}

__declspec(naked) void CEntity::UpdateRwFrame(void)
{
	__asm jmp g_UpdateRwFrame;
}

__declspec(naked) void CEntity::RegisterReference(CEntity **)
{
	__asm jmp g_RegisterReference;
}
