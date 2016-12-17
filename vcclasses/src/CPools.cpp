#include "vcclasses.h"
#include "vcversion.h"

CPool<CObject, CCutsceneHead> *&CPools::ms_pObjectPool = *(CPool<CObject, CCutsceneHead> **)vcversion::AdjustOffset(0x0094DBE0);
CPool<CBuilding> *&CPools::ms_pBuildingPool = *(CPool<CBuilding> **)vcversion::AdjustOffset(0x0097F240);
CPool<CPed, CPlayerPed> *&CPools::ms_pPedPool = *(CPool<CPed, CPlayerPed> **)vcversion::AdjustOffset(0x0097F2AC);
CPool<CVehicle, CAutomobile> *&CPools::ms_pVehiclePool = *(CPool<CVehicle, CAutomobile> **)vcversion::AdjustOffset(0x00A0FDE4);

static unsigned long g_CVehicle_CAutomobile_GetIndex = vcversion::AdjustOffset(0x0042C4B0);
static unsigned long g_CObject_CCutsceneHead_GetIndex = vcversion::AdjustOffset(0x00434A10);
static unsigned long g_CObject_CCutsceneHead_GetAt = vcversion::AdjustOffset(0x00451C30);
static unsigned long g_CVehicle_CAutomobile_GetAt = vcversion::AdjustOffset(0x00451C70);
static unsigned long g_CPed_CPlayerPed_GetAt = vcversion::AdjustOffset(0x00451CB0);
static unsigned long g_CPed_CPlayerPed_GetIndex = vcversion::AdjustOffset(0x00451CF0);

__declspec(naked) int CPool<CVehicle, CAutomobile>::GetIndex(CVehicle *)
{
	__asm jmp g_CVehicle_CAutomobile_GetIndex;
}

__declspec(naked) int CPool<CObject, CCutsceneHead>::GetIndex(CObject *)
{
	__asm jmp g_CObject_CCutsceneHead_GetIndex;
}

__declspec(naked) CObject *CPool<CObject, CCutsceneHead>::GetAt(int)
{
	__asm jmp g_CObject_CCutsceneHead_GetAt;
}

__declspec(naked) CVehicle *CPool<CVehicle, CAutomobile>::GetAt(int)
{
	__asm jmp g_CVehicle_CAutomobile_GetAt;
}

__declspec(naked) CPed *CPool<CPed, CPlayerPed>::GetAt(int)
{
	__asm jmp g_CPed_CPlayerPed_GetAt;
}

__declspec(naked) int CPool<CPed, CPlayerPed>::GetIndex(CPed *)
{
	__asm jmp g_CPed_CPlayerPed_GetIndex;
}
