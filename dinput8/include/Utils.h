#pragma once

#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"

using namespace VCGlobals;

namespace Utils
{
	unsigned int GetPlayerMoney()
	{
		return CWorld::Players[0].m_MoneyCounter;
	}

	void SetPlayerMoney(unsigned int amount)
	{
		CWorld::Players[0].m_Money = amount;
	}

	float GetPlayerHealth()
	{
		return *(float *)(reinterpret_cast<unsigned char *>(FindPlayerPed()) + 0x0354);
	}

	float GetPlayerArmor()
	{
		return *(float *)(reinterpret_cast<unsigned char *>(FindPlayerPed()) + 0x0358);
	}

	unsigned int GetPlayerWantedLevel()
	{
		return *(unsigned int *)(*(unsigned int *)(reinterpret_cast<unsigned char *>(FindPlayerPed()) + 0x05F4) + 0x20);
	}
}
