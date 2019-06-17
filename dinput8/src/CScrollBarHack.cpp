#include "CScrollBarHack.h"
#include <cmath>
#include <cstring>
#include "Globals.h"
#include "vcclasses.h"

static char ScrollBarTime[22] = "THE TIME IS 12:34    ";
static char *ScrollBarMsgs[55] =
{
#include "ScrollBarMessages.inc"
};

void CScrollBarHack::Update()
{
	char *currentMsg = text;

	float x = VCGlobals::TheCamera.GetMatrix().pos.x - xStart;
	float y = VCGlobals::TheCamera.GetMatrix().pos.y - yStart;
	float distance = sqrt(x*x + y*y);

	if (distance > 100.0f) {
		draw = false;
		return;
	}

	draw = true;
	thickness = (distance < 75.0f ? 1.0f : 1.0f - (distance - 75.0f) * 4.0f * 0.0099999998f);
	count++;

	int countDiv = count & 7;
	if (countDiv == 0) {
		charCount++;

		if (charCount >= textLength) {
			switch (messageSet)
			{
			case 0:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[0];
						break;
					case 1:
						text = ScrollBarMsgs[1];
						break;
					case 2:
						text = ScrollBarMsgs[2];
						break;
					case 3:
						text = LibertyTunnelMsgDynamic();
						break;
					case 4:
						text = BridgesMsgDynamic();
						break;
					case 5:
						text = TimeMsgDynamic();
						break;
					case 6:
						if (CMenuManager::m_PrefsLanguage == 1 || CMenuManager::m_PrefsLanguage == 2)
							text = TimeMsgDynamic();
						else
							text = ScrollBarMsgs[50];
						break;
					}
				} while (text == currentMsg);
				break;

			case 1:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[3];
						break;
					case 1:
						text = ScrollBarMsgs[6];
						break;
					case 2:
						text = ScrollBarMsgs[7];
						break;
					case 3:
						text = ScrollBarMsgs[8];
						break;
					case 4:
						if (CWeather::Foggyness > 0.5)
							text = ScrollBarMsgs[4];
						else if (CWeather::WetRoads > 0.5)
							text = ScrollBarMsgs[5];
						else
							text = ScrollBarMsgs[9];
						break;
					case 5:
						text = LibertyTunnelMsgDynamic();
						break;
					case 6:
						text = BridgesMsgDynamic();
						break;
					case 7:
						text = TimeMsgDynamic();
						break;
					}
				} while (text == currentMsg);
				break;

			case 2:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[10];
						break;
					case 1:
						text = ScrollBarMsgs[11];
						break;
					case 2:
						text = ScrollBarMsgs[12];
						break;
					case 3:
						text = ScrollBarMsgs[13];
						break;
					case 4:
						text = ScrollBarMsgs[14];
						break;
					case 5:
						text = ScrollBarMsgs[15];
						break;
					case 6:
						text = ScrollBarMsgs[16];
						break;
					case 7:
						text = ScrollBarMsgs[17];
						break;
					case 8:
						text = LibertyTunnelMsgDynamic();
						break;
					case 9:
						text = BridgesMsgDynamic();
						break;
					case 10:
						text = TimeMsgDynamic();
						break;
					case 11:
						text = ScrollBarMsgs[51];
						break;
					}
				} while (text == currentMsg);
				break;

			case 3:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[18];
						break;
					case 1:
						text = ScrollBarMsgs[19];
						break;
					case 2:
						text = ScrollBarMsgs[20];
						break;
					case 3:
						text = TimeMsgDynamic();
						break;
					case 4:
						text = ScrollBarMsgs[54];
						break;
					}
				} while (text == currentMsg);
				break;

			case 4:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[21];
						break;
					case 1:
						text = ScrollBarMsgs[22];
						break;
					case 2:
						text = ScrollBarMsgs[23];
						break;
					case 3:
						text = TimeMsgDynamic();
						break;
					}
				} while (text == currentMsg);
				break;

			case 5:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[49];
						break;
					case 1:
						text = ScrollBarMsgs[31];
						break;
					case 2:
						text = ScrollBarMsgs[32];
						break;
					case 3:
						text = ScrollBarMsgs[33];
						break;
					case 4:
						text = ScrollBarMsgs[34];
						break;
					case 5:
						text = ScrollBarMsgs[35];
						break;
					case 6:
						text = ScrollBarMsgs[36];
						break;
					case 7:
						text = ScrollBarMsgs[37];
						break;
					case 8:
						text = ScrollBarMsgs[38];
						break;
					case 9:
						text = TimeMsgDynamic();
						break;
					case 10:
						text = ScrollBarMsgs[53];
						break;
					}
				} while (text == currentMsg);
				break;

			case 6:
				do
				{
					switch (VCGlobals::rand() & 0x0F)
					{
					case 0:
						text = ScrollBarMsgs[39];
						break;
					case 1:
						text = ScrollBarMsgs[40];
						break;
					case 2:
						text = ScrollBarMsgs[41];
						break;
					case 3:
						text = ScrollBarMsgs[42];
						break;
					case 4:
						text = ScrollBarMsgs[43];
						break;
					case 5:
						text = ScrollBarMsgs[44];
						break;
					case 6:
						text = ScrollBarMsgs[45];
						break;
					case 7:
						text = ScrollBarMsgs[46];
						break;
					case 8:
						text = ScrollBarMsgs[47];
						break;
					case 9:
						if (CMenuManager::m_PrefsLanguage == 1 || CMenuManager::m_PrefsLanguage == 2)
							text = ScrollBarMsgs[39];
						else
							text = ScrollBarMsgs[48];
						break;
					case 10:
						text = TimeMsgDynamic();
						break;
					case 11:
						text = ScrollBarMsgs[52];
						break;
					}
				} while (text == currentMsg);
				break;
			}
			textLength = strlen(text) - 1;
			charCount = 0;
		}
	}

	for (int i = 0; i < 39; i++)
		letterBuffer[i] = letterBuffer[i + 1];

	if (countDiv < 5) {
		char charIdx = text[charCount] - ' ';
		letterBuffer[39] = VCGlobals::ScrollCharSet[countDiv + charIdx * 5];
	}
	else
		letterBuffer[39] = 0;

	switch (VCGlobals::rand() & 0x0FF)
	{
	case 0x0D:
		letterBuffer[39] = 0;
		break;
	case 0x64:
		letterBuffer[39] = !letterBuffer[39];
		break;
	case 0xE3:
		letterBuffer[39] = 0xE3;
		break;
	}
}

char *CScrollBarHack::BridgesMsgDynamic()
{
	if (CStats::CommercialPassed)
		return ScrollBarMsgs[29];
	else if (CStats::IndustrialPassed)
		return ScrollBarMsgs[28];
	else
		return ScrollBarMsgs[27];
}

char *CScrollBarHack::LibertyTunnelMsgDynamic()
{
	if (CStats::CommercialPassed)
		return ScrollBarMsgs[26];
	else if (CStats::IndustrialPassed)
		return ScrollBarMsgs[25];
	else
		return ScrollBarMsgs[24];
}

char *CScrollBarHack::TimeMsgDynamic()
{
	ScrollBarTime[12] = (CClock::ms_nGameClockHours / 10) + '0';
	ScrollBarTime[13] = (CClock::ms_nGameClockHours % 10) + '0';
	ScrollBarTime[15] = (CClock::ms_nGameClockMinutes / 10) + '0';
	ScrollBarTime[16] = (CClock::ms_nGameClockMinutes % 10) + '0';

	return ScrollBarTime;
}
