
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <tchar.h>

#include "../Header/config.h"
#include "../Header/packet.h"
#include "../Header/regid.h"

Regid* Regid::instance = 0;
Regid::KEY Regid::REG;
wchar_t Regid::REG_DIR[] = L"Software\\CPWKey\\";
wchar_t Regid::REG_VALUE[] = L"CPW_VALUE";

void Regid::Init()
{
	REG.command = Packet::CMD_SEND_HWID;
	REG.data = RegOpen();
	if (!REG.data)
	{
		REG.data = RegCreate();
	}
}

unsigned long long Regid::RegOpen()
{
	HKEY REG_KEY;
	DWORD REG_SIZE = sizeof(int64_t);
	BYTE VALUE[sizeof(int64_t)];

	if (RegOpenKeyEx(
		HKEY_CURRENT_USER,
		REG_DIR,
		NULL,
		KEY_QUERY_VALUE,
		&REG_KEY
	) != ERROR_SUCCESS)
		return 0;

	RegQueryValueEx(
		REG_KEY,
		REG_VALUE,
		NULL,
		NULL,
		(LPBYTE)&VALUE,
		&REG_SIZE
	);
	RegCloseKey(REG_KEY);
	return *(unsigned long long*)&VALUE[0];
}

unsigned long long Regid::RegCreate()
{
	HKEY REG_KEY;
	DWORD REG_SIZE = sizeof(int64_t);
	BYTE VALUE[sizeof(int64_t)];

	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		REG_DIR,
		0,
		NULL,
		REG_OPTION_VOLATILE,
		KEY_WRITE,
		NULL,
		&REG_KEY,
		NULL
	) != ERROR_SUCCESS)
		return 0;

	*(DWORD*)&VALUE[0] = rand();
	*(DWORD*)&VALUE[4] = rand();
	RegSetValueEx(
		REG_KEY,
		REG_VALUE,
		0,
		REG_DWORD,
		VALUE,
		REG_SIZE
	);
	RegCloseKey(REG_KEY);
	return *(unsigned long long*)&VALUE[0];
}

