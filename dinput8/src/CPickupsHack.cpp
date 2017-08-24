#include "CPickupsHack.h"
#include "Globals.h"
#include "SilentCall.h"
#include "vcversion.h"

using namespace VCGlobals;

// RenderPickUpText
static unsigned long pickupText0Jump = vcversion::AdjustOffset(0x0043E649);
static unsigned long pickupTextGetTextJump = vcversion::AdjustOffset(0x0043E6FD);
static char text[53][8] =
{
#include "PickupText.inc"
};

// DoPickUpEffects
static unsigned long pickupEffectEndJump = vcversion::AdjustOffset(0x0043F294);
static unsigned long pickupEffectNoMatchJump = vcversion::AdjustOffset(0x0043F246);

static unsigned short AmmoForWeapon[38] =
{
	0,
	1,
	1,
	1,
	1,
	1,
	1, // bat
	1,
	1,
	1,
	1,
	1,
	5, // grenade
	8,
	8,
	5, // molotov
	8,
	45, // colt45
	24,
	32,
	28,
	25, // shotgun
	200,
	125, // uzi
	120,
	120,
	300, // m16
	150, // ak47
	25, // sniper
	28,
	5, // rocket
	250, // flame
	200,
	1000,
	1,
	400,
	36,
	0
};

static unsigned short AmmoForWeapon_OnStreet[38] =
{
	0,
	1,
	1,
	1,
	1,
	1,
	1, // bat
	1,
	1,
	1,
	1,
	1,
	1, // grenade
	4,
	4,
	1, // molotov
	4,
	9, // colt45
	12,
	16,
	14,
	5, // shotgun
	100,
	25, // uzi
	60,
	60,
	60, // m16
	30, // ak47
	5, // sniper
	14,
	1, // rocket
	50, // flame
	100,
	500,
	1,
	400,
	36,
	0
};

static short CostOfWeapon[40] =
{
	0,
	10,
	10,
	10,
	10,
	10,
	10, // bat
	10,
	10,
	10,
	10,
	10,
	2000, // grenade
	1000,
	1000,
	2000, // molotov
	8000,
	250, // colt45
	400,
	1200,
	1250,
	1500, // shotgun
	800,
	800, // uzi
	650,
	1200,
	5000, // m16
	3000, // ak47
	10000, // sniper
	10000,
	25000, // rocket
	25000, // flame
	8000,
	10000,
	1000,
	11000,
	500,
	20,
	3000, // armor/adrenaline
	0
};

struct PickupColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char unk1;
	float unk2;
} aPickupColor[41] =
{
	{ 0x80, 0x80, 0x80, 0, 1.0 },
	{ 0x80, 0x80, 0x80, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0xFF,    0,    0, 0, 1.0 }, // bat
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0x61, 0xC2, 0xF7, 0, 1.0 },
	{ 0xFF, 0xFF, 0xFF, 0, 1.0 }, // grenade
	{ 0x1B, 0x59, 0x82, 0, 1.0 },
	{ 0x1B, 0x59, 0x82, 0, 1.0 },
	{ 0x80, 0xFF,    0, 0, 1.0 }, // molotov
	{ 0x1B, 0x59, 0x82, 0, 1.0 },
	{    0, 0xFF,    0, 0, 1.0 }, // colt45
	{ 0x95, 0xC2, 0x18, 0, 1.0 },
	{ 0x2D, 0x9B, 0x5A, 0, 1.0 },
	{ 0x2D, 0x9B, 0x5A, 0, 1.0 },
	{ 0xFF, 0xFF,    0, 0, 1.0 }, // shotgun
	{ 0xFF, 0xE3, 0x4F, 0, 1.0 },
	{ 0x80, 0x80, 0xFF, 0, 1.0 }, // uzi
	{ 0xFF, 0xE3, 0x4F, 0, 1.0 },
	{ 0xFF, 0xE3, 0x4F, 0, 1.0 },
	{    0, 0xFF, 0xFF, 0, 1.0 }, // m16
	{ 0xFF,    0, 0xFF, 0, 1.0 }, // ak47
	{ 0xFF, 0x80,    0, 0, 1.0 }, // sniper
	{ 0xF9, 0x83, 0xD7, 0, 1.0 },
	{    0, 0xFF, 0x80, 0, 1.0 }, // rocket
	{ 0x80,    0, 0xFF, 0, 1.0 }, // flame
	{ 0xA4, 0x28, 0xB2, 0, 1.0 },
	{ 0xA4, 0x28, 0xB2, 0, 1.0 },
	{ 0x45, 0x45, 0x45, 0, 1.0 },
	{ 0x45, 0x45, 0x45, 0, 1.0 },
	{ 0x45, 0x45, 0x45, 0, 1.0 },
	{ 0x80, 0xFF, 0x80, 0, 1.0 }, // 37
	{    0,    0, 0xFF, 0, 1.0 }, // 38
	{    0,    0,    0, 0, 1.0 }, // 39
	{ 0xFF, 0xFF, 0x64, 0, 1.0 }
};

bool CPickupsHack::initialise()
{
	InjectHook(0x0043E639, &CPickupsHack::RenderPickUpTextHack, PATCH_JUMP);

	// non-weapon pickup effects
	InjectHook(0x0043F0F5, &CPickupsHack::DoPickUpEffectsHack, PATCH_JUMP);

	// pickups light glow
	Patch<unsigned char>(0x0043F52B, 0x10);
	Patch<unsigned char>(0x0043EC03, 0x10);
	Patch<unsigned char>(0x0043E983, 0x10);
	Patch<unsigned char>(0x0043EECB, 0x10);
	Patch<unsigned char>(0x0043F842, 0x10);

	// package rewards
	InjectHook(0x00441293, &CPickupsHack::UpdateHack);
	Patch<unsigned short>(0x00441298, 0x9090);
	Patch<unsigned int>(0x004412DC, 1000000);

	// weapon ammo and cost
	for (int i = 0; i < 38; i++) {
		Patch<unsigned short>(0x00687F68 + i * 2, AmmoForWeapon[i]);
	}
	for (int i = 0; i < 38; i++) {
		Patch<unsigned short>(0x00687FB4 + i * 2, AmmoForWeapon_OnStreet[i]);
	}
	for (int i = 0; i < 40; i++) {
		Patch<short>(0x00688000 + i * 2, CostOfWeapon[i]);
	}

	// pickup colors
	for (int i = 0; i < 41; i++) {
		Patch<PickupColor>(0x00688098 + i * sizeof(PickupColor), aPickupColor[i]);
	}

	// do not halve ammo of dropped weapon
	Nop(0x0043DFED, 11);
	Nop(0x0043E0F6, 11);

	// package corona
	Patch<unsigned char>(0x0043EF12, 7);

	// package sound
	Patch<unsigned char>(0x00441368, 85);

	// weapon corona
	Patch<unsigned char>(0x0043F68C, 0);
	Patch<unsigned int>(0x0043F6AF, 0);
	Patch<float>(0x0068832C, 0);
	Patch<float>(0x00688334, 0.05);

	return true;
}

void __declspec(naked) CPickupsHack::RenderPickUpTextHack()
{
	__asm
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

void __declspec(naked) CPickupsHack::DoPickUpEffectsHack()
{
	__asm
	{
		movsx ecx, word ptr [ebp+5Ch] // get pickup model index

		mov edx, MI_PICKUP_ADRENALINE // get adrenaline model address, must use edx
		movzx edx, word ptr [edx]     // read address to get model index
		cmp edx, ecx                  // compare with pickup model index
		jz adrenalineCameraEffect
		mov eax, MI_PICKUP_CAMERA     // get camera model address
		movzx eax, word ptr [eax]     // read address to get model index
		cmp eax, ecx                  // compare with pickup model index
		jnz bodyarmourBribeModels
	adrenalineCameraEffect:
		mov ebx, 6                    // color FF0000
		jmp endMatch

	bodyarmourBribeModels:
		mov eax, MI_PICKUP_BODYARMOUR // get bodyarmour model address, must use eax
		movzx eax, word ptr [eax]     // read address to get model index
		cmp eax, ecx                  // compare with pickup model index
		jz bodyarmourBribeEffect
		mov ebx, MI_PICKUP_BRIBE      // get bribe model address
		movzx ebx, word ptr [ebx]     // read address to get model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz infoKillfrenzyModels
	bodyarmourBribeEffect:
		mov ebx, 37                   // color 80FF80
		jmp endMatch

	infoKillfrenzyModels:
		mov esi, MI_PICKUP_INFO       // get info model address
		movzx esi, word ptr [esi]     // read address to get model index
		cmp esi, ecx                  // compare with pickup model index
		jz infoKillfrenzyEffect
		mov ebx, MI_PICKUP_KILLFRENZY // get killfrenzy model address
		movzx ebx, word ptr [ebx]     // read address to get model index
		cmp ebx, ecx                  // compare with pickup model index
		jnz healthBonusModels
	infoKillfrenzyEffect:
		mov ebx, 38                   // color 0000FF
		jmp endMatch

	healthBonusModels:
		mov esi, MI_PICKUP_HEALTH     // get health model address, must use esi
		movzx esi, word ptr [esi]     // read address to get model index
		cmp esi, ecx                  // compare with pickup model index
		jz healthBonusEffect
		mov ebx, MI_PICKUP_BONUS      // get bonus model address
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

void CPickupsHack::UpdateHack()
{
	CWorld::Players[CWorld::PlayerInFocus].m_Money += 1000;
}
