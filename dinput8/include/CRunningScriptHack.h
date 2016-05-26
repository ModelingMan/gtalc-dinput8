#pragma once

#include "vcclasses.h"

class CRunningScriptHack : public CRunningScript
{
public:
	static bool initialise();

	bool ProcessOneCommandHack();

	bool _014D_text_pager();

	bool _024C_set_phone_message();

	bool _0351_is_nasty_game();

	bool _03C2_is_phone_displaying_message();

	bool _0410_set_gang_ped_model_preference();

	bool _0421_force_rain();

	bool _0422_does_garage_contain_car();

	bool _042A_is_threat_for_ped_type();

	bool _0444_set_script_fire_audio();

	bool _0447_is_player_lifting_a_phone();
};
