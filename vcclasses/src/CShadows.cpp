#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_StoreShadowToBeRendered = vcversion::AdjustOffset(0x0056E6C0);

__declspec(naked) void CShadows::StoreShadowToBeRendered(unsigned char, RwTexture *, CVector *, float, float, float, float, short, unsigned char, unsigned char, unsigned char, float, bool, float, unsigned long, bool)
{
	__asm jmp g_StoreShadowToBeRendered;
}
