#include "Globals.h"
#include "vcversion.h"

namespace VCGlobals
{
	CCamera &TheCamera = *reinterpret_cast<CCamera *>(vcversion::AdjustOffset(0x007E4688));
	CText &TheText = *reinterpret_cast<CText *>(vcversion::AdjustOffset(0x0094B220));
	cDMAudio &DMAudio = *reinterpret_cast<cDMAudio *>(vcversion::AdjustOffset(0x00A10B8A));
	cSampleManager &SampleManager = *reinterpret_cast<cSampleManager *>(vcversion::AdjustOffset(0x00983B90));
	cAudioManager &AudioManager = *reinterpret_cast<cAudioManager *>(vcversion::AdjustOffset(0x0078D718));
	CPathFind &ThePaths = *reinterpret_cast<CPathFind *>(vcversion::AdjustOffset(0x009B6E5C));

	char *ScrollCharSet = reinterpret_cast<char *>(vcversion::AdjustOffset(0x00696674));

	unsigned short &MI_DOUBLESTREETLIGHTS = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E82C));
	unsigned short &MI_CARMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E8B0));
	unsigned short &MI_NAUTICALMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E910));
	unsigned short &MI_LITTLEHA_POLICE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9A0));
	unsigned short &MI_LIGHTBEAM = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9B4));
	ScriptParameter *ScriptParams = reinterpret_cast<ScriptParameter *>(vcversion::AdjustOffset(0x007D7438));
	CPhoneInfo &gPhoneInfo = *reinterpret_cast<CPhoneInfo *>(vcversion::AdjustOffset(0x00817CF0));
	RwTexture *&gpShadowHeliTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00975218));
	RwTexture *&gpShadowExplosionTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00978DB4));
	RwTexture *&gpShadowCarTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x0097F2EC));
	RsGlobalType &RsGlobal = *reinterpret_cast<RsGlobalType *>(vcversion::AdjustOffset(0x009B48D8));
	RwTexture *&gpShadowPedTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x009B5F2C));
	RwTexture *&gpBloodPoolTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00A0DAC8));
	RwTexture *&gpShadowHeadLightsTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00A1073C));
	bool &gbFastTime = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B87));

	static unsigned long g_MatchModelString = vcversion::AdjustOffset(0x004A75DD);
	static unsigned long g_InitModelIndices = vcversion::AdjustOffset(0x004A8C64);
	static unsigned long g_VehicleCheat = vcversion::AdjustOffset(0x004AE8F0);
	static unsigned long g_FindPlayerHeading = vcversion::AdjustOffset(0x004BBF70);
	static unsigned long g_FindPlayerPed = vcversion::AdjustOffset(0x004BC120);
	static unsigned long g_FindPlayerVehicle = vcversion::AdjustOffset(0x004BC1E0);
	static unsigned long g_FindPlayerCoors = vcversion::AdjustOffset(0x004BC240);
	static unsigned long g_strcpy = vcversion::AdjustOffset(0x00642560);
	static unsigned long g_strncpy = vcversion::AdjustOffset(0x00642580);
	static unsigned long g_strcmp = vcversion::AdjustOffset(0x00642620);
	static unsigned long g_sprintf = vcversion::AdjustOffset(0x00648C10);
	static unsigned long g_rand = vcversion::AdjustOffset(0x006499F0);
	static unsigned long g_sscanf = vcversion::AdjustOffset(0x0064A730);

	__declspec(naked) void MatchModelString(char *, unsigned short)
	{
		__asm jmp g_MatchModelString;
	}

	__declspec(naked) void InitModelIndices(void)
	{
		__asm jmp g_InitModelIndices;
	}

	__declspec(naked) void VehicleCheat(int)
	{
		__asm jmp g_VehicleCheat;
	}

	__declspec(naked) float FindPlayerHeading(void)
	{
		__asm jmp g_FindPlayerHeading;
	}

	__declspec(naked) CPlayerPed *FindPlayerPed(void)
	{
		__asm jmp g_FindPlayerPed;
	}

	__declspec(naked) CVehicle *FindPlayerVehicle(void)
	{
		__asm jmp g_FindPlayerVehicle;
	}

	__declspec(naked) CVector *FindPlayerCoors(CVector *)
	{
		__asm jmp g_FindPlayerCoors;
	}

	__declspec(naked) char *strcpy(char *dest, const char *src)
	{
		__asm jmp g_strcpy;
	}

	__declspec(naked) char *strncpy(char *dest, const char *src, size_t n)
	{
		__asm jmp g_strncpy;
	}

	__declspec(naked) int strcmp(const char *s1, const char *s2)
	{
		__asm jmp g_strcmp;
	}

	__declspec(naked) int sprintf(char *s, const char *format, ...)
	{
		__asm jmp g_sprintf;
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
