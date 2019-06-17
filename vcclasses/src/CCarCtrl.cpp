#include "vcclasses.h"
#include "vcversion.h"

unsigned int &CCarCtrl::LastTimeFireTruckCreated = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x0094DD14));
unsigned int &CCarCtrl::LastTimeAmbulanceCreated = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00A0D8D0));

static unsigned long g_ReInit = vcversion::AdjustOffset(0x00429320);

__declspec(naked) void CCarCtrl::ReInit(void)
{
	__asm jmp g_ReInit;
}
