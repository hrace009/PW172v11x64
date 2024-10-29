
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
#include "../Header/asm.h"
#include "../Header/packet.h"
#include "../Header/main.h"
#include "../Header/gobject.h"

Gobject* Gobject::instance = 0;
NpcRemote* NpcRemote::instance = 0;
NpcRemote::npc_pool NpcRemote::pNPCs[NpcRemote::DISTANCE_NPC_MAX];
CRITICAL_SECTION object_cs;

CECBase* GetCECBase()
{
	return (CECBase*)CONFIG::BASE_ADDRES;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void NpcRemote::Init()
{
	memset(&pNPCs, 0x00, sizeof(pNPCs));
}

void* NpcRemote::Create(int tid, size_t i)
{
	if (i < DISTANCE_NPC_MAX && !pNPCs[i].npc)
	{
		info_npc Info;
		memset(&Info, 0x00, sizeof(Info));
		int id = 0x7FFF | 0x80000000 + i;

		pNPCs[i].id = id;
		pNPCs[i].tid = tid;

		Info.nid = id;
		Info.tid = tid;
		Info.vis_tid = tid;

		void* npcman = GetCECBase()->g_pGame->m_pGameRun->m_pWorld->m_aManagers[MAN_NPC];
		if (npcman)
		{
			pNPCs[i].npc = ASM_CreateNPC(npcman, &Info);
			return pNPCs[i].npc;
		}
	}
	return NULL;
}

void NpcRemote::Delete(size_t i)
{
	if (i < DISTANCE_NPC_MAX && pNPCs[i].npc)
	{
		//ASM_DeleteNPC(pNPCs[i].npc);
	}
}

void* NpcRemote::Get(size_t i)
{
	if (i < DISTANCE_NPC_MAX)
	{
		return pNPCs[i].npc;
	}
	return NULL;
}

int NpcRemote::GetNPCid(size_t i)
{
	if (i < DISTANCE_NPC_MAX)
	{
		return pNPCs[i].id;
	}
	return 0;
}

void* NpcRemote::GetNPCbyID(int id)
{
	for (size_t i = 0; i < DISTANCE_NPC_MAX; i++)
	{
		if (id == pNPCs[i].id)
		{
			return pNPCs[i].npc;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Gobject::Init()
{
	InitializeCriticalSection(&object_cs);
	EnterCriticalSection(&object_cs);

	player_pool.clear();
	player_pool.reserve(MAX_POOL);

	npc_pool.clear();
	//npc_pool.reserve(MAX_POOL);

	matter_pool.clear();
	//matter_pool.reserve(MAX_POOL);
	LeaveCriticalSection(&object_cs);
}

void Gobject::Create(int type, int id, void* offt)
{
	EnterCriticalSection(&object_cs);
	MainApi* Api = MainApi::GetInstance();
	switch (type)
	{
	case PLAYER_POOL:
	{
		for (size_t i = 0; i < player_pool.size(); i++)
		{
			if (player_pool.at(i).id == id)
			{
				player_pool.erase(player_pool.begin() + i);
				break;
			}
		}
		player_pool.push_back(PLAYER(offt, id));

		if (Api->GetLog())
		{
			char Src[256];
			sprintf_s(Src, "[%.24s] Object::Create: id = %d , pool_size = %d \n", Api->GetTimeStr(), id, player_pool.size() );
			Api->Log(Src);
		}

		break;
	}

	default:
		break;
	}
	LeaveCriticalSection(&object_cs);
}

void Gobject::Destroy(int type, int id)
{
	EnterCriticalSection(&object_cs);
	MainApi* Api = MainApi::GetInstance();
	switch (type)
	{
	case PLAYER_POOL:
	{
		for (size_t i = 0; i < player_pool.size(); i++)
		{
			if (player_pool.at(i).id == id)
			{
				player_pool.erase(player_pool.begin() + i);
				break;
			}
		}

		if (Api->GetLog())
		{
			char Src[256];
			sprintf_s(Src, "[%.24s] Object::Destroy: id = %d , pool_size = %d \n", Api->GetTimeStr(), id, player_pool.size());
			Api->Log(Src);
		}

		break;
	}
	default:
		break;
	}
	LeaveCriticalSection(&object_cs);
}

Gobject::PLAYER* Gobject::GetPlayerInfo(int id)
{
	static PLAYER pElse(0, 0);
	EnterCriticalSection(&object_cs);
	MainApi* Api = MainApi::GetInstance();
	memset(&pElse, 0x00, sizeof(pElse));
	for (size_t i = 0; i < player_pool.size(); i++)
	{
		if (player_pool.at(i).id == id)
		{
			pElse = player_pool.at(i);
			break;
		}
	}
	/*
	if (Api->GetLog())
	{
		char Src[256];
		sprintf_s(Src, "[%.24s] Object::Info: id = %d , pool_size = %d , get_id = %d \n", Api->GetTimeStr(), id, player_pool.size(), pElse.id);
		Api->Log(Src);
	}
	*/
	LeaveCriticalSection(&object_cs);
	return &pElse;
}

size_t Gobject::SetPlayerInfo(void* buf, size_t size)
{
	size_t res = -1;
	EnterCriticalSection(&object_cs);
	MainApi* Api = MainApi::GetInstance();
	if (buf && size >= sizeof(Packet::get_main_info_other))
	{
		Packet::get_main_info_other* gmio = (Packet::get_main_info_other*)buf;
		int id = gmio->roleid;

		for (size_t i = 0; i < player_pool.size(); i++)
		{
			if (player_pool.at(i).id == id)
			{
				Packet::get_main_info_other* gmio = (Packet::get_main_info_other*)buf;
				player_pool.at(i).colot_name = gmio->colot_name;
				player_pool.at(i).rank_exp = gmio->rank_exp;
				player_pool.at(i).rank_level = gmio->rank_level;
				res = -2;
				break;
			}
		}

		if (Api->GetLog())
		{
			char Src[256];
			sprintf_s(Src, "[%.24s] Object::Info: id = %d , pool_size = %d , res = %d \n", Api->GetTimeStr(), id, player_pool.size(), res);
			Api->Log(Src);
		}

	}
	LeaveCriticalSection(&object_cs);
	return res;
}

