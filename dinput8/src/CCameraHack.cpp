#include "CCameraHack.h"
#include <Windows.h>
#include "vcversion.h"
#include "SilentCall.h"

// CamControlHack
unsigned long camControlOther = vcversion::AdjustOffset(0x00472BF9);
unsigned long camControlCar = vcversion::AdjustOffset(0x00472C02);

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
	Patch<unsigned long>(0x004796F2, (unsigned long)&mouseXSensitivity);
	Patch<unsigned long>(0x0047A48D, (unsigned long)&mouseXSensitivity);
	Patch<unsigned long>(0x0047AFF5, (unsigned long)&mouseXSensitivity);
	Patch<unsigned long>(0x0047C0BF, (unsigned long)&mouseXSensitivity);
	Patch<unsigned long>(0x00481FB3, (unsigned long)&mouseXSensitivity);

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
		movzx edi, word ptr [eax+5Ch] // get model index of vehicle
		cmp edi, 194                  // compare with model index of RC Baron
		jnz car
	other:
		jmp camControlOther
	car:
		jmp camControlCar
	}
}
