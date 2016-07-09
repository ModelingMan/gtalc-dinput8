#include "CMovingThingsHack.h"
#include "CDigitalClockHack.h"
#include "CScrollBarHack.h"
#include "CTowerClockHack.h"
#include "Globals.h"
#include "vcclasses.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <memory.h>

using namespace VCGlobals;

CScrollBarHack aScrollBars[11];
CTowerClockHack aTowerClocks[2];
CDigitalClockHack aDigitalClocks[3];

bool CMovingThingsHack::initialise()
{
	unsigned char *MovingThingsInitHackAddr = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x0054FBFD));
	memset(MovingThingsInitHackAddr, 0x90, 102);
	MovingThingsInitHackAddr[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&MovingThingsInitHackAddr[1]) = reinterpret_cast<unsigned long>(&Init) - reinterpret_cast<unsigned long>(&MovingThingsInitHackAddr[5]);

	unsigned char *MovingThingsUpdateHackAddr = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x0054F4E6));
	memset(MovingThingsUpdateHackAddr, 0x90, 51);
	MovingThingsUpdateHackAddr[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&MovingThingsUpdateHackAddr[1]) = reinterpret_cast<unsigned long>(&Update) - reinterpret_cast<unsigned long>(&MovingThingsUpdateHackAddr[5]);

	unsigned char *MovingThingsRenderHackAddr = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x0054F25B));
	memset(MovingThingsRenderHackAddr, 0x90, 45);
	MovingThingsRenderHackAddr[0] = 0xE8;
	*reinterpret_cast<unsigned long *>(&MovingThingsRenderHackAddr[1]) = reinterpret_cast<unsigned long>(&Render) - reinterpret_cast<unsigned long>(&MovingThingsRenderHackAddr[5]);
	*reinterpret_cast<unsigned long *>(&MovingThingsRenderHackAddr[5]) = 0xEED9EED9;

	// VC's CScrollBar::Init function takes in the full position of where the scrollbar ends, whereas III only takes the offset from the start
	// These nops make the CScrollBar::Init function behave like in III
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x0054EC00)), 0x90, 10);
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x0054EC0F)), 0x90, 8);
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(0x0054EC1C)), 0x90, 8);

	// undo nop
	call(0x004A6556, 0x0054F250, PATCH_CALL); // render
	call(0x004A4EC9, 0x0054F880, PATCH_CALL); // initialise
	call(0x004A4953, 0x0054F880, PATCH_CALL); // reinitialise
	call(0x004A45B4, 0x0054F420, PATCH_CALL); // update

	// do not update trails and banner
	call(0x005AFDD3, 0x005AFE37, PATCH_JUMP);

	// do not update escalators
	call(0x0054F435, 0x0054F453, PATCH_JUMP);

	return true;
}

#include <math.h>

void CMovingThingsHack::Init()
{
	float x, y, z;
	float xExtra = -335.0f, zExtra = 6.0f;

	x = 228.3f + xExtra;
	y = -669.0f;
	z = 39.0f + zExtra;
	aScrollBars[0].Init(x, y, z, 0.0f, 0.5f, 0.5f, 0, 255, 128, 0, 0.3f);

	x = 772.0f + xExtra;
	y = 164.0f;
	z = -9.5f + zExtra;
	aScrollBars[1].Init(x, y, z, 0.0f, 0.5f, 0.25f, 1, 128, 255, 0, 0.3f);

	x = -1089.61f + xExtra;
	y = -584.224f;
	z = 13.246f + zExtra;
	aScrollBars[2].Init(x, y, z, 0.0f, -0.1706f, 0.107f, 3, 255, 0, 0, 0.11f);

	x = -1089.61f + xExtra;
	y = -602.04602f;
	z = 13.246f + zExtra;
	aScrollBars[3].Init(x, y, z, 0.0f, -0.1706f, 0.107f, 3, 0, 255, 0, 0.11f);

	x = -1089.61f + xExtra;
	y = -619.81702f;
	z = 13.246f + zExtra;
	aScrollBars[4].Init(x, y, z, 0.0f, -0.1706f, 0.107f, 3, 255, 128, 0, 0.11f);

	x = -754.578f + xExtra;
	y = -633.50897f;
	z = 18.410999f + zExtra;
	aScrollBars[5].Init(x, y, z, 0.0f, 0.59f, 0.52f, 4, 100, 100, 255, 0.3f);

	x = -754.578f + xExtra;
	y = -586.672f;
	z = 18.410999f + zExtra;
	aScrollBars[6].Init(x, y, z, 0.0f, 0.59f, 0.52f, 4, 100, 100, 255, 0.3f);

	x = 85.473f + xExtra;
	y = -1069.512f;
	z = 30.5f + zExtra;
	aScrollBars[7].Init(x, y, z, 0.625f, -0.3125f, 0.727f, 5, 100, 100, 255, 0.5f);

	x = 74.822998f + xExtra;
	y = -1086.879f;
	z = 31.495001f + zExtra;
	aScrollBars[8].Init(x, y, z, -0.2083f, 0.1041f, 0.5f, 2, 255, 255, 128, 0.3f);

	x = -36.459f + xExtra;
	y = -1031.2371f;
	z = 32.534f + zExtra;
	aScrollBars[9].Init(x, y, z, -0.1442f, 0.0721f, 0.229f, 2, 150, 255, 50, 0.3f);

	x = 1208.0f + xExtra;
	y = -62.208f;
	z = 19.157f + zExtra;
	aScrollBars[10].Init(x, y, z, 0.0642f, -0.20365f, 0.229f, 6, 255, 128, 0, 0.3f);

	CVector v;
	v.x = 59.400002f + xExtra;
	v.y = -1081.3f;
	v.z = 54.150002f + zExtra;
	aTowerClocks[0].Init(v, -1.0f, 0.0f, 0, 0, 0, 80.0f, 2.0f);

	v.x = 55.400002f + xExtra;
	v.y = -1083.6f;
	v.z = 54.150002f + zExtra;
	aTowerClocks[1].Init(v, 0.0f, -1.0f, 0, 0, 0, 80.0f, 2.0f);

	float v10 = sqrt(18.280056f);
	float v11 = 1.0f / v10;
	float v12 = 2.144001f * v11;
	float v13 = -3.6990967f * v11;
	float v14 = sqrt(18.279154f);
	float v15 = 1.0f / v14;
	float v16 = -2.144001f * v15;
	float v17 = 3.6989746f * v15;
	float v18 = sqrt(18.27953f);
	float v19 = 1.0f / v18;
	float v20 = -3.6990013f * v19;
	float v21 = -2.144043f * v19;
	float v22 = 0.3f * v12 + 54.48500061035156f + xExtra;
	float v23 = 0.3f * v13 + -1081.678955078125f;
	float v24 = 0.05f * v20 + v22;
	float v25 = 0.05f * v21 + v23;
	float v26 = v13;
	float v27 = v12;
	v.x = v24;
	v.y = v25;
	v.z = 32.80299758911133f + zExtra;
	aDigitalClocks[0].Init(v, v27, v26, -1, 0, 0, 100.0f, 0.8f);
	float v28 = 0.3f * v16 + 60.56399917602539f + xExtra;
	float v29 = 0.3f * v17 + -1083.088989257812f;
	float v30 = -v20 * 0.05f + v28;
	float v31 = -v21 * 0.05f + v29;
	v.x = v30;
	v.y = v31;
	v.z = 32.80299758911133f + zExtra;
	aDigitalClocks[1].Init(v, v16, v17, 0, 0, -1, 100.0f, 0.8f);
	float v32 = 0.3f * v20 + 58.14500045776367f + xExtra;
	float v33 = 0.3f * v21 + -1079.267944335938f;
	float v34 = 0.05f * v16 + v32;
	float v35 = 0.05f * v17 + v33;
	v.x = v34;
	v.y = v35;
	v.z = 32.80299758911133f + zExtra;
	aDigitalClocks[2].Init(v, v20, v21, 0, -1, 0, 100.0f, 0.8f);

}

void CMovingThingsHack::Update()
{
	for (int i = 0; i < 11; i++)
	{
		if (aScrollBars[i].draw || (i + CTimer::m_FrameCounter) % 8 != 0)
			aScrollBars[i].Update();
	}

	for (int i = 0; i < 2; i++)
	{
		if (aTowerClocks[i].IsToBeRendered() || (i + CTimer::m_FrameCounter) % 8 != 0)
			aTowerClocks[i].Update();
	}

	for (int i = 0; i < 3; i++)
	{
		if (aDigitalClocks[i].IsToBeRendered() || (i + CTimer::m_FrameCounter) % 8 != 0)
			aDigitalClocks[i].Update();
	}
}

void CMovingThingsHack::Render()
{
	for (int i = 0; i < 11; i++)
	{
		if (aScrollBars[i].draw == true)
			aScrollBars[i].Render();
	}

	for (int i = 0; i < 2; i++)
	{
		if (aTowerClocks[i].IsToBeRendered())
			aTowerClocks[i].Render();
	}

	for (int i = 0; i < 3; i++)
	{
		if (aDigitalClocks[i].IsToBeRendered())
			aDigitalClocks[i].Render();
	}
}
