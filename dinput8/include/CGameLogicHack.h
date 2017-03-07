#pragma once

#include "vcclasses.h"

class CGameLogicHack : public CGameLogic
{
public:
	static bool isShortcutDropoffEnabled;
	static char skipClearShortcutStage;

	static bool initialise();
	static void ClearTaxiShotcutHack();
	static void UpdateHack();
};
