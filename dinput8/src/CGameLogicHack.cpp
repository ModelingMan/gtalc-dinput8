#include "CGameLogicHack.h"
#include <Windows.h>
#include "vcversion.h"
#include "SilentCall.h"
#include "ModelIndices.h"

bool CGameLogicHack::isShortcutDropoffEnabled;
char CGameLogicHack::skipClearShortcutStage;

// GameLogicUpdate
unsigned long gameLogicUpdateEndJump = vcversion::AdjustOffset(0x0042BC6D);

bool CGameLogicHack::initialise()
{
	// switch shortcut dropoff
	isShortcutDropoffEnabled = !!GetPrivateProfileInt("Misc", "UseShortcutDropoff", 1, "./gta-lc.ini");

	// use cabbie model
	Patch<unsigned long>(0x0042AE8D, vcversion::AdjustOffset(0x0094DDD8) + CAR_CABBIE * 0x14);
	Patch<unsigned int>(0x0042AEAC, CAR_CABBIE);
	Patch<unsigned int>(0x0042AFB3, CAR_CABBIE);
	Patch<unsigned int>(0x0042B87B, CAR_CABBIE);

	// skip clear taxi shortcut for custom opcode 036B
	skipClearShortcutStage = 0;
	InjectHook(0x00608CD9, &CGameLogicHack::ClearTaxiShotcutHack);
	InjectHook(0x00451746, &CGameLogicHack::ClearTaxiShotcutHack);

	// hospital cost
	InjectHook(0x0042BC64, &CGameLogicHack::UpdateHack, PATCH_JUMP);

	return true;
}

void CGameLogicHack::ClearTaxiShotcutHack()
{
	if (skipClearShortcutStage) {
		skipClearShortcutStage--;
	} else {
		CGameLogic::ClearShortCut();
	}
}

void __declspec(naked) CGameLogicHack::UpdateHack()
{
	__asm
	{
		mov eax, dword ptr [ebx+0A0h] // get current cash
		add eax, 0FFFFFC18h           // subtract 1000
		jmp gameLogicUpdateEndJump
	}
}
