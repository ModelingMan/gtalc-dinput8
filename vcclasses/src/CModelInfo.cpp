#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_IsBikeModel = vcversion::AdjustOffset(0x0055F4E0);
static unsigned long g_IsBoatModel = vcversion::AdjustOffset(0x0055F540);

__declspec(naked) bool CModelInfo::IsBikeModel(int)
{
	__asm jmp g_IsBikeModel;
}

__declspec(naked) bool CModelInfo::IsBoatModel(int)
{
	__asm jmp g_IsBoatModel;
}
