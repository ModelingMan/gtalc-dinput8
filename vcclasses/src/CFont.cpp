#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_DrawFonts = vcversion::AdjustOffset(0x00550250);
static unsigned long g_GetNumberOfLines = vcversion::AdjustOffset(0x00550C70);
static unsigned long g_GetTextRect = vcversion::AdjustOffset(0x00550720);
static unsigned long g_Initialise = vcversion::AdjustOffset(0x00552310);
static unsigned long g_PrintString = vcversion::AdjustOffset(0x00551040);
static unsigned long g_SetAlphaFade = vcversion::AdjustOffset(0x0054FFC0);
static unsigned long g_SetBackGroundOnlyTextOff = vcversion::AdjustOffset(0x00550080);
static unsigned long g_SetBackGroundOnlyTextOn = vcversion::AdjustOffset(0x00550090);
static unsigned long g_SetBackgroundColor = vcversion::AdjustOffset(0x005500A0);
static unsigned long g_SetBackgroundOff = vcversion::AdjustOffset(0x005500D0);
static unsigned long g_SetBackgroundOn = vcversion::AdjustOffset(0x005500E0);
static unsigned long g_SetCentreOff = vcversion::AdjustOffset(0x00550110);
static unsigned long g_SetCentreOn = vcversion::AdjustOffset(0x00550120);
static unsigned long g_SetCentreSize = vcversion::AdjustOffset(0x005500F0);
static unsigned long g_SetColor = vcversion::AdjustOffset(0x00550170);
static unsigned long g_SetDropColor = vcversion::AdjustOffset(0x0054FF30);
static unsigned long g_SetDropShadowPosition = vcversion::AdjustOffset(0x0054FF20);
static unsigned long g_SetFontStyle = vcversion::AdjustOffset(0x0054FFE0);
static unsigned long g_SetJustifyOff = vcversion::AdjustOffset(0x00550140);
static unsigned long g_SetJustifyOn = vcversion::AdjustOffset(0x00550150);
static unsigned long g_SetPropOff = vcversion::AdjustOffset(0x00550030);
static unsigned long g_SetPropOn = vcversion::AdjustOffset(0x00550020);
static unsigned long g_SetRightJustifyOff = vcversion::AdjustOffset(0x00550040);
static unsigned long g_SetRightJustifyOn = vcversion::AdjustOffset(0x00550060);
static unsigned long g_SetRightJustifyWrap = vcversion::AdjustOffset(0x0054FFD0);
static unsigned long g_SetScale = vcversion::AdjustOffset(0x00550230);
static unsigned long g_SetWrapx = vcversion::AdjustOffset(0x00550100);

__declspec(naked) void CFont::DrawFonts()
{
	__asm jmp g_DrawFonts;
}

__declspec(naked) void CFont::GetNumberOfLines(float x, float y, wchar_t *text)
{
	__asm jmp g_GetNumberOfLines;
}

__declspec(naked) void CFont::GetTextRect(CRect *rectOut, float x, float y, wchar_t *text)
{
	__asm jmp g_GetTextRect;
}

__declspec(naked) void CFont::Initialise()
{
	__asm jmp g_Initialise;
}

__declspec(naked) void CFont::PrintString(float x, float y, wchar_t *text)
{
	__asm jmp g_PrintString;
}

__declspec(naked) void CFont::SetAlphaFade(float alpha)
{
	__asm jmp g_SetAlphaFade;
}

__declspec(naked) void CFont::SetBackGroundOnlyTextOff()
{
	__asm jmp g_SetBackGroundOnlyTextOff;
}

__declspec(naked) void CFont::SetBackGroundOnlyTextOn()
{
	__asm jmp g_SetBackGroundOnlyTextOn;
}

__declspec(naked) void CFont::SetBackgroundColor(CRGBA *color)
{
	__asm jmp g_SetBackgroundColor;
}

__declspec(naked) void CFont::SetBackgroundOff()
{
	__asm jmp g_SetBackgroundOff;
}

__declspec(naked) void CFont::SetBackgroundOn()
{
	__asm jmp g_SetBackgroundOn;
}

__declspec(naked) void CFont::SetCentreOff()
{
	__asm jmp g_SetCentreOff;
}

__declspec(naked) void CFont::SetCentreOn()
{
	__asm jmp g_SetCentreOn;
}

__declspec(naked) void CFont::SetCentreSize(float size)
{
	__asm jmp g_SetCentreSize;
}

__declspec(naked) void CFont::SetColor(CRGBA *color)
{
	__asm jmp g_SetColor;
}

__declspec(naked) void CFont::SetDropColor(CRGBA *color)
{
	__asm jmp g_SetDropColor;
}

__declspec(naked) void CFont::SetDropShadowPosition(short pos)
{
	__asm jmp g_SetDropShadowPosition;
}

__declspec(naked) void CFont::SetFontStyle(short style)
{
	__asm jmp g_SetFontStyle;
}

__declspec(naked) void CFont::SetJustifyOff()
{
	__asm jmp g_SetJustifyOff;
}

__declspec(naked) void CFont::SetJustifyOn()
{
	__asm jmp g_SetJustifyOn;
}

__declspec(naked) void CFont::SetPropOff()
{
	__asm jmp g_SetPropOff;
}

__declspec(naked) void CFont::SetPropOn()
{
	__asm jmp g_SetPropOn;
}

__declspec(naked) void CFont::SetRightJustifyOff()
{
	__asm jmp g_SetRightJustifyOff;
}

__declspec(naked) void CFont::SetRightJustifyOn()
{
	__asm jmp g_SetRightJustifyOn;
}

__declspec(naked) void CFont::SetRightJustifyWrap(float wrap)
{
	__asm jmp g_SetRightJustifyWrap;
}

__declspec(naked) void CFont::SetScale(float x, float y)
{
	__asm jmp g_SetScale;
}

__declspec(naked) void CFont::SetWrapx(float wrapx)
{
	__asm jmp g_SetWrapx;
}