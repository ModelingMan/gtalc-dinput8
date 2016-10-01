#include "CWeaponEffectsHack.h"
#include "CRunningScriptHack.h"
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"
#include <Windows.h>

unsigned long initJumpEnd = vcversion::AdjustOffset(0x005D512D);

bool CWeaponEffectsHack::initialise()
{
	// auto-aim crosshair
	InjectHook(0x005D511C, &CWeaponEffectsHack::InitHackProxy, PATCH_JUMP);
	return true;
}

void __declspec(naked) CWeaponEffectsHack::InitHackProxy()
{
	__asm
	{
		call CWeaponEffectsHack::InitHack
		jmp initJumpEnd
	}
}

unsigned long CWeaponEffectsHack::InitHack()
{
	unsigned long addr = RwTextureRead("crosshair", "crosshairm");
	// use alternative target texture if it exists
	if (!(CRunningScriptHack::debugMode & DEBUG_VICECITY) && addr) {
		VCGlobals::strcpy(reinterpret_cast<char *>(vcversion::AdjustOffset(0x0069D818)), "crosshair");
		VCGlobals::strcpy(reinterpret_cast<char *>(vcversion::AdjustOffset(0x0069D80C)), "crosshairm");
		memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x005D4ECC)), 0x90, 11);
		Patch<unsigned char>(0x005D4EE3, 2);
		Patch<unsigned char>(0x005D4EEE, 2);
	} else {
		addr = RwTextureRead("target256", "target256m");
		Patch<unsigned char>(0x005D4EEE, 9);
	}
	return addr;
}
