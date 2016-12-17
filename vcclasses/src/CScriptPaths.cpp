#include "vcclasses.h"
#include "vcversion.h"

CScriptPaths *CScriptPaths::ScriptPath = reinterpret_cast<CScriptPaths *>(vcversion::AdjustOffset(0x009B69AC));
