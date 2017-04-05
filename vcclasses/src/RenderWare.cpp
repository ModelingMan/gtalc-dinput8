#include "renderware.h"
#include "vcversion.h"

static unsigned long g_RsMouseSetPos = vcversion::AdjustOffset(0x006030C0);
static unsigned long g_RwMatrixDestroy = vcversion::AdjustOffset(0x006445F0);
static unsigned long g_RwRenderStateSet = vcversion::AdjustOffset(0x00649BA0);
static unsigned long g_RwTextureRead = vcversion::AdjustOffset(0x0064E110);
static unsigned long g_RwIm3DTransform = vcversion::AdjustOffset(0x0065AE90);
static unsigned long g_RwIm3DEnd = vcversion::AdjustOffset(0x0065AF60);
static unsigned long g_RwIm3DRenderIndexedPrimitive = vcversion::AdjustOffset(0x0065AF90);
static unsigned long g_RwIm3DRenderLine = vcversion::AdjustOffset(0x0065B0F0);

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

__declspec(naked) RxObjSpace3DVertex *RwIm3DTransform(RxObjSpace3DVertex *, unsigned int, void *, unsigned int)
{
	__asm jmp g_RwIm3DTransform;
}

__declspec(naked) int RwIm3DEnd(void)
{
	__asm jmp g_RwIm3DEnd;
}

__declspec(naked) int RwIm3DRenderIndexedPrimitive(int, unsigned short *, int)
{
	__asm jmp g_RwIm3DRenderIndexedPrimitive;
}

__declspec(naked) int RwIm3DRenderLine(int, int)
{
	__asm jmp g_RwIm3DRenderLine;
}
