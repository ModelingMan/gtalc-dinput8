#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CBoat_Constructor = vcversion::AdjustOffset(0x005A6470);
unsigned long g_CBoat_Destructor = vcversion::AdjustOffset(0x005BAB30);

static unsigned long g_constructor = vcversion::AdjustOffset(0x005A6470);

/*__declspec(naked) CBoat::CBoat(int, unsigned char)
{
	__asm jmp g_constructor;
}*/
