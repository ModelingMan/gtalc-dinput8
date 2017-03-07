#include "CRunningScriptHack.h"
#include "CPagerHack.h"
#include "CScrollBarHack.h"
#include "CCranesHack.h"
#include "CExplosionHack.h"
#include "CProjectileInfoHack.h"
#include "CPacManPickupsHack.h"
#include "CObjectHack.h"
#include "CSpecialParticleStuffHack.h"
#include "CGameLogicHack.h"
#include "CRecordDataForChaseHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <Windows.h>
#include <math.h>

using namespace VCGlobals;

// GetRandomCarOfTypeInAreaNoSave
static void GetRandomCarOfTypeInAreaNoSave();
unsigned long getRandomCarProceedJump = vcversion::AdjustOffset(0x0062F23D);
unsigned long getRandomCarEndJump = vcversion::AdjustOffset(0x0062F269);

int CRunningScriptHack::debugMode;

bool CRunningScriptHack::initialise()
{
	auto function = &CRunningScriptHack::ProcessOneCommandHack;
	InjectHook(0x0044FDB5, (unsigned long &)function);

	// make 053E accept mission vehicles - workaround for crusher
	InjectHook(0x0062F234, &GetRandomCarOfTypeInAreaNoSave, PATCH_JUMP);

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
	case 0x14D:
		return this->_014D_text_pager();
	case 0x34A:
		return this->_034A_industrial_passed();
	case 0x34B:
		return this->_034B_commercial_passed();
	case 0x34C:
		return this->_034C_suburban_passed();

	// additional opcodes
	case 0x0A2:
		return this->_00A2_is_char_still_alive();
	case 0x135:
		return this->_0135_change_car_lock();
	case 0x16F:
		return this->_016F_draw_shadow();
	case 0x1EE:
		return this->_01EE_activate_crane();
	case 0x1EF:
		return this->_01EF_deactivate_crane();
	case 0x24C:
		return this->_024C_set_phone_message();
	case 0x250:
		return this->_0250_draw_light();
	case 0x2A1:
		return this->_02A1_message_wait();
	case 0x2A2:
		return this->_02A2_add_particle_effect();
	case 0x2BD:
		return this->_02BD_is_debug_mode();
	case 0x2CD:
		return this->_02CD_gosub_file();
	case 0x2FB:
		return this->_02FB_activate_crusher_crane();
	case 0x351:
		return this->_0351_is_nasty_game();
	case 0x356:
		return this->_0356_is_explosion_in_area();
	case 0x368:
		return this->_0368_activate_military_crane();
	case 0x37F:
		return this->_037F_give_player_detonator();
	case 0x3A0:
		return this->_03A0_is_crane_lifting_car();
	case 0x3C2:
		return this->_03C2_is_phone_displaying_message();
	case 0x3DD:
		return this->_03DD_add_sprite_blip_for_pickup();
	case 0x3EC:
		return this->_03EC_has_military_crane_collected_all_cars();
	case 0x3F8:
		return this->_03F8_get_body_cast_health();
	case 0x410:
		return this->_0410_set_gang_ped_model_preference();
	case 0x41C:
		return this->_041C_set_char_say();
	case 0x421:
		return this->_0421_force_rain();
	case 0x422:
		return this->_0422_does_garage_contain_car();
	case 0x42A:
		return this->_042A_is_threat_for_ped_type();
	case 0x43B:
		return this->_043B_update_boat_foam_animation();
	case 0x444:
		return this->_0444_set_script_fire_audio();
	case 0x447:
		return this->_0447_is_player_lifting_a_phone();
	case 0x58E:
		return this->_058E_set_shortcut_dropoff_point_for_mission();

	case 0x0AC:
		return this->_00AC_is_car_still_alive();
	case 0x130:
		return this->_0130_has_player_been_arrested();
	case 0x178:
		return this->_0178_is_player_touching_object();
	case 0x21D:
		return this->_021D_set_free_bombs();
	case 0x228:
		return this->_0228_is_car_armed_with_bomb();
	case 0x240:
		return this->_0240_flash_object();
	case 0x242:
		return this->_0242_arm_car_with_bomb();
	case 0x255:
		return this->_0255_restart_critical_mission();
	case 0x299:
		return this->_0299_activate_garage();
	case 0x29C:
		return this->_029C_is_boat();
	case 0x2A0:
		return this->_02A0_is_char_stopped();
	case 0x2B9:
		return this->_02B9_deactivate_garage();
	case 0x2C3:
		return this->_02C3_start_pacman_race();
	case 0x2C5:
		return this->_02C5_get_number_of_power_pills_eaten();
	case 0x2C6:
		return this->_02C6_clear_pacman();
	case 0x2C7:
		return this->_02C7_start_pacman_scramble();
	case 0x2C8:
		return this->_02C8_get_number_of_power_pills_carried();
	case 0x2C9:
		return this->_02C9_clear_number_of_power_pills_carried();
	case 0x2D9:
		return this->_02D9_clear_number_of_power_pills_eaten();
	case 0x2EE:
		return this->_02EE_is_projectile_in_area();
	case 0x2EF:
		return this->_02EF_destroy_projectiles_in_area();
	case 0x2F0:
		return this->_02F0_drop_mine();
	case 0x2F1:
		return this->_02F1_drop_nautical_mine();
	case 0x32D:
		return this->_032D_set_car_block_car();
	case 0x3A5:
		return this->_03A5_change_garage_type_with_car_model();
	case 0x3C9:
		return this->_03C9_is_car_visibly_damaged();
	case 0x3FB:
		return this->_03FB_set_car_stays_in_current_level();
	case 0x3FC:
		return this->_03FC_set_char_stays_in_current_level();
	case 0x41F:
		return this->_041F_override_hospital_level();
	case 0x420:
		return this->_0420_override_police_station_level();
	case 0x438:
		return this->_0438_set_char_ignore_level_transitions();
	case 0x44E:
		return this->_044E_set_car_ignore_level_transitions();
	case 0x44F:
		return this->_044F_make_craigs_car_a_bit_stronger();
	case 0x452:
		return this->_0452_enable_player_control_camera();

	case 0x15E:
		return this->_015E_is_car_in_air();
	case 0x2BC:
		return this->_02BC_set_swat_required();
	case 0x354:
		return this->_0354_start_chase_scene();
	case 0x355:
		return this->_0355_stop_chase_scene();
	case 0x367:
		return this->_0367_start_kill_frenzy_headshot();
	case 0x36B:
		return this->_036B_skip_clear_taxi_shortcut();
	case 0x3C6:
		return this->_03C6_is_collision_in_memory();
	case 0x40A:
		return this->_040A_remove_car_from_chase();
	case 0x430:
		return this->_0430_warp_char_into_car_as_passenger();
	case 0x432:
		return this->_0432_get_char_in_car_passenger_seat();
	}

	CTheScripts::CommandsExecuted--;
	m_dwScriptIP -= 2;
	// Call VC's CRunningScript::ProcessOneCommand
	return ProcessOneCommand();
}

bool CRunningScriptHack::_014D_text_pager()
{
	char text[8];
	VCGlobals::strcpy(text, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]));
	this->m_dwScriptIP += 8;
	this->CollectParameters(&this->m_dwScriptIP, 3);
	reinterpret_cast<CPagerHack *>(CUserDisplay::Pager)->AddMessage(TheText.Get(text), ScriptParams[0].uint16, ScriptParams[1].uint16, ScriptParams[2].uint16);
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

bool CRunningScriptHack::_00A2_is_char_still_alive()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(ped && ped->state != 0x37 && ped->state != 0x36);
	return 0;
}

bool CRunningScriptHack::_0135_change_car_lock()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	vehicle->lock = ScriptParams[1].uint32;
	return 0;
}

bool CRunningScriptHack::_016F_draw_shadow()
{
	this->CollectParameters(&this->m_dwScriptIP, 10);
	unsigned char type = 0;
	RwTexture *texture = 0;
	CVector pos = { ScriptParams[1].float32, ScriptParams[2].float32, ScriptParams[3].float32 };
	switch (ScriptParams[0].uint8) {
	case 1:
		type = 1;
		texture = VCGlobals::gpShadowCarTex;
		break;
	case 2:
		type = 1;
		texture = VCGlobals::gpShadowPedTex;
		break;
	case 3:
		type = 2;
		texture = VCGlobals::gpShadowExplosionTex;
		break;
	case 4:
		type = 1;
		texture = VCGlobals::gpShadowHeliTex;
		break;
	case 5:
		type = 2;
		texture = VCGlobals::gpShadowHeadLightsTex;
		break;
	case 6:
		type = 1;
		texture = VCGlobals::gpBloodPoolTex;
		break;
	default:
		return 0;
	}
	CShadows::StoreShadowToBeRendered(type, texture, &pos,
		-sin(ScriptParams[4].float32) * ScriptParams[5].float32, cos(ScriptParams[4].float32) * ScriptParams[5].float32, cos(ScriptParams[4].float32) * ScriptParams[5].float32, sin(ScriptParams[4].float32) * ScriptParams[5].float32,
		ScriptParams[6].int16, ScriptParams[7].uint8, ScriptParams[8].uint8, ScriptParams[9].uint8, 15.0, false, 1.0, 0, false);
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
	VCGlobals::gPhoneInfo.SetPhoneMessage_JustOnce(ScriptParams[0].int32, TheText.Get(text), 0, 0, 0, 0, 0);
	return 0;
}

bool CRunningScriptHack::_0250_draw_light()
{
	this->CollectParameters(&this->m_dwScriptIP, 6);
	CVector pos1 = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	CVector pos2 = { 0, 0, 0 };
	CPointLights::AddLight(0, pos1, pos2, 12.0, ScriptParams[3].uint32 / 255.0f, ScriptParams[4].uint32 / 255.0f, ScriptParams[5].uint32 / 255.0f, 0, true);
	return 0;
}

bool CRunningScriptHack::_02A1_message_wait()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	this->m_dwWakeTime = ScriptParams[0].uint32 + CTimer::m_snTimeInMilliseconds;
	if (ScriptParams[1].int32) {
		this->m_bSkipWakeTime = 1;
	}
	return 1; // special
}

bool CRunningScriptHack::_02A2_add_particle_effect()
{
	this->CollectParameters(&this->m_dwScriptIP, 5);
	CVector pos = { ScriptParams[1].float32, ScriptParams[2].float32, ScriptParams[3].float32 };
	if (pos.z <= -100.0) {
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
	}
	CParticleObject::AddObject(ScriptParams[0].uint16, pos, !!ScriptParams[4].int32);
	return 0;
}

bool CRunningScriptHack::_02BD_is_debug_mode()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(!!(debugMode & ScriptParams[0].int32));
	return 0;
}

bool CRunningScriptHack::_02CD_gosub_file()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	this->m_dwReturnStack[this->m_dwStackPointer] = this->m_dwScriptIP;
	this->m_dwStackPointer += 1;
	this->m_dwScriptIP = ScriptParams[0].uint32;
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
	this->UpdateCompareFlag(CGame::nastyGame);
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

bool CRunningScriptHack::_037F_give_player_detonator()
{
	CStreaming::RequestModel(291, 1);
	CStreaming::LoadAllRequestedModels(false);
	VCGlobals::FindPlayerPed()->GiveWeapon(34, 1, 1);
	int slot = *(int *)(CWeaponInfo::GetWeaponInfo(34) + 0x60);
	VCGlobals::FindPlayerPed()->weapons[slot].state = 0;
	return 0;
}

bool CRunningScriptHack::_03A0_is_crane_lifting_car()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[2].int32);
	this->UpdateCompareFlag(CCranesHack::IsThisCarPickedUp(ScriptParams[0].float32, ScriptParams[1].float32, vehicle));
	return 0;
}

bool CRunningScriptHack::_03C2_is_phone_displaying_message()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag((unsigned long)&VCGlobals::gPhoneInfo.phones[ScriptParams[0].int32] == *(unsigned long *)vcversion::AdjustOffset(0x007030E8));
	return 0;
}

bool CRunningScriptHack::_03DD_add_sprite_blip_for_pickup()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CRadar::GetActualBlipArrayIndex(this->CollectNextParameterWithoutIncreasingPC(this->m_dwScriptIP));
	ScriptParams[0].int32 = CRadar::SetEntityBlip(3, CPools::ms_pObjectPool->GetIndex(CPickups::pickups[CPickups::GetActualPickupIndex(ScriptParams[0].int32)].object), 6, 3);
	CRadar::SetBlipSprite(ScriptParams[0].int32, ScriptParams[1].int32);
	this->StoreParameters(&this->m_dwScriptIP, 1);
	return 0;
}

bool CRunningScriptHack::_03EC_has_military_crane_collected_all_cars()
{
	this->UpdateCompareFlag(CCranes::CarsCollectedMilitaryCrane == MILITARYCRANETOTAL);
	return 0;
}

bool CRunningScriptHack::_03F8_get_body_cast_health()
{
	ScriptParams[0].int32 = CObjectHack::nBodyCastHealth;
	this->StoreParameters(&this->m_dwScriptIP, 1);
	return 0;
}

bool CRunningScriptHack::_0410_set_gang_ped_model_preference()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CGangs::Gang[ScriptParams[0].int16].pedModelPreference = ScriptParams[1].int8;
	return 0;
}

bool CRunningScriptHack::_041C_set_char_say()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
	unsigned short say = ScriptParams[1].uint16;
	switch (say) {
	case 95:
		ped->Say(0x8F);
		break;
	case 96:
		ped->Say(0x8F);
		break;
	case 101:
		ped->Say(0x84);
		break;
	case 103:
		ped->Say(0xA0);
		break;
	case 104:
		ped->Say(0xA1);
		break;
	case 105:
		ped->Say(0xA2);
		break;
	default:
		if (CRunningScriptHack::debugMode & DEBUG_MASTERDEBUG) {
			ped->Say(say);
		}
	}
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
	this->UpdateCompareFlag(CGarages::garages[ScriptParams[0].int16].IsEntityEntirelyInside3D(vehicle, 0.0));
	return 0;
}

bool CRunningScriptHack::_042A_is_threat_for_ped_type()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	this->UpdateCompareFlag(ScriptParams[1].int32 == (*(int *)(*(DWORD *)(vcversion::AdjustOffset(0xA0DA64) + ScriptParams[0].int32 * 4) + 0x18) & ScriptParams[1].int32));
	return 0;
}

bool CRunningScriptHack::_043B_update_boat_foam_animation()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CObject *object = CPools::ms_pObjectPool->GetAt(ScriptParams[0].int32);
	CSpecialParticleStuffHack::UpdateBoatFoamAnimation(&object->GetMatrix());
	return 0;
}

bool CRunningScriptHack::_0444_set_script_fire_audio()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CFireManager::fires[ScriptParams[0].int16].sfx = !!ScriptParams[1].int32;
	return 0;
}

bool CRunningScriptHack::_0447_is_player_lifting_a_phone()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(CWorld::Players[ScriptParams[0].int32].playerEntity->state == 0x13);
	return 0;
}

bool CRunningScriptHack::_058E_set_shortcut_dropoff_point_for_mission()
{
	this->CollectParameters(&this->m_dwScriptIP, 4);
	if (CGameLogicHack::isShortcutDropoffEnabled) {
		CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
		CGameLogic::AddShortCutDropOffPointForMission(pos, ScriptParams[3].float32);
	}
	return 0;
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
	CPlayerPed *player = CWorld::Players[ScriptParams[0].int32].playerEntity;
	CObject *object = CPools::ms_pObjectPool->GetAt(ScriptParams[1].int32);
	CPhysical *source = player;
	if (player->isInAnyVehicle && player->vehicle) {
		source = player->vehicle;
	}
	this->UpdateCompareFlag(source->GetHasCollidedWith(object));
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
	this->UpdateCompareFlag((vehicle->bombState & 7) == ScriptParams[1].int32);
	return 0;
}

bool CRunningScriptHack::_0240_flash_object()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CObject *object = CPools::ms_pObjectPool->GetAt(ScriptParams[0].int32);
	object->field_052 &= 0xDF;
	if (ScriptParams[1].int32) {
		object->field_052 |= 0x20;
	}
	return 0;
}

bool CRunningScriptHack::_0242_arm_car_with_bomb()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	vehicle->bombState = (vehicle->bombState & 0xF8) | (ScriptParams[1].uint8 & 7);
	vehicle->bombOwner = VCGlobals::FindPlayerPed();
	return 0;
}

bool CRunningScriptHack::_0255_restart_critical_mission()
{
	this->CollectParameters(&this->m_dwScriptIP, 4);
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	if (pos.z <= -100.0) {
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
	}
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
	CGarage *garage = &CGarages::garages[ScriptParams[0].int16];
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
	this->UpdateCompareFlag(vehicle->type == 1);
	return 0;
}

bool CRunningScriptHack::_02A0_is_char_stopped()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
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
	this->UpdateCompareFlag(false);
	return 0;
}

bool CRunningScriptHack::_02B9_deactivate_garage()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CGarages::garages[ScriptParams[0].int16].isInactive = 1;
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
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	if (pos.z <= -100.0) {
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
	}
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
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	if (pos.z <= -100.0) {
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + 0.5f;
	}
	CPickups::GenerateNewOne(pos, VCGlobals::MI_CARMINE, 9, 0, 0, 0, 0);
	return 0;
}

bool CRunningScriptHack::_02F1_drop_nautical_mine()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	CVector pos = { ScriptParams[0].float32, ScriptParams[1].float32, ScriptParams[2].float32 };
	if (pos.z <= -100.0) {
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + 0.5f;
	}
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
	CGarages::ChangeGarageType(ScriptParams[0].int16, ScriptParams[1].uint8, ScriptParams[2].uint32);
	return 0;
}

bool CRunningScriptHack::_03C9_is_car_visibly_damaged()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(!!(vehicle->field_1FB & 2));
	return 0;
}

bool CRunningScriptHack::_03FB_set_car_stays_in_current_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	vehicle->originLevel = ScriptParams[1].int32 ? (char)CTheZones::GetLevelFromPosition(&vehicle->GetPos()) : 0;
	return 0;
}

bool CRunningScriptHack::_03FC_set_char_stays_in_current_level()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
	ped->originLevel = ScriptParams[1].int32 ? (char)CTheZones::GetLevelFromPosition(&ped->GetPos()) : 0;
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
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
	ped->originLevel = ScriptParams[1].int32 ? -1 : (char)CTheZones::GetLevelFromPosition(&ped->GetPos());
	return 0;
}

bool CRunningScriptHack::_044E_set_car_ignore_level_transitions()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	vehicle->originLevel = ScriptParams[1].int32 ? -1 : (char)CTheZones::GetLevelFromPosition(&vehicle->GetPos());
	return 0;
}

bool CRunningScriptHack::_044F_make_craigs_car_a_bit_stronger()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	vehicle->field_501 &= 0xDF;
	if (ScriptParams[1].int32) {
		vehicle->field_501 |= 0x20;
	}
	return 0;
}

bool CRunningScriptHack::_0452_enable_player_control_camera()
{
	*(unsigned short *)(CPad::GetPad(0) + 0xF0) &= 0xFFFE;
	return 0;
}

bool CRunningScriptHack::_015E_is_car_in_air()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	this->UpdateCompareFlag(vehicle->numberOfWheelsOnGround == 0);
	return 0;
}

bool CRunningScriptHack::_02BC_set_swat_required()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CPlayerPed *player = VCGlobals::FindPlayerPed();
	player->wanted->activity &= 0xFB;
	if (ScriptParams[0].int32) {
		player->wanted->activity |= 4;
	}
	return 0;
}

bool CRunningScriptHack::_0354_start_chase_scene()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CTimer::Suspend();
	CRecordDataForChaseHack::StartChaseScene(ScriptParams[0].float32);
	CTimer::Resume();
	return 0;
}

bool CRunningScriptHack::_0355_stop_chase_scene()
{
	CRecordDataForChaseHack::CleanUpChaseScene();
	return 0;
}

bool CRunningScriptHack::_0367_start_kill_frenzy_headshot()
{
	char text[8];
	VCGlobals::strcpy(text, reinterpret_cast<char *>(&CTheScripts::ScriptSpace[this->m_dwScriptIP]));
	this->m_dwScriptIP += 8;
	this->CollectParameters(&this->m_dwScriptIP, 8);
	CDarkel::StartFrenzy(ScriptParams[0].int32, ScriptParams[1].int32, ScriptParams[2].uint16, ScriptParams[3].int32, VCGlobals::TheText.Get(text), ScriptParams[4].int32, ScriptParams[5].int32, ScriptParams[6].int32, !!ScriptParams[7].int32, true);
	return 0;
}

bool CRunningScriptHack::_036B_skip_clear_taxi_shortcut()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	if (ScriptParams[0].int32) CGameLogicHack::skipClearShortcutStage = 4;
	return 0;
}

bool CRunningScriptHack::_03C6_is_collision_in_memory()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	this->UpdateCompareFlag(ScriptParams[0].int32 == CGame::currLevel);
	return 0;
}

bool CRunningScriptHack::_040A_remove_car_from_chase()
{
	this->CollectParameters(&this->m_dwScriptIP, 1);
	CRecordDataForChaseHack::RemoveCarFromChase(ScriptParams[0].int32);
	return 0;
}

bool CRunningScriptHack::_0430_warp_char_into_car_as_passenger()
{
	this->CollectParameters(&this->m_dwScriptIP, 3);
	CPed *ped = CPools::ms_pPedPool->GetAt(ScriptParams[0].int32);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[1].int32);
	ped->SetObjective(0x12, vehicle);
	char seat = ScriptParams[2].int8;
	if (seat < 0) {
		vehicle->AddPassenger(ped);
	} else {
		vehicle->AddPassenger(ped, seat);
	}
	ped->vehicle = vehicle;
	ped->vehicle->RegisterReference((CEntity **)&ped->vehicle);
	ped->isInAnyVehicle = 1;
	if (ped->state == 0xB) {
		ped->ClearFollowPath();
	}
	ped->state = 0x32;
	ped->field_051 &= 0xFE;
	ped->AddInCarAnims(vehicle, false);
	return 0;
}

bool CRunningScriptHack::_0432_get_char_in_car_passenger_seat()
{
	this->CollectParameters(&this->m_dwScriptIP, 2);
	CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(ScriptParams[0].int32);
	ScriptParams[0].int32 = CPools::ms_pPedPool->GetIndex(vehicle->passengers[ScriptParams[1].int32]);
	this->StoreParameters(&this->m_dwScriptIP, 1);
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
