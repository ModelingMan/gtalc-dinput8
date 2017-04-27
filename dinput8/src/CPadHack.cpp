#include "CPadHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "ModelIndices.h"

static void UpdatePedCount();
static unsigned long updatePedCountEndJump = vcversion::AdjustOffset(0x0053B6ED);
static char weaponsForAllArr[12] = { 6, 17, 23, 21, 25, 26, 28, 30, 31, 15, 12, 0 };

static char specialCharacters[10][8] =
{
	"eight2",
	"misty",
	"ray",
	"tony",
	"love",
	"dealer",
	"frankie",
	"maria",
	"donky",
	"sam"
};

bool CPadHack::initialise()
{
	// allow for additional cheats
	auto function = &CPadHack::AddToCheatStringHack;
	InjectHook(0x00602BE7, (unsigned long &)function);

	// remove cheat warning
	InjectHook(0x004990AD, vcversion::AdjustOffset(0x004990C0), PATCH_JUMP);

	// modify weapon set for arm everybody cheat
	InjectHook(0x0053B6B9, &UpdatePedCount, PATCH_JUMP);

	// modify special character cheats
	Patch<void *>(0x004ACA66, &specialCharacters[0]); // igbuddy
	Patch<void *>(0x004ACA96, &specialCharacters[1]); // igcandy
	Patch<void *>(0x004ACAC6, &specialCharacters[2]); // igken
	Patch<void *>(0x004ACAF6, &specialCharacters[3]); // ighlary
	Patch<void *>(0x004ACB26, &specialCharacters[4]); // igjezz
	Patch<void *>(0x004ACB56, &specialCharacters[5]); // igphil
	Patch<void *>(0x004ACB86, &specialCharacters[6]); // igsonny
	Patch<void *>(0x004ACD76, &specialCharacters[7]); // igmerc
	Patch<void *>(0x004ACDA6, &specialCharacters[8]); // igdick
	Patch<void *>(0x004ACEB6, &specialCharacters[9]); // igdiaz

	// cheat weapon ammo fix (SilentPatch)
	Patch<unsigned char>(0x004AED15, 1);
	Patch<unsigned char>(0x004AEB75, 1);

	return true;
}

void CPadHack::WeaponCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT2"), true, false);
	CStreaming::RequestModel(264, 1); // bat
	CStreaming::RequestModel(274, 1); // colt45
	CStreaming::RequestModel(282, 1); // uzi
	CStreaming::RequestModel(279, 1); // shotgun
	CStreaming::RequestModel(284, 1); // ak47
	CStreaming::RequestModel(280, 1); // m16
	CStreaming::RequestModel(285, 1); // sniper
	CStreaming::RequestModel(287, 1); // rocket
	CStreaming::RequestModel(288, 1); // flame
	CStreaming::RequestModel(272, 1); // molotov
	CStreaming::RequestModel(270, 1); // grenade
	CStreaming::LoadAllRequestedModels(false);
	VCGlobals::FindPlayerPed()->GiveWeapon(6, 1, true);    // bat
	VCGlobals::FindPlayerPed()->GiveWeapon(17, 100, true); // colt45
	VCGlobals::FindPlayerPed()->GiveWeapon(23, 100, true); // uzi
	VCGlobals::FindPlayerPed()->GiveWeapon(21, 20, true);  // shotgun
	VCGlobals::FindPlayerPed()->GiveWeapon(25, 200, true); // ak47
	VCGlobals::FindPlayerPed()->GiveWeapon(26, 200, true); // m16
	VCGlobals::FindPlayerPed()->GiveWeapon(28, 5, true);   // sniper
	VCGlobals::FindPlayerPed()->GiveWeapon(30, 5, true);   // rocket
	VCGlobals::FindPlayerPed()->GiveWeapon(31, 200, true); // flame
	VCGlobals::FindPlayerPed()->GiveWeapon(15, 5, true);   // molotov
	VCGlobals::FindPlayerPed()->GiveWeapon(12, 5, true);   // grenade
	CStreaming::SetModelIsDeletable(264);
	CStreaming::SetModelIsDeletable(274);
	CStreaming::SetModelIsDeletable(282);
	CStreaming::SetModelIsDeletable(279);
	CStreaming::SetModelIsDeletable(284);
	CStreaming::SetModelIsDeletable(280);
	CStreaming::SetModelIsDeletable(285);
	CStreaming::SetModelIsDeletable(287);
	CStreaming::SetModelIsDeletable(288);
	CStreaming::SetModelIsDeletable(272);
	CStreaming::SetModelIsDeletable(270);
}

void CPadHack::MoneyCheat()
{
	CWorld::Players[CWorld::PlayerInFocus].m_Money += 250000;
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT6"), true, false);
}

void CPadHack::HealthCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT3"), true, false);
	VCGlobals::FindPlayerPed()->health = static_cast<float>(CWorld::Players[CWorld::PlayerInFocus].maxHealth);
	if (CVehicle *vehicle = VCGlobals::FindPlayerVehicle()) {
		vehicle->health = 1000.0;
		if (!vehicle->type) {
			CDamageManager *damageManager = &vehicle->damageManager;
			damageManager->SetEngineStatus(0);
			damageManager->SetWheelStatus(0, 0);
			damageManager->SetWheelStatus(1, 0);
			damageManager->SetWheelStatus(2, 0);
			damageManager->SetWheelStatus(3, 0);
		}
	}
}

void CPadHack::WantedLevelUpCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT5"), true, false);
	CWanted *wanted = VCGlobals::FindPlayerPed()->wanted;
	int level = wanted->level + 2;
	if (level > 6) {
		level = 6;
	}
	wanted->SetWantedLevelCheat(level);
}

void CPadHack::WantedLevelDownCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT5"), true, false);
	CWanted *wanted = VCGlobals::FindPlayerPed()->wanted;
	wanted->SetWantedLevelCheat(0);
}

void CPadHack::TankCheat()
{
	VCGlobals::VehicleCheat(CAR_RHINO);
}

void CPadHack::BlowUpCarsCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	for (int i = 0; i < CPools::ms_pVehiclePool->totalCount; i++) {
		if ((CPools::ms_pVehiclePool->flags[i] & 0x80) != 0x80) {
			CVehicle *vehicle = &CPools::ms_pVehiclePool->entities[i];
			if (vehicle) {
				auto BlowUpCar = (void(__thiscall *)(CVehicle *, int))*(unsigned long *)(vehicle->vtbl + 0x80);
				BlowUpCar(vehicle, 0);
			}
		}
	}
}

void CPadHack::WeaponsForAllCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	CPopulation::ms_bGivePedsWeapons = !CPopulation::ms_bGivePedsWeapons;
}

void CPadHack::FastTimeCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	if (CTimer::ms_fTimeScale < 4.0) {
		CTimer::ms_fTimeScale *= 2;
	}
}

void CPadHack::SlowTimeCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	if (CTimer::ms_fTimeScale > 0.25) {
		CTimer::ms_fTimeScale /= 2;
	}
}

void CPadHack::ArmourCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT4"), true, false);
	VCGlobals::FindPlayerPed()->armour = static_cast<float>(CWorld::Players[CWorld::PlayerInFocus].maxArmour);
}

void CPadHack::SunnyWeatherCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT7"), true, false);
	CWeather::ForceWeatherNow(0);
}

void CPadHack::CloudyWeatherCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT7"), true, false);
	CWeather::ForceWeatherNow(1);
}

void CPadHack::RainyWeatherCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT7"), true, false);
	CWeather::ForceWeatherNow(2);
}

void CPadHack::FoggyWeatherCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT7"), true, false);
	CWeather::ForceWeatherNow(3);
}

void CPadHack::FastWeatherCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	VCGlobals::gbFastTime = !VCGlobals::gbFastTime;
}

void CPadHack::OnlyRenderWheelsCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	CVehicle::bWheelsOnlyCheat = !CVehicle::bWheelsOnlyCheat;
}

void CPadHack::ChittyChittyBangBangCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	CVehicle::bAllDodosCheat = !CVehicle::bAllDodosCheat;
}

void CPadHack::StrongGripCheat()
{
	CHud::SetHelpMessage(VCGlobals::TheText.Get("CHEAT1"), true, false);
	CVehicle::bCheat3 = !CVehicle::bCheat3;
}

void CPadHack::AddToCheatStringHack(char key)
{
	this->AddToPCCheatString(key);
	if (VCGlobals::strncmp("SNUGSNUGSNUG", KeyBoardCheatString, 12) == 0) {
		WeaponCheat();
	} else if (VCGlobals::strncmp("NAMHCIRAEREWIFI", KeyBoardCheatString, 15) == 0) {
		MoneyCheat();
	} else if (VCGlobals::strncmp("TIEHDNUSEG", KeyBoardCheatString, 10) == 0) {
		HealthCheat();
	} else if (VCGlobals::strncmp("ESAELPECILOPEROM", KeyBoardCheatString, 16) == 0) {
		WantedLevelUpCheat();
	} else if (VCGlobals::strncmp("ESAELPECILOPON", KeyBoardCheatString, 14) == 0) {
		WantedLevelDownCheat();
	} else if (VCGlobals::strncmp("KNATASUEVIG", KeyBoardCheatString, 11) == 0) {
		TankCheat();
	} else if (VCGlobals::strncmp("GNABGNABGNAB", KeyBoardCheatString, 12) == 0) {
		BlowUpCarsCheat();
	} else if (VCGlobals::strncmp("PUGNISSERDEKILI", KeyBoardCheatString, 15) == 0) {
		// ChangePlayerCheat
	} else if (VCGlobals::strncmp("DAAAMGNIOGLLASTI", KeyBoardCheatString, 16) == 0) {
		// MayhemCheat
	} else if (VCGlobals::strncmp("EMSEKILYDOBON", KeyBoardCheatString, 13) == 0) {
		// EverybodyAttacksPlayerCheat
	} else if (VCGlobals::strncmp("LLAROFSNOPAEW", KeyBoardCheatString, 13) == 0) {
		WeaponsForAllCheat();
	} else if (VCGlobals::strncmp("UOYNEHWSEILFEMIT", KeyBoardCheatString, 16) == 0) {
		FastTimeCheat();
	} else if (VCGlobals::strncmp("GNIROOOOOB", KeyBoardCheatString, 10) == 0) {
		SlowTimeCheat();
	} else if (VCGlobals::strncmp("ESIOTRUT", KeyBoardCheatString, 8) == 0) { // 1.0
		ArmourCheat();
	} else if (VCGlobals::strncmp("ESIOTROT", KeyBoardCheatString, 8) == 0) { // 1.1
		ArmourCheat();
	} else if (VCGlobals::strncmp("EMROFRECNACNIKS", KeyBoardCheatString, 15) == 0) {
		SunnyWeatherCheat();
	} else if (VCGlobals::strncmp("DNALTOCSEKILI", KeyBoardCheatString, 13) == 0) {
		CloudyWeatherCheat();
	} else if (VCGlobals::strncmp("DNALTOCSEVOLI", KeyBoardCheatString, 13) == 0) {
		RainyWeatherCheat();
	} else if (VCGlobals::strncmp("PUOSAEP", KeyBoardCheatString, 7) == 0) {
		FoggyWeatherCheat();
	} else if (VCGlobals::strncmp("REHTAEWDAM", KeyBoardCheatString, 10) == 0) {
		FastWeatherCheat();
	} else if (VCGlobals::strncmp("SLEEHWFOTESECINA", KeyBoardCheatString, 16) == 0) {
		OnlyRenderWheelsCheat();
	} else if (VCGlobals::strncmp("BBYTTIHCYTTIHC", KeyBoardCheatString, 14) == 0) {
		ChittyChittyBangBangCheat();
	} else if (VCGlobals::strncmp("DAMEKILSRENROC", KeyBoardCheatString, 14) == 0) {
		StrongGripCheat();
	} else if (VCGlobals::strncmp("TAEHCSBMILYTSAN", KeyBoardCheatString, 15) == 0) {
		// NastyLimbsCheat
	}
}

void __declspec(naked) UpdatePedCount()
{
	__asm
	{
		xor edx, edx              // zero edx
		mov bx, 11                // divisor
		div bx                    // divide ax by 11 -> quotient = ax, remainder = dx
		lea eax, weaponsForAllArr // get base address of weapons array
		add eax, edx              // add remainder to address
		movzx ebx, byte ptr [eax] // get array element to use as weapon number
		jmp updatePedCountEndJump
	}
}
