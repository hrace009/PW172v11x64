//---------------------------------------------------------------------------------------------------------------------------
//--PW LUA SCRIPT GDELIVERYD (C) DeadRaky 2023
//---------------------------------------------------------------------------------------------------------------------------
#ifndef __GNET_LUABASE_H
#define __GNET_LUABASE_H

#define LUA_MUTEX_BEGIN Lock(); \
							try \
						{ 
							//TODO
#define LUA_MUTEX_END	} \
							catch (...) \
							{ \
								printf("LUA::PANIC::EXCEPTION: ERROR \n"); \
							} \
							Unlock();

#pragma pack(push, 1)
struct lua_State;
class LuaTimer;
class LuaBase
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
public:
	LuaBase();
	~LuaBase();

	void Init(const char *);
	void Init();
	void HeartBeat();
	void Update();
	void Lock();
	void Unlock();
	void SetIt();
	void GetIt();
	void Exec();
	void Register();

	template <class... Args> void Event(const char* EventName, Args&&... args);
	template <typename T, class... Args> T Event(const char* EventName, Args&&... args);

	bool GetNum(const char* s, double& v);
	bool GetString(const char* s, const char* v);
	bool SetNum(const char* s, double v);
	bool SetString(const char* s, const char* v);
	bool SetAddr(const char* s, long long v);
	bool IsTrue(int it, int * table);
	time_t GetFileTime(const char* path);

public:
	static void game__Patch(long long address, int type, double value);
	static double game__Get(long long address, int type, long long offset);

public:
	virtual void EventInit();
	virtual void EventUpdate();
	virtual void EventHeartBeat();
	virtual void FunctionsRegister();
	virtual void FunctionsExecute();
	virtual void GetItem();
	virtual void SetItem();

protected:
	lua_State* L;
	pthread_mutex_t lua_mutex;
	LuaTimer * lua_timer;
	const char* FName;
	size_t tick;
	time_t reload_tm;
	bool lua_debug;
};

#pragma pack(pop)

#ifdef LUABRIDGE

template <class... Args> inline void LuaBase::Event(const char* EventName, Args&&... args)
{
	LUA_MUTEX_BEGIN
	luabridge::LuaRef Event = luabridge::getGlobal(L, EventName);
	if (L && !Event.isNil() && Event.isFunction())
	{
		Event(std::forward<Args>(args)...);
	}
	else
	{
		printf("LuaBase::Event: %s not font !!! \n", EventName);
	}
	LUA_MUTEX_END
}

template <typename T, class... Args> inline T LuaBase::Event(const char* EventName, Args&&... args)
{
	T res = NULL;
	LUA_MUTEX_BEGIN
	luabridge::LuaRef Event = luabridge::getGlobal(L, EventName);
	if (L && !Event.isNil() && Event.isFunction())
	{
		res = Event(std::forward<Args>(args)...)[0];
	}
	else
	{
		printf("LuaBase::Event: %s not font !!! \n", EventName);
	}
	LUA_MUTEX_END
	return res;
}

#endif

#endif