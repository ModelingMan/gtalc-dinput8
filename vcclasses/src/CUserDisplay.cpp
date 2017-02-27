#include "vcclasses.h"
#include "vcversion.h"

CPager *CUserDisplay::Pager = reinterpret_cast<CPager *>(vcversion::AdjustOffset(0x00978AA8));
