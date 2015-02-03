/*******************************************************************************
	CRunningScript -
*******************************************************************************/

#include "vcclasses.h"
#include "vcversion.h"

//SCMParameter *SCMParams = (SCMParameter *)0x007D7438;

static unsigned long g_pCollectParameters = vcversion::AdjustOffset(0x00451010);
static unsigned long g_pProcessOneCommand = vcversion::AdjustOffset(0x0044FBE0);
static unsigned long g_pUpdateCompareFlag = vcversion::AdjustOffset(0x00463F00);

__declspec(naked) void CRunningScript::CollectParameters(unsigned int *scriptIP, int paramCount)
{
	__asm jmp g_pCollectParameters;
}

__declspec(naked) bool CRunningScript::ProcessOneCommand()
{
	__asm jmp g_pProcessOneCommand;
}

__declspec(naked) void CRunningScript::UpdateCompareFlag(bool flag)
{
	__asm jmp g_pUpdateCompareFlag;
}
