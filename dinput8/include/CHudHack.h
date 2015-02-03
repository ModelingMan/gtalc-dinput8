#pragma once

class CHudHack
{
private:
	static void DrawTimeText();
	static void DrawMoneyText();
	static void DrawHealthText();
	static void DrawArmorText();
	static void DrawWantedStars();

public:
	static bool initialise();
};
