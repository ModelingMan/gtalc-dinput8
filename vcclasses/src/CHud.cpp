#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetHelpMessage = vcversion::AdjustOffset(0x0055BFC0);

__declspec(naked) void CHud::SetHelpMessage(wchar_t *, bool, bool)
{
	__asm jmp g_SetHelpMessage;
}
