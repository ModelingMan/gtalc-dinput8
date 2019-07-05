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
	char *String_DigitalClock = reinterpret_cast<char *>(vcversion::AdjustOffset(0x0069696C));

	unsigned short &MI_SINGLESTREETLIGHTS1 = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E820));
	unsigned short &MI_DOUBLESTREETLIGHTS = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E82C));
	unsigned short &MI_CARMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E8B0));
	unsigned short &MI_NAUTICALMINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E910));
	unsigned short &MI_PICKUP_ADRENALINE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E924));
	unsigned short &MI_PICKUP_BODYARMOUR = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E928));
	unsigned short &MI_PICKUP_INFO = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E92C));
	unsigned short &MI_PICKUP_HEALTH = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E930));
	unsigned short &MI_PICKUP_BONUS = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E934));
	unsigned short &MI_PICKUP_BRIBE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E938));
	unsigned short &MI_PICKUP_KILLFRENZY = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E93C));
	unsigned short &MI_PICKUP_CAMERA = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E940));
	unsigned short &MI_LITTLEHA_POLICE = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9A0));
	unsigned short &MI_LIGHTBEAM = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x0068E9B4));
	short *WeatherTypesList = reinterpret_cast<short *>(vcversion::AdjustOffset(0x00699EE4));
	RwTexture *&gpWhiteTexture = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x0077EF58));
	ScriptParameter *ScriptParams = reinterpret_cast<ScriptParameter *>(vcversion::AdjustOffset(0x007D7438));
	CProjectileInfo *gaProjectileInfo = reinterpret_cast<CProjectileInfo *>(vcversion::AdjustOffset(0x007DB888));
	wchar_t *gUString2 = reinterpret_cast<wchar_t *>(vcversion::AdjustOffset(0x007D9010));
	char *gString = reinterpret_cast<char *>(vcversion::AdjustOffset(0x007F8378));
	CPhoneInfo &gPhoneInfo = *reinterpret_cast<CPhoneInfo *>(vcversion::AdjustOffset(0x00817CF0));
	wchar_t *gUString = reinterpret_cast<wchar_t *>(vcversion::AdjustOffset(0x00821068));
	PathNode *&pPath4Nodes = *reinterpret_cast<PathNode **>(vcversion::AdjustOffset(0x0094DDAC));
	PathNode *&pPath3Nodes = *reinterpret_cast<PathNode **>(vcversion::AdjustOffset(0x00974B4C));
	PathNode *&pPath2Nodes = *reinterpret_cast<PathNode **>(vcversion::AdjustOffset(0x00974B78));
	CPlane *&pDropOffCesna = *reinterpret_cast<CPlane **>(vcversion::AdjustOffset(0x009751C0));
	RwTexture *&gpShadowHeliTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00975218));
	PathNode *&pPathNodes = *reinterpret_cast<PathNode **>(vcversion::AdjustOffset(0x00978750));
	RwTexture *&gpShadowExplosionTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00978DB4));
	int &NumPathNodes = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0097F220));
	RwTexture *&gpShadowCarTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x0097F2EC));
	RsGlobalType &RsGlobal = *reinterpret_cast<RsGlobalType *>(vcversion::AdjustOffset(0x009B48D8));
	RwTexture *&gpShadowPedTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x009B5F2C));
	CPlane *&pDrugRunCesna = *reinterpret_cast<CPlane **>(vcversion::AdjustOffset(0x009B5F7C));
	RwTexture *&gpBloodPoolTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00A0DAC8));
	RwTexture *&gpShadowHeadLightsTex = *reinterpret_cast<RwTexture **>(vcversion::AdjustOffset(0x00A1073C));
	bool &gbFastTime = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B87));

	static unsigned long g_GetLevelSplashScreen = vcversion::AdjustOffset(0x004A6D90);
	static unsigned long g_LoadSplash = vcversion::AdjustOffset(0x004A6E80);
	static unsigned long g_MatchModelString = vcversion::AdjustOffset(0x004A75DD);
	static unsigned long g_InitModelIndices = vcversion::AdjustOffset(0x004A8C64);
	static unsigned long g_VehicleCheat = vcversion::AdjustOffset(0x004AE8F0);
	static unsigned long g_FindPlayerHeading = vcversion::AdjustOffset(0x004BBF70);
	static unsigned long g_FindPlayerPed = vcversion::AdjustOffset(0x004BC120);
	static unsigned long g_FindPlayerVehicle = vcversion::AdjustOffset(0x004BC1E0);
	static unsigned long g_FindPlayerCoors = vcversion::AdjustOffset(0x004BC240);
	static unsigned long g_CrossProduct = vcversion::AdjustOffset(0x004E00B0);
	static unsigned long g_UnicodeStrCpy = vcversion::AdjustOffset(0x005524D0);
	static unsigned long g_DefinedState = vcversion::AdjustOffset(0x0057F9C0);
	static unsigned long g_strcpy = vcversion::AdjustOffset(0x00642560);
	static unsigned long g_strncpy = vcversion::AdjustOffset(0x00642580);
	static unsigned long g_strcat = vcversion::AdjustOffset(0x006425B0);
	static unsigned long g_strcmp = vcversion::AdjustOffset(0x00642620);
	static unsigned long g_strncmp = vcversion::AdjustOffset(0x00642650);
	static unsigned long g_sprintf = vcversion::AdjustOffset(0x00648C10);
	static unsigned long g_rand = vcversion::AdjustOffset(0x006499F0);
	static unsigned long g_sscanf = vcversion::AdjustOffset(0x0064A730);
	static unsigned long g_GetFrameNodeName = vcversion::AdjustOffset(0x00580600);
	static unsigned long g_GetFrameHierarchy = vcversion::AdjustOffset(0x0057F1E0);
	static unsigned long g_SetAtomicHierarchyCB = vcversion::AdjustOffset(0x00541510);
	static unsigned long g_GetAtomicSkinHierarchy = vcversion::AdjustOffset(0x0057F250);
	static unsigned long g_GetAnimHierarchyFromSkinClump = vcversion::AdjustOffset(0x0057F250);
	static unsigned long g_ConvertPedNode2BoneTag = vcversion::AdjustOffset(0x00405DE0);
	static unsigned long g_GetFirstAtomic = vcversion::AdjustOffset(0x0057F980);

	__declspec(naked) char *GetLevelSplashScreen(int)
	{
		__asm jmp g_GetLevelSplashScreen;
	}

	__declspec(naked) CSprite2d *LoadSplash(char const *)
	{
		__asm jmp g_LoadSplash;
	}

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

	__declspec(naked) CVector *CrossProduct(CVector *, CVector const &, CVector const &)
	{
		__asm jmp g_CrossProduct;
	}

	__declspec(naked) void UnicodeStrCpy(wchar_t *, wchar_t const *)
	{
		__asm jmp g_UnicodeStrCpy;
	}

	__declspec(naked) void DefinedState(void)
	{
		__asm jmp g_DefinedState;
	}

	__declspec(naked) char *strcpy(char *, const char *)
	{
		__asm jmp g_strcpy;
	}

	__declspec(naked) char *strncpy(char *, const char *, size_t)
	{
		__asm jmp g_strncpy;
	}

	__declspec(naked) char *strcat(char *, const char *)
	{
		__asm jmp g_strcat;
	}

	__declspec(naked) int strcmp(const char *, const char *)
	{
		__asm jmp g_strcmp;
	}

	__declspec(naked) int strncmp(const char *, const char *, size_t)
	{
		__asm jmp g_strncmp;
	}

	__declspec(naked) int sprintf(char *, const char *, ...)
	{
		__asm jmp g_sprintf;
	}

	__declspec(naked) int rand(void)
	{
		__asm jmp g_rand;
	}

	__declspec(naked) int sscanf(const char *, const char *, ...)
	{
		__asm jmp g_sscanf;
	}

	__declspec(naked) const char *GetFrameNodeName(void *)
	{
		__asm jmp g_GetFrameNodeName;
	}

	__declspec(naked) RpHAnimHierarchy *GetFrameHierarchy(RpClump *)
	{
		__asm jmp g_GetFrameHierarchy;
	}

	__declspec(naked) RpAtomic *SetAtomicHierarchyCB(RpAtomic *, void *)
	{
		__asm jmp g_SetAtomicHierarchyCB;
	}

	__declspec(naked) RpHAnimHierarchy *GetAnimHierarchyFromSkinClump(RpClump *)
	{
		__asm jmp g_GetAnimHierarchyFromSkinClump;
	}

	__declspec(naked) int ConvertPedNode2BoneTag(int)
	{
		__asm jmp g_ConvertPedNode2BoneTag;
	}

	__declspec(naked) RpAtomic *GetFirstAtomic(RpClump *clump)
	{
		__asm jmp g_GetFirstAtomic;
	}
}
