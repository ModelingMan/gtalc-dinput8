#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CMenuManager::m_PrefsLanguage = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00869680));
