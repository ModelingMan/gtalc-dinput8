#include "vcclasses.h"
#include "vcversion.h"

bool &CCutsceneMgr::ms_cutsceneProcessing = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B63));
