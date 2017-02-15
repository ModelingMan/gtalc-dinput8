#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CGame::nastyGame = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x0068DD68));
unsigned int &CGame::currArea = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00978810));
int &CGame::currLevel = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D9AC));
