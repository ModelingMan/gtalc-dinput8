#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CAutomobile::m_sAllTaxiLights = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10ABB));

static unsigned long g_constructor = vcversion::AdjustOffset(0x0059E620);

__declspec(naked) CAutomobile::CAutomobile(int, unsigned char)
{
	__asm jmp g_constructor;
}
