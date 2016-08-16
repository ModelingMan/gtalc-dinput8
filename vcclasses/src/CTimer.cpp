#include "vcclasses.h"
#include "vcversion.h"

unsigned int &CTimer::m_snTimeInMilliseconds = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00974B2C));
float &CTimer::ms_fTimeStep = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975424));
float &CTimer::ms_fTimeScale = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F264));
unsigned int &CTimer::m_FrameCounter = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00A0D898));
