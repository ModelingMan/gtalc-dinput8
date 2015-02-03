#pragma once

#include "vcclasses.h"

class CPagerHack : public CPager
{
public:
	void AddMessage(wchar_t *text, unsigned short delay, unsigned short unk1, unsigned short unk2);
	static void Draw();
	static void SetMessage(wchar_t *text);

	static bool initialise();
};
