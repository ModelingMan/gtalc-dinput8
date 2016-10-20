#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetMaximumNumberOfPassengersFromNumberOfDoors = vcversion::AdjustOffset(0x00578A70);

__declspec(naked) unsigned int CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(int)
{
	__asm jmp g_GetMaximumNumberOfPassengersFromNumberOfDoors;
}
