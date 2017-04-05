#include "CStatsHack.h"
#include "vcversion.h"
#include "SilentCall.h"

char *gxtKey = "FEST_MP";
unsigned long missionsGivenStatJump = vcversion::AdjustOffset(0x004CB15D);
unsigned long playingTimeStatJump = vcversion::AdjustOffset(0x004CB16E);
unsigned long highestLevelFireMissionStatDisplay = vcversion::AdjustOffset(0x004CC0B5);
unsigned long highestLevelFireMissionStatNext = vcversion::AdjustOffset(0x004CC0D9);
unsigned long storesKnockedOffStatDisplay = vcversion::AdjustOffset(0x004CC0E0);
unsigned long storesKnockedOffStatNext = vcversion::AdjustOffset(0x004CC137);
unsigned long assassinationsStatDisplay = vcversion::AdjustOffset(0x004CC1B1);
unsigned long assassinationsStatNext = vcversion::AdjustOffset(0x004CC203);
unsigned long buildStatLine = vcversion::AdjustOffset(0x004CD1A8);

bool CStatsHack::initialise()
{
	/*
	// add missions passed line
	Patch<unsigned char>(0x004CB19D, 3);
	Patch<unsigned char>(0x004CB1C4, 4);
	Patch<unsigned char>(0x004CB1E7, 5);
	Patch<unsigned char>(0x004CB20A, 6);
	InjectHook(0x004CB14B, &CStatsHack::MissionsPassedHack, PATCH_JUMP);
	// replace missions passed stat with loan sharks stat
	Patch<unsigned long>(0x00456C0F, (unsigned long)&CStats::LoanSharks);
	InjectHook(0x004CBF22, vcversion::AdjustOffset(0x004CBF83), PATCH_JUMP);

	InjectHook(0x004CC0AE, &CStatsHack::HighestLevelFireMissionHack, PATCH_JUMP);
	InjectHook(0x004CC0D9, &CStatsHack::StoresKnockedOffHack, PATCH_JUMP);
	InjectHook(0x004CC1A7, &CStatsHack::AssassinationsHack, PATCH_JUMP);
	*/
	return true;
}

void __declspec(naked) CStatsHack::MissionsPassedHack()
{
	__asm
	{
		cmp esi, 1                   // compare current line with 1
		jnz missionsPassed
		mov eax, MissionsGiven
		jmp missionsGivenStatJump
	missionsPassed:
		cmp esi, 2                   // compare current line with 2
		jnz playingTime
		mov ebx, TotalNumberMissions // store address of total number of missions stat
		mov eax, LoanSharks          // store address of missions passed stat
		push 0                       // stat display primary type
		push ebx                     // push address of total number of missions stat
		push 0                       // stat display secondary type
		push eax                     // push address of missions passed stat
		mov eax, gxtKey              // store address of gxt key
		push eax                     // push address of gxt key
		jmp buildStatLine
	playingTime:
		jmp playingTimeStatJump
	}
}

void __declspec(naked) CStatsHack::HighestLevelFireMissionHack()
{
	__asm
	{
		mov eax, HighestLevelFireMission // store address of fire truck mission level stat
		cmp [eax], 0                     // compare value of stat with 0
		jle decr
		lea eax, dword ptr [ebp+7]
		cmp eax, esi
		jnz next
		jmp highestLevelFireMissionStatDisplay
	decr:
		dec ebp                          // skip over line in menu
	next:
		jmp highestLevelFireMissionStatNext
	}
}

void __declspec(naked) CStatsHack::StoresKnockedOffHack()
{
	__asm
	{
		fldz                      // push 0.0 onto stack
		mov eax, StoresKnockedOff // store address of stores knocked off stat
		fld [eax]                 // get value of stat and push onto stack
		fcompp                    // compare value of stat with 0.0 and pop stack twice
		fnstsw ax
		test ah, 45h
		jnz decr
		lea eax, dword ptr [ebp+8]
		cmp eax, esi
		jnz next
		jmp storesKnockedOffStatDisplay
	decr:
		dec ebp                   // skip over line in menu
	next:
		jmp storesKnockedOffStatNext
	}
}

void __declspec(naked) CStatsHack::AssassinationsHack()
{
	__asm
	{
		fldz                    // push 0.0 onto stack
		mov eax, Assassinations // store address of assassination contracts completed stat
		fld [eax]               // get value of stat and push onto stack
		fcompp                  // compare value of stat with 0.0 and pop stack twice
		fnstsw ax
		test ah, 45h
		jnz next
		cmp ebp, esi
		jnz incr
		mov eax, Assassinations
		fld [eax]
		jmp assassinationsStatDisplay
	incr:
		inc ebp                 // proceed to next line in menu
	next:
		jmp assassinationsStatNext
	}
}
