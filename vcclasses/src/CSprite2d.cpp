#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CSprite2d_Constructor = vcversion::AdjustOffset(0x00578A60);
unsigned long g_CSprite2d_Destructor = vcversion::AdjustOffset(0x00578A40);

static unsigned long g_Constructor = vcversion::AdjustOffset(0x00578A60);
static unsigned long g_Destructor = vcversion::AdjustOffset(0x00578A40);
static unsigned long g_Draw = vcversion::AdjustOffset(0x005786A0);
static unsigned long g_Draw2 = vcversion::AdjustOffset(0x00578710);
static unsigned long g_DrawRect = vcversion::AdjustOffset(0x00577B00);
static unsigned long g_SetTexture = vcversion::AdjustOffset(0x005789B0);

/*__declspec(naked) CSprite2d::CSprite2d()
{
	__asm jmp g_Constructor;
}

__declspec(naked) CSprite2d::~CSprite2d()
{
	__asm jmp g_Destructor;
}*/

__declspec(naked) void CSprite2d::Draw(const CRect &, const CRGBA &, float, float, float, float, float, float, float, float)
{
	__asm jmp g_Draw;
}

__declspec(naked) void CSprite2d::Draw(const CRect &, const CRGBA &)
{
	__asm jmp g_Draw2;
}

__declspec(naked) void CSprite2d::DrawRect(const CRect &, const CRGBA &)
{
	__asm jmp g_DrawRect;
}

__declspec(naked) void CSprite2d::SetTexture(char *, char *)
{
	__asm jmp g_SetTexture;
}
