#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_TestForSniperBullet = vcversion::AdjustOffset(0x005C3B20);

__declspec(naked) bool CBulletInfo::TestForSniperBullet(float, float, float, float, float, float)
{
	__asm jmp g_TestForSniperBullet;
}
