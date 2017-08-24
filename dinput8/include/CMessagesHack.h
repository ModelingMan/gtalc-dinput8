#pragma once

#include "vcclasses.h"

class CMessagesHack : public CMessages
{
public:
	static bool initialise();

	static void AddMessageSoon(wchar_t *, unsigned int, unsigned short);
	static void AddMessageSoonWithNumber(wchar_t *, unsigned int, unsigned short, int, int, int, int, int, int);
};
