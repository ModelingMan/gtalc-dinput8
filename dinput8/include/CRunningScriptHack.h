#pragma once

#include "vcclasses.h"

class CRunningScriptHack : public CRunningScript
{
public:
	static bool initialise();

	bool ProcessOneCommandHack();

	bool _014D_text_pager();
};
