#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetMaximumNumberOfPassengersFromNumberOfDoors = vcversion::AdjustOffset(0x00578A70);
static unsigned long g_ChooseVehicleColour = vcversion::AdjustOffset(0x00579190);

__declspec(naked) unsigned int CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(int)
{
	__asm jmp g_GetMaximumNumberOfPassengersFromNumberOfDoors;
}

__declspec(naked) void CVehicleModelInfo::ChooseVehicleColour(unsigned char &, unsigned char &)
{
	__asm jmp g_ChooseVehicleColour;
}
