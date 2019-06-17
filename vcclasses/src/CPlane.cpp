#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_LoadPath = vcversion::AdjustOffset(0x005B1FF0);
static unsigned long g_constructor = vcversion::AdjustOffset(0x005B2B50);

__declspec(naked) PathNode *CPlane::LoadPath(char const *, int &, float &, bool)
{
	__asm jmp g_LoadPath;
}

__declspec(naked) CPlane::CPlane(int, unsigned char)
{
	__asm jmp g_constructor;
}
