#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_ObjectDamage = vcversion::AdjustOffset(0x004E0990);
static unsigned long g_operator_new = vcversion::AdjustOffset(0x004E4070);
static unsigned long g_constructor = vcversion::AdjustOffset(0x004E41B0);
static unsigned long g_constructor2 = vcversion::AdjustOffset(0x004E4220);

__declspec(naked) void CObject::ObjectDamage(float)
{
	__asm jmp g_ObjectDamage;
}

__declspec(naked) void *CObject::operator new(unsigned int)
{
	__asm jmp g_operator_new;
}

__declspec(naked) CObject::CObject(int, bool)
{
	__asm jmp g_constructor;
}

__declspec(naked) CObject::CObject(void)
{
	__asm jmp g_constructor2;
}
