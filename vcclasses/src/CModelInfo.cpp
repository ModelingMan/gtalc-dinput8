#include "vcclasses.h"
#include "vcversion.h"

unsigned long *CModelInfo::ms_modelInfoPtrs = reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x0092D4C8));

static unsigned long g_IsBikeModel = vcversion::AdjustOffset(0x0055F4E0);
static unsigned long g_IsCarModel = vcversion::AdjustOffset(0x0055F510);
static unsigned long g_IsBoatModel = vcversion::AdjustOffset(0x0055F540);
static unsigned long g_GetModelInfo = vcversion::AdjustOffset(0x0055F7D0);

__declspec(naked) bool CModelInfo::IsBikeModel(int)
{
	__asm jmp g_IsBikeModel;
}

__declspec(naked) bool CModelInfo::IsCarModel(int)
{
	__asm jmp g_IsCarModel;
}

__declspec(naked) bool CModelInfo::IsBoatModel(int)
{
	__asm jmp g_IsBoatModel;
}

__declspec(naked) unsigned long CModelInfo::GetModelInfo(char const *, int *)
{
	__asm jmp g_GetModelInfo;
}
