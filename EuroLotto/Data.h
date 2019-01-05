#pragma once
#include "defs.h"

int ReadData( Player*** pAllDraws, const char* sFileName );
void FreeMem( Player*** pTab, int nDrawsNo );