#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RenderOneXLUSprite = vcversion::AdjustOffset(0x00576690);
static unsigned long g_RenderBufferedOneXLUSprite = vcversion::AdjustOffset(0x00577350);
static unsigned long g_InitSpriteBuffer = vcversion::AdjustOffset(0x00577770);
static unsigned long g_FlushSpriteBuffer = vcversion::AdjustOffset(0x00577790);
static unsigned long g_CalcScreenCoors = vcversion::AdjustOffset(0x005778B0);

__declspec(naked) void CSprite::RenderOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char)
{
	__asm jmp g_RenderOneXLUSprite;
}

__declspec(naked) void CSprite::RenderBufferedOneXLUSprite(float, float, float, float, float, unsigned char, unsigned char, unsigned char, short, float, unsigned char)
{
	__asm jmp g_RenderBufferedOneXLUSprite;
}

__declspec(naked) void CSprite::InitSpriteBuffer()
{
	__asm jmp g_InitSpriteBuffer;
}

__declspec(naked) void CSprite::FlushSpriteBuffer()
{
	__asm jmp g_FlushSpriteBuffer;
}

__declspec(naked) bool CSprite::CalcScreenCoors(const RwV3d &, RwV3d *, float *, float *, bool)
{
	__asm jmp g_CalcScreenCoors;
}
