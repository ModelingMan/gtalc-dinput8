#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_IsSphereTouchingVehicle = vcversion::AdjustOffset(0x005B7F00);

__declspec(naked) bool CVehicle::IsSphereTouchingVehicle(float, float, float, float)
{
	__asm jmp g_IsSphereTouchingVehicle;
}
