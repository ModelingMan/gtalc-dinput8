#include "CHudHack.h"
#include "Utils.h"
#include "Globals.h"
#include "vcclasses.h"

#include <wchar.h>
#include <memory.h>
#include <math.h>

using namespace VCGlobals;

bool CHudHack::initialise()
{
	unsigned char *WorkAddress;

	unsigned long DrawTimeTextStartAddr		= vcversion::AdjustOffset(0x00559EAF);
	unsigned long DrawTimeTextEndAddr		= vcversion::AdjustOffset(0x00559FF9);
	unsigned long DrawMoneyTextStartAddr	= vcversion::AdjustOffset(0x0055818C);
	unsigned long DrawMoneyTextEndAddr		= vcversion::AdjustOffset(0x00558317);
	unsigned long DrawHealthTextStartAddr	= vcversion::AdjustOffset(0x00558B07);
	unsigned long DrawHealthTextEndAddr		= vcversion::AdjustOffset(0x00558CFC);
	unsigned long DrawArmorTextStartAddr	= vcversion::AdjustOffset(0x00558D1E);
	unsigned long DrawArmorTextEndAddr		= vcversion::AdjustOffset(0x00558F6C);
	unsigned long DrawWantedStarsStartAddr	= vcversion::AdjustOffset(0x00558FAC);
	unsigned long DrawWantedStarsEndAddr	= vcversion::AdjustOffset(0x005591D2);

	WorkAddress = reinterpret_cast<unsigned char*>(DrawTimeTextStartAddr);
	//memset(WorkAddress, 0x90, DrawTimeTextEndAddr - DrawTimeTextStartAddr);
	WorkAddress[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&WorkAddress[1]) = reinterpret_cast<unsigned long>(&DrawTimeText) - reinterpret_cast<unsigned long>(&WorkAddress[5]);
	WorkAddress[5] = 0xE9;
	*reinterpret_cast<unsigned long *>(&WorkAddress[6]) = DrawTimeTextEndAddr - reinterpret_cast<unsigned long>(&WorkAddress[10]);

	WorkAddress = reinterpret_cast<unsigned char*>(DrawMoneyTextStartAddr);
	//memset(WorkAddress, 0x90, DrawMoneyTextEndAddr - DrawMoneyTextStartAddr);
	WorkAddress[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&WorkAddress[1]) = reinterpret_cast<unsigned long>(&DrawMoneyText) - reinterpret_cast<unsigned long>(&WorkAddress[5]);
	WorkAddress[5] = 0xE9;
	*reinterpret_cast<unsigned long *>(&WorkAddress[6]) = DrawMoneyTextEndAddr - reinterpret_cast<unsigned long>(&WorkAddress[10]);

	WorkAddress = reinterpret_cast<unsigned char*>(DrawHealthTextStartAddr);
	//memset(WorkAddress, 0x90, DrawHealthTextEndAddr - DrawHealthTextStartAddr);
	WorkAddress[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&WorkAddress[1]) = reinterpret_cast<unsigned long>(&DrawHealthText) - reinterpret_cast<unsigned long>(&WorkAddress[5]);
	WorkAddress[5] = 0xE9;
	*reinterpret_cast<unsigned long *>(&WorkAddress[6]) = DrawHealthTextEndAddr - reinterpret_cast<unsigned long>(&WorkAddress[10]);

	WorkAddress = reinterpret_cast<unsigned char*>(DrawArmorTextStartAddr);
	//memset(WorkAddress, 0x90, DrawArmorTextEndAddr - DrawArmorTextStartAddr);
	WorkAddress[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&WorkAddress[1]) = reinterpret_cast<unsigned long>(&DrawArmorText) - reinterpret_cast<unsigned long>(&WorkAddress[5]);
	WorkAddress[5] = 0xE9;
	*reinterpret_cast<unsigned long *>(&WorkAddress[6]) = DrawArmorTextEndAddr - reinterpret_cast<unsigned long>(&WorkAddress[10]);

	WorkAddress = reinterpret_cast<unsigned char*>(DrawWantedStarsStartAddr);
	//memset(WorkAddress, 0x90, DrawWantedStarsEndAddr - DrawWantedStarsStartAddr);
	WorkAddress[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&WorkAddress[1]) = reinterpret_cast<unsigned long>(&DrawWantedStars) - reinterpret_cast<unsigned long>(&WorkAddress[5]);
	WorkAddress[5] = 0xE9;
	*reinterpret_cast<unsigned long *>(&WorkAddress[6]) = DrawWantedStarsEndAddr - reinterpret_cast<unsigned long>(&WorkAddress[10]);

	return true;
}

void CHudHack::DrawTimeText()
{
	wchar_t timeWString[9];

	const float width = static_cast<float>(Globals.currentWidth);
	const float height = static_cast<float>(Globals.currentHeight);

	swprintf(timeWString, 9, L"%02d:%02d", CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes);

	CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetScale(width * (0.8f / 640.0f), height * (1.35f / 448.0f));
	CFont::SetCentreOff();
	CFont::SetRightJustifyOn();
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(2);
	CFont::SetPropOff();

	CFont::SetDropColor(&CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(2);

	CFont::SetColor(&CRGBA(194, 165, 120, 255));

	CFont::PrintString(width * (529.0f / 640.0f), height * (22.0f / 448.0f), timeWString);
}

void CHudHack::DrawMoneyText()
{
	wchar_t moneyWString[10];

	const float width = static_cast<float>(Globals.currentWidth);
	const float height = static_cast<float>(Globals.currentHeight);

	swprintf(moneyWString, 10, L"$%08d", Utils::GetPlayerMoney());

	CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetScale(width * (0.8f / 640.0f), height * (1.35f / 448.0f));
	CFont::SetCentreOff();
	CFont::SetRightJustifyOn();
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(2);
	CFont::SetPropOff();

	CFont::SetDropColor(&CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(2);

	CFont::SetColor(&CRGBA(89, 115, 150, 255));

	CFont::PrintString(width * (530.0f / 640.0f), height * (43.0f / 448.0f), moneyWString);
}

void CHudHack::DrawHealthText()
{
	wchar_t healthIconWString[2] = L"{";
	wchar_t healthWString[9];

	const float width = static_cast<float>(Globals.currentWidth);
	const float height = static_cast<float>(Globals.currentHeight);

	swprintf(healthWString, 9, L"%03d", static_cast<unsigned int>(Utils::GetPlayerHealth()));

	CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetScale(width * (0.8f / 640.0f), height * (1.35f / 448.0f));
	CFont::SetCentreOff();
	CFont::SetRightJustifyOn();
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(2);
	CFont::SetPropOff();

	float healthIconOffset = floorf(width * (55.0f / 640.0f));

	CFont::SetDropColor(&CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(2);

	CFont::SetColor(&CRGBA(186, 101, 50, 255));

	CFont::PrintString(width * (530.0f / 640.0f), height * (65.0f / 448.0f), healthWString);
	CFont::PrintString(width * (530.0f / 640.0f) - healthIconOffset, height * (65.0f / 448.0f), healthIconWString);
}

void CHudHack::DrawArmorText()
{
	wchar_t armorIconWString[2] = L"<";
	wchar_t armorWString[9];

	const float width = static_cast<float>(Globals.currentWidth);
	const float height = static_cast<float>(Globals.currentHeight);

	if (Utils::GetPlayerArmor() >= 1.0f)
	{
		swprintf(armorWString, 9, L"%03d", static_cast<unsigned int>(Utils::GetPlayerArmor()));

		CFont::SetPropOff();
		CFont::SetBackgroundOff();
		CFont::SetScale(width * (0.8f / 640.0f), height * (1.35f / 448.0f));
		CFont::SetCentreOff();
		CFont::SetRightJustifyOn();
		CFont::SetRightJustifyWrap(0.0f);
		CFont::SetBackGroundOnlyTextOff();
		CFont::SetFontStyle(2);
		CFont::SetPropOff();

		float armourIconOffset = floorf(width * (52.0f / 640.0f));

		CFont::SetDropColor(&CRGBA(0, 0, 0, 255));
		CFont::SetDropShadowPosition(2);

		CFont::SetColor(&CRGBA(124, 140, 95, 255));

		CFont::PrintString(width * (458.0f / 640.0f), height * (65.0f / 448.0f), armorWString);
		CFont::PrintString(width * (458.0f / 640.0f) - armourIconOffset, height * (65.0f / 448.0f), armorIconWString);
	}
}

void CHudHack::DrawWantedStars()
{
	wchar_t wantedStarIcon[2] = L">";

	const float width = static_cast<float>(Globals.currentWidth);
	const float height = static_cast<float>(Globals.currentHeight);

	CFont::SetBackgroundOff();
	CFont::SetScale(width * (0.8f / 640.0f), height * (1.35f / 448.0f));
	CFont::SetJustifyOff();
	CFont::SetCentreOff();
	CFont::SetRightJustifyOff();
	CFont::SetPropOn();
	CFont::SetFontStyle(2);

	CFont::SetDropShadowPosition(0);

	float x = width * (580.0f / 640.0f);
	float y = height * (87.0f / 448.0f);
	for (unsigned int i = 0; i < 6; i++, x -= width * (23.0f / 640.0f))
	{
		CFont::SetColor(&CRGBA(0, 0, 0, 255));
		CFont::PrintString(x + 2.0f, y + 2.0f, wantedStarIcon);

		if (Utils::GetPlayerWantedLevel() > i)
		{
			unsigned int wanted = *reinterpret_cast<unsigned int *>(*reinterpret_cast<unsigned int *>(VCGlobals::FindPlayerPed() + 0x05F4) + 0x0C);
			if (wanted + 2000 <= CTimer::m_snTimeInMilliseconds || !(CTimer::m_FrameCounter & 4))
			{
				CFont::SetColor(&CRGBA(193, 164, 120, 255));
				CFont::PrintString(x, y, wantedStarIcon);
			}
		}
	}
}
