#include "vcclasses.h"
#include "vcversion.h"

CPlayerInfo *CWorld::Players = reinterpret_cast<CPlayerInfo *>(vcversion::AdjustOffset(0x0094AD28));
unsigned char &CWorld::PlayerInFocus = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10AFB));

static unsigned long g_RepositionOneObject = vcversion::AdjustOffset(0x004D43A0);
static unsigned long g_FindGroundZFor3DCoord = vcversion::AdjustOffset(0x004D53A0);
static unsigned long g_FindGroundZForCoord = vcversion::AdjustOffset(0x004D5540);
static unsigned long g_ProcessVerticalLine = vcversion::AdjustOffset(0x004D8B00);
static unsigned long g_Remove = vcversion::AdjustOffset(0x004DB310);
static unsigned long g_Add = vcversion::AdjustOffset(0x004DB3F0);

__declspec(naked) void CWorld::RepositionOneObject(CEntity *)
{
	__asm jmp g_RepositionOneObject;
}

__declspec(naked) float CWorld::FindGroundZFor3DCoord(float, float, float, bool *)
{
	__asm jmp g_FindGroundZFor3DCoord;
}

__declspec(naked) float CWorld::FindGroundZForCoord(float, float)
{
	__asm jmp g_FindGroundZForCoord;
}

__declspec(naked) bool CWorld::ProcessVerticalLine(CVector const &, float, CColPoint &, CEntity *&, bool, bool, bool, bool, bool, bool, unsigned long)
{
	__asm jmp g_ProcessVerticalLine;
}

__declspec(naked) void CWorld::Remove(CEntity *)
{
	__asm jmp g_Remove;
}

__declspec(naked) void CWorld::Add(CEntity *)
{
	__asm jmp g_Add;
}
