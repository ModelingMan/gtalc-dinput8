#include "CTowerClockHack.h"
#include "Globals.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace VCGlobals;

struct RxObjSpace3DVertex
{
	CVector objVertex;
	CVector objNormal;
	unsigned int color;
	float u;
	float v;
};

RxObjSpace3DVertex verts[4];

void CTowerClockHack::Init(CVector position, float p2, float p3, unsigned char p4, unsigned char p5, unsigned char p6, float drawDistance, float p8)
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

void CTowerClockHack::Render()
{
	//if (CSprite::GetIsOnScreen(this->m_Position, this->m_1C))
	{
		unsigned char alpha = (unsigned char)(255 * this->m_fScale);
		float hourHand = ((CClock::ms_nGameClockHours * 60 + CClock::ms_nGameClockMinutes) / 720.0f) * (float)M_PI * 2;
		float minuteHand = ((CClock::ms_nGameClockMinutes * 60 + CClock::ms_nGameClockSeconds) / 3600.0f) * (float)M_PI * 2;
		
		//RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
		//RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
		//RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
		//RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)5);
		//RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)6);
		//RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)2);
		//RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
		((int(*)(int, int))0x00649BA0)(8, 1);
		((int(*)(int, int))0x00649BA0)(6, 1);
		((int(*)(int, int))0x00649BA0)(12, 1);
		((int(*)(int, int))0x00649BA0)(10, 5);
		((int(*)(int, int))0x00649BA0)(11, 6);
		((int(*)(int, int))0x00649BA0)(9, 2);
		((int(*)(int, int))0x00649BA0)(1, 0);
		
		verts[0].color = this->m_22 | (this->m_21 << 8) | (this->m_20 << 16) | alpha << 24;
		verts[1].color = this->m_22 | (this->m_21 << 8) | (this->m_20 << 16) | alpha << 24;
		verts[2].color = this->m_22 | (this->m_21 << 8) | (this->m_20 << 16) | alpha << 24;
		verts[3].color = this->m_22 | (this->m_21 << 8) | (this->m_20 << 16) | alpha << 24;
		
		verts[0].objVertex = this->m_Position;
		verts[1].objVertex.x = this->m_0C * this->m_1C * sin(minuteHand) + this->m_Position.x;
		verts[1].objVertex.y = this->m_10 * this->m_1C * sin(minuteHand) + this->m_Position.y;
		verts[1].objVertex.z = this->m_1C * cos(minuteHand) + this->m_Position.z;

		verts[2].objVertex = this->m_Position;
		verts[3].objVertex.x = 0.75f * this->m_0C * this->m_1C * sin(hourHand) + this->m_Position.x;
		verts[3].objVertex.y = 0.75f * this->m_10 * this->m_1C * sin(hourHand) + this->m_Position.y;
		verts[3].objVertex.z = 0.75f * this->m_1C * cos(hourHand) + this->m_Position.z;

		if (((void*(*)(RxObjSpace3DVertex *, int, void *, int))0x0065AE90)(verts, 4, 0, 0))//if (RwIm3DTransform(verts, 4, 0, 0))
		{
			((void(*)(int, int))0x0065B0F0)(0, 1);//RwIm3DRenderLine(0, 1);
			((void(*)(int, int))0x0065B0F0)(2, 3);//RwIm3DRenderLine(2, 3);
			((void(*)())0x0065AF60)();//RwIm3DEnd();
		}
	}

}

void CTowerClockHack::Update()
{
	float x = TheCamera.GetMatrix().pos.x - this->m_Position.x;
	float y = TheCamera.GetMatrix().pos.y - this->m_Position.y;
	float distance = sqrt(x*x + y*y);

	if (distance > this->m_fDrawDistance)
	{
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