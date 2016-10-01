#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CGame::nastyGame = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x0068DD68));
int &CGame::currLevel = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0D9AC));
