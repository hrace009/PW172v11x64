//---------------------------------------------------------------------------------------------------------------------------
//--PW LUA SCRIPT GCLIENT (C) DeadRaky 2022
//---------------------------------------------------------------------------------------------------------------------------

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


#include "../Header/luaman.h"
#include <LuaBridge/LuaBridge.h>
using namespace luabridge;


LuaManager* LuaManager::instance = 0;
lua_State* LuaManager::L;
CRITICAL_SECTION LuaManager::cs_lua;
const char* LuaManager::FName;
time_t LuaManager::reload_tm = 0;
bool   LuaManager::lua_debug = false;
LuaManager::CONFIG LuaManager::config;

time_t LuaManager::GetFileTime(const char* path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) == -1) {
		perror(path);
		exit(1);
	}
	return statbuf.st_mtime;
}

void LuaManager::game__Patch(size_t address, int type, double value)
{
	if (!address) { printf("game__Patch: ERROR ADDRESS! \n"); return; }
	switch (type)
	{
	case TYPE_CHAR: { *(unsigned char*)address = value; return; break; }
	case TYPE_SHORT: { *(unsigned short*)address = value; return; break; }
	case TYPE_INT: { *(unsigned int*)address = value; return; break; }
	case TYPE_INT64: { *(unsigned long long*)address = value; return; break; }
	case TYPE_FLOAT: { *(float*)address = value; return; break; }
	case TYPE_DOUBLE: { *(double*)address = value; return; break; }
	default: { printf("game__Patch: ERROR TYPE %d ! \n", type);   return; break; }
	}
}

double LuaManager::game__Get(size_t address, int type, size_t offset)
{
	if (!address)
	{
		printf("game__Get: ERROR ADDRESS! \n");
		return 0;
	}
	switch (type)
	{
	case TYPE_CHAR: { return *(unsigned char*)(&((char*)address)[offset]); break; }
	case TYPE_SHORT: { return *(unsigned short*)(&((char*)address)[offset]); break; }
	case TYPE_INT: { return *(unsigned int*)(&((char*)address)[offset]); break; }
	case TYPE_INT64: { return *(unsigned long long*)(&((char*)address)[offset]); break; }
	case TYPE_FLOAT: { return *(float*)(&((char*)address)[offset]); break; }
	case TYPE_DOUBLE: { return *(double*)(&((char*)address)[offset]); break; }
	default: { printf("game__Get: ERROR TYPE %d ! \n", type);   return 0; 			break; }
	}
	return 0;
}

void LuaManager::FunctionsRegister()
{
	getGlobalNamespace(L).addFunction("game__Patch", game__Patch);
	getGlobalNamespace(L).addFunction("game__Get", game__Get);
}

void LuaManager::SetItem()
{
	//config.SET_ADDR("GUILD_UPGRADE_COST", config.GUILD_UPGRADE_COST);

}

void LuaManager::GetItem()
{
	double res = -0;
	res = config.GET_NUM("lua_debug"); res != -0 ? lua_debug = res : res == -0;
}

void LuaManager::FunctionsExec()
{
	config.INIT();
}

#define LUA_MUTEX_BEGIN EnterCriticalSection(&cs_lua); \
							try { 

#define LUA_MUTEX_END	} \
							catch (...) {  } \
							LeaveCriticalSection(&cs_lua);

void LuaManager::Init()
{
	FName = "script.lua";
	InitializeCriticalSection(&cs_lua);
	LUA_MUTEX_BEGIN
	reload_tm = GetFileTime(FName);
	L = luaL_newstate();
	luaL_openlibs(L);
	FunctionsRegister();
	FunctionsExec();
	luaL_dofile(L, FName);
	SetItem();
	LuaRef Event = getGlobal(L, "EventOnStartScript");
	if (!Event.isNil() && Event.isFunction())
		Event();
	else
		printf("LUA::Event: NULL!!! EventOnStartScript \n");
	GetItem();
	LUA_MUTEX_END
}

void LuaManager::Update()
{
	time_t last_tm = GetFileTime(FName);
	if (reload_tm == last_tm) return;
	reload_tm = last_tm;
	LUA_MUTEX_BEGIN
	lua_close(L);
	L = luaL_newstate();
	luaL_openlibs(L);
	FunctionsRegister();
	FunctionsExec();
	luaL_dofile(L, FName);
	SetItem();
	LuaRef Event = getGlobal(L, "EventOnReloadScript");
	if (!Event.isNil() && Event.isFunction())
		Event();
	else
		printf("LUA::Event: NULL!!! EventOnReloadScript \n");
	GetItem();
	LUA_MUTEX_END
}

void LuaManager::HeartBeat(size_t tick)
{
	if (!(tick & 20))
	{
		LUA_MUTEX_BEGIN
			LuaRef Event = getGlobal(L, "EventOnHeartBeat");
		if (!Event.isNil() && Event.isFunction())
			Event(tick);
		else
			printf("LUA::Event: NULL!!! EventOnHeartBeat \n");
		LUA_MUTEX_END
			if (!(tick & 600))
				Update();
	}
}

bool LuaManager::CONFIG::IS_TRUE(int it, int* table)
{
	for (size_t i = 0; table[i] && i < 128; i++)
		if (table[i] == it)
			return true;
	return false;
}

double LuaManager::CONFIG::GET_NUM(const char* s)
{
	LuaRef out = getGlobal(L, s);
	if (out.isNil() || !out.isNumber())
	{
		printf("LuaManager::GET_NUM: error %s not found! \n", s);
		return -0;
	}
	return out.cast<double>();
}

const char* LuaManager::CONFIG::GET_STR(const char* s)
{
	LuaRef out = getGlobal(L, s);
	if (out.isNil() || !out.isString())
	{
		printf("LuaManager::GET_STR: error %s not found! \n", s);
		return 0;
	}
	return out.cast<const char*>();
}

void LuaManager::CONFIG::SET_NUM(const char* s, double v)
{
	LuaRef out = getGlobal(L, s);
	if (out.isNil() || !out.isNumber())
	{
		printf("LuaManager::SET_NUM: error %s not found! \n", s);
		return;
	}
	setGlobal(L, v, s);
}

void LuaManager::CONFIG::SET_STR(const char* s, const char* v)
{
	LuaRef out = getGlobal(L, s);
	if (out.isNil() || !out.isString())
	{
		printf("LuaManager::SET_STR: error %s not found! \n", s);
		return;
	}
	setGlobal(L, v, s);
}

void LuaManager::CONFIG::SET_ADDR(const char* s, size_t v)
{
	LuaRef out = getGlobal(L, s);
	if (out.isNil() || !out.isNumber())
	{
		printf("LuaManager::SET_ADDR: error %s not found! \n", s);
		return;
	}
	setGlobal(L, v, s);
}



