#include "CRunningScriptHack.h"
#include "CPagerHack.h"
#include "CScrollBarHack.h"
#include "CCranesHack.h"
#include "CExplosionHack.h"
#include "CProjectileInfoHack.h"
#include "CPacManPickupsHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <Windows.h>

using namespace VCGlobals;

unsigned long *ProcessOneCommandHackAddr = reinterpret_cast<unsigned long *>(vcversion::AdjustOffset(0x0044FDB6));

// GetRandomCarOfTypeInAreaNoSave
static void GetRandomCarOfTypeInAreaNoSave();
unsigned long getRandomCarProceedJump = vcversion::AdjustOffset(0x0062F23D);
unsigned long getRandomCarEndJump = vcversion::AdjustOffset(0x0062F269);

// GangsInitialise
static void GangsInitialise();
unsigned long gangInitialiseEndJump = vcversion::AdjustOffset(0x004EEEDF);

// GameLogicUpdate
static void GameLogicUpdate();
unsigned long gameLogicUpdateEndJump = vcversion::AdjustOffset(0x0042BC6D);

// AutomobilePreRender
static void AutomobilePreRender();
unsigned long preRenderMatchAmbulan = vcversion::AdjustOffset(0x0058BE77);
unsigned long preRenderMatchFbiranch = vcversion::AdjustOffset(0x0058C8F0);
unsigned long preRenderNoMatch = vcversion::AdjustOffset(0x0058BE34);

// RenderReflections
float RenderReflections();

// CarCtrlReInit
void CarCtrlReInit();

// CivilianAI
void CivilianAI();
unsigned long civilianAIValidPed = vcversion::AdjustOffset(0x004E94E6);
unsigned long civilianAIInvalidPed = vcversion::AdjustOffset(0x004E9555);

// center mouse (SilentPatch)
static bool bGameInFocus = true;
static LRESULT(CALLBACK **OldWndProc)(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KILLFOCUS:
		bGameInFocus = false;
		break;
	case WM_SETFOCUS:
		bGameInFocus = true;
		break;
	}

	return (*OldWndProc)(hwnd, uMsg, wParam, lParam);
}
static auto* pCustomWndProc = CustomWndProc;
void ResetMousePos()
{
	if (bGameInFocus) {
		RwV2d vecPos = { resolutionX * 0.5f, resolutionY * 0.5f };
		RsMouseSetPos(&vecPos);
	}
	CRenderer::ConstructRenderList();
}

int CRunningScriptHack::debugMode;

bool CRunningScriptHack::initialise()
{
	//Memory is protected from write (write protection of .text section removed at startup)
	union { bool (CRunningScriptHack::*func)(); unsigned long offset; } nasty = { &ProcessOneCommandHack };
	*ProcessOneCommandHackAddr = nasty.offset - reinterpret_cast<unsigned long>(ProcessOneCommandHackAddr + 1);

	// detonator weapon switch
	Patch<unsigned char>(0x005D49C7, 0xD);
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x005345ED)), 0x90, 9);

	// 0410 (Purple Nines) fix
	InjectHook(0x004EEED1, &GangsInitialise, PATCH_JUMP);

	// 053E accept mission vehicles - workaround for crusher
	InjectHook(0x0062F234, &GetRandomCarOfTypeInAreaNoSave, PATCH_JUMP);

	// horizon ships
	if (!(CRunningScriptHack::debugMode & DEBUG_VICECITY)) {
		Patch<unsigned short>(0x005BC5BC, 0xE990);
	}

	// cylindrical marker colors
	Patch<unsigned int>(0x00458E82, 0x000080); // CTheScripts::DrawScriptSpheres
	Patch<unsigned int>(0x00689CA8, 0xFF8000);
	Patch<unsigned int>(0x00568E45, 0x000080); // CShadows::RenderIndicatorShadow
	Patch<unsigned int>(0x00698D58, 0xFF8000);
	Patch<unsigned int>(0x004C3F99, 0x000080); // CRadar::Draw3dMarkers
	Patch<unsigned int>(0x0068F958, 0xFF8000);

	// undo ocean change
	Patch<float>(0x69CD70, 70.0);

	// taxi cash
	Patch<unsigned char>(0x005B8AB6, 25); // CVehicle::SetDriver

	// hospital cost
	InjectHook(0x0042BC64, &GameLogicUpdate, PATCH_JUMP); // CGameLogic::Update

	// FBI Rancher roof light
	InjectHook(0x0058BE2F, &AutomobilePreRender, PATCH_JUMP); // CAutomobile::PreRender

	// fire light glow (SilentPatch)
	Patch<unsigned char>(0x0048EB27, 0x10); // CFire::ProcessFire
	
	// wet roads reflection (SilentPatch)
	InjectHook(0x005433BD, &RenderReflections);

	// support treadables
	Patch<unsigned int>(0x004C0325, 0x4068006A);
	Patch<unsigned int>(0x004C0329, 0xE800001F);

	// reinit firetruck/ambulance timer (SilentPatch)
	InjectHook(0x004A489B, &CarCtrlReInit);

	// investigate ped crash fix
	InjectHook(0x004E94E0, &CivilianAI, PATCH_JUMP);

	// center mouse (SilentPatch)
	InjectHook(0x004A5E45, &ResetMousePos);
	OldWndProc = *(LRESULT(CALLBACK***)(HWND, UINT, WPARAM, LPARAM))vcversion::AdjustOffset(0x00601727);
	Patch(0x00601727, &pCustomWndProc);

	return true;
}

bool CRunningScriptHack::ProcessOneCommandHack()
{
	CTheScripts::CommandsExecuted++;
	short opCode = MAKEWORD(CTheScripts::ScriptSpace[this->m_dwScriptIP], CTheScripts::ScriptSpace[this->m_dwScriptIP + 1]);
	m_dwScriptIP += 2;
	this->m_bNotFlag = opCode < 0;
	short opCodeNum = opCode & 0x7FFF;

	switch (opCodeNum)
	{
	case 0x014D:
		return this->_014D_text_pager();
	case 0x034A:
		return this->_034A_industrial_passed();
	case 0x034B:
		return this->_034B_commercial_passed();
	case 0x034C:
		return this->_034C_suburban_passed();

	// additional opcodes
	case 0x01EE:
		return this->_01EE_activate_crane();
	case 0x01EF:
		return this->_01EF_deactivate_crane();
	case 0x024C:
		return this->_024C_set_phone_message();
	case 0x02BD:
		return this->_02BD_is_debug_mode(); // custom opcode
	case 0x02FB:
		return this->_02FB_activate_crusher_crane();
	case 0x0351:
		return this->_0351_is_nasty_game();
	case 0x0356:
		return this->_0356_is_explosion_in_area();
	case 0x0368:
		return this->_0368_activate_military_crane();
	case 0x03A0:
		return this->_03A0_is_crane_lifting_car();
	case 0x03C2:
		return this->_03C2_is_phone_displaying_message();
	case 0x03EC:
		return this->_03EC_has_military_crane_collected_all_cars();
	case 0x0410:
		return this->_0410_set_gang_ped_model_preference();
	case 0x0421:
		return this->_0421_force_rain();
	case 0x0422:
		return this->_0422_does_garage_contain_car();
	case 0x042A:
		return this->_042A_is_threat_for_ped_type();
	case 0x0444:
		return this->_0444_set_script_fire_audio();
	case 0x0447:
		return this->_0447_is_player_lifting_a_phone();

	case 0x00AC:
		return this->_00AC_is_car_still_alive();
	case 0x0130:
		return this->_0130_has_player_been_arrested();
	case 0x0178:
		return this->_0178_is_player_touching_object();
	case 0x021D:
		return this->_021D_set_free_bombs();
	case 0x0228:
		return this->_0228_is_car_armed_with_bomb();
	case 0x0240:
		return this->_0240_flash_object();
	case 0x0242:
		return this->_0242_arm_car_with_bomb();
	case 0x0255:
		return this->_0255_restart_critical_mission();
	case 0x0299:
		return this->_0299_activate_garage();
	case 0x029C:
		return this->_029C_is_boat();
	case 0x02A0:
		return this->_02A0_is_char_stopped();
	case 0x02B9:
		return this->_02B9_deactivate_garage();
	case 0x02C3:
		return this->_02C3_start_pacman_race();
	case 0x02C5:
		return this->_02C5_get_number_of_power_pills_eaten();
	case 0x02C6:
		return this->_02C6_clear_pacman();
	case 0x02C7:
		return this->_02C7_start_pacman_scramble();
	case 0x02C8:
		return this->_02C8_get_number_of_power_pills_carried();
	case 0x02C9:
		return this->_02C9_clear_number_of_power_pills_carried();
	case 0x02D9:
		return this->_02D9_clear_number_of_power_pills_eaten();
	case 0x02EE:
		return this->_02EE_is_projectile_in_area();
	case 0x02EF:
		return this->_02EF_destroy_projectiles_in_area();
	case 0x02F0:
		return this->_02F0_drop_mine();
	case 0x02F1:
		return this->_02F1_drop_nautical_mine();
	case 0x032D:
		return this->_032D_set_car_block_car();
	case 0x03A5:
		return this->_03A5_change_garage_type_with_car_model();
	case 0x03C9:
		return this->_03C9_is_car_visibly_damaged();
	case 0x03FB:
		return this->_03FB_set_car_stays_in_current_level();
	case 0x03FC:
		return this->_03FC_set_char_stays_in_current_level();
	case 0x041F:
		return this->_041F_override_hospital_level();
	case 0x0420:
		return this->_0420_override_police_station_level();
	case 0x0438:
		return this->_0438_set_char_ignore_level_transitions();
	case 0x044E:
		return this->_044E_set_car_ignore_level_transitions();
	case 0x044F:
		return this->_044F_make_craigs_car_a_bit_stronger();
	case 0x0452:
		return this->_0452_enable_player_control_camera();
	}

	CTheScripts::CommandsExecuted--;
	m_dwScriptIP -= 2;
	// Call VC's CRunningScript::ProcessOneCommand
	return ProcessOneCommand();
}

bool CRunningScriptHack::_014D_text_pager()
{
	char pagerText[8];
	
	VCGlobals::strcpy(pagerText, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]));
	this->m_dwScriptIP += 8;
	
	this->CollectParameters(&this->m_dwScriptIP, 3);

	wchar_t *scmPagerText = TheText.Get(pagerText);

	CPagerHack *pager = reinterpret_cast<CPagerHack *>(&CUserDisplay::Pager); //YUCKY YUCKY!!! but it'll do the job
	pager->AddMessage(scmPagerText, ScriptParams[0].uint16, ScriptParams[1].uint16, ScriptParams[2].uint16);
	
	return 0;
}

bool CRunningScriptHack::_034A_industrial_passed()
{
	CStats::IndustrialPassed = 1;
	VCGlobals::DMAudio.PlayRadioAnnouncement(25); // must match COMopen.wav in gta-lc.ini
	return 0;
}

bool CRunningScriptHack::_034B_commercial_passed()
{
	CStats::CommercialPassed = 1;
	VCGlobals::DMAudio.PlayRadioAnnouncement(26); // must match SUBopen.wav in gta-lc.ini
	return 0;
}

bool CRunningScriptHack::_034C_suburban_passed()
{
	CStats::SuburbanPassed = 1;
	return 0;
}

bool CRunningScriptHack::_01EE_activate_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, false, false, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_01EF_deactivate_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CCranesHack::DeActivateCrane(ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_024C_set_phone_message()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	char text[8];
	VCGlobals::strncpy(text, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]), 8);
	this->m_dwScriptIP += 8;
	VCGlobals::ThePhoneInfo.SetPhoneMessage_JustOnce(ScriptParams[0].int32, TheText.Get(text), 0, 0, 0, 0, 0);
	return 0;
}

bool CRunningScriptHack::_02BD_is_debug_mode()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(!!(debugMode & ScriptParams[0].int32));
	return 0;
}

bool CRunningScriptHack::_02FB_activate_crusher_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, true, false, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_0351_is_nasty_game()
{
	this->UpdateCompareFlag(*(bool *)vcversion::AdjustOffset(0x68DD68));
	return 0;
}

bool CRunningScriptHack::_0356_is_explosion_in_area()
{
	this->CollectParameters(&this->m_dwScriptIP, 7);
	this->UpdateCompareFlag(CExplosionHack::TestForExplosionInArea(ScriptParams[0].int32, ScriptParams[1].float32, ScriptParams[4].float32, ScriptParams[2].float32, ScriptParams[5].float32, ScriptParams[3].float32, ScriptParams[6].float32));
	return 0;
}

bool CRunningScriptHack::_0368_activate_military_crane()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	float temp;
	if (ScriptParams[2].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	if (ScriptParams[3].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[3].float32;
		ScriptParams[3].float32 = temp;
	}
	ScriptParams[9].float32 = ScriptParams[9].float32 * 3.1415927f * 5.5555557e-3f;
	CCranesHack::ActivateCrane(ScriptParams[2].float32, ScriptParams[4].float32, ScriptParams[3].float32, ScriptParams[5].float32, ScriptParams[6].float32, ScriptParams[7].float32, ScriptParams[8].float32, ScriptParams[9].float32, false, true, ScriptParams[0].float32, ScriptParams[1].float32);
	return 0;
}

bool CRunningScriptHack::_03A0_is_crane_lifting_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	this->UpdateCompareFlag(CCranesHack::IsThisCarPickedUp(ScriptParams[0].float32, ScriptParams[1].float32, CPools::ms_pVehiclePool->GetAt(ScriptParams[2].int32)));
	return 0;
}

bool CRunningScriptHack::_03C2_is_phone_displaying_message()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag((unsigned long)&VCGlobals::ThePhoneInfo.phones[ScriptParams[0].int32] == *(unsigned long *)vcversion::AdjustOffset(0x007030E8));
	return 0;
}

bool CRunningScriptHack::_03EC_has_military_crane_collected_all_cars()
{
	this->UpdateCompareFlag(CCranes::CarsCollectedMilitaryCrane == MILITARYCRANETOTAL);
	return 0;
}

bool CRunningScriptHack::_0410_set_gang_ped_model_preference()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	*(BYTE *)(ScriptParams[0].int32 * 0x18 + vcversion::AdjustOffset(0x7D925C)) = (BYTE)ScriptParams[1].int32;
	return 0;
}

bool CRunningScriptHack::_0421_force_rain()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CWeather::bScriptsForceRain = !!ScriptParams[0].int32;
	return 0;
}

bool CRunningScriptHack::_0422_does_garage_contain_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[1].int32);
	this->UpdateCompareFlag(vehicle && CGarages::garages[ScriptParams[0].int32].IsEntityEntirelyInside3D(vehicle, 0.0));
	return 0;
}

bool CRunningScriptHack::_042A_is_threat_for_ped_type()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	this->UpdateCompareFlag(ScriptParams[1].int32 == (*(int *)(*(DWORD *)(vcversion::AdjustOffset(0xA0DA64) + ScriptParams[0].int32 * 4) + 0x18) & ScriptParams[1].int32));
	return 0;
}

bool CRunningScriptHack::_0444_set_script_fire_audio()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CFireManager::fires[ScriptParams[0].int32].sfx = !!ScriptParams[1].int32;
	return 0;
}

bool CRunningScriptHack::_0447_is_player_lifting_a_phone()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(CWorld::Players[ScriptParams[0].int32].playerEntity->state == 0x13);
	return 0;
}

void __declspec(naked) GetRandomCarOfTypeInAreaNoSave()
{
	__asm
	{
		cmp byte ptr [ebx+1F8h], 1 // is traffic vehicle
		jz proceed
		cmp byte ptr [ebx+1F8h], 2 // is mission vehicle
		jz proceed
		jmp getRandomCarEndJump
	proceed:
		jmp getRandomCarProceedJump
	}
}

void GangsInitialise()
{
	for (int i = 0; i < 8 * 0x18; i += 0x18) {
		*(BYTE *)(i + vcversion::AdjustOffset(0x7D925C)) = 255;
	}
}

void __declspec(naked) GameLogicUpdate()
{
	__asm
	{
		mov eax, dword ptr [ebx+0A0h] // get current cash
		add eax, 0FFFFFC18h           // subtract 1000
		jmp gameLogicUpdateEndJump
	}
}

void __declspec(naked) AutomobilePreRender()
{
	__asm
	{
		sub ecx, 9 // ambulan
		jz matchAmbulan
		dec ecx    // fbiranch
		jz matchFbiranch
		inc ecx    // resume before change
		jmp preRenderNoMatch
	matchAmbulan:
		jmp preRenderMatchAmbulan
	matchFbiranch:
		jmp preRenderMatchFbiranch
	}
}

float RenderReflections()
{
	return 1.0;
}

void CarCtrlReInit()
{
	CCarCtrl::ReInit();
	CCarCtrl::LastTimeFireTruckCreated = 0;
	CCarCtrl::LastTimeAmbulanceCreated = 0;
}

void __declspec(naked) CivilianAI()
{
	__asm
	{
		mov edx, dword ptr [ebp+1A0h] // get ped to investigate
		test edx, edx
		jz invalidPed
		jmp civilianAIValidPed
	invalidPed:
		jmp civilianAIInvalidPed
	}
}

bool CRunningScriptHack::_00AC_is_car_still_alive()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag((vehicle && (vehicle->status >> 3) != 5) && (vehicle->type == 1 || !(vehicle->field_11A & 0x10)));
	return 0;
}

bool CRunningScriptHack::_0130_has_player_been_arrested()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(CWorld::Players[ScriptParams[0].int32].deathArrestState == 2);
	return 0;
}

bool CRunningScriptHack::_0178_is_player_touching_object()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CObject *object = CPools::ms_pObjectPool->GetAt(ScriptParams[1].int32)) {
		CPlayerPed *player = CWorld::Players[ScriptParams[0].int32].playerEntity;
		CPhysical *source = player;
		if (player->isInAnyVehicle && player->vehicle) {
			source = player->vehicle;
		}
		this->UpdateCompareFlag(source->GetHasCollidedWith(object));
		return 0;
	}
	this->UpdateCompareFlag(false);
	return 0;
}

bool CRunningScriptHack::_021D_set_free_bombs()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CGarages::BombsAreFree = !!ScriptParams[0].int32;
	return 0;
}

bool CRunningScriptHack::_0228_is_car_armed_with_bomb()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(vehicle && (vehicle->bombState & 7) == ScriptParams[1].int32);
	return 0;
}

bool CRunningScriptHack::_0240_flash_object()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CObject *object = CPools::ms_pObjectPool->GetAt(ScriptParams[0].int32)) {
		object->field_052 &= 0xDF;
		if (ScriptParams[1].int32) {
			object->field_052 |= 0x20;
		}
	}
	return 0;
}

bool CRunningScriptHack::_0242_arm_car_with_bomb()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32)) {
		vehicle->bombState = (vehicle->bombState & 0xF8) | (((unsigned char)ScriptParams[1].int32) & 7);
		vehicle->bombOwner = VCGlobals::FindPlayerPed();
	}
	return 0;
}

bool CRunningScriptHack::_0255_restart_critical_mission()
{
	this->CollectParameters(&this->m_dwScriptIP, 4);
	if (ScriptParams[2].float32 <= -100.0) {
		ScriptParams[2].float32 = CWorld::FindGroundZForCoord(ScriptParams[0].float32, ScriptParams[1].float32);
	}
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	CRestart::OverrideNextRestart(pos, ScriptParams[3].float32);
	CPlayerInfo *player = &CWorld::Players[CWorld::PlayerInFocus];
	if (player->deathArrestState == 0) {
		player->deathArrestState = 3;
		player->timeDeathArrest = CTimer::m_snTimeInMilliseconds;
		CDarkel::ResetOnPlayerDeath();
	}
	return 0;
}

bool CRunningScriptHack::_0299_activate_garage()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CGarage *garage = &CGarages::garages[ScriptParams[0].int32];
	if (garage->type == 11 && garage->state == 0) {
		garage->state = 3;
	}
	garage->isInactive = 0;
	return 0;
}

bool CRunningScriptHack::_029C_is_boat()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(vehicle && vehicle->type == 1);
	return 0;
}

bool CRunningScriptHack::_02A0_is_char_stopped()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	if (CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32)) {
		if (ped->isInAnyVehicle) {
			CVehicle *vehicle = ped->vehicle;
			if (vehicle && vehicle->speed < CTimer::ms_fTimeStep * 0.01) {
				this->UpdateCompareFlag(true);
				return 0;
			}
		} else {
			if (ped->moveState <= 1) {
				this->UpdateCompareFlag(true);
				return 0;
			}
		}
	}
	this->UpdateCompareFlag(false);
	return 0;
}

bool CRunningScriptHack::_02B9_deactivate_garage()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CGarages::garages[ScriptParams[0].int32].isInactive = 1;
	return 0;
}

bool CRunningScriptHack::_02C3_start_pacman_race()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CPacManPickupsHack::StartPacManRace(ScriptParams[0].int32);
	return 0;
}

bool CRunningScriptHack::_02C5_get_number_of_power_pills_eaten()
{
	ScriptParams[0].int32 = CPacManPickupsHack::QueryPowerPillsEatenInRace();
	this->StoreParameters(&this->m_dwScriptIP, 1);
	return 0;
}

bool CRunningScriptHack::_02C6_clear_pacman()
{
	CPacManPickupsHack::CleanUpPacManStuff();
	return 0;
}

bool CRunningScriptHack::_02C7_start_pacman_scramble()
{
	this->CollectParameters(&this->m_dwScriptIP, 5);
	if (ScriptParams[2].float32 <= -100.0) {
		ScriptParams[2].float32 = CWorld::FindGroundZForCoord(ScriptParams[0].float32, ScriptParams[1].float32);
	}
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	CPacManPickupsHack::StartPacManScramble(pos, ScriptParams[3].float32, ScriptParams[4].int16);
	return 0;
}

bool CRunningScriptHack::_02C8_get_number_of_power_pills_carried()
{
	ScriptParams[0].int32 = CPacManPickupsHack::QueryPowerPillsCarriedByPlayer();
	this->StoreParameters(&this->m_dwScriptIP, 1);
	return 0;
}

bool CRunningScriptHack::_02C9_clear_number_of_power_pills_carried()
{
	CPacManPickupsHack::ResetPowerPillsCarriedByPlayer();
	return 0;
}

bool CRunningScriptHack::_02D9_clear_number_of_power_pills_eaten()
{
	CPacManPickupsHack::ResetPowerPillsEatenInRace();
	return 0;
}

bool CRunningScriptHack::_02EE_is_projectile_in_area()
{
	this->CollectParameters(&this->m_dwScriptIP, 6);
	float temp;
	if (ScriptParams[0].float32 > ScriptParams[3].float32) {
		temp = ScriptParams[3].float32;
		ScriptParams[3].float32 = ScriptParams[0].float32;
		ScriptParams[0].float32 = temp;
	}
	if (ScriptParams[1].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[1].float32;
		ScriptParams[1].float32 = temp;
	}
	if (ScriptParams[2].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	this->UpdateCompareFlag(CProjectileInfoHack::IsProjectileInRange(ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32, ScriptParams[3].float32, ScriptParams[4].float32, ScriptParams[5].float32, 0));
	return 0;
}

bool CRunningScriptHack::_02EF_destroy_projectiles_in_area()
{
	this->CollectParameters(&this->m_dwScriptIP, 6);
	float temp;
	if (ScriptParams[0].float32 > ScriptParams[3].float32) {
		temp = ScriptParams[3].float32;
		ScriptParams[3].float32 = ScriptParams[0].float32;
		ScriptParams[0].float32 = temp;
	}
	if (ScriptParams[1].float32 > ScriptParams[4].float32) {
		temp = ScriptParams[4].float32;
		ScriptParams[4].float32 = ScriptParams[1].float32;
		ScriptParams[1].float32 = temp;
	}
	if (ScriptParams[2].float32 > ScriptParams[5].float32) {
		temp = ScriptParams[5].float32;
		ScriptParams[5].float32 = ScriptParams[2].float32;
		ScriptParams[2].float32 = temp;
	}
	this->UpdateCompareFlag(CProjectileInfoHack::IsProjectileInRange(ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32, ScriptParams[3].float32, ScriptParams[4].float32, ScriptParams[5].float32, 1));
	return 0;
}

bool CRunningScriptHack::_02F0_drop_mine()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	if (ScriptParams[2].float32 <= -100.0) {
		ScriptParams[2].float32 = CWorld::FindGroundZForCoord(ScriptParams[0].float32, ScriptParams[1].float32) + 0.5f;
	}
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	CPickups::GenerateNewOne(pos, VCGlobals::MI_CARMINE, 9, 0, 0, 0, 0);
	return 0;
}

bool CRunningScriptHack::_02F1_drop_nautical_mine()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	if (ScriptParams[2].float32 <= -100.0) {
		ScriptParams[2].float32 = CWorld::FindGroundZForCoord(ScriptParams[0].float32, ScriptParams[1].float32) + 0.5f;
	}
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	CPickups::GenerateNewOne(pos, VCGlobals::MI_NAUTICALMINE, 11, 0, 0, 0, 0);
	return 0;
}

bool CRunningScriptHack::_032D_set_car_block_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	CVehicle *target = CPools::ms_pVehiclePool->GetAt(ScriptParams[1].int32);
	vehicle->targetEntity = target;
	target->RegisterReference(&vehicle->targetEntity);
	vehicle->targetBehavior = 0x11;
	vehicle->field_1F9 &= 0xEF;
	vehicle->field_1F9 |= 0x10;
	if (vehicle->cruiseSpeed < 6) {
		vehicle->cruiseSpeed = 6;
	}
	return 0;
}

bool CRunningScriptHack::_03A5_change_garage_type_with_car_model()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	CGarages::ChangeGarageType(ScriptParams[0].int16, ScriptParams[1].int8, ScriptParams[2].int32);
	return 0;
}

bool CRunningScriptHack::_03C9_is_car_visibly_damaged()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(vehicle && (vehicle->field_1FB & 2));
	return 0;
}

bool CRunningScriptHack::_03FB_set_car_stays_in_current_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32)) {
		vehicle->originLevel = ScriptParams[1].int32 ? (char)CTheZones::GetLevelFromPosition(&vehicle->GetPos()) : 0;
	}
	return 0;
}

bool CRunningScriptHack::_03FC_set_char_stays_in_current_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32)) {
		ped->originLevel = ScriptParams[1].int32 ? (char)CTheZones::GetLevelFromPosition(&ped->GetPos()) : 0;
	}
	return 0;
}

bool CRunningScriptHack::_041F_override_hospital_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CRestart::OverrideHospitalLevel = ScriptParams[0].uint8;
	return 0;
}

bool CRunningScriptHack::_0420_override_police_station_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CRestart::OverridePoliceStationLevel = ScriptParams[0].uint8;
	return 0;
}

bool CRunningScriptHack::_0438_set_char_ignore_level_transitions()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32)) {
		ped->originLevel = ScriptParams[1].int32 ? -1 : (char)CTheZones::GetLevelFromPosition(&ped->GetPos());
	}
	return 0;
}

bool CRunningScriptHack::_044E_set_car_ignore_level_transitions()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32)) {
		vehicle->originLevel = ScriptParams[1].int32 ? -1 : (char)CTheZones::GetLevelFromPosition(&vehicle->GetPos());
	}
	return 0;
}

bool CRunningScriptHack::_044F_make_craigs_car_a_bit_stronger()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	if (CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32)) {
		vehicle->field_501 &= 0xDF;
		if (ScriptParams[1].int32) {
			vehicle->field_501 |= 0x20;
		}
	}
	return 0;
}

bool CRunningScriptHack::_0452_enable_player_control_camera()
{
	*(unsigned short *)(CPad::GetPad(0) + 0xF0) &= 0xFFFE;
	return 0;
}
