#include "CPedHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Globals.h"

// ServiceTalkingHackProxy
static unsigned long serviceTalkingEndJump = vcversion::AdjustOffset(0x00522890);

bool CPedHack::initialise()
{
	// allow bomber talk sfx
	InjectHook(0x0052287E, &CPedHack::ServiceTalkingHackProxy, PATCH_JUMP);
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
