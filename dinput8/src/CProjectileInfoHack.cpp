#include "CProjectileInfoHack.h"
#include "vcversion.h"
#include "SilentCall.h"

// UpdateHack
unsigned long projectileInfoUpdateProceedJump = vcversion::AdjustOffset(0x005C6ECC);
unsigned long projectileInfoUpdateEndJump = vcversion::AdjustOffset(0x005C6F45);

bool CProjectileInfoHack::initialise()
{
	// ProjectileInfo null thrower fix
	InjectHook(0x005C6EC6, &CProjectileInfoHack::UpdateHack, PATCH_JUMP);

	return true;
}

bool CProjectileInfoHack::IsProjectileInRange(float x1, float y1, float z1, float x2, float y2, float z2, bool flag)
{
	unsigned long *address = (unsigned long *)vcversion::AdjustOffset(0x0094B708);
	for (int i = 0; i < 0x20; i++) {
		CObject *object = *(CObject **)&address[i];
		if (object) {
			if (projectiles[i].doesProjectileExist && projectiles[i].weaponType >= 12 && projectiles[i].weaponType <= 16) {
				if (object->GetX() >= x1 && object->GetX() <= x2) {
					if (object->GetY() >= y1 && object->GetY() <= y2) {
						if (object->GetZ() >= z1 && object->GetZ() <= z2) {
							if (flag) {
								projectiles[i].doesProjectileExist = 0;
								auto Destroy = (void(__thiscall *)(CObject *, int))*(unsigned long *)(object->vtbl + 8);
								CWorld::Remove(object);
								Destroy(object, 1);
							}
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void __declspec(naked) CProjectileInfoHack::UpdateHack()
{
	__asm
	{
		mov eax, [ebp+4] // get pointer of projectile thrower
		test eax, eax    // compare pointer with 0
		jz end
		mov eax, [ebp+0]
		cmp eax, 0Ch
		jmp projectileInfoUpdateProceedJump
	end:
		jmp projectileInfoUpdateEndJump
	}
}
