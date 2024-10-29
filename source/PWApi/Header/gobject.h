//-------------------------------------------------------------------------------------------------------------------------
//--ASM DATA (c) DEADRAKY 2022
//-------------------------------------------------------------------------------------------------------------------------
#ifndef _GOBJECT_H_
#define _GOBJECT_H_

#include <iostream>
#include <vector>
#include "player.h"


enum MAN : size_t
{
	MAN_PLAYER = 0,		//	Player manager
	MAN_NPC,			//	NPC manager
	MAN_MATTER,			//	Matter manager
	MAN_ORNAMENT,		//	Ornament manager
	MAN_SKILLGFX,		//	Skill Gfx Manager
	MAN_ATTACKS,		//	Attack Manager
	MAN_DECAL,			//	Decal manager
	NUM_MANAGER,
};

struct CECWorld
{
	void* offt;
	void* m_pGameRun;
	void* m_pA3DTerrain;				//	Terrain object
	void* m_pA3DTerrainWater;			//	Terrain water object
	void* m_pA3DTrnCuller;				//	Terrain culler
	void* m_pA3DSky;					//	Sky object
	void* m_pCDS;						//	CDS object
	void* CAnimationManager;
	void* m_aManagers[NUM_MANAGER];		//	Manager array
	void* m_pForest;					//	Forest Object for the world
	void* m_pGrassLand;					//	Grass Land Object for the world
	void* m_pTerrainOutline;			//	Terrain outline object
	void* m_pCloudManager;				//	Clouds object
	void* m_pScene;						//	Scene object
	void* m_pSunMoon;					//	Sun and moon in the world
	void* m_pRain;						//	rain in the world
	void* m_pSnow;						//	snow in the world
	void* m_pPrecinctSet;				//	Precinct set
	void* m_pCurPrecinct;				//	Current precinct host player is in
	void* m_pRegionSet;					//	Region set
	void* m_pCurRegion;					//	Current region host player is in
	void* m_pCurPetRegion;				//  Current region the pet is in
	void* m_pSceneLights;				//	all lights in the scene
	void* m_pAssureMove;				//	object used to assure move
};

struct CECUIManager
{
	void* offt;
	void*	m_pA3DEngine;	//	A3D engine object
	void*	m_pCurUIMan;	//	Current UI manager
	size_t	m_iCurUIMan;	//	Current UI manager inde
	void*	m_pScriptMan;	//	help system
};

struct CECGameRun
{
	void* offt;
	void* reserve1;
	void* reserve2;
	void* reserve3;
	void* reserve4;
	void* reserve5;
	CECUIManager* m_pUIManager;		//	UI manager
	CECWorld* m_pWorld;			//	Game world
	void* m_pInputCtrl;		//	Input controller
	void* m_pHostInputFilter;		//	Host input filter
	void* m_pHomeInputFilter;		//	Home input filter
	void* reserve6;
	GPlayer* m_pHostPlayer;		//	Host player object

};

struct CECGame
{
	void* offt;
	void* m_pA3DEngine;
	void* m_pA3DDevice;
	void* m_pDirLight;			//	Directional light
	void* m_pDynamicLight;		//	Dynamic point light
	void* m_pViewport;			//	Main viewport
	void* m_pConfigs;			//	Configs
	CECGameRun* m_pGameRun;			//	Game run object
	void* m_pGameSession;		//	Game session
	void* m_pRTDebug;			//	Run-Time debug object
	void* m_pA3DGFXExMan;		//	GFX object manager
	void* m_pECModelMan;		//	ECModel manager
	void* m_pShadowRender;		//	Shadow renderer object
	void* m_pPortraitRender;	//	Portrait renderer object
	void* m_pGFXCaster;			//	GFX caster
	void* m_FixedMsgs;			//	Fixed message table
	void* m_ItemDesc;			//	Item desciption string table
	void* m_ItemExtDesc;		//	Item extend description string table
	void* m_SkillDesc;			//	Skill description string table
	void* m_BuffDesc;			//	Buff description string table
	void* m_ItemExtProps;		//	Item extend properties table
	void* m_ItemColTab;			//	Item color table	
	void* m_CoordTab;			//  Object(NPC,maps, etc) coordinates table
	void* m_ConsumeReward;		//  Current consume reward configs
	void* m_pItemDataMan;		//	global templates manager
	void* m_pElementDataMan;	//	global element templates manager
	void* m_pTaskMan;			//	Task template manager
	void* m_pImageRes;			//	Image resources
	void* m_pSkinRender1;		//	Skin render 1
	void* m_pSkinRender2;		//	Skin render 2
	void* m_pBackMusic;			//	Back ground music
	void* m_pSoundCache;		//	Sound cache
	void* m_pPrivilege;			//	Client privilege
	void* m_pFactionMan;		//	Faction manager
	void* m_pDynObjPath;		//	Dynamic object path table
	void* m_SuiteEquipTab;		//	Suite equipment table
	void* m_SuiteFashionTab;
	void* m_pLitModelRender1;	//	Backup lit model render
	void* m_PetAutoSkills;		//  Pet Auto skill table
};

struct CECBase
{
	CECGame* g_pGame;
};

CECBase* GetCECBase();

//----------------------------------------------------------------------------------------------------------------------------------------------

class NpcRemote
{
private:
	enum : size_t
	{
		GP_STATE_SHAPE = 0x00000001,
		GP_STATE_EMOTE = 0x00000002,
		GP_STATE_INVADER = 0x00000004,
		GP_STATE_SITDOWN = 0x00000020,
		GP_STATE_EXTEND_PROPERTY = 0x00000040,
		GP_STATE_CORPSE = 0x00000080,

		//	Used only by player
		GP_STATE_PARIAH = 0x00000008,
		GP_STATE_FLY = 0x00000010,
		GP_STATE_TEAM = 0x00000100,
		GP_STATE_TEAMLEADER = 0x00000200,
		GP_STATE_ADV_MODE = 0x00000400,
		GP_STATE_FACTION = 0x00000800,
		GP_STATE_BOOTH = 0x00001000,
		GP_STATE_FASHION = 0x00002000,
		GP_STATE_GMFLAG = 0x00004000,
		GP_STATE_PVPFLAG = 0x00008000,
		GP_STATE_EFFECT = 0x00010000,
		GP_STATE_INPVPCOMBAT = 0x00020000,
		GP_STATE_IN_DUEL = 0x00040000,	//	是否正在决斗中
		GP_STATE_IN_MOUNT = 0x00080000,	//	正在骑乘中
		GP_STATE_IN_BIND = 0x00100000,	//	和别人绑在一起
		GP_STATE_BC_INVADER = 0x00200000,	//	Battle camp: invader
		GP_STATE_BC_DEFENDER = 0x00400000,	//	Battle camp: defender
		GP_STATE_SPOUSE = 0x00800000,	//	配偶id
		GP_STATE_GOBLINREFINE = 0x01000000,	//  小精灵是否已经激活
		GP_STATE_SHIELDUSER = 0x02000000,	//  是否完美神盾用户
		GP_STATE_INVISIBLE = 0x04000000,	//  隐身
		GP_STATE_EQUIPDISABLED = 0x08000000,	//  Equipment disabled
		GP_STATE_FORBIDBESELECTED = 0x10000000,	//	禁止被选中 (NPC也有效)
		GP_STATE_PLAYERFORCE = 0x20000000,	//	已加入势力
		GP_STATE_MULTIOBJ_EFFECT = 0x40000000,	//	与其他对象存在特殊效果
		GP_STATE_COUNTRY = 0x80000000,		//已加入国家

		//	Used only by NPC
		GP_STATE_NPC_DELAYDEAD = 0x00000008,
		GP_STATE_NPC_ADDON1 = 0x00000100,
		GP_STATE_NPC_ADDON2 = 0x00000200,
		GP_STATE_NPC_ADDON3 = 0x00000400,
		GP_STATE_NPC_ADDON4 = 0x00000800,
		GP_STATE_NPC_ALLADDON = 0x00000F00,
		GP_STATE_NPC_PET = 0x00001000,	//	Pet flag
		GP_STATE_NPC_NAME = 0x00002000,
		GP_STATE_NPC_FIXDIR = 0x00004000,	//	方向固定
		GP_STATE_NPC_MAFIA = 0x00008000,	//	所属帮派（用于帮派PVP中矿车等）
		GP_STATE_NPC_FLY = 0x00010000,
		GP_STATE_NPC_SWIM = 0x00020000,

		DISTANCE_NPC_MAX = 8,
	};
private:
	struct A3DVECTOR3
	{
		float x, y, z;
	};

	struct info_npc
	{
		int nid;
		int tid;			//template id
		int vis_tid;		//
		A3DVECTOR3 pos;
		unsigned short seed;		// seed of customize data
		unsigned char dir;
		int state;
		int state2;
	};

	struct npc_pool
	{
		int id;
		int tid;
		void* npc;
	};

private:

	static npc_pool pNPCs[DISTANCE_NPC_MAX];

public:
	void Init();
	void* Create(int tid, size_t i);
	void Delete(size_t i);
	void* Get(size_t i);
	void* GetNPCbyID(int id);
	int GetNPCid(size_t i);

	static NpcRemote* GetInstance()
	{
		if (!instance)
			instance = new NpcRemote();
		return instance;
	}
	static NpcRemote* instance;
};

//----------------------------------------------------------------------------------------------------------------------------------------------

class Gobject
{
public:
	enum : size_t
	{
		PLAYER_POOL = 0,
		NPC_POOL = 1,
		MATTER_POOL = 2,
		
		MAX_POOL = 6000,
	};
private:
	struct OBJECT
	{
		void* object;
		int id;
	};

	struct PLAYER : public OBJECT
	{
		int colot_name;
		int rank_exp;
		int rank_level;

		PLAYER(void * object, int id)
		{
			memset(this, 0x00, sizeof(this[0]));
			this->object = object;
			this->id = id;
		}
	};

	struct NPC : public OBJECT
	{
		
		NPC(void* object, int id)
		{
			memset(this, 0x00, sizeof(this[0]));
			this->object = object;
			this->id = id;
		}
	};

	struct MATTER : public OBJECT
	{
		
		MATTER(void* object, int id)
		{
			memset(this, 0x00, sizeof(this[0]));
			this->object = object;
			this->id = id;
		}
	};
private:
	std::vector <PLAYER> player_pool;
	std::vector <NPC> npc_pool;
	std::vector <MATTER> matter_pool;


public:
	void Init();
	void Create(int type, int id, void* offt);
	void Destroy(int type, int id);

	PLAYER* GetPlayerInfo(int id);
	size_t SetPlayerInfo(void* buf, size_t size);


	static Gobject* GetInstance()
	{
		if (!instance)
			instance = new Gobject();
		return instance;
	}
	static Gobject* instance;
};


#endif