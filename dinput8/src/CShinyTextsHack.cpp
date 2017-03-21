#include "CShinyTextsHack.h"
#include <cmath>
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"

unsigned long shinyTextsJumpEnd = vcversion::AdjustOffset(0x00465BB8);
static char LightForPedsHack();

bool CShinyTextsHack::initialise()
{
	InjectHook(0x00464BD9, &CShinyTextsHack::RegisterOneCallProxy, PATCH_JUMP);

	InjectHook(0x004F190F, &LightForPedsHack);
	return true;
}

void CShinyTextsHack::RegisterOne(CVector vec1, CVector vec2, CVector vec3, CVector vec4, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, unsigned char type, unsigned char r, unsigned char g, unsigned char b, float maxDistance)
{
	aShinyTexts[NumShinyTexts].distance = sqrt(
		pow((vec1.x - VCGlobals::TheCamera.GetMatrix().pos.x), 2) +
		pow((vec1.y - VCGlobals::TheCamera.GetMatrix().pos.y), 2) +
		pow((vec1.z - VCGlobals::TheCamera.GetMatrix().pos.z), 2));
	if (aShinyTexts[NumShinyTexts].distance <= maxDistance) {
		aShinyTexts[NumShinyTexts].vec1 = vec1;
		aShinyTexts[NumShinyTexts].vec2 = vec2;
		aShinyTexts[NumShinyTexts].vec3 = vec3;
		aShinyTexts[NumShinyTexts].vec4 = vec4;
		aShinyTexts[NumShinyTexts].unk[0] = f0;
		aShinyTexts[NumShinyTexts].unk[1] = f1;
		aShinyTexts[NumShinyTexts].unk[2] = f2;
		aShinyTexts[NumShinyTexts].unk[3] = f3;
		aShinyTexts[NumShinyTexts].unk[4] = f4;
		aShinyTexts[NumShinyTexts].unk[5] = f5;
		aShinyTexts[NumShinyTexts].unk[6] = f6;
		aShinyTexts[NumShinyTexts].unk[7] = f7;
		aShinyTexts[NumShinyTexts].type = type;
		aShinyTexts[NumShinyTexts].r = r;
		aShinyTexts[NumShinyTexts].g = g;
		aShinyTexts[NumShinyTexts].b = b;
		if (aShinyTexts[NumShinyTexts].distance > maxDistance / 2.0f) {
			float fade = 2.0f - 2.0f * aShinyTexts[NumShinyTexts].distance / maxDistance;
			aShinyTexts[NumShinyTexts].r = static_cast<unsigned char>(static_cast<float>(r) * fade);
			aShinyTexts[NumShinyTexts].g = static_cast<unsigned char>(static_cast<float>(g) * fade);
			aShinyTexts[NumShinyTexts].b = static_cast<unsigned char>(static_cast<float>(b) * fade);
		}
		NumShinyTexts++;
	}
}

void __declspec(naked) CShinyTextsHack::RegisterOneCallProxy()
{
	__asm
	{
		lea edi, [edi+4]
		push edi
		call CShinyTextsHack::RegisterOneCall
		add esp, 4
		jmp shinyTextsJumpEnd
	}
}

void CShinyTextsHack::RegisterOneCall(CMatrix &mat)
{
	auto ml = (CVector *(__cdecl *)(CVector *, const CMatrix &, const CVector &))vcversion::AdjustOffset(0x004DFF20);
	CVector vec1 = {}, vec2 = {}, vec3 = {}, vec4 = {}, in1, in2, in3, in4;
	if (LightForPedsHack() == 2) {
		// don't walk
		in1 = { 2.7, 0.706, -0.127 };
		in2 = { 2.7, 1.256, -0.127 };
		in3 = { 2.7, 0.706, -0.40166664 };
		in4 = { 2.7, 1.256, -0.40166664 };
		ml(&vec1, mat, in1);
		ml(&vec2, mat, in2);
		ml(&vec3, mat, in3);
		ml(&vec4, mat, in4);
		CShinyTextsHack::RegisterOne(vec1, vec2, vec3, vec4, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1, 255, 0, 0, 60.0);
	} else if (LightForPedsHack() == 0 || CTimer::m_snTimeInMilliseconds & 0x100) {
		// walk
		in1 = { 2.7, 0.706, -0.40166664 };
		in2 = { 2.7, 1.256, -0.40166664 };
		in3 = { 2.7, 0.706, -0.539 };
		in4 = { 2.7, 1.256, -0.539 };
		ml(&vec1, mat, in1);
		ml(&vec2, mat, in2);
		ml(&vec3, mat, in3);
		ml(&vec4, mat, in4);
		CShinyTextsHack::RegisterOne(vec1, vec2, vec3, vec4, 1.0, 0.5, 0.0, 0.5, 1.0, 1.0, 0.0, 1.0, 1, 255, 255, 255, 60.0);
	}
}

char LightForPedsHack()
{
	unsigned int time = CTimer::m_snTimeInMilliseconds & 0x3FFF;
	if (time < 0x2EE0) {
		return 2;
	} else if (time < 0x3C18) {
		return 0;
	}
	return 1;
}
