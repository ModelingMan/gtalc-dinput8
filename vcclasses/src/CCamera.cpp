#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetMotionBlurAlpha = vcversion::AdjustOffset(0x0046B9F3);
static unsigned long g_SetMotionBlur = vcversion::AdjustOffset(0x0046BA00);
static unsigned long g_CamShake = vcversion::AdjustOffset(0x0046FF21);

__declspec(naked) void CCamera::SetMotionBlurAlpha(int)
{
	__asm jmp g_SetMotionBlurAlpha;
}

__declspec(naked) void CCamera::SetMotionBlur(int, int, int, int, int)
{
	__asm jmp g_SetMotionBlur;
}

__declspec(naked) void CCamera::CamShake(float, float, float, float)
{
	__asm jmp g_CamShake;
}
