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
	*reinterpret_cast<unsigned char *>(address) = nType == PATCH_JUMP ? 0xE9 : 0xE8;
	*reinterpret_cast<unsigned long *>(address + 1) = (unsigned long)data - address - 5;
}

template<typename T>
inline void Patch(unsigned long address, T value)
{
	*reinterpret_cast<T *>(vcversion::AdjustOffset(address)) = value;
}
