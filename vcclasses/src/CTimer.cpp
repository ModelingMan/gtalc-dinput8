#include "vcclasses.h"
#include "vcversion.h"

unsigned int& CTimer::m_snTimeInMilliseconds = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00974B2C));
unsigned int& CTimer::m_FrameCounter = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00A0D898));