#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CReplay::Mode = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10AF6));
