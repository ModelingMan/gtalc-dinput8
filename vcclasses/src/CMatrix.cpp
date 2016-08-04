#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetRotate = vcversion::AdjustOffset(0x004DF240);
static unsigned long g_SetRotateZOnly = vcversion::AdjustOffset(0x004DF590);
static unsigned long g_UpdateRW = vcversion::AdjustOffset(0x004DF8F0);

__declspec(naked) void CMatrix::SetRotate(float, float, float)
{
	__asm jmp g_SetRotate;
}

__declspec(naked) void CMatrix::SetRotateZOnly(float)
{
	__asm jmp g_SetRotateZOnly;
}

__declspec(naked) void CMatrix::UpdateRW(void)
{
	__asm jmp g_UpdateRW;
}
