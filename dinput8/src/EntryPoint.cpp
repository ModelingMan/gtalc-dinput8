#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

#include "cAudioManagerHack.h"
#include "CFontHack.h"
#include "CHudHack.h"
#include "CMovingThingsHack.h"
#include "CPagerHack.h"
#include "CRunningScriptHack.h"
#include "CRendererHack.h"
#include "CCranesHack.h"
#include "CPickupsHack.h"
#include "CPadHack.h"
#include "CGaragesHack.h"
#include "CWantedHack.h"

HMODULE hOrigDLL = NULL;

FARPROC OldDirectInput8Create = NULL;
FARPROC OldDllCanUnloadNow = NULL;
FARPROC OldDllGetClassObject = NULL;
FARPROC OldDllRegisterServer = NULL;
FARPROC OldDllUnregisterServer = NULL;

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

_declspec(naked) HRESULT WINAPI NewDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
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

#include "vcversion.h"

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
			!CWantedHack::initialise())
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
