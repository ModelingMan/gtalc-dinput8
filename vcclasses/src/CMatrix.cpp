#include "vcclasses.h"
#include "vcversion.h"

unsigned long g_CMatrix_Constructor_RwMatrix_bool = vcversion::AdjustOffset(0x004DFB00);
unsigned long g_CMatrix_Copy_Constructor = vcversion::AdjustOffset(0x004DFBA0);
unsigned long g_CMatrix_Destructor = vcversion::AdjustOffset(0x004DFAE0);

static unsigned long g_SetRotate = vcversion::AdjustOffset(0x004DF240);
static unsigned long g_SetRotateY = vcversion::AdjustOffset(0x004DF450);
static unsigned long g_SetRotateZ = vcversion::AdjustOffset(0x004DF3B0);
static unsigned long g_SetRotateZOnly = vcversion::AdjustOffset(0x004DF590);
static unsigned long g_SetTranslate = vcversion::AdjustOffset(0x004DF6D0);
static unsigned long g_ResetOrientation = vcversion::AdjustOffset(0x004DF780);
static unsigned long g_UpdateRW = vcversion::AdjustOffset(0x004DF8F0);
static unsigned long g_OperatorAssignment = vcversion::AdjustOffset(0x004DF8C0);

__declspec(naked) CMatrix &CMatrix::operator =(const CMatrix &rhs)
{
	__asm jmp g_OperatorAssignment;
}

__declspec(naked) void CMatrix::SetRotate(float, float, float)
{
	__asm jmp g_SetRotate;
}

__declspec(naked) void CMatrix::SetRotateY(float)
{
	__asm jmp g_SetRotateY;
}

__declspec(naked) void CMatrix::SetRotateZ(float)
{
	__asm jmp g_SetRotateZ;
}

__declspec(naked) void CMatrix::SetRotateZOnly(float)
{
	__asm jmp g_SetRotateZOnly;
}

__declspec(naked) void CMatrix::SetTranslate(float, float, float)
{
	__asm jmp g_SetTranslate;
}

__declspec(naked) void CMatrix::ResetOrientation(void)
{
	__asm jmp g_ResetOrientation;
}

__declspec(naked) void CMatrix::UpdateRW(void)
{
	__asm jmp g_UpdateRW;
}

CMatrix operator *(const RwMatrix *lhs, const CMatrix &rhs)
{
	CMatrix matrix;
	matrix.right.x = lhs->up.x * rhs.right.y + lhs->right.x * rhs.right.x + lhs->at.x * rhs.right.z;
	matrix.right.y = lhs->up.y * rhs.right.y + lhs->right.y * rhs.right.x + lhs->at.y * rhs.right.z;
	matrix.right.z = lhs->up.z * rhs.right.y + lhs->right.z * rhs.right.x + lhs->at.z * rhs.right.z;
	matrix.up.x = lhs->up.x * rhs.up.y + lhs->right.x * rhs.up.x + lhs->at.x * rhs.up.z;
	matrix.up.y = lhs->up.y * rhs.up.y + lhs->right.y * rhs.up.x + lhs->at.y * rhs.up.z;
	matrix.up.z = lhs->up.z * rhs.up.y + lhs->right.z * rhs.up.x + lhs->at.z * rhs.up.z;
	matrix.at.x = lhs->up.x * rhs.at.y + lhs->right.x * rhs.at.x + lhs->at.x * rhs.at.z;
	matrix.at.y = lhs->up.y * rhs.at.y + lhs->right.y * rhs.at.x + lhs->at.y * rhs.at.z;
	matrix.at.z = lhs->up.z * rhs.at.y + lhs->right.z * rhs.at.x + lhs->at.z * rhs.at.z;
	matrix.pos.x = lhs->up.x * rhs.pos.y + lhs->right.x * rhs.pos.x + lhs->at.x * rhs.pos.z + lhs->pos.x;
	matrix.pos.y = lhs->up.y * rhs.pos.y + lhs->right.y * rhs.pos.x + lhs->at.y * rhs.pos.z + lhs->pos.y;
	matrix.pos.z = lhs->up.z * rhs.pos.y + lhs->right.z * rhs.pos.x + lhs->at.z * rhs.pos.z + lhs->pos.z;
	return matrix;
}