#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddRef = vcversion::AdjustOffset(0x00580A60);
static unsigned long g_AddTxdSlot = vcversion::AdjustOffset(0x00580F00);
static unsigned long g_FindTxdSlot = vcversion::AdjustOffset(0x00580D70);
static unsigned long g_LoadTxd = vcversion::AdjustOffset(0x00580CD0);
static unsigned long g_PopCurrentTxd = vcversion::AdjustOffset(0x00580AA0);
static unsigned long g_PushCurrentTxd = vcversion::AdjustOffset(0x00580AC0);
static unsigned long g_SetCurrentTxd = vcversion::AdjustOffset(0x00580AD0);

__declspec(naked) void CTxdStore::AddRef(int)
{
	__asm jmp g_AddRef;
}

__declspec(naked) int CTxdStore::AddTxdSlot(const char *)
{
	__asm jmp g_AddTxdSlot;
}

__declspec(naked) int CTxdStore::FindTxdSlot(const char *)
{
	__asm jmp g_FindTxdSlot;
}

__declspec(naked) void CTxdStore::LoadTxd(int, const char *)
{
	__asm jmp g_LoadTxd;
}

__declspec(naked) void CTxdStore::PopCurrentTxd(void)
{
	__asm jmp g_PopCurrentTxd
}

__declspec(naked) void CTxdStore::PushCurrentTxd(void)
{
	__asm jmp g_PushCurrentTxd;
}

__declspec(naked) void CTxdStore::SetCurrentTxd(int)
{
	__asm jmp g_SetCurrentTxd;
}
