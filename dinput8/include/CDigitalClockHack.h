#ifndef __CDIGITALCLOCKHACK_H__
#define __CDIGITALCLOCKHACK_H__

#include "vcclasses.h"

class CDigitalClockHack
{
protected:
	CVector m_Position;
	float m_0C;
	float m_10;
	int m_14;
	float m_fDrawDistance;
	float m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_22;
	bool m_bRender;
	float m_fScale;

public:
	void Init(CVector, float, float, unsigned char, unsigned char, unsigned char, float, float);
	void Render();
	void Update();

	bool IsToBeRendered() { return m_bRender; }
};

#endif