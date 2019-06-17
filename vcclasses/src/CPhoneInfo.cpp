#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetPhoneMessage_JustOnce = vcversion::AdjustOffset(0x0043C430);

__declspec(naked) void CPhoneInfo::SetPhoneMessage_JustOnce(int, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *)
{
	__asm jmp g_SetPhoneMessage_JustOnce;
}
