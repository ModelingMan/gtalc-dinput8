#include <Windows.h>
#include <tchar.h>
#include <time.h>

#include "CBridgeHack.h"
#include "CCameraHack.h"
#include "CCarCtrlHack.h"
#include "CCranesHack.h"
#include "CFileLoaderHack.h"
#include "CFontHack.h"
#include "CGameLogicHack.h"
#include "CGaragesHack.h"
#include "CMenuManagerHack.h"
#include "CMessagesHack.h"
#include "CMovingThingsHack.h"
#include "CObjectHack.h"
#include "CPacManPickupsHack.h"
#include "CPadHack.h"
#include "CPagerHack.h"
#include "CPathFindHack.h"
#include "CPedHack.h"
#include "CPickupsHack.h"
#include "CProjectileInfoHack.h"
#include "CRadarHack.h"
#include "CRecordDataForChaseHack.h"
#include "CRendererHack.h"
#include "CRunningScriptHack.h"
#include "CShinyTextsHack.h"
#include "CStatsHack.h"
#include "CTheZonesHack.h"
#include "CVehicleHack.h"
#include "CWantedHack.h"
#include "CWaterLevelHack.h"
#include "CWeaponEffectsHack.h"
#include "CWeaponHack.h"
#include "Globals.h"
#include "ModelIndices.h"
#include "Offset.h"
#include "SilentCall.h"
#include "WeaponTypes.h"
#include "cAudioManagerHack.h"
#include "vcversion.h"

HMODULE hOrigDLL = NULL;

FARPROC OldDirectInput8Create = NULL;
FARPROC OldDllCanUnloadNow = NULL;
FARPROC OldDllGetClassObject = NULL;
FARPROC OldDllRegisterServer = NULL;
FARPROC OldDllUnregisterServer = NULL;

static const char *windowName = "GTA: Liberty City";

// GangsInitialise
static void GangsInitialise();
static unsigned long gangInitialiseEndJump = vcversion::AdjustOffset(0x004EEEDF);

// RenderReflections
static float RenderReflections();

// CivilianAI
static void CivilianAI();
static unsigned long civilianAIValidPed = vcversion::AdjustOffset(0x004E94E6);
static unsigned long civilianAIInvalidPed = vcversion::AdjustOffset(0x004E9555);

// PedCommentsProcess
static void PedCommentsProcess();
static unsigned long sfxNoMatch = vcversion::AdjustOffset(0x005DDB73);
static unsigned long sfxMatch = vcversion::AdjustOffset(0x005DDBAC);

// support treadables
static void TreadablesHack(int, const char *);
static unsigned long treadablesCall = vcversion::AdjustOffset(0x004C0DD0);
static unsigned int numberOfTreadables;

// RepositionOneObject
static void RepositionOneObjectHack(CEntity *);

// dodo wheels
static void DodoWheels1();
static unsigned long dodoWheels1EndJump = vcversion::AdjustOffset(0x0059F000);
static void DodoWheels2();
static unsigned long dodoWheels2EndJump = vcversion::AdjustOffset(0x0061FBEF);

// dodo shadow
static void DodoShadow();
static float dodoShadowX = 0.4f;
static float dodoShadowY = 0.9f;
static unsigned long dodoShadowJumpEnd = vcversion::AdjustOffset(0x0056E346);

// dodo anims
static void DodoAnims();
static unsigned long dodoAnimsEndJump = vcversion::AdjustOffset(0x00590260);

static unsigned char splashIndex[] = { 25, 22, 4, 13, 1, 21, 14, 16, 10, 12, 5, 9, 11, 18, 3, 2, 19, 23, 7, 17, 15, 6, 8, 20 };

// center mouse (SilentPatch)
static bool bGameInFocus = true;
static LRESULT(CALLBACK **OldWndProc)(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KILLFOCUS:
		bGameInFocus = false;
		break;
	case WM_SETFOCUS:
		bGameInFocus = true;
		break;
	}

	return (*OldWndProc)(hwnd, uMsg, wParam, lParam);
}
static auto* pCustomWndProc = CustomWndProc;
void ResetMousePos()
{
	if (bGameInFocus) {
		RwV2d vecPos = { VCGlobals::RsGlobal.currentWidth * 0.5f, VCGlobals::RsGlobal.currentHeight * 0.5f };
		RsMouseSetPos(&vecPos);
	}
	CRenderer::ConstructRenderList();
}

bool SetupDirectInputProxy()
{
	TCHAR szPath[MAX_PATH];
	GetSystemDirectory(szPath, MAX_PATH);
	_tcscat_s(szPath, TEXT("\\dinput8.dll"));
	hOrigDLL = LoadLibrary(szPath);

	if (hOrigDLL != NULL) {
		OldDirectInput8Create = GetProcAddress(hOrigDLL, "DirectInput8Create");
		OldDllCanUnloadNow = GetProcAddress(hOrigDLL, "DllCanUnloadNow");
		OldDllGetClassObject = GetProcAddress(hOrigDLL, "DllGetClassObject");
		OldDllRegisterServer = GetProcAddress(hOrigDLL, "DllRegisterServer");
		OldDllUnregisterServer = GetProcAddress(hOrigDLL, "DllUnregisterServer");
	}

	return OldDirectInput8Create != NULL && OldDllCanUnloadNow != NULL && OldDllGetClassObject != NULL && OldDllRegisterServer != NULL && OldDllUnregisterServer != NULL;
}

_declspec(naked) HRESULT WINAPI NewDirectInput8Create(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN)
{
	__asm jmp OldDirectInput8Create;
}

__declspec(naked) HRESULT WINAPI NewDllCanUnloadNow()
{
	__asm jmp OldDllCanUnloadNow;
}

__declspec(naked) HRESULT WINAPI NewDllGetClassObject(const CLSID *const, const IID *const, LPVOID *)
{
	__asm jmp OldDllGetClassObject;
}

__declspec(naked) HRESULT WINAPI NewDllRegisterServer()
{
	__asm jmp OldDllRegisterServer;
}

__declspec(naked) HRESULT WINAPI NewDllUnregisterServer()
{
	__asm jmp OldDllUnregisterServer;
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		srand((unsigned)time(NULL));

		if (!SetupDirectInputProxy()) {
			MessageBox(NULL, TEXT("Failed to load dinput8.dll"), TEXT("Error!"), MB_OK);
			return FALSE;
		}

		DWORD OldProtect;
		PIMAGE_DOS_HEADER dosheader;
		PIMAGE_NT_HEADERS ntheader;
		PIMAGE_FILE_HEADER fileheader;
		PIMAGE_SECTION_HEADER sectionheader;
		WORD numSections;

		dosheader = reinterpret_cast<PIMAGE_DOS_HEADER>(0x400000);
		ntheader = (PIMAGE_NT_HEADERS)((BYTE*)dosheader + dosheader->e_lfanew);
		fileheader = (PIMAGE_FILE_HEADER)&ntheader->FileHeader;
		sectionheader = (PIMAGE_SECTION_HEADER)((BYTE*)ntheader + sizeof(IMAGE_NT_HEADERS));

		// write protection of .text section removed at startup
		numSections = fileheader->NumberOfSections;
		for (; numSections-- > 0; sectionheader++) {
			if (strcmp((const char *)sectionheader->Name, ".text") == 0)
				break;
		}

		if (!VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, PAGE_EXECUTE_READWRITE, &OldProtect)) {
			MessageBox(NULL, TEXT("Unable to set VC's code to writable memory"), TEXT("Error!"), MB_OK);
			return FALSE;
		}

		// A/B drive fix (SilentPatch)
		Patch<unsigned int>(0x005D7940 + 1, 'A');
		Patch<unsigned int>(0x005D7B00 + 4, 'A');

		// disable DirectPlay dependency (SilentPatch)
		Patch<unsigned char>(0x00601CA0, 0xB8);
		Patch<unsigned int>(0x00601CA0 + 1, 0x900);

		// disable video memory check (SilentPatch)
		Patch<unsigned char>(0x00601E26, 0xEB);

		// window name
		Patch<const char *>(0x00602D30 + 6, windowName);

		// debug modes
		{
			const char *debugKeys[11] =
			{
				"MasterDebug",
				"MasterExtras1",
				"MasterExtras2",
				"MasterPackagesCompleted",
				"MasterParamedicCompleted",
				"MasterVigilanteCompleted",
				"MasterFirefighterCompleted",
				"MasterIEGaragesCompleted",
				"Master100Completed",
				"SkipHelp",
				"ViceCity"
			};

			for (int i = 0; i < 11; i++) {
				if (GetPrivateProfileInt("Debug", debugKeys[i], 0, "./gta-lc.ini")) {
					CRunningScriptHack::debugMode |= (1 << i);
				}
			}
		}

		// detonator weapon switch
		Patch<unsigned char>(0x005D49C7, 0xD); // CWeapon::Update
		Nop(0x005345ED, 9); // CPlayerPed::ProcessWeaponSwitch

		// 0410 (Purple Nines) fix
		InjectHook(0x004EEED1, &GangsInitialise, PATCH_JUMP); // CGangs::Initialise

		// cylindrical marker colors
		Patch<unsigned int>(0x00458E82, 0x000080); // CTheScripts::DrawScriptSpheres
		Patch<unsigned int>(0x00689CA8, 0xFF8000);
		Patch<unsigned int>(0x00568E45, 0x000080); // CShadows::RenderIndicatorShadow
		Patch<unsigned int>(0x00698D58, 0xFF8000);
		Patch<unsigned int>(0x004C3F99, 0x000080); // CRadar::Draw3dMarkers
		Patch<unsigned int>(0x0068F958, 0xFF8000);

		// remove arrow marker glow
		if (!GetPrivateProfileInt("Misc", "ShowArrowMarkerGlow", 1, "./gta-lc.ini")) {
			Patch<unsigned int>(0x00570C30, 0); // C3dMarkers::Render
			Patch<unsigned int>(0x00699074, 0);
		}

		// remove dead ped in front of car
		if (!GetPrivateProfileInt("Misc", "AllowDeadPedInFrontOfCar", 1, "./gta-lc.ini")) {
			Patch<float>(0x00687238, 1.0);
		}

		// undo ocean change
		Patch<float>(0x0069CD70, 70.0);

		// fire light glow (SilentPatch)
		Patch<unsigned char>(0x0048EB27, 0x10); // CFire::ProcessFire

		// wet roads reflection (SilentPatch)
		InjectHook(0x005433BD, &RenderReflections); // CCoronas::RenderReflections

		// support treadables
		numberOfTreadables = GetPrivateProfileInt("Misc", "Treadables", 8000, "./gta-lc.ini");
		InjectHook(0x004C032C, &TreadablesHack); // CPools::Initialise

		// investigate ped crash fix
		InjectHook(0x004E94E0, &CivilianAI, PATCH_JUMP); // CCivilianPed::CivilianAI

		// script paths allow replay
		Nop(0x00624EDB, 9); // CReplay::Update

		// prioritize specific ped sfx
		InjectHook(0x005DDB6C, &PedCommentsProcess, PATCH_JUMP); // cPedComments::Process

		// reposition streetlights
		InjectHook(0x004D4889, &RepositionOneObjectHack); // CWorld::RepositionCertainDynamicObjects

		// allow grouped security guards
		Patch<unsigned char>(0x0053BFD0, 0);

		// reposition buoy
		Patch<float>(0x006912D8, OFFSETZ);

		// additional model matches
		InjectHook(0x004A4C75, &ModelIndices::InitModelIndicesHack);
		InjectHook(0x0048C511, &ModelIndices::MatchModelStringHack);
		InjectHook(0x0048C6E3, &ModelIndices::MatchModelStringHack);
		InjectHook(0x0048CA7B, &ModelIndices::MatchModelStringHack);

		// lod fix (HM128)
		Patch<float>(0x0056F516, 100.0);

		// leaf scaling
		Patch<float>(0x00698CD8, 0.3f);

		// random loading screen (Silent), requires ids 0-25 to exist
		if (GetPrivateProfileInt("Misc", "RandomLoadScreen", 0, "./gta-lc.ini")) {
			Patch<unsigned char>(0x004A69D4, 0x90);
			Patch<unsigned int>(0x004A69D4 + 1, 0x782474FF); // push [esp+78h]
			Patch<unsigned char>(0x004A6DF7, 4);
			Patch<void *>(0x004A6E09, &splashIndex);
			Nop(0x004A5C49, 5);
		}

		if (!GetPrivateProfileInt("Misc", "UseRCBaron", 0, "./gta-lc.ini")) {
			// dodo wheels
			InjectHook(0x0059EFF8, &DodoWheels1, PATCH_JUMP);
			InjectHook(0x0061FBE9, &DodoWheels2, PATCH_JUMP);
			// dodo shadow
			InjectHook(0x0056E31C, &DodoShadow, PATCH_JUMP);
			// dodo anims
			InjectHook(0x00590258, &DodoAnims, PATCH_JUMP);
		}

		// remove security guard behavior
		Patch<unsigned char>(0x0050BF78, 0xEB);

		// remove vercetti gang behavior
		Patch<unsigned char>(0x005143B7, 0xEB);
		Patch<unsigned char>(0x0051BDEE, 0xEB);
		Patch<unsigned char>(0x0051C278, 0xEB);
		Patch<unsigned char>(0x00525BC5, 0xEB);

		// ak47 changes
		Nop(0x005349DD, 5);
		Nop(0x0055762E, 5);
		Patch<unsigned char>(0x004ED820, WEAPONTYPE_CHAINGUN);
		Patch<unsigned char>(0x004ED827, WEAPONTYPE_CHAINGUN);

		// center mouse (SilentPatch)
		InjectHook(0x004A5E45, &ResetMousePos);
		OldWndProc = *(LRESULT(CALLBACK***)(HWND, UINT, WPARAM, LPARAM))vcversion::AdjustOffset(0x00601727);
		Patch(0x00601727, &pCustomWndProc);

		if (!CBridgeHack::initialise() ||
			!CCameraHack::initialise() ||
			!CCarCtrlHack::initialise() ||
			!CCranesHack::initialise() ||
			!CFileLoaderHack::initialise() ||
			!CFontHack::initialise() ||
			!CGameLogicHack::initialise() ||
			!CGaragesHack::initialise() ||
			!CMenuManagerHack::initialise() ||
			!CMessagesHack::initialise() ||
			!CMovingThingsHack::initialise() ||
			!CObjectHack::initialise() ||
			!CPacManPickupsHack::initialise() ||
			!CPadHack::initialise() ||
			!CPagerHack::initialise() ||
			!CPathFindHack::initialise() ||
			!CPedHack::initialise() ||
			!CPickupsHack::initialise() ||
			!CProjectileInfoHack::initialise() ||
			!CRadarHack::initialise() ||
			!CRecordDataForChaseHack::initialise() ||
			!CRendererHack::initialise() ||
			!CRunningScriptHack::initialise() ||
			!CShinyTextsHack::initialise() ||
			!CStatsHack::initialise() ||
			!CTheZonesHack::initialise() ||
			!CVehicleHack::initialise() ||
			!CWantedHack::initialise() ||
			!CWaterLevelHack::initialise() ||
			!CWeaponEffectsHack::initialise() ||
			!CWeaponHack::initialise() ||
			!cAudioManagerHack::initialise()) {
			VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, OldProtect, &OldProtect);
			return FALSE;
		}

		VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, OldProtect, &OldProtect);
		break;

	case DLL_PROCESS_DETACH:
		if (hOrigDLL != NULL) {
			OldDirectInput8Create = NULL;
			OldDllCanUnloadNow = NULL;
			OldDllGetClassObject = NULL;
			OldDllRegisterServer = NULL;
			OldDllUnregisterServer = NULL;
			FreeLibrary(hOrigDLL);
			hOrigDLL = NULL;
		}
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}

void GangsInitialise()
{
	for (int i = 0; i < 9; i++) {
		CGangs::Gang[i].pedModelPreference = -1;
	}
}

float RenderReflections()
{
	return 1.0;
}

void __declspec(naked) CivilianAI()
{
	__asm
	{
		mov edx, dword ptr [ebp+1A0h] // get ped to investigate
		test edx, edx
		jz invalidPed
		jmp civilianAIValidPed
	invalidPed:
		jmp civilianAIInvalidPed
	}
}

void __declspec(naked) PedCommentsProcess()
{
	__asm
	{
		mov eax, [esi+edi] // get sfx id
		mov [esp+8], eax

		// chunky
		sub eax, 723
		cmp eax, 5
		jbe match
		add eax, 723

		// bomber
		sub eax, 861
		cmp eax, 7
		jbe match
		add eax, 861

		// s_guard
		sub eax, 2668
		cmp eax, 12
		jbe match
		add eax, 2668

		// sam
		sub eax, 3029
		cmp eax, 3
		jbe match
		add eax, 3029

		jmp sfxNoMatch
	match:
		jmp sfxMatch
	}
}

void __declspec(naked) TreadablesHack(int, const char *)
{
	__asm
	{
		// ecx must be preserved
		push 0                  // push second argument
		push numberOfTreadables // push first argument
		call treadablesCall     // call treadables function
		// eax must be preserved
		ret 8
	}
}

void RepositionOneObjectHack(CEntity *entity)
{
	if (entity->modelIndex == VCGlobals::MI_SINGLESTREETLIGHTS1 ||
		entity->modelIndex == VCGlobals::MI_DOUBLESTREETLIGHTS) {
		float updateZ = CWorld::FindGroundZFor3DCoord(entity->GetX(), entity->GetY(), entity->GetZ() + 2.0f, 0);
		unsigned long collisionModel = *reinterpret_cast<unsigned long *>(CModelInfo::ms_modelInfoPtrs[entity->modelIndex] + 0x1C);
		updateZ -= *reinterpret_cast<float *>(collisionModel + 0x18);
		entity->GetZ() = updateZ;
		entity->GetMatrix().UpdateRW();
		entity->UpdateRwFrame();
		return;
	}
	CWorld::RepositionOneObject(entity);
}

void __declspec(naked) DodoWheels1()
{
	__asm
	{
		mov bp, [eax+5Ch] // get model index
		cmp bp, CAR_DODO  // test for dodo
		jmp dodoWheels1EndJump
	}
}

void __declspec(naked) DodoWheels2()
{
	__asm
	{
		mov edi, ebp
		cmp ax, CAR_DODO // test for dodo
		jmp dodoWheels2EndJump
	}
}

void __declspec(naked) DodoShadow()
{
	__asm
	{
		fld dword ptr [esp+8]
		fmul dodoShadowY
		mov ebp, VCGlobals::gpShadowCarTex
		mov ebp, [ebp]
		fstp dword ptr [esp+8]
		fld dword ptr [esp+0Ch]
		fmul dodoShadowX
		fstp dword ptr [esp+0Ch]
		jmp dodoShadowJumpEnd
	}
}

void __declspec(naked) DodoAnims()
{
	__asm
	{
		mov ax, [ebp+5Ch] // get model index
		cmp ax, CAR_DODO  // test for dodo
		jmp dodoAnimsEndJump
	}
}
