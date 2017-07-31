#include "CPedHack.h"
#include "Globals.h"
#include "SilentCall.h"
#include "WeaponTypes.h"
#include "vcversion.h"

// ServiceTalkingHackProxy
static unsigned long serviceTalkingEndJump = vcversion::AdjustOffset(0x00522890);

// InflictDamageHack
static unsigned long inflictDamageHackMatch = vcversion::AdjustOffset(0x005261B3);
static unsigned long inflictDamageHackNoMatch = vcversion::AdjustOffset(0x005261B7);

bool CPedHack::initialise()
{
	// allow bomber talk sfx
	InjectHook(0x0052287E, &CPedHack::ServiceTalkingHackProxy, PATCH_JUMP);

	// ak47 critical hits
	InjectHook(0x005261A4, &CPedHack::InflictDamageHack, PATCH_JUMP);

	return true;
}

void __declspec(naked) CPedHack::ServiceTalkingHackProxy()
{
	__asm
	{
		mov ecx, ebx
		call CPedHack::ServiceTalkingHack
		jmp serviceTalkingEndJump
	}
}

void CPedHack::ServiceTalkingHack() {
	char *modelName = reinterpret_cast<char *>(CModelInfo::ms_modelInfoPtrs[this->modelIndex] + 0x4);
	if (this->activeFire || VCGlobals::strcmp(modelName, "bomber") == 0) {
		this->talkType = 0x6C;
	}
}

void __declspec(naked) CPedHack::InflictDamageHack()
{
	__asm
	{
		cmp eax, WEAPONTYPE_M16
		jz match
		cmp eax, WEAPONTYPE_SNIPERRIFLE
		jz match
		cmp eax, WEAPONTYPE_LASERSCOPE
		jz match
		jmp inflictDamageHackNoMatch
	match:
		jmp inflictDamageHackMatch
	}
}
