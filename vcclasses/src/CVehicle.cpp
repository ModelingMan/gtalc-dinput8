#include "vcclasses.h"
#include "vcversion.h"

bool &CVehicle::bCheat3 = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B0F));
bool &CVehicle::bAllDodosCheat = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B28));
bool &CVehicle::bWheelsOnlyCheat = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B30));

static unsigned long g_IsSphereTouchingVehicle = vcversion::AdjustOffset(0x005B7F00);
static unsigned long g_FindTyreNearestPoint = vcversion::AdjustOffset(0x005B96A0);
static unsigned long g_operator_new = vcversion::AdjustOffset(0x005BAB20);

__declspec(naked) bool CVehicle::IsSphereTouchingVehicle(float, float, float, float)
{
	__asm jmp g_IsSphereTouchingVehicle;
}

__declspec(naked) int CVehicle::FindTyreNearestPoint(float, float)
{
	__asm jmp g_FindTyreNearestPoint;
}

__declspec(naked) void *CVehicle::operator new(unsigned int)
{
	__asm jmp g_operator_new;
}
