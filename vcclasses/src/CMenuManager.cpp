#include "vcclasses.h"
#include "vcversion.h"

unsigned int &CMenuManager::m_PrefsLanguage = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00869680));
