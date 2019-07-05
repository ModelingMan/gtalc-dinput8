#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CCutsceneObject_Constructor = vcversion::AdjustOffset(0x004E04D0);
unsigned long g_CCutsceneObject_Destructor = vcversion::AdjustOffset(0x004E0490);

static unsigned long g_SetModelIndex = vcversion::AdjustOffset(0x004E0440);
static unsigned long g_ProcessControl = vcversion::AdjustOffset(0x004E02E0);
static unsigned long g_PreRender = vcversion::AdjustOffset(0x004E0160);
static unsigned long g_Render = vcversion::AdjustOffset(0x004E0130);
static unsigned long g_SetupLighting = vcversion::AdjustOffset(0x004C9B20);
static unsigned long g_RemoveLighting = vcversion::AdjustOffset(0x004C9AF0);

__declspec(naked) void CCutsceneObject::SetModelIndex(unsigned int idx)
{
	__asm jmp g_SetModelIndex;
}

__declspec(naked) void CCutsceneObject::ProcessControl()
{
	__asm jmp g_ProcessControl;
}

__declspec(naked) void CCutsceneObject::PreRender()
{
	__asm jmp g_PreRender;
}

__declspec(naked) void CCutsceneObject::Render()
{
	__asm jmp g_Render;
}

__declspec(naked) bool CCutsceneObject::SetupLighting()
{
	__asm jmp g_SetupLighting;
}

__declspec(naked) void CCutsceneObject::RemoveLighting(bool reset)
{
	__asm jmp g_RemoveLighting;
}
