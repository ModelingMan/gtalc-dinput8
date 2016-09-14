#include "renderware.h"
#include "vcversion.h"

static unsigned long g_RsMouseSetPos = vcversion::AdjustOffset(0x006030C0);
static unsigned long g_RwRenderStateSet = vcversion::AdjustOffset(0x00649BA0);

__declspec(naked) void RsMouseSetPos(RwV2d *)
{
	__asm jmp g_RsMouseSetPos;
}

__declspec(naked) int RwRenderStateSet(int, int)
{
	__asm jmp g_RwRenderStateSet;
}
