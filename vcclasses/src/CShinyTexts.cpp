#include "vcclasses.h"
#include "vcversion.h"

CShinyTexts *CShinyTexts::aShinyTexts = reinterpret_cast<CShinyTexts *>(vcversion::AdjustOffset(0x0094A218));
unsigned int &CShinyTexts::NumShinyTexts = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00978618));
