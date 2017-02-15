#include "renderware.h"
#include "vcversion.h"

static unsigned long g_RsMouseSetPos = vcversion::AdjustOffset(0x006030C0);
static unsigned long g_RwMatrixDestroy = vcversion::AdjustOffset(0x006445F0);
static unsigned long g_RwRenderStateSet = vcversion::AdjustOffset(0x00649BA0);
static unsigned long g_RwTextureRead = vcversion::AdjustOffset(0x0064E110);

__declspec(naked) void RsMouseSetPos(RwV2d *)
{
	__asm jmp g_RsMouseSetPos;
}

__declspec(naked) bool RwMatrixDestroy(RwMatrix *)
{
	__asm jmp g_RwMatrixDestroy;
}

__declspec(naked) int RwRenderStateSet(int, int)
{
	__asm jmp g_RwRenderStateSet;
}

__declspec(naked) unsigned long RwTextureRead(const char *, const char *)
{
	__asm jmp g_RwTextureRead;
}
