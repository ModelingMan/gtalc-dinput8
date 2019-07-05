#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CPlane_Constructor = vcversion::AdjustOffset(0x005B2B50);
unsigned long g_CPlane_Destructor = vcversion::AdjustOffset(0x005B2B30);

static unsigned long g_LoadPath = vcversion::AdjustOffset(0x005B1FF0);
static unsigned long g_constructor = vcversion::AdjustOffset(0x005B2B50);

__declspec(naked) PathNode *CPlane::LoadPath(char const *, int &, float &, bool)
{
	__asm jmp g_LoadPath;
}

/*__declspec(naked) CPlane::CPlane(int, unsigned char)
{
	__asm jmp g_constructor;
}*/
