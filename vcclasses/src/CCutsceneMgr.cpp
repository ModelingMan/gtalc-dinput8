#include "vcclasses.h"
#include "vcversion.h"

bool &CCutsceneMgr::ms_cutsceneProcessing = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B63));
float& CCutsceneMgr::ms_cutsceneTimer = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009753A8));
CDirectory *&CCutsceneMgr::ms_pCutsceneDir = *reinterpret_cast<CDirectory **>(vcversion::AdjustOffset(0x009B5F88));
char *CCutsceneMgr::ms_cutsceneName = reinterpret_cast<char *>(vcversion::AdjustOffset(0x007EFE08)); // Length is 8
CCutsceneObject **CCutsceneMgr::ms_pCutsceneObjects = reinterpret_cast<CCutsceneObject **>(vcversion::AdjustOffset(0x00938288));
unsigned int &CCutsceneMgr::ms_numCutsceneObjs = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00A0FC74));

static unsigned long g_Update = vcversion::AdjustOffset(0x00405FA0);

__declspec(naked) void CCutsceneMgr::Update(void)
{
	__asm jmp g_Update;
}
