#include "vcclasses.h"
#include "vcversion.h"

bool &CMBlur::BlurOn = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00697D54));
