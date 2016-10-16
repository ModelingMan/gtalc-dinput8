#include "vcclasses.h"
#include "vcversion.h"

bool &CVehicle::bCheat3 = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B0F));
bool &CVehicle::bAllDodosCheat = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B28));
bool &CVehicle::bWheelsOnlyCheat = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B30));

static unsigned long g_IsSphereTouchingVehicle = vcversion::AdjustOffset(0x005B7F00);

__declspec(naked) bool CVehicle::IsSphereTouchingVehicle(float, float, float, float)
{
	__asm jmp g_IsSphereTouchingVehicle;
}
