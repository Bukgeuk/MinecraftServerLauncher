#include "MinecraftServerLauncher.h"

short getmemoryinfo()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	DWORDLONG Size = statex.ullTotalPhys;
	for (int i = 0; i < 3; i++)
	{
		Size /= 1024;
	}

	return static_cast<short>(Size);
}

string getjarfile()
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".\\*.jar", &fd);

	if (handle == -1)
		return "NULL";
	
	return fd.name;
}