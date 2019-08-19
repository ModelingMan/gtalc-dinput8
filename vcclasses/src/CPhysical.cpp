#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CPhysical_Constructor = vcversion::AdjustOffset(0x004BB650);
unsigned long g_CPhysical_Destructor = vcversion::AdjustOffset(0x004BB630);

static unsigned long g_Add = vcversion::AdjustOffset(0x004BB310);
static unsigned long g_Remove = vcversion::AdjustOffset(0x004BB280);
static unsigned long g_GetBoundRect = vcversion::AdjustOffset(0x004BB5C0);
static unsigned long g_ProcessControl = vcversion::AdjustOffset(0x004BA6F0);
static unsigned long g_ProcessCollision = vcversion::AdjustOffset(0x004B94B0);
static unsigned long g_ProcessShift = vcversion::AdjustOffset(0x004B9120);
static unsigned long g_ProcessEntityCollision = vcversion::AdjustOffset(0x004AF240);
static unsigned long g_GetHasCollidedWith = vcversion::AdjustOffset(0x004B9010);
static unsigned long g_RemoveAndAdd = vcversion::AdjustOffset(0x004BAEE0);

__declspec(naked) bool CPhysical::GetHasCollidedWith(CEntity *)
{
	__asm jmp g_GetHasCollidedWith;
}

__declspec(naked) void CPhysical::RemoveAndAdd(void)
{
	__asm jmp g_RemoveAndAdd;
}

__declspec(naked) void CPhysical::Add()
{
	__asm jmp g_Add;
}

__declspec(naked) void CPhysical::Remove()
{
	__asm jmp g_Remove;
}

__declspec(naked) CRect *CPhysical::GetBoundRect(CRect *rect)
{
	__asm jmp g_GetBoundRect;
}

__declspec(naked) void CPhysical::ProcessControl()
{
	__asm jmp g_ProcessControl;
}

__declspec(naked) void CPhysical::ProcessCollision()
{
	__asm jmp g_ProcessCollision;
}

__declspec(naked) void CPhysical::ProcessShift()
{
	__asm jmp g_ProcessShift;
}

__declspec(naked) int CPhysical::ProcessEntityCollision(CEntity *other, void *colPoint)
{
	__asm jmp g_ProcessEntityCollision;
}