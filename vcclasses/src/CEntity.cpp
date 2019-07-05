#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CEntity_Constructor = vcversion::AdjustOffset(0x00489910);
unsigned long g_CEntity_Destructor = vcversion::AdjustOffset(0x004898E0);

static unsigned long g_GetDistanceFromCentreOfMassToBaseOfModel = vcversion::AdjustOffset(0x00487D10);

static unsigned long g_Add = vcversion::AdjustOffset(0x00487FD0);
static unsigned long g_Remove = vcversion::AdjustOffset(0x00487D30);
static unsigned long g_SetModelIndex = vcversion::AdjustOffset(0x004898B0);
static unsigned long g_SetModelIndexNoCreate = vcversion::AdjustOffset(0x00489880);
static unsigned long g_CreateRwObject = vcversion::AdjustOffset(0x00489810);
static unsigned long g_DeleteRwObject = vcversion::AdjustOffset(0x004896C0);
static unsigned long g_GetBoundRect = vcversion::AdjustOffset(0x00489400);
static unsigned long g_ProcessControl = vcversion::AdjustOffset(0x00407EC0);
static unsigned long g_ProcessCollision = vcversion::AdjustOffset(0x00407ED0);
static unsigned long g_ProcessShift = vcversion::AdjustOffset(0x00407EE0);
static unsigned long g_Teleport = vcversion::AdjustOffset(0x00407EF0);
static unsigned long g_PreRender = vcversion::AdjustOffset(0x00488810);
static unsigned long g_Render = vcversion::AdjustOffset(0x004887D0);
static unsigned long g_SetupLighting = vcversion::AdjustOffset(0x004C9D90);
static unsigned long g_RemoveLighting = vcversion::AdjustOffset(0x004C9D80);
static unsigned long g_FlagToDestroyWhenNextProcessed = vcversion::AdjustOffset(0x00407F00);
static unsigned long g_UpdateRwFrame = vcversion::AdjustOffset(0x00489360);
static unsigned long g_UpdateRpHAnim = vcversion::AdjustOffset(0x00489330);
static unsigned long g_RegisterReference = vcversion::AdjustOffset(0x004C6AC0);

__declspec(naked) float CEntity::GetDistanceFromCentreOfMassToBaseOfModel(void)
{
	__asm jmp g_GetDistanceFromCentreOfMassToBaseOfModel;
}

__declspec(naked) void CEntity::Add()
{
	__asm jmp g_Add;
}

__declspec(naked) void CEntity::Remove()
{
	__asm jmp g_Remove;
}

__declspec(naked) void CEntity::SetModelIndex(unsigned int modelIndex)
{
	__asm jmp g_SetModelIndex;
}

__declspec(naked) void CEntity::SetModelIndexNoCreate(unsigned int modelIndex)
{
	__asm jmp g_SetModelIndexNoCreate;
}

__declspec(naked) void CEntity::CreateRwObject()
{
	__asm jmp g_CreateRwObject;
}

__declspec(naked) void CEntity::DeleteRwObject()
{
	__asm jmp g_DeleteRwObject;
}

__declspec(naked) CRect CEntity::GetBoundRect()
{
	__asm jmp g_GetBoundRect;
}

__declspec(naked) void CEntity::ProcessControl()
{
	__asm jmp g_ProcessControl;
}

__declspec(naked) void CEntity::ProcessCollision()
{
	__asm jmp g_ProcessCollision;
}

__declspec(naked) void CEntity::ProcessShift()
{
	__asm jmp g_ProcessShift;
}

__declspec(naked) void CEntity::Teleport(CVector posn)
{
	__asm jmp g_Teleport;
}

__declspec(naked) void CEntity::PreRender()
{
	__asm jmp g_PreRender;
}

__declspec(naked) void CEntity::Render()
{
	__asm jmp g_Render;
}

__declspec(naked) bool CEntity::SetupLighting()
{
	__asm jmp g_SetupLighting;
}

__declspec(naked) void CEntity::RemoveLighting(bool resetWorldColors)
{
	__asm jmp g_RemoveLighting;
}

__declspec(naked) void CEntity::FlagToDestroyWhenNextProcessed()
{
	__asm jmp g_FlagToDestroyWhenNextProcessed;
}

__declspec(naked) void CEntity::UpdateRwFrame()
{
	__asm jmp g_UpdateRwFrame;
}

__declspec(naked) void CEntity::UpdateRpHAnim()
{
	__asm jmp g_UpdateRpHAnim;
}

__declspec(naked) void CEntity::RegisterReference(CEntity ** pEntity)
{
	__asm jmp g_RegisterReference;
}

