#include "Globals.h"
#include "vcversion.h"

namespace VCGlobals
{
	CCamera &TheCamera = *reinterpret_cast<CCamera *>(vcversion::AdjustOffset(0x007E4688));
	CText &TheText = *reinterpret_cast<CText *>(vcversion::AdjustOffset(0x0094B220));
	cDMAudio &DMAudio = *reinterpret_cast<cDMAudio *>(vcversion::AdjustOffset(0x00A10B8A));
	cSampleManager &SampleManager = *reinterpret_cast<cSampleManager *>(vcversion::AdjustOffset(0x00983B90));
	cAudioManager &AudioManager = *reinterpret_cast<cAudioManager *>(vcversion::AdjustOffset(0x0078D718));
	CPhoneInfo &ThePhoneInfo = *reinterpret_cast<CPhoneInfo *>(vcversion::AdjustOffset(0x00817CF0));
	CMissionCleanup &TheMissionCleanup = *reinterpret_cast<CMissionCleanup *>(vcversion::AdjustOffset(0x0097F060));
	CPathFind &ThePaths = *reinterpret_cast<CPathFind *>(vcversion::AdjustOffset(0x009B6E5C));

	char *ScrollCharSet = reinterpret_cast<char *>(vcversion::AdjustOffset(0x00696674));

	unsigned short &MI_CARMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E8B0));
	unsigned short &MI_NAUTICALMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E910));
	unsigned short &MI_LITTLEHA_POLICE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9A0));
	unsigned short &MI_LIGHTBEAM = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9B4));
	unsigned int &resolutionX = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x009B48E4));
	unsigned int &resolutionY = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x009B48E8));
	float &resolutionXMultiplier = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x006CD9BC));
	float &resolutionYMultiplier = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x006CD9B4));

	ScriptParameter *ScriptParams = reinterpret_cast<ScriptParameter *>(vcversion::AdjustOffset(0x007D7438));

	RsGlobalType &Globals = *reinterpret_cast<RsGlobalType *>(vcversion::AdjustOffset(0x009B48D8));
	
	static unsigned long g_pFindPlayerPed = vcversion::AdjustOffset(0x004BC120);
	static unsigned long g_pFindPlayerVehicle = vcversion::AdjustOffset(0x004BC1E0);
	static unsigned long g_pFindPlayerCoors = vcversion::AdjustOffset(0x004BC240);
	static unsigned long g_strcpy = vcversion::AdjustOffset(0x00642560);
	static unsigned long g_strncpy = vcversion::AdjustOffset(0x00642580);
	static unsigned long g_rand = vcversion::AdjustOffset(0x006499F0);
	static unsigned long g_sscanf = vcversion::AdjustOffset(0x0064A730);

	__declspec(naked) CPlayerPed *FindPlayerPed(void)
	{
		__asm jmp g_pFindPlayerPed;
	}

	__declspec(naked) CVehicle *FindPlayerVehicle(void)
	{
		__asm jmp g_pFindPlayerVehicle;
	}

	__declspec(naked) CVector *FindPlayerCoors(CVector *)
	{
		__asm jmp g_pFindPlayerCoors;
	}

	__declspec(naked) char *strcpy(char *dest, const char *src)
	{
		__asm jmp g_strcpy;
	}

	__declspec(naked) char *strncpy(char *dest, const char *src, size_t n)
	{
		__asm jmp g_strncpy;
	}

	__declspec(naked) int rand(void)
	{
		__asm jmp g_rand;
	}

	__declspec(naked) int sscanf(const char *s, const char *format, ...)
	{
		__asm jmp g_sscanf;
	}
}
