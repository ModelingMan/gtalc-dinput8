#include "vcversion.h"
#include "SilentCall.h"

// call function from Silent's hooked mss32.dll
void _call(unsigned long addr, unsigned long data, eCallPatcher bPatchType)
{
	addr = vcversion::AdjustOffset(addr);
	switch (bPatchType)
	{
	case PATCH_JUMP:
		*(unsigned char *)addr = (unsigned char)0xE9;
		break;
	case PATCH_CALL:
		*(unsigned char *)addr = (unsigned char)0xE8;
		break;
	}
	*(unsigned long *)(addr + 1) = data - addr - 5;
}
