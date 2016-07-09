#include "CPadHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"

static void AddToCheatString();
static void UpdatePedCount();
unsigned long addToCheatEndJump = vcversion::AdjustOffset(0x004ACF2D);
unsigned long updatePedCountEndJump = vcversion::AdjustOffset(0x0053B6ED);
unsigned long cipherFunction = vcversion::AdjustOffset(0x004ACF60);
unsigned long recentKeys = vcversion::AdjustOffset(0x00A10942);
char *weaponCheatString = "VS\\H`iXNTYbO";
char *moneyCheatString = "QFTIPdUHF]R_PfV";
char *healthCheatString = "WNLIQiXZFR";
char *wantedCheatString = "HXHFYkHJJW\\XLr\\S";
char *notWantedCheatString = "HXHFYkHJJW\\XVn";
char *tankCheatString = "NSHUNnXLWTT";
char *blowUpCarsCheatString = "JSHCTiDIHYNJ";
char *dressingUpCheatString = "SZNOVnVLSORSPlV";
char *mayhemCheatString = "GFHBZbQPPRYTHsaO";
char *everybodyAttacksPlayerCheatString = "HRZFXdO`EZOWU";
char *armEverybodyCheatString = "OQHS\\aVUP[NM^";
char *fastTimeCheatString = "XT`ORcZZFTYNLmVZ";
char *slowTimeCheatString = "JSPS\\jRVPM";
char *armourCheatString = "HXPPamX[";
char *armourFixedCheatString = "HXPPamR[";
char *sunnyWeatherCheatString = "HRYPSmHJOLPVPk`";
char *cloudyWeatherCheatString = "GSHMajFZFVVTP";
char *rainyWeatherCheatString = "GSHMajFZFa\\TP";
char *foggyWeatherCheatString = "SZVTN`S";
char *timeTravelCheatString = "UJOUN`ZKBX";
char *wheelsOnlyCheatString = "VQLFUrIVUP`MJi[G";
char *flyboyCheatString = "EG`UadKJZ_aQOc";
char *gripCheatString = "GFTFXdOZSP[ZVc";
char *goreCheatString = "WFLIPnETJWf\\Za[";
char *skinnyCheatString = "UJTNNmJVS[";
char weaponsForAll[12] = { 6, 17, 23, 21, 25, 26, 28, 30, 31, 15, 12, 0 };

bool CPadHack::initialise()
{
	// allow for additional cheats
	call(0x004ACF28, &AddToCheatString, PATCH_JUMP);

	// remove cheat warning
	call(0x004990AD, 0x004990C0, PATCH_JUMP);

	// modified weapon set for arm everybody cheat
	call(0x0053B6B9, &UpdatePedCount, PATCH_JUMP);
	return true;
}

void CPadHack::WeaponCheat()
{
	char gxtKey[8] = "CHEAT2";
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
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::MoneyCheat()
{
	char gxtKey[8] = "CHEAT6";
	CWorld::Players->m_Money += 250000;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::HealthCheat()
{
	char gxtKey[8] = "CHEAT3";
	float maxHealth = (float)*(unsigned char *)vcversion::AdjustOffset(0x0094AE6B);
	VCGlobals::FindPlayerPed()->health = maxHealth;
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
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::WantedCheat()
{
	char gxtKey[8] = "CHEAT5";
	CWanted *wanted = VCGlobals::FindPlayerPed()->wanted;
	int level = wanted->level + 2;
	if (level > 6) {
		level = 6;
	}
	wanted->SetWantedLevelCheat(level);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::NotWantedCheat()
{
	char gxtKey[8] = "CHEAT5";
	CWanted *wanted = VCGlobals::FindPlayerPed()->wanted;
	wanted->SetWantedLevelCheat(0);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::TankCheat()
{
	auto VehicleCheat = (void(__cdecl *)(int))vcversion::AdjustOffset(0x004AE8F0);
	VehicleCheat(162);
}

void CPadHack::BlowUpCarsCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned int vehicles = *(unsigned int *)vcversion::AdjustOffset(0x00A0FDE4);
	unsigned int vehicleObjects = *(unsigned int *)vehicles; // pointer to entity array of vehicles
	unsigned int vehicleValidities = *(unsigned int *)(vehicles + 4); // pointer to char array of valid and invalid vehicles
	int numberOfVehicles = *(int *)(vehicles + 8); // number of vehicles
	for (int i = 0; i < numberOfVehicles; i++) {
		if (((*(char *)(vehicleValidities + i)) & 0x80) != 0x80) { // is vehicle in array valid
			unsigned long *vehicle = (unsigned long *)(vehicleObjects + i * 0x5DC); // pointer to vehicle
			if (vehicle) {
				auto BlowUpCar = (void(__thiscall *)(unsigned long *, int))*(unsigned long *)(*vehicle + 0x80);
				BlowUpCar(vehicle, 0);
			}
		}
	}
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::ArmEverybodyCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned char &c = *(unsigned char *)vcversion::AdjustOffset(0x00A10AB3);
	c = c == 0 ? 1 : 0;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::FastTimeCheat()
{
	char gxtKey[8] = "CHEAT1";
	if (VCGlobals::timeScale < 4.0) {
		VCGlobals::timeScale *= 2;
	}
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::SlowTimeCheat()
{
	char gxtKey[8] = "CHEAT1";
	if (VCGlobals::timeScale > 0.25) {
		VCGlobals::timeScale /= 2;
	}
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::ArmourCheat()
{
	char gxtKey[8] = "CHEAT4";
	float maxArmour = (float)*(unsigned char *)vcversion::AdjustOffset(0x0094AE6C);
	VCGlobals::FindPlayerPed()->armour = maxArmour;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::SunnyWeatherCheat()
{
	char gxtKey[8] = "CHEAT7";
	CWeather::ForceWeatherNow(0);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::CloudyWeatherCheat()
{
	char gxtKey[8] = "CHEAT7";
	CWeather::ForceWeatherNow(1);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::RainyWeatherCheat()
{
	char gxtKey[8] = "CHEAT7";
	CWeather::ForceWeatherNow(2);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::FoggyWeatherCheat()
{
	char gxtKey[8] = "CHEAT7";
	CWeather::ForceWeatherNow(3);
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::TimeTravelCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned char &c = *(unsigned char *)vcversion::AdjustOffset(0x00A10B87);
	c = c == 0 ? 1 : 0;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::WheelsOnlyCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned char &c = *(unsigned char *)vcversion::AdjustOffset(0x00A10B30);
	c = c == 0 ? 1 : 0;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::FlyboyCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned char &c = *(unsigned char *)vcversion::AdjustOffset(0x00A10B28);
	c = c == 0 ? 1 : 0;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
}

void CPadHack::GripCheat()
{
	char gxtKey[8] = "CHEAT1";
	unsigned char &c = *(unsigned char *)vcversion::AdjustOffset(0x00A10B0F);
	c = c == 0 ? 1 : 0;
	CHud::SetHelpMessage(VCGlobals::TheText.Get(gxtKey), true, false);
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
		push wantedCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz notWanted
		call CPadHack::WantedCheat
		jmp end
	notWanted:
		push notWantedCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz tank
		call CPadHack::NotWantedCheat
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
		jnz armEverybody
		jmp end
	armEverybody:
		push armEverybodyCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz fastTime
		call CPadHack::ArmEverybodyCheat
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
		jnz timeTravel
		call CPadHack::FoggyWeatherCheat
		jmp end
	timeTravel:
		push timeTravelCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz wheelsOnly
		call CPadHack::TimeTravelCheat
		jmp end
	wheelsOnly:
		push wheelsOnlyCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz flyboy
		call CPadHack::WheelsOnlyCheat
		jmp end
	flyboy:
		push flyboyCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz grip
		call CPadHack::FlyboyCheat
		jmp end
	grip:
		push gripCheatString
		push recentKeys
		call cipherFunction
		test al, al
		pop ecx
		pop ecx
		jnz end
		call CPadHack::GripCheat
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
		lea eax, weaponsForAll    // get base address of weapons array
		add eax, edx              // add remainder to address
		movzx ebx, byte ptr [eax] // get array element to use as weapon number
		jmp updatePedCountEndJump
	}
}
