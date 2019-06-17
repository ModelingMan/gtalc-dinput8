#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CRecordDataForChase::Status = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10B98));
