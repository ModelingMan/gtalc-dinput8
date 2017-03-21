#include "vcclasses.h"
#include "vcversion.h"

bool &CCutsceneMgr::ms_cutsceneProcessing = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B63));

static unsigned long g_Update = vcversion::AdjustOffset(0x00405FA0);

__declspec(naked) void CCutsceneMgr::Update(void)
{
	__asm jmp g_Update;
}
