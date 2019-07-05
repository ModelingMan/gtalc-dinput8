#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CAutomobile_Constructor = vcversion::AdjustOffset(0x0059E620);
unsigned long g_CAutomobile_Destructor = vcversion::AdjustOffset(0x0059E600);

unsigned char &CAutomobile::m_sAllTaxiLights = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10ABB));

static unsigned long g_SetPanelDamage = vcversion::AdjustOffset(0x0059B2A0);
static unsigned long g_constructor = vcversion::AdjustOffset(0x0059E620);

__declspec(naked) void CAutomobile::SetPanelDamage(int, int, bool)
{
	__asm jmp g_SetPanelDamage;
}

/*__declspec(naked) CAutomobile::CAutomobile(int, unsigned char)
{
	__asm jmp g_constructor;
}*/
