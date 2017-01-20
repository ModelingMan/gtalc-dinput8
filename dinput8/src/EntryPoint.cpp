#include <Windows.h>
#include <tchar.h>
#include <time.h>

#include "cAudioManagerHack.h"
#include "CFontHack.h"
//#include "CHudHack.h"
#include "CMovingThingsHack.h"
#include "CPagerHack.h"
#include "CRunningScriptHack.h"
#include "CRendererHack.h"
#include "CCranesHack.h"
#include "CPickupsHack.h"
#include "CPadHack.h"
#include "CGaragesHack.h"
#include "CWantedHack.h"
#include "CPacManPickupsHack.h"
#include "CProjectileInfoHack.h"
#include "CCameraHack.h"
#include "CFileLoaderHack.h"
#include "CPathFindHack.h"
#include "CBridgeHack.h"
#include "CStatsHack.h"
#include "CWeaponEffectsHack.h"
#include "CObjectHack.h"
#include "CRadarHack.h"
#include "CPedHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"

HMODULE hOrigDLL = NULL;

FARPROC OldDirectInput8Create = NULL;
FARPROC OldDllCanUnloadNow = NULL;
FARPROC OldDllGetClassObject = NULL;
FARPROC OldDllRegisterServer = NULL;
FARPROC OldDllUnregisterServer = NULL;

const char *windowName = "GTA: Liberty City";

// GangsInitialise
static void GangsInitialise();
unsigned long gangInitialiseEndJump = vcversion::AdjustOffset(0x004EEEDF);

// GameLogicUpdate
static void GameLogicUpdate();
unsigned long gameLogicUpdateEndJump = vcversion::AdjustOffset(0x0042BC6D);

// AutomobilePreRender
static void AutomobilePreRender();
unsigned long preRenderMatchAmbulan = vcversion::AdjustOffset(0x0058BE77);
unsigned long preRenderMatchFbiranch = vcversion::AdjustOffset(0x0058C8F0);
unsigned long preRenderNoMatch = vcversion::AdjustOffset(0x0058BE34);

// RenderReflections
float RenderReflections();

// CarCtrlReInit
void CarCtrlReInit();

// CivilianAI
void CivilianAI();
unsigned long civilianAIValidPed = vcversion::AdjustOffset(0x004E94E6);
unsigned long civilianAIInvalidPed = vcversion::AdjustOffset(0x004E9555);

// PedCommentsProcess
static void PedCommentsProcess();
unsigned long sfxNoMatch = vcversion::AdjustOffset(0x005DDB73);
unsigned long sfxMatch = vcversion::AdjustOffset(0x005DDBAC);

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

	if (hOrigDLL != NULL)
	{
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
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		srand((unsigned)time(NULL));

		if (!SetupDirectInputProxy())
		{
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

		numSections = fileheader->NumberOfSections;
		for (; numSections-- > 0; sectionheader++)
		{
			if (strcmp((const char *)sectionheader->Name, ".text") == 0)
				break;
		}

		if (!VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			MessageBox(NULL, TEXT("Unable to set VC's code to writable memory"), TEXT("Error!"), MB_OK);
			return FALSE;
		}

		// A/B drive fix (SilentPatch)
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005D7941)) = 'A';
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005D7B04)) = 'A';

		// disable DirectPlay dependency (SilentPatch)
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00601CA0)) = 0xB8;
		*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00601CA1)) = 0x900;

		// disable video memory check (SilentPatch)
		*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00601E26)) = 0xEB;

		// window name
		*reinterpret_cast<const char **>(vcversion::AdjustOffset(0x00602D36)) = windowName;

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
		Patch<unsigned char>(0x005D49C7, 0xD);
		memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x005345ED)), 0x90, 9);

		// 0410 (Purple Nines) fix
		InjectHook(0x004EEED1, &GangsInitialise, PATCH_JUMP); // CGangs::Initialise

		// remove horizon ships
		if (!GetPrivateProfileInt("Misc", "AllowHorizonShips", 0, "./gta-lc.ini")) {
			Patch<unsigned short>(0x005BC5BC, 0xE990); // CWaterLevel::RenderShipsOnHorizon
		}

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

		// taxi cash
		Patch<unsigned char>(0x005B8AB6, 25); // CVehicle::SetDriver

		// hospital cost
		InjectHook(0x0042BC64, &GameLogicUpdate, PATCH_JUMP); // CGameLogic::Update

		// FBI Rancher roof light
		InjectHook(0x0058BE2F, &AutomobilePreRender, PATCH_JUMP); // CAutomobile::PreRender

		// fire light glow (SilentPatch)
		Patch<unsigned char>(0x0048EB27, 0x10); // CFire::ProcessFire

		// wet roads reflection (SilentPatch)
		InjectHook(0x005433BD, &RenderReflections); // CCoronas::RenderReflections

		// support treadables
		Patch<unsigned int>(0x004C0325, 0x4068006A); // CPools::Initialise
		Patch<unsigned int>(0x004C0329, 0xE800001F);

		// reinit firetruck/ambulance timer (SilentPatch)
		InjectHook(0x004A489B, &CarCtrlReInit);

		// investigate ped crash fix
		InjectHook(0x004E94E0, &CivilianAI, PATCH_JUMP);

		// script paths allow replay
		memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x00624EDB)), 0x90, 9);

		// prioritize specific ped sfx
		InjectHook(0x005DDB6C, &PedCommentsProcess, PATCH_JUMP);

		// center mouse (SilentPatch)
		InjectHook(0x004A5E45, &ResetMousePos);
		OldWndProc = *(LRESULT(CALLBACK***)(HWND, UINT, WPARAM, LPARAM))vcversion::AdjustOffset(0x00601727);
		Patch(0x00601727, &pCustomWndProc);

		if (!cAudioManagerHack::initialise() ||
			!CFontHack::initialise() ||
			//!CHudHack::initialise() ||
			!CMovingThingsHack::initialise() ||
			!CPagerHack::initialise() ||
			!CRunningScriptHack::initialise() ||
			!CRendererHack::initialise() ||
			!CCranesHack::initialise() ||
			!CPickupsHack::initialise() ||
			!CPadHack::initialise() ||
			!CGaragesHack::initialise() ||
			!CWantedHack::initialise() ||
			!CPacManPickupsHack::initialise() ||
			!CProjectileInfoHack::initialise() ||
			!CCameraHack::initialise() ||
			!CFileLoaderHack::initialise() ||
			!CPathFindHack::initialise() ||
			!CBridgeHack::initialise() ||
			!CStatsHack::initialise() ||
			!CWeaponEffectsHack::initialise() ||
			!CObjectHack::initialise() ||
			!CRadarHack::initialise() ||
			!CPedHack::initialise())
		{
			VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, OldProtect, &OldProtect);
			return FALSE;
		}

		VirtualProtect((LPVOID)(0x400000 + sectionheader->VirtualAddress), sectionheader->Misc.VirtualSize, OldProtect, &OldProtect);
		break;

	case DLL_PROCESS_DETACH:
		if (hOrigDLL != NULL)
		{
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

void __declspec(naked) GameLogicUpdate()
{
	__asm
	{
		mov eax, dword ptr [ebx+0A0h] // get current cash
		add eax, 0FFFFFC18h           // subtract 1000
		jmp gameLogicUpdateEndJump
	}
}

void __declspec(naked) AutomobilePreRender()
{
	__asm
	{
		sub ecx, 9 // ambulan
		jz matchAmbulan
		dec ecx    // fbiranch
		jz matchFbiranch
		inc ecx    // resume before change
		jmp preRenderNoMatch
	matchAmbulan:
		jmp preRenderMatchAmbulan
	matchFbiranch:
		jmp preRenderMatchFbiranch
	}
}

float RenderReflections()
{
	return 1.0;
}

void CarCtrlReInit()
{
	CCarCtrl::ReInit();
	CCarCtrl::LastTimeFireTruckCreated = 0;
	CCarCtrl::LastTimeAmbulanceCreated = 0;
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
