#include "vcclasses.h"
#include "vcversion.h"

unsigned short& CTheScripts::CommandsExecuted = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A66));
unsigned char *CTheScripts::ScriptSpace = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00821280));