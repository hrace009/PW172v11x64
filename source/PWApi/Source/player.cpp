
#include "../Header/asm.h"
#include "../Header/config.h"
#include "../Header/informer.h"
#include "../Header/main.h"
#include "../Header/player.h"

GPlayer* GetPlayer()
{
	if ((size_t)GetCECBase() > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun->m_pHostPlayer > CONFIG::VAL_ADDRESS
		)
	{
		return GetCECBase()->g_pGame->m_pGameRun->m_pHostPlayer;
	}
	return NULL;
}

GPlayer* GetElsePlayer(int tid)
{
	if ((size_t)GetCECBase() > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun->m_pWorld > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun->m_pWorld->m_aManagers > CONFIG::VAL_ADDRESS &&
		(size_t)GetCECBase()->g_pGame->m_pGameRun->m_pWorld->m_aManagers[0] > CONFIG::VAL_ADDRESS
		)
	{
		if (tid < 1024)
		{
			GPlayer* pImp = GetPlayer();
			if (pImp)
			{
				tid = pImp->GetTargetId();
				if (tid >= 1024)
				{
					return (GPlayer*)ASM_GetElsePlayer(GetCECBase()->g_pGame->m_pGameRun->m_pWorld->m_aManagers[0], tid);
				}
			}
		}
	}
	return NULL;
}

void GetElsePlayerInfo()
{
	char Src[512];
	MainApi * api = MainApi::GetInstance();
	ClassInformer * info = ClassInformer::GetInstance();

	GPlayer* pElse = GetElsePlayer(0);
	if (pElse)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			int offt = (i * sizeof(size_t));
			int value = pElse->GetData((i * sizeof(size_t)));
			
			if (value > CONFIG::SECTION_RDATA_BEGIN && value < CONFIG::SECTION_RDATA_END)
			{
				sprintf_s(Src, "ElsePlayerEnter: offt = %d , value = %d:%s \n", offt, value, info->GetCnet(value).str);
			}
			else
			{
				sprintf_s(Src, "ElsePlayerEnter: offt = %d , value = %d \n", offt, value);
			}
			api->Log(Src);
		}
	}
}

int GPlayer::GetData(int v)
{
	return get_int(this, v);
}

int GPlayer::GetId()
{
	return get_int(this, CONFIG::PIMP_ROLEID);
}

int GPlayer::GetTargetId()
{
	return get_int(this, CONFIG::PIMP_TARGET_ID);
}

int GPlayer::GetTargetNPCId()
{
	return get_int(this, CONFIG::PIMP_NPC_TARGET_ID);
}

void GPlayer::SetTargetNPCId(int it)
{
	setup_int((this+CONFIG::PIMP_NPC_TARGET_ID), it);
}

void GPlayer::PrepareNPCService(int it)
{
	ASM_PrepareNPCService(this, it);
}

int GPlayer::GetLevel()
{
	return get_int(this, CONFIG::PIMP_LEVEL);
}

int GPlayer::GetMp()
{
	return get_int(this, CONFIG::PIMP_CUR_MP);
}

int GPlayer::GetMaxMp()
{
	return get_int(this, CONFIG::PIMP_MAX_MP);
}

int GPlayer::GetHp()
{
	return get_int(this, CONFIG::PIMP_CUR_HP);
}

int GPlayer::GetMaxHp()
{
	return get_int(this, CONFIG::PIMP_MAX_HP);
}
