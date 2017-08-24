#include <Windows.h>
#include "vcversion.h"

// based on SilentPatch
enum eCallPatcher
{
	PATCH_CALL,
	PATCH_JUMP
};

template<typename T>
inline void InjectHook(unsigned long address, T data, eCallPatcher nType = PATCH_CALL)
{
	address = vcversion::AdjustOffset(address);
	*reinterpret_cast<unsigned char *>(address) = static_cast<unsigned char>(nType == PATCH_JUMP ? 0xE9 : 0xE8);
	*reinterpret_cast<unsigned long *>(address + 1) = (unsigned long)data - address - 5;
}

template<typename T>
inline void Patch(unsigned long address, T value)
{
	*reinterpret_cast<T *>(vcversion::AdjustOffset(address)) = value;
}

template<typename T>
inline void ReadCall(unsigned long address, T &function)
{
	address = vcversion::AdjustOffset(address);
	function = T(*(unsigned long *)(address + 1) + address + 5);
}

inline void Nop(unsigned long address, size_t n)
{
	memset(reinterpret_cast<void *>(vcversion::AdjustOffset(address)), 0x90, n);
}
