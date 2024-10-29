//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

struct GPlayer
{
	int GetData(int v);
	int GetId();
	int GetTargetId();
	void PrepareNPCService(int it);
	int GetTargetNPCId();
	void SetTargetNPCId(int it);
	int GetLevel();
	int GetMp();
	int GetMaxMp();
	int GetHp();
	int GetMaxHp();


};


GPlayer* GetPlayer();
GPlayer* GetElsePlayer(int tid);
void GetElsePlayerInfo();

#endif
