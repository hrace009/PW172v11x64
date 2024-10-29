//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _PACKET_H_
#define _PACKET_H_

class Packet
{
public:
	enum
	{
		CGAME_SEND = 0,
		CGAME_RECV = 1,
		GET_MAIN_INFO_RE = 13001,
		GET_MAIN_INFO_OTHER_RE = 13002,
		ARENAQUERYINFO_RE = 13009,

		CMD_INSTANCE_REFRESH = 700,
		CMD_MONEY = 701,
		CMD_MONEYS = 702,
		CMD_OFFLINE_ROLE = 721,
		CMD_OFFLINE_CAT = 722,
		CMD_SKILL_SET = 703,
		CMD_SKILL_SENDER = 704,
		CMD_SKILL_SCRIPT = 705,
		CMD_PLAYER_DUMP = 706,
		CMD_PLAYER_INFO = 707,
		CMD_AUTOSWAP = 708,
		CMD_ELEMENTSKILL = 709,
		CMD_TEST = 710,
		CMD_CLIENT_SKILL = 711,
		CMD_FILTER_SKILL = 712,
		CMD_SEND_HWID = 713,
		CMD_CSKILL = 999,
		GET_MAIN_INFO = 743,
		CMD_COLOR_NAME = 744,


		ARENA_MODE_1X1 = 1,
		ARENA_MODE_3X3 = 2,
		ARENA_MODE_6X6 = 3,
		ARENA_CMD_QUIT = 730,
		ARENA_CMD_JOIN = 731,
		ARENA_CMD_QUERY = 739,

	};
public:
#pragma pack(push, 1)
	struct arena_query_info
	{
		//short cmd;
		int search_time;
		int self_score;
		int team_score;
		int win_count;
		int lose_count;
	};

	struct get_main_info_other
	{
		//short cmd;
		int roleid;
		int colot_name;
		int rank_exp;
		int rank_level;
	};

	struct get_main_info
	{
		short cmd;
		int roleid;
	};

	struct arena_join
	{
		short cmd;
		int mode;
	};

#pragma pack(pop)

private:
	size_t offt;
	size_t type;
public:
	void Init();
	void Log(const char* s);
	void Log(int c, unsigned short cmd, size_t x);
	void Dump(int c, unsigned short cmd, void* buf, size_t size);

	inline short GetProtocol() { return type & 0xffff; }

	size_t OnSend();
	size_t OnRecv();
	size_t OnGameDataSend(int c, unsigned short cmd, void * buf, size_t size);
	size_t OnGameDataRecv(int type, void* it, int size, int result);
	size_t FactionOPRequest();

	void GameDataSend(void* Buf, size_t size);
	void GameDataSend(short Buf);

	int SelfGetExtProperty(void* buff, int size);
	int ArenaQueryInfoRe(void* _this, size_t size);
	void EquipItem(void* Buf, size_t size);
	void GetMainInfo(int roleid);
	void ArenaJoin(int mode);

public:
	static Packet* GetInstance()
	{
		if (!instance)
			instance = new Packet();
		return instance;
	}
	static Packet* instance;
};


#endif