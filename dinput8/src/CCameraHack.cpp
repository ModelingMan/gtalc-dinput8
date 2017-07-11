#include "CCameraHack.h"
#include <cmath>
#include <Windows.h>
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"

// CamControlHack
static unsigned long camControlOther = vcversion::AdjustOffset(0x00472BF9);
static unsigned long camControlCar = vcversion::AdjustOffset(0x00472C02);

// cinematic camera help message
static unsigned long cinemaCameraEndJump = vcversion::AdjustOffset(0x0046C03A);
static const char *cincam = "CINCAM";
static bool &cameraSound = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00703684));

bool CCameraHack::initialise()
{
	// RC Baron camera controls
	if (!GetPrivateProfileInt("Misc", "UseRCBaron", 0, "./gta-lc.ini")) {
		Patch<float>(0x0068ABF4, 0.0);
		Patch<float>(0x0068ABEC, 0.0);
		InjectHook(0x00483F6A, vcversion::AdjustOffset(0x00483F7D), PATCH_JUMP);
		Patch<unsigned char>(0x00597CBE, 3);
		InjectHook(0x00472BE8, &CCameraHack::CamControlHack, PATCH_JUMP);
	}

	// mouse sensitivity fix (SilentPatch/ThirteenAG)
	float &mouseXSensitivity = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0094DBD0));
	Patch<float>(0x0046F4AD, 0.0025);
	Patch<void *>(0x004796F2, &mouseXSensitivity);
	Patch<void *>(0x0047A48D, &mouseXSensitivity);
	Patch<void *>(0x0047AFF5, &mouseXSensitivity);
	Patch<void *>(0x0047C0BF, &mouseXSensitivity);
	Patch<void *>(0x00481FB3, &mouseXSensitivity);

	// fade to/from splash (Silent)
	Patch<unsigned char>(0x0046BA41, 0);
	Patch<unsigned char>(0x0046BA51, 0);
	Patch<unsigned char>(0x0046BA55, 0);

	// cinematic camera help message
	InjectHook(0x0046C033, &CCameraHack::ProcessObbeCinemaCameraCarHack, PATCH_JUMP);

	return true;
}

void __declspec(naked) CCameraHack::CamControlHack()
{
	__asm
	{
		mov eax, dword ptr [ebp+80Ch]
		mov edi, dword ptr [eax+29Ch]
		cmp edi, 1
		jz other
		movsx edi, word ptr [eax+5Ch] // get model index of vehicle
		cmp edi, 194                  // compare with model index of RC Baron
		jnz car
	other:
		jmp camControlOther
	car:
		jmp camControlCar
	}
}

void __declspec(naked) CCameraHack::ProcessObbeCinemaCameraCarHack()
{
	__asm
	{
		mov cameraSound, 1
		mov ecx, VCGlobals::TheText
		push 0
		push 1
		push cincam
		call CText::Get
		push eax
		call CHud::SetHelpMessage
		add esp, 12
		jmp cinemaCameraEndJump
	}
}
