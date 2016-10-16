#pragma once

#include "vcclasses.h"

#define DEBUG_MASTERDEBUG 1

class CRunningScriptHack : public CRunningScript
{
public:
	static bool initialise();

	bool ProcessOneCommandHack();

	bool _014D_text_pager();
	bool _034A_industrial_passed();
	bool _034B_commercial_passed();
	bool _034C_suburban_passed();

	// additional opcodes
	bool _00A2_is_char_still_alive();
	bool _0135_change_car_lock();
	bool _016F_draw_shadow();
	bool _01EE_activate_crane();
	bool _01EF_deactivate_crane();
	bool _024C_set_phone_message();
	bool _0250_draw_light();
	bool _02A1_message_wait();
	bool _02A2_add_particle_effect();
	bool _02BD_is_debug_mode();
	bool _02CD_gosub_file();
	bool _02FB_activate_crusher_crane();
	bool _0351_is_nasty_game();
	bool _0356_is_explosion_in_area();
	bool _0368_activate_military_crane();
	bool _037F_give_player_detonator();
	bool _03A0_is_crane_lifting_car();
	bool _03C2_is_phone_displaying_message();
	bool _03DD_add_sprite_blip_for_pickup();
	bool _03EC_has_military_crane_collected_all_cars();
	bool _0410_set_gang_ped_model_preference();
	bool _0421_force_rain();
	bool _0422_does_garage_contain_car();
	bool _042A_is_threat_for_ped_type();
	bool _0444_set_script_fire_audio();
	bool _0447_is_player_lifting_a_phone();

	bool _00AC_is_car_still_alive();
	bool _0130_has_player_been_arrested();
	bool _0178_is_player_touching_object();
	bool _021D_set_free_bombs();
	bool _0228_is_car_armed_with_bomb();
	bool _0240_flash_object();
	bool _0242_arm_car_with_bomb();
	bool _0255_restart_critical_mission();
	bool _0299_activate_garage();
	bool _029C_is_boat();
	bool _02A0_is_char_stopped();
	bool _02B9_deactivate_garage();
	bool _02C3_start_pacman_race();
	bool _02C5_get_number_of_power_pills_eaten();
	bool _02C6_clear_pacman();
	bool _02C7_start_pacman_scramble();
	bool _02C8_get_number_of_power_pills_carried();
	bool _02C9_clear_number_of_power_pills_carried();
	bool _02D9_clear_number_of_power_pills_eaten();
	bool _02EE_is_projectile_in_area();
	bool _02EF_destroy_projectiles_in_area();
	bool _02F0_drop_mine();
	bool _02F1_drop_nautical_mine();
	bool _032D_set_car_block_car();
	bool _03A5_change_garage_type_with_car_model();
	bool _03C9_is_car_visibly_damaged();
	bool _03F8_get_body_cast_health();
	bool _03FB_set_car_stays_in_current_level();
	bool _03FC_set_char_stays_in_current_level();
	bool _041F_override_hospital_level();
	bool _0420_override_police_station_level();
	bool _0438_set_char_ignore_level_transitions();
	bool _044E_set_car_ignore_level_transitions();
	bool _044F_make_craigs_car_a_bit_stronger();
	bool _0452_enable_player_control_camera();

	static int debugMode;
};
