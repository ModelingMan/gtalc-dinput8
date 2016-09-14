#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_ConstructRenderList = vcversion::AdjustOffset(0x004CA260);

__declspec(naked) void CRenderer::ConstructRenderList(void)
{
	__asm jmp g_ConstructRenderList;
}
