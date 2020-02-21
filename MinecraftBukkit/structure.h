#pragma once

#include "include.h"

#pragma pack(push, 1)
typedef struct _DateType {
	short year = 0;
	short month = 0;
	short day = 0;
} DateType;

typedef struct _RunTimeType {
	int hour = 0;
	short minute = 0;
	short second = 0;
} RunTimeType;

typedef struct _OtherData {
	bool UAR = false;
	bool ISR = false;
	bool IEE = false;
	short AR = 1;
	char BN[1024] = "NULL";
} OtherData;
#pragma pack(pop)
