#include "CSpecialParticleStuffHack.h"
#include "Globals.h"
#include "Offset.h"

void CSpecialParticleStuffHack::UpdateBoatFoamAnimation(CMatrix *matrix)
{
	for (int i = 0; i < 2; i++) {
		int rand = VCGlobals::rand();
		float x = static_cast<float>((rand & 0xFF) - 0x80) * 107.0f * 0.0090909088f;
		float y = static_cast<float>(((rand >> 8) & 0xFF) - 0x80) * 107.0f * 0.0090909088f;
		float z = 0.0 + OFFSETZ;
		x += matrix->pos.x;
		y += matrix->pos.y;
		CParticle::AddParticle(29, { x, y, z }, { 0, 0, 0 }, 0, 4.0, { 255, 255, 255, 255 }, 1, 0, 0, 0); // STEAM2
	}
}
