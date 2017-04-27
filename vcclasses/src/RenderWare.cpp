#include "renderware.h"
#include "vcversion.h"

static unsigned long g_RsMouseSetPos = vcversion::AdjustOffset(0x006030C0);
static unsigned long g_RpClumpForAllAtomics = vcversion::AdjustOffset(0x00640D00);
static unsigned long g_RwMatrixDestroy = vcversion::AdjustOffset(0x006445F0);
static unsigned long g_RwRenderStateSet = vcversion::AdjustOffset(0x00649BA0);
static unsigned long g_RpGeometryForAllMaterials = vcversion::AdjustOffset(0x0064CC90);
static unsigned long g_RwTextureRead = vcversion::AdjustOffset(0x0064E110);
static unsigned long g_RpMaterialSetTexture = vcversion::AdjustOffset(0x00655890);
static unsigned long g_RpMatFXAtomicEnableEffects = vcversion::AdjustOffset(0x00657020);
static unsigned long g_RpMatFXMaterialSetEffects = vcversion::AdjustOffset(0x00657050);
static unsigned long g_RpMatFXMaterialSetupEnvMap = vcversion::AdjustOffset(0x00657180);
static unsigned long g_RpMatFXMaterialGetEffects = vcversion::AdjustOffset(0x006572F0);
static unsigned long g_RwIm3DTransform = vcversion::AdjustOffset(0x0065AE90);
static unsigned long g_RwIm3DEnd = vcversion::AdjustOffset(0x0065AF60);
static unsigned long g_RwIm3DRenderIndexedPrimitive = vcversion::AdjustOffset(0x0065AF90);
static unsigned long g_RwIm3DRenderLine = vcversion::AdjustOffset(0x0065B0F0);

__declspec(naked) void RsMouseSetPos(RwV2d *)
{
	__asm jmp g_RsMouseSetPos;
}

__declspec(naked) unsigned long RpClumpForAllAtomics(unsigned long, unsigned long(*)(unsigned long, void *), void *)
{
	__asm jmp g_RpClumpForAllAtomics;
}

__declspec(naked) bool RwMatrixDestroy(RwMatrix *)
{
	__asm jmp g_RwMatrixDestroy;
}

__declspec(naked) int RwRenderStateSet(int, int)
{
	__asm jmp g_RwRenderStateSet;
}

__declspec(naked) unsigned long RpGeometryForAllMaterials(unsigned long, unsigned long(*)(unsigned long, void *), void *)
{
	__asm jmp g_RpGeometryForAllMaterials;
}

__declspec(naked) RwTexture *RwTextureRead(const char *, const char *)
{
	__asm jmp g_RwTextureRead;
}

__declspec(naked) unsigned long RpMaterialSetTexture(unsigned long, RwTexture *)
{
	__asm jmp g_RpMaterialSetTexture;
}

__declspec(naked) unsigned long RpMatFXAtomicEnableEffects(unsigned long)
{
	__asm jmp g_RpMatFXAtomicEnableEffects;
}

__declspec(naked) unsigned long RpMatFXMaterialSetEffects(unsigned long, unsigned long)
{
	__asm jmp g_RpMatFXMaterialSetEffects;
}

__declspec(naked) unsigned long RpMatFXMaterialSetupEnvMap(unsigned long, RwTexture *, unsigned long, int, float)
{
	__asm jmp g_RpMatFXMaterialSetupEnvMap;
}

__declspec(naked) unsigned long RpMatFXMaterialGetEffects(unsigned long)
{
	__asm jmp g_RpMatFXMaterialGetEffects;
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
