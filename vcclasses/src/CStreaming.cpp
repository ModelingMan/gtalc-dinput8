#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetModelTxdIsDeletable = vcversion::AdjustOffset(0x0040ADF0);
static unsigned long g_SetModelIsDeletable = vcversion::AdjustOffset(0x0040AEA0);
static unsigned long g_LoadAllRequestedModels = vcversion::AdjustOffset(0x0040B5F0);
static unsigned long g_RequestModel = vcversion::AdjustOffset(0x0040E310);
static unsigned long g_pMakeSpaceFor = vcversion::AdjustOffset(0x0040C190);

__declspec(naked) void CStreaming::SetModelTxdIsDeletable(int)
{
	__asm jmp g_SetModelTxdIsDeletable;
}

__declspec(naked) void CStreaming::SetModelIsDeletable(int)
{
	__asm jmp g_SetModelIsDeletable;
}

__declspec(naked) void CStreaming::LoadAllRequestedModels(bool)
{
	__asm jmp g_LoadAllRequestedModels;
}

__declspec(naked) void CStreaming::RequestModel(int, int)
{
	__asm jmp g_RequestModel;
}

__declspec(naked) void CStreaming::MakeSpaceFor(int size)
{
	__asm jmp g_pMakeSpaceFor;
}