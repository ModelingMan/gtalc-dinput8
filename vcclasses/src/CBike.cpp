#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CBike_Constructor = vcversion::AdjustOffset(0x00615740);
unsigned long g_CBike_Destructor = vcversion::AdjustOffset(0x00615720);

static unsigned long g_constructor = vcversion::AdjustOffset(0x00615740);

/*__declspec(naked) CBike::CBike(int, unsigned char)
{
	__asm jmp g_constructor;
}*/
