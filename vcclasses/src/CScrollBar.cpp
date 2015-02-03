#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_Init = vcversion::AdjustOffset(0x0054EB60);
static unsigned long g_Render = vcversion::AdjustOffset(0x0054E2B0);

__declspec(naked) void CScrollBar::Init(float xStart, float yStart, float zStart, float xEndOffset, float yEndOffset, float zEndOffset,
	unsigned char messages, unsigned char red, unsigned char green, unsigned char blue, float thickness)
{
	__asm jmp g_Init;
}

__declspec(naked) void CScrollBar::Render()
{
	__asm jmp g_Render;
}