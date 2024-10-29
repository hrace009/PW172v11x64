//---------------------------------------------------------------------------------------------------------------------------
//--PW LUA SCRIPT GDELIVERYD (C) DeadRaky 2022
//---------------------------------------------------------------------------------------------------------------------------
#ifndef __GNET_LUAMANAGER_H
#define __GNET_LUAMANAGER_H

#include <Windows.h>
#include <lua.hpp>

class LuaManager
{
public:
	enum
	{
		TYPE_CHAR = 0,
		TYPE_SHORT = 1,
		TYPE_INT = 2,
		TYPE_INT64 = 3,
		TYPE_FLOAT = 4,
		TYPE_DOUBLE = 5,
	};
private:
#pragma pack(push, 1)
struct CONFIG
{
	void INIT()
	{
		size_t i;
	}
	bool IS_TRUE(int it, int* table);
	double GET_NUM(const char* s);
	const char* GET_STR(const char* s);
	void SET_NUM(const char* s, double v);
	void SET_STR(const char* s, const char* v);
	void SET_ADDR(const char* s, size_t v);
};
#pragma pack(pop)
private:
	static lua_State* L;
	static CRITICAL_SECTION cs_lua;
	static const char* FName;
	static time_t reload_tm;
	static bool lua_debug;
	static CONFIG config;

public:
	static void game__Patch(size_t address, int type, double value);
	static double game__Get(size_t address, int type, size_t offset);

public:
	time_t GetFileTime(const char* path);
	void FunctionsRegister();
	void FunctionsExec();
	void SetItem();
	void GetItem();
	void Init();
	void Update();
	void HeartBeat(size_t tick);


public:
	CONFIG GetConfig() { return config; }

public:
	static LuaManager* GetInstance()
	{
		if (!instance)
			instance = new LuaManager();
		return instance;
	}
	static LuaManager* instance;
};


#endif