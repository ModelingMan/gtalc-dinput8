#include "CRadarHack.h"
#include "vcversion.h"
#include "SilentCall.h"

unsigned long entityBlipJumpEnd = vcversion::AdjustOffset(0x004C3B7E);
unsigned long blipColour = vcversion::AdjustOffset(0x007D7D38);

bool CRadarHack::initialise()
{
	// blip color
	InjectHook(0x004C3B70, &CRadarHack::SetEntityBlipHack, PATCH_JUMP);
	return true;
}

void __declspec(naked) CRadarHack::SetEntityBlipHack()
{
	__asm
	{
		push ecx              // store ecx
		mov ecx, blipColour   // get blip colour base address
		mov eax, [esp+10h]    // get blip colour from stack
		mov [edx+ecx], eax    // set blip colour
		pop ecx               // restore ecx
		mov eax, [esp+8]
		jmp entityBlipJumpEnd
	}
}
