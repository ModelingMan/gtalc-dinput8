#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CObject_Constructor = vcversion::AdjustOffset(0x004E4220);
unsigned long g_CObject_ConstructorWithIntBool = vcversion::AdjustOffset(0x004E41B0);
unsigned long g_CObject_Destructor = vcversion::AdjustOffset(0x004E4080);

static unsigned long g_ObjectDamage = vcversion::AdjustOffset(0x004E0990);
static unsigned long g_operator_new = vcversion::AdjustOffset(0x004E4070);
static unsigned long g_constructor = vcversion::AdjustOffset(0x004E41B0);
static unsigned long g_constructor2 = vcversion::AdjustOffset(0x004E4220);

static unsigned long g_OperatorNewWithIndex = vcversion::AdjustOffset(0x004E4050);
static unsigned long g_OperatorDelete = vcversion::AdjustOffset(0x004E4030);

static unsigned long g_ProcessControl = vcversion::AdjustOffset(0x004E3690);
static unsigned long g_Teleport = vcversion::AdjustOffset(0x004E0920);
static unsigned long g_Render = vcversion::AdjustOffset(0x004E2770);

__declspec(naked) void CObject::ObjectDamage(float)
{
	__asm jmp g_ObjectDamage;
}

__declspec(naked) void *CObject::operator new(unsigned int)
{
	__asm jmp g_operator_new;
}

/*__declspec(naked) CObject::CObject(int, bool)
{
	__asm jmp g_constructor;
}

__declspec(naked) CObject::CObject(void)
{
	__asm jmp g_constructor2;
}*/

__declspec(naked) void CObject::ProcessControl()
{
	__asm jmp g_ProcessControl;
}

__declspec(naked) void CObject::Teleport(CVector position)
{
	__asm jmp g_Teleport;
}

__declspec(naked) void CObject::Render()
{
	__asm jmp g_Render;
}

__declspec(naked) void *CObject::operator new(unsigned int size, int poolIndex)
{
	__asm jmp g_OperatorNewWithIndex;
}

__declspec(naked) void CObject::operator delete(void *)
{
	__asm jmp g_OperatorDelete;
}
