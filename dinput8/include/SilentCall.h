#define call(a, v, bAddCall) _call((unsigned long)(a), (unsigned long)(v), (bAddCall))

enum eCallPatcher
{
	PATCH_CALL,
	PATCH_JUMP,
	PATCH_NOTHING
};

void _call(unsigned long addr, unsigned long data, eCallPatcher bPatchType);
