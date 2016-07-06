#include "CPickupsHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"

// RenderPickUpText
static void RenderPickUpText();
unsigned long pickupText0Jump = vcversion::AdjustOffset(0x0043E649);
unsigned long pickupTextGetTextJump = vcversion::AdjustOffset(0x0043E6FD);
char text[53][8] =
{
#include "PickupText.inc"
};

// DoPickUpEffects
static void DoPickUpEffects();
unsigned long adrenalineModel = vcversion::AdjustOffset(0x0068E924);
unsigned long cameraModel = vcversion::AdjustOffset(0x0068E940);
unsigned long bodyarmourModel = vcversion::AdjustOffset(0x0068E928);
unsigned long bribeModel = vcversion::AdjustOffset(0x0068E938);
unsigned long infoModel = vcversion::AdjustOffset(0x0068E92C);
unsigned long killfrenzyModel = vcversion::AdjustOffset(0x0068E93C);
unsigned long healthModel = vcversion::AdjustOffset(0x0068E930);
unsigned long bonusModel = vcversion::AdjustOffset(0x0068E934);
unsigned long pickupEffectEndJump = vcversion::AdjustOffset(0x0043F294);
unsigned long pickupEffectNoMatchJump = vcversion::AdjustOffset(0x0043F246);

bool CPickupsHack::initialise()
{
	call(0x0043E639, &RenderPickUpText, PATCH_JUMP);
	call(0x0043F0F5, &DoPickUpEffects, PATCH_JUMP);

	// pickup colors, blue-green-red
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x006881C0)) = 0x80FF80; // color 37
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x006881C8)) = 0xFF0000; // color 38
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x006881D0)) = 0;        // color 39

	return true;
}

void __declspec(naked) RenderPickUpText()
{
	_asm
	{
		test eax, eax
		jz text0
		dec eax       // start index at 0
		lea edx, text // get base address of text array
		shl eax, 3    // multiply index by 8
		add edx, eax  // add to base address to get address of text
		push edx      // push address of text
		jmp pickupTextGetTextJump
	text0:
		jmp pickupText0Jump
	}
}

void __declspec(naked) DoPickUpEffects()
{
	_asm
	{
		movsx ecx, word ptr [ebp+5Ch] // get pickup model index

		mov edx, adrenalineModel      // get adrenaline model address, must use edx
		movzx edx, word ptr [edx]     // read address to get model index
		cmp edx, ecx                  // compare with pickup model index
		jz adrenalineCameraEffect
		mov eax, cameraModel          // get camera model address
		movzx eax, word ptr [eax]     // read address to get model index
		cmp eax, ecx                  // compare with pickup model index
		jnz armorBribeModels
	adrenalineCameraEffect:
		mov ebx, 6                    // color FF0000
		jmp endMatch

	armorBribeModels:
		mov eax, bodyarmourModel      // get bodyarmour model address, must use eax
		movzx eax, word ptr [eax]     // read address to get model index
		cmp eax, ecx                  // compare with pickup model index
		jz armorBribeEffect
		mov ebx, bribeModel           // get bribe model address
		movzx ebx, word ptr [ebx]     // read address to get model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz infoKillfrenzyModels
	armorBribeEffect:
		mov ebx, 37                   // color 80FF80
		jmp endMatch

	infoKillfrenzyModels:
		mov esi, infoModel            // get info model address
		movzx esi, word ptr [esi]     // read address to get model index
		cmp esi, ecx                  // compare with pickup model index
		jz infoKillfrenzyEffect
		mov ebx, killfrenzyModel      // get killfrenzy model address
		movzx ebx, word ptr [ebx]     // read address to get model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz healthBonusModels
	infoKillfrenzyEffect:
		mov ebx, 38                   // color 0000FF
		jmp endMatch

	healthBonusModels:
		mov esi, healthModel          // get health model address, must use esi
		movzx esi, word ptr [esi]     // read address to get model index
		cmp esi, ecx                  // compare with pickup model index
		jz healthBonusEffect
		mov ebx, bonusModel           // get bonus model address
		movzx ebx, word ptr [ebx]     // read address to get model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz floatpackge1ModelEffect
	healthBonusEffect:
		mov ebx, 21                   // color FFFF00
		jmp endMatch

	floatpackge1ModelEffect:
		mov ebx, 1320                 // floatpackge1 model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz endNoMatch
		mov dword ptr [esp+0Ch], 39   // color 000000
		mov byte ptr [esp+10h], 0     // halo
		mov byte ptr [esp+14h], 0     // glow
		jmp pickupEffectEndJump

	endMatch:
		mov dword ptr [esp+0Ch], ebx  // color
		mov byte ptr [esp+10h], 1     // halo
		mov byte ptr [esp+14h], 0     // glow
		jmp pickupEffectEndJump

	endNoMatch:
		jmp pickupEffectNoMatchJump
	}
}
