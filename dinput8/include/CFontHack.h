#pragma once

class CFontHack
{
public:
	static bool initialise();

	static void PrintPagerString(float posX, float posY, float scaleX, float scaleY, wchar_t *text);
};
