#include "CPadHack.h"
#include "CRunningScriptHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Vehicles.h"

static void AddToCheatString();
static void UpdatePedCount();
unsigned long addToCheatEndJump = vcversion::AdjustOffset(0x004ACF2D);
unsigned long updatePedCountEndJump = vcversion::AdjustOffset(0x0053B6ED);
unsigned long cipherFunction = vcversion::AdjustOffset(0x004ACF60);
unsigned long recentKeys = vcversion::AdjustOffset(0x00A10942);
char *weaponCheatString = "VS\\H`iXNTYbO";
char *moneyCheatString = "QFTIPdUHF]R_PfV";
char *healthCheatString = "WNLIQiXZFR";
char *wantedLevelUpCheatString = "HXHFYkHJJW\\XLr\\S";
char *wantedLevelDownCheatString = "HXHFYkHJJW\\XVn";
char *tankCheatString = "NSHUNnXLWTT";
char *blowUpCarsCheatString = "JSHCTiDIHYNJ";
char *dressingUpCheatString = "SZNOVnVLSORSPlV";
char *mayhemCheatString = "GFHBZbQPPRYTHsaO";
char *everybodyAttacksPlayerCheatString = "HRZFXdO`EZOWU";
char *weaponsForAllCheatString = "OQHS\\aVUP[NM^";
char *fastTimeCheatString = "XT`ORcZZFTYNLmVZ";
char *slowTimeCheatString = "JSPS\\jRVPM";
char *armourCheatString = "HXPPamX[";
char *armourFixedCheatString = "HXPPamR[";
char *sunnyWeatherCheatString = "HRYPSmHJOLPVPk`";
char *cloudyWeatherCheatString = "GSHMajFZFVVTP";
char *rainyWeatherCheatString = "GSHMajFZFa\\TP";
char *foggyWeatherCheatString = "SZVTN`S";
char *fastWeatherCheatString = "UJOUN`ZKBX";
char *onlyRenderWheelsCheatString = "VQLFUrIVUP`MJi[G";
char *chittyChittyBangBangCheatString = "EG`UadKJZ_aQOc";
char *strongGripCheatString = "GFTFXdOZSP[ZVc";
char *goreCheatString = "WFLIPnETJWf\\Za[";
char *vehicleCheatString = "UFJSN^UHD";
char *vehicleReverseCheatString = "FFYDNmFHS";
char *skinnyCheatString = "UJTNNmJVS[";
char weaponsForAllArr[12] = { 6, 17, 23, 21, 25, 26, 28, 30, 31, 15, 12, 0 };
int vehicleModel = CAR_LANDSTAL;

char specialCharacters[10][8] =
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
	InjectHook(0x004ACF28, &AddToCheatString, PATCH_JUMP);

	// remove cheat warning
	InjectHook(0x004990AD, vcversion::AdjustOffset(0x004990C0), PATCH_JUMP);

	// modify weapon set for arm everybody cheat
	InjectHook(0x0053B6B9, &UpdatePedCount, PATCH_JUMP);

	// modify special character cheats
	Patch<unsigned long>(0x004ACA66, (unsigned long)&specialCharacters[0]); // igbuddy
	Patch<unsigned long>(0x004ACA96, (unsigned long)&specialCharacters[1]); // igcandy
	Patch<unsigned long>(0x004ACAC6, (unsigned long)&specialCharacters[2]); // igken
	Patch<unsigned long>(0x004ACAF6, (unsigned long)&specialCharacters[3]); // ighlary
	Patch<unsigned long>(0x004ACB26, (unsigned long)&specialCharacters[4]); // igjezz
	Patch<unsigned long>(0x004ACB56, (unsigned long)&specialCharacters[5]); // igphil
	Patch<unsigned long>(0x004ACB86, (unsigned long)&specialCharacters[6]); // igsonny
	Patch<unsigned long>(0x004ACD76, (unsigned long)&specialCharacters[7]); // igmerc
	Patch<unsigned long>(0x004ACDA6, (unsigned long)&specialCharacters[8]); // igdick
	Patch<unsigned long>(0x004ACEB6, (unsigned long)&specialCharacters[9]); // igdiaz

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
			CDamageManager *damageManager = (CDamageManager *)&(vehicle->damageManager);
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

void CPadHack::VehicleCheat()
{
	if (CRunningScriptHack::debugMode & DEBUG_MASTERDEBUG) {
		VCGlobals::VehicleCheat(vehicleModel++);
		if (vehicleModel == BOAT_RIO ||
			vehicleModel == BOAT_PREDATOR ||
			vehicleModel == BOAT_SQUALO ||
			vehicleModel == BIKE_PIZZABOY ||
			vehicleModel == BOAT_MARQUIS ||
			vehicleModel == BOAT_JETMAX) {
			vehicleModel++;
		}
		if (vehicleModel == HELI_CHOPPER ||
			vehicleModel == BOAT_GHOST) {
			vehicleModel += 2;
		}
		if (vehicleModel == CAR_BLISTAC) {
			vehicleModel += 3;
		}
		if (vehicleModel == BOAT_SKIMMER) {
			vehicleModel += 4;
		}
		if (vehicleModel == PLANE_AIRTRAIN) {
			vehicleModel += 5;
		}
		if (vehicleModel > CAR_VICECHEE) {
			vehicleModel = CAR_LANDSTAL;
		}
	}
}

void CPadHack::VehicleReverseCheat()
{
	if (CRunningScriptHack::debugMode & DEBUG_MASTERDEBUG) {
		VCGlobals::VehicleCheat(vehicleModel--);
		if (vehicleModel == BOAT_RIO ||
			vehicleModel == BOAT_PREDATOR ||
			vehicleModel == BOAT_SQUALO ||
			vehicleModel == BIKE_PIZZABOY ||
			vehicleModel == BOAT_MARQUIS ||
			vehicleModel == BOAT_JETMAX) {
			vehicleModel--;
		}
		if (vehicleModel == BIKE_ANGEL ||
			vehicleModel == BOAT_DINGHY) {
			vehicleModel -= 2;
		}
		if (vehicleModel == CAR_DELOFLY) {
			vehicleModel -= 3;
		}
		if (vehicleModel == BIKE_FREEWAY) {
			vehicleModel -= 4;
		}
		if (vehicleModel == BOAT_TROPIC) {
			vehicleModel -= 5;
		}
		if (vehicleModel < CAR_LANDSTAL) {
			vehicleModel = CAR_VICECHEE;
		}
	}
}

void __declspec(naked) AddToCheatString()
{
	__asm
	{
		push weaponCheatString    // second argument of cipher function
		push recentKeys           // first argument of cipher function
		call cipherFunction       // call cipher function
		test al, al               // true if both arguments match
		pop ecx
		pop ecx
		jnz money
		//mov ebx, recentKeys     // added in Vice City to prevent stringing of cheats
		//mov byte ptr [ebx], 20h
		call CPadHack::WeaponCheat
		jmp end
	money:
		push moneyCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz health
		call CPadHack::MoneyCheat
		jmp end
	health:
		push healthCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz wanted
		call CPadHack::HealthCheat
		jmp end
	wanted:
		push wantedLevelUpCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz notWanted
		call CPadHack::WantedLevelUpCheat
		jmp end
	notWanted:
		push wantedLevelDownCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz tank
		call CPadHack::WantedLevelDownCheat
		jmp end
	tank:
		push tankCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz blowUpCars
		call CPadHack::TankCheat
		jmp end
	blowUpCars:
		push blowUpCarsCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz dressingUp
		call CPadHack::BlowUpCarsCheat
		jmp end
	dressingUp:
		push dressingUpCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz mayhem
		jmp end
	mayhem:
		push mayhemCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz everybodyAttacksPlayer
		jmp end
	everybodyAttacksPlayer:
		push everybodyAttacksPlayerCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz weaponsForAll
		jmp end
	weaponsForAll:
		push weaponsForAllCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz fastTime
		call CPadHack::WeaponsForAllCheat
		jmp end
	fastTime:
		push fastTimeCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz slowTime
		call CPadHack::FastTimeCheat
		jmp end
	slowTime:
		push slowTimeCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz armour
		call CPadHack::SlowTimeCheat
		jmp end
	armour:
		push armourCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz armourFixed
		call CPadHack::ArmourCheat
		jmp end
	armourFixed:
		push armourFixedCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz sunnyWeather
		call CPadHack::ArmourCheat
		jmp end
	sunnyWeather:
		push sunnyWeatherCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz cloudyWeather
		call CPadHack::SunnyWeatherCheat
		jmp end
	cloudyWeather:
		push cloudyWeatherCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz rainyWeather
		call CPadHack::CloudyWeatherCheat
		jmp end
	rainyWeather:
		push rainyWeatherCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz foggyWeather
		call CPadHack::RainyWeatherCheat
		jmp end
	foggyWeather:
		push foggyWeatherCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz fastWeather
		call CPadHack::FoggyWeatherCheat
		jmp end
	fastWeather:
		push fastWeatherCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz onlyRenderWheels
		call CPadHack::FastWeatherCheat
		jmp end
	onlyRenderWheels:
		push onlyRenderWheelsCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz chittyChittyBangBang
		call CPadHack::OnlyRenderWheelsCheat
		jmp end
	chittyChittyBangBang:
		push chittyChittyBangBangCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz strongGrip
		call CPadHack::ChittyChittyBangBangCheat
		jmp end
	strongGrip:
		push strongGripCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz vehicle
		call CPadHack::StrongGripCheat
		jmp end
	vehicle:
		push vehicleCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz vehicleReverse
		call CPadHack::VehicleCheat
		jmp end
	vehicleReverse:
		push vehicleReverseCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz end
		call CPadHack::VehicleReverseCheat
	end:
		push skinnyCheatString
		jmp addToCheatEndJump
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
