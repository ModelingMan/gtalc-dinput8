#include "CDigitalClockHack.h"
#include <cmath>
#include "Globals.h"
#include "vcversion.h"

using namespace VCGlobals;

void CDigitalClockHack::Init(CVector position, float p2, float p3, unsigned char p4, unsigned char p5, unsigned char p6, float drawDistance, float p8)
{
	this->m_bRender = false;
	this->m_Position = position;
	this->m_0C = p2;
	this->m_10 = p3;
	this->m_14 = 0;
	this->m_20 = p4;
	this->m_21 = p5;
	this->m_22 = p6;
	this->m_fDrawDistance = drawDistance;
	this->m_1C = p8;
}

char *FindDigitalClockMessage()
{
	if (((CTimer::m_snTimeInMilliseconds >> 10) & 7) >= 6) {
		short temprature = static_cast<short>(13.0f - 6.0f * cosf((CClock::ms_nGameClockHours * 60 + CClock::ms_nGameClockMinutes) * 0.0043611112f - 1.0f));
		String_DigitalClock[0] = static_cast<char>(temprature / 10 + '0');
		if (String_DigitalClock[0] == '0')
			String_DigitalClock[0] = ' ';
		String_DigitalClock[1] = temprature % 10 + '0';
		String_DigitalClock[2] = ' ';
		String_DigitalClock[3] = '@';
		String_DigitalClock[4] = 'C';
	} else {
		String_DigitalClock[0] = CClock::ms_nGameClockHours / 10 + '0';
		String_DigitalClock[1] = CClock::ms_nGameClockHours % 10 + '0';
		String_DigitalClock[3] = CClock::ms_nGameClockMinutes / 10 + '0';
		String_DigitalClock[4] = CClock::ms_nGameClockMinutes % 10 + '0';
		if (CTimer::m_snTimeInMilliseconds & 0x200)
			String_DigitalClock[2] = ':';
		else
			String_DigitalClock[2] = ' ';
	}
	return String_DigitalClock;
}

void CDigitalClockHack::Render()
{
	float v5; // st7@2
	float v10; // ST10_4@7
	float v11; // ST0C_4@7
	int v17; // [sp+40h] [bp-5Ch]@3
	RwV3d v24; // [sp+6Ch] [bp-30h]@6
	float v27; // [sp+78h] [bp-24h]@6
	float v28; // [sp+7Ch] [bp-20h]@6
	RwV3d v29; // [sp+80h] [bp-1Ch]@6

	//if (CSprite::GetIsOnScreen(this->m_Position, this->m_1C * 5.0f))
	{
		CSprite::InitSpriteBuffer();
		char *text = FindDigitalClockMessage();

		v5 = (static_cast<float>(rand() % 256 + 768) * this->m_fScale) / 1024.0f;
		unsigned char r = static_cast<unsigned char>(static_cast<float>(this->m_20) * v5);
		unsigned char g = static_cast<unsigned char>(static_cast<float>(this->m_21) * v5);
		unsigned char b = static_cast<unsigned char>(static_cast<float>(this->m_22) * v5);

		//RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
		//RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
		//RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)2);
		//RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)2);
		//RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)2);
		//RwRenderStateSet(rwRENDERSTATETEXTURERASTER, dword_5FAF44->raster);
		//RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
		RwRenderStateSet(8, 0);
		RwRenderStateSet(12, 1);
		RwRenderStateSet(10, 2);
		RwRenderStateSet(11, 2);
		RwRenderStateSet(9, 2);
		RwRenderStateSet(1, (int)**(void ***)vcversion::AdjustOffset(0x00695538));//dword_5FAF44->raster);
		RwRenderStateSet(6, 1);

		int v20 = 0;
		for (int i = 0; i < 5; i++, v20 += 8) {
			v17 = 5 * (text[i] - ' ');
			int v12 = v20;
			for (int o = 0; o < 5; o++, v12++) {
				for (int u = 0; u < 5; u++) {
					if (ScrollCharSet[v17 + o] & (1 << u)) {
						v29.x = v12 * this->m_0C * this->m_1C * 0.125f + this->m_Position.x;
						v29.y = v12 * this->m_10 * this->m_1C * 0.125f + this->m_Position.y;
						v29.z = u * this->m_1C * 0.125f + this->m_Position.z;
						if (CSprite::CalcScreenCoors(v29, &v24, &v27, &v28, 1)) {
							v10 = v28 * this->m_1C * 0.12f;
							v11 = v27 * this->m_1C * 0.12f;
							CSprite::RenderBufferedOneXLUSprite(v24.x, v24.y, v24.z, v11, v10, r, g, b, 255, 1.0f / v24.z, 255);
						}
					}
				}
			}
		}
		CSprite::FlushSpriteBuffer();
	}
}

void CDigitalClockHack::Update()
{
	float x = TheCamera.GetMatrix().pos.x - this->m_Position.x;
	float y = TheCamera.GetMatrix().pos.y - this->m_Position.y;
	float distance = sqrt(x*x + y*y);

	if (distance > this->m_fDrawDistance) {
		this->m_bRender = false;
		return;
	}

	this->m_bRender = true;
	float scale = this->m_fDrawDistance * 3 / 4;
	if (distance < scale)
		this->m_fScale = 1.0f - (distance - scale) * 4.0f / this->m_fDrawDistance;
	else
		this->m_fScale = 1.0f;
}
