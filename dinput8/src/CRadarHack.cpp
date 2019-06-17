#include "CRadarHack.h"
#include "vcversion.h"
#include "SilentCall.h"

static unsigned long entityBlipJumpEnd = vcversion::AdjustOffset(0x004C3B7E);
static unsigned long coordBlipJumpEnd = vcversion::AdjustOffset(0x004C3CC8);
static unsigned long blipColour = vcversion::AdjustOffset(0x007D7D38);

bool CRadarHack::initialise()
{
	// entity blip color
	InjectHook(0x004C3B74, &CRadarHack::SetEntityBlipHack, PATCH_JUMP);

	// coord blip color
	InjectHook(0x004C3CBE, &CRadarHack::SetCoordBlipHack, PATCH_JUMP);

	return true;
}

void __declspec(naked) CRadarHack::SetEntityBlipHack()
{
	__asm
	{
		push eax              // store eax
		push ecx              // store ecx
		mov ecx, blipColour   // get blip colour base address
		mov eax, [esp+14h]    // get blip colour from stack
		mov [edx+ecx], eax    // set blip colour
		pop ecx               // restore ecx
		pop eax               // restore eax
		jmp entityBlipJumpEnd
	}
}

void __declspec(naked) CRadarHack::SetCoordBlipHack()
{
	__asm
	{
		push eax             // store eax
		push edx             // store edx
		mov edx, blipColour  // get blip colour base address
		mov eax, [esp+1Ch]   // get blip colour from stack
		mov [ecx+edx], eax   // set blip colour
		pop edx              // restore edx
		pop eax              // restore eax
		jmp coordBlipJumpEnd
	}
}
