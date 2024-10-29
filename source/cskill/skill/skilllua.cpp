//---------------------------------------------------------------------------------------------------------------------------
//--PW LUA SCRIPT CSKILL (C) DeadRaky 2023 x 64
//---------------------------------------------------------------------------------------------------------------------------
#define LUABRIDGE

#include <lua.hpp>
#include <LuaBridge.h>
#include <luabase.h>

#include "skill.h"
#include "skilllua.h"

using namespace GNET;
using namespace luabridge;

// ================================================================
// LUA GLOBAL ITEM  
// ================================================================

LuaSkill* LuaSkill::instance = NULL;
LuaSkill::MEMSPACE LuaSkill::data;

// ================================================================
// LUA STRUCT  
// ================================================================

LuaSkill::CSKILL::CSKILL()
{
	memset(this,0x00,sizeof(*this));
}

void LuaSkill::CSKILL::INIT()
{
	memset(this,0x00,sizeof(*this));
}

void LuaSkill::CSKILL::SET_SKILL(int ID, long long FUNC, long long STATE, long long SKILL, long long REID)
{
	if (ID > 0 && ID < MAX_SKILL_COUNT)
	{
		S[ID].FUNC = FUNC;
		S[ID].STATE = STATE;
		S[ID].SKILL = SKILL;
		S[ID].REID = REID;
	}
}

long long LuaSkill::CSKILL::GET_SKILL(int ID, long long & FUNC, long long & STATE, long long & SKILL, long long & REID)
{
	if (ID > 0 && ID < MAX_SKILL_COUNT && S[ID].FUNC)
	{
		FUNC = S[ID].FUNC;
		STATE = S[ID].STATE;
		SKILL = S[ID].SKILL;
		REID = S[ID].REID;
		return 1LL;
	}
	return FUNC = STATE = SKILL = REID = 0LL;
}

long long LuaSkill::CSKILL::GET_STATE(int STATE_INDEX, long long FUNC)
{
	return STATE_INDEX < MAX_STATE_COUNT ? ((FUNC >> STATE_INDEX) & 1u) : 0;
}

//-------------------------------------------------------------------

LuaSkill::CONFIG::CONFIG()
{
	memset(this, 0x00, sizeof(*this));
}

void LuaSkill::CONFIG::INIT()
{
	MAX_SOUL = 72000;
	MAX_SOUL_SHAMAN = 56000;
	FREE_SP = 0; //не требовать дух
	FREE_MONEY = 0; //не требовать монеты
	FREE_ITEM = 0; //не требовать итемы
}

//-------------------------------------------------------------------

LuaSkill::MEMSPACE::MEMSPACE()
{
	config.INIT();
	cskill.INIT();
}

void LuaSkill::MEMSPACE::INIT()
{
	config.INIT();
	cskill.INIT();
}

// ================================================================
// LUA FUNCTIONS 
// ================================================================

void LuaSkill::game__AddSkill(int ID, long long FUNC, long long STATE, long long SKILL, long long REID)
{
	data.cskill.SET_SKILL(ID,FUNC,STATE,SKILL,REID);
}

void LuaSkill::game__Editor(long long skill, int type, double value)
{
	if (skill) ((Skill *)skill)->SkillEdit(type , value);
}

// ================================================================
// LUA ITEMS GET & SET
// ================================================================

void LuaSkill::FunctionsRegister()
{
	getGlobalNamespace(L).addFunction("game__Editor"	,game__Editor	);
	getGlobalNamespace(L).addFunction("game__AddSkill"	,game__AddSkill	);

	SetFuncALLData();
}	

void LuaSkill::SetItem()
{
	
}

void LuaSkill::GetItem()
{
	double res = -1;
	GetNum( "MAX_SOUL"			, res ) ? data.config.MAX_SOUL 			= res : res == -1;
	GetNum( "MAX_SOUL_SHAMAN"	, res ) ? data.config.MAX_SOUL_SHAMAN 	= res : res == -1;
	GetNum( "FREE_SP"			, res ) ? data.config.FREE_SP 			= res : res == -1;
	GetNum( "FREE_MONEY"		, res ) ? data.config.FREE_MONEY 		= res : res == -1;
	GetNum( "FREE_ITEM"			, res ) ? data.config.FREE_ITEM			= res : res == -1;
}	

void LuaSkill::FunctionsExecute()
{
	data.INIT();
}

// ================================================================
// LUA EVENTS 
// ================================================================

void LuaSkill::EventInit()
{
	Event("Init");
}

void LuaSkill::EventUpdate()
{
	Event("Update");
}

void LuaSkill::EventHeartBeat()
{
	Event("HeartBeat", tick);
}

// ================================================================
// LUA SKILL EVENTS 
// ================================================================

double LuaSkill::StateAttack(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_STATEATTACK) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__StateAttack", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::BlessMe(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_BLESSME) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__BlessMe", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetExecutetime(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETEXECUTETIME) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetExecutetime", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetCoolingtime(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETCOOLINGTIME) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetCoolingtime", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetEnmity(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETENMITY) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetEnmity", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetRequiredSp(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETREQUIREDSP) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRequiredSp", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetRequiredLevel(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETREQUIREDLEVEL) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRequiredLevel", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetRequiredItem(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETREQUIREDITEM) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRequiredItem", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetRequiredMoney(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETREQUIREDMONEY) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRequiredMoney", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetMaxability(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETMAXABILITY) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetMaxability", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetRequiredRealmLevel(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETREQUIREDREALMLEVEL) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRequiredRealmLevel", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetRadius(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETRADIUS) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetRadius", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetAttackdistance(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETATTACKDISTANCE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetAttackdistance", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetAngle(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETANGLE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetAngle", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetPraydistance(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETPRAYDISTANCE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetPraydistance", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetEffectdistance(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETEFFECTDISTANCE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetEffectdistance", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetT0(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETTALENT0) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetT0", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetT1(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETTALENT1) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetT1", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetT2(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETTALENT2) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetT2", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}	

double LuaSkill::GetAttackspeed(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETATTACKSPEED) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetAttackspeed", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::TakeEffect(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_TAKEEFFECT) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__TakeEffect", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetHitrate(GNET::Skill * skill, int id)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && (FUNC & FUNC_SKILL) && (SKILL & SKILL_GETHITRATE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__GetHitrate", id);
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::GetTime(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_GETTIME) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__GetTime", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Quit(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_QUIT) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Quit", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Loop(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_LOOP) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Loop", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Bypass(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_BYPASS) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Bypass", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Calculate(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_CALCULATE) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Calculate", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Interrupt(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_INTERRUPT) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Interrupt", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Cancel(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_CANCEL) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Cancel", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

double LuaSkill::Skip(GNET::Skill * skill, int id, unsigned int state)
{
	double res = -0;
	long long FUNC, STATE, SKILL, REID;
	if( skill && id > 0 && state < 10 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && data.cskill.GET_STATE(state,FUNC) && (STATE & STATE_SKIP) )
	{
		char EventName[40];
		sprintf(EventName, "Skill%dStub__State%d__Skip", id , (state+1));
		res = Event<double>(EventName,(long long)skill);
	}
	return res;
}

Skill * LuaSkill::Create(int id)
{
	Skill * skill = NULL;
	long long FUNC, STATE, SKILL, REID;
	if( id > 0 && data.cskill.GET_SKILL(id, FUNC, STATE, SKILL, REID) && ((FUNC & FUNC_CREATE) || (FUNC & FUNC_REID)) )
	{
		const Skill * sk = Skill::GetStub( ((FUNC & FUNC_REID) && REID) ? REID : id );
		if (sk)
		{
			skill = sk->Clone();
			
			if ( skill->GetId() == REID ) 
			{
				skill->SetId(id);
			}
			
			if ( (FUNC & FUNC_CREATE) )
			{
				char EventName[40];
				sprintf(EventName, "Skill%d__Create", id );
				long long v = (long long)skill;
				GetInstance()->Event(EventName,v);
			}
		}
	}
	if(skill == NULL)
	{
		const Skill * sk = Skill::GetStub(id);
		return sk?sk->Clone():NULL;
	}
	return skill;
}

// ================================================================
// LUA CONSTRUCTOR 
// ================================================================

LuaSkill::LuaSkill()
{

}

LuaSkill::~LuaSkill()
{
	
}

LuaSkill * LuaSkill::GetInstance()
{
	if (!instance)
	{
		instance = new LuaSkill();
	}
	return instance;
}

//============================================================================================
//--SKILL & FUNC & DATA BASE 
//============================================================================================

#define REG_FUNC(v) getGlobalNamespace(L).addFunction( #v , v);
void LuaSkill::SetFuncALLData()
{
	REG_FUNC(SetPray        				);
	REG_FUNC(SetInform      				);
	REG_FUNC(SetPerform     				);
	REG_FUNC(SetDecelfmp    				);
	REG_FUNC(SetDecelfap    				);
	REG_FUNC(UseArrow       				);
	REG_FUNC(IsUsingWeapon  				);
	REG_FUNC(GetSkilllevel  				);
	REG_FUNC(SetShowicon    				);
	REG_FUNC(SetIntarg      				);
	REG_FUNC(SetEnable      				);
	REG_FUNC(SetInvader     				);
	REG_FUNC(SetDecsp       				);
	REG_FUNC(SetForm        				);
	REG_FUNC(SetMaxhp       				);
	REG_FUNC(SetInteam      				);
	REG_FUNC(SetSp          				);
	REG_FUNC(SetRange       				);
	REG_FUNC(SetLevel       				);
	REG_FUNC(SetRank        				);
	REG_FUNC(SetHpgen       				);
	REG_FUNC(SetMpgen       				);
	REG_FUNC(SetPlus        				);
	REG_FUNC(SetRatioState  				);
	REG_FUNC(SetDamage      				);
	REG_FUNC(SetGolddamage  				);
	REG_FUNC(SetWooddamage  				);
	REG_FUNC(SetWaterdamage 				);
	REG_FUNC(SetFiredamage  				);
	REG_FUNC(SetEarthdamage 				);
	REG_FUNC(SetMagicDamage 				);
	REG_FUNC(SetDegree      				);
	REG_FUNC(GetSLevel      				);
	REG_FUNC(GetSAttack     				);
	REG_FUNC(GetSMagicattack				);
	REG_FUNC(GetPlus       					);
	REG_FUNC(GetRatioState 					);
	REG_FUNC(GetDamage     					);
	REG_FUNC(GetGolddamage 					);
	REG_FUNC(GetWooddamage 					);
	REG_FUNC(GetWaterdamage					);
	REG_FUNC(GetFiredamage 					);
	REG_FUNC(GetEarthdamage					);
	REG_FUNC(GetMagicdamage					);
	REG_FUNC(GetDegree     					);
	REG_FUNC(GetWorldTag                    );
	REG_FUNC(GetId		                    );
	REG_FUNC(GetMp                          );
	REG_FUNC(GetHp                          );
	REG_FUNC(GetSp                          );
	REG_FUNC(GetAp                          );
	REG_FUNC(GetCls                         );
	REG_FUNC(GetForm                        );
	REG_FUNC(GetMaxhp                       );
	REG_FUNC(GetMaxmp                       );
	REG_FUNC(GetLevel                       );
	REG_FUNC(GetRank                        );
	REG_FUNC(GetMoney                       );
	REG_FUNC(GetCurWeapon                   );
	REG_FUNC(GetCurweapon                   );
	REG_FUNC(GetWeapondamage                );
	REG_FUNC(GetWeaponmagicdamage           );
	REG_FUNC(GetInteam                      );
	REG_FUNC(CanAttack                      );
	REG_FUNC(GetRange                       );
	REG_FUNC(GetAttack                      );
	REG_FUNC(GetMagicattack                 );
	REG_FUNC(GetPureattack	                );
	REG_FUNC(GetPuremagicattack             );
	REG_FUNC(GetDefenddegree                );
	REG_FUNC(GetAttackdegree                );
	REG_FUNC(GetDefense	                    );
	REG_FUNC(GetGoldresist	                );
	REG_FUNC(GetWoodresist	                );
	REG_FUNC(GetWaterresist                 );
	REG_FUNC(GetFireresist	                );
	REG_FUNC(GetEarthresist                 );
	REG_FUNC(GetCrit		                );
	REG_FUNC(GetSoulpower	                );
	REG_FUNC(GetHistoricalmaxlevel          );
	REG_FUNC(GetRealm                       );
	REG_FUNC(GetEquipattack                 );
	REG_FUNC(GetEquipmagicattack            );
	REG_FUNC(GetLocalval0                   );
	REG_FUNC(GetLocalval1                   );
	REG_FUNC(GetLocalval2                   );
	REG_FUNC(GetCombat		                );
	REG_FUNC(GetElfmp                       );
	REG_FUNC(GetElfap                       );
	REG_FUNC(GetLanding                     );
	REG_FUNC(GetAiring                      );
	REG_FUNC(GetWatering                    );
	REG_FUNC(GetRiding                      );
	REG_FUNC(GetSkillenhance2               );
	REG_FUNC(GetRangetotarget               );
	REG_FUNC(GetProduceSkill                );
	REG_FUNC(GetDynskillcounter             );
	REG_FUNC(GetLvalue                      );
	REG_FUNC(GetPrayrangeplus               );
	REG_FUNC(GetRand                        );
	REG_FUNC(GetBalls                       );
	REG_FUNC(GetProbability                 );
	REG_FUNC(GetProbabilityInt              );
	REG_FUNC(GetRatio                       );
	REG_FUNC(GetValue                       );
	REG_FUNC(GetAmount                      );
	REG_FUNC(GetRatioInt                    );
	REG_FUNC(GetValueInt                    );
	REG_FUNC(GetAmountInt                   );
	REG_FUNC(GetShowicon                    );
	REG_FUNC(GetSuccess                     );
	REG_FUNC(GetImmune                      );
	REG_FUNC(Gettime                        );
	REG_FUNC(GetIntarg                      );
	REG_FUNC(GetEnable                      );
	REG_FUNC(GetInvader                     );
	REG_FUNC(GetElfstr                      );
	REG_FUNC(GetElfagi                      );
	REG_FUNC(GetElfvit                      );
	REG_FUNC(GetElfeng                      );
	REG_FUNC(GetElflevel                    );
	REG_FUNC(GetTargetregionplayernum       );
	REG_FUNC(GetCharging                    );
	REG_FUNC(GetDecsp                       );
	REG_FUNC(GetDecmp                       );
	REG_FUNC(GetIncgold                     );
	REG_FUNC(GetIncwood                     );
	REG_FUNC(GetIncwater                    );
	REG_FUNC(GetIncfire                     );
	REG_FUNC(GetIncearth                    );
	REG_FUNC(SetDecmp                       );
	REG_FUNC(SetProbability                 );
	REG_FUNC(SetTime                        );
	REG_FUNC(SetRatio                       );
	REG_FUNC(SetValue                       );
	REG_FUNC(SetAmount                      );
	REG_FUNC(SetHp                          );
	REG_FUNC(SetMp                          );
	REG_FUNC(SetIncswim                     );
	REG_FUNC(SetIncgold                     );
	REG_FUNC(SetIncwood                     );
	REG_FUNC(SetIncwater                    );
	REG_FUNC(SetIncfire                     );
	REG_FUNC(SetIncearth                    );
	REG_FUNC(SetAdddefence                  );
	REG_FUNC(SetInchitrate                  );
	REG_FUNC(SetIncpethp                    );
	REG_FUNC(SetIncpetmp                    );
	REG_FUNC(SetIncpetdamage                );
	REG_FUNC(SetIncpetmagicdamage           );
	REG_FUNC(SetIncpetdefense               );
	REG_FUNC(SetIncpetmagicdefense          );
	REG_FUNC(SetIncpetattackdegree          );
	REG_FUNC(SetIncpetdefenddegree          );
	REG_FUNC(SetAddresistance               );
	REG_FUNC(SetAddskilldamage              );
	REG_FUNC(SetAddmaxhp                    );
	REG_FUNC(SetIncswimspeed                );
	REG_FUNC(SetIncdefenselevel             );
	REG_FUNC(SetIncCritReduce               );
	REG_FUNC(SetDirecthurt                  );
	REG_FUNC(SetHeal                        );
	REG_FUNC(SetResurrect                   );
	REG_FUNC(SetSpeedup                     );
	REG_FUNC(SetIncdefence                  );
	REG_FUNC(SetIncattack                   );
	REG_FUNC(SetIncsmite                    );
	REG_FUNC(SetIncmagic                    );
	REG_FUNC(SetDecmagic                    );
	REG_FUNC(SetAbsorbhp                    );
	REG_FUNC(SetInchp                       );
	REG_FUNC(SetDechp                       );
	REG_FUNC(SetIncmp                       );
	REG_FUNC(SetIncdodge                    );
	REG_FUNC(SetDecdodge                    );
	REG_FUNC(SetRepel                       );
	REG_FUNC(SetRepel2                      );
	REG_FUNC(SetRepelAtr                    );
	REG_FUNC(SetBlind                       );
	REG_FUNC(SetDecresist                   );
	REG_FUNC(SetIncresist                   );
	REG_FUNC(SetIncresist2                  );
	REG_FUNC(SetInchurt                     );
	REG_FUNC(SetDechurt                     );
	REG_FUNC(SetDecaccuracy                 );
	REG_FUNC(SetIncaccuracy                 );
	REG_FUNC(SetMagicleak                   );
	REG_FUNC(SetDecattack                   );
	REG_FUNC(SetDecdefence                  );
	REG_FUNC(SetFrighten                    );
	REG_FUNC(SetDizzy                       );
	REG_FUNC(SetSleep                       );
	REG_FUNC(SetFix                         );
	REG_FUNC(SetSealed                      );
	REG_FUNC(SetSlow                        );
	REG_FUNC(SetBleeding                    );
	REG_FUNC(SetThunder                     );
	REG_FUNC(SetToxic                       );
	REG_FUNC(SetBurning                     );
	REG_FUNC(SetFallen                      );
	REG_FUNC(SetFlood                       );
	REG_FUNC(SetFeathershield               );
	REG_FUNC(SetFireshield                  );
	REG_FUNC(SetIceshield                   );
	REG_FUNC(SetRetort                      );
	REG_FUNC(SetSlowpray                    );
	REG_FUNC(SetFastmpgen                   );
	REG_FUNC(SetScaleinchp                  );
	REG_FUNC(SetScaleincmp                  );
	REG_FUNC(SetScaledecmp                  );
	REG_FUNC(SetScaledechp                  );
	REG_FUNC(SetFasthpgen                   );
	REG_FUNC(SetFastattack                  );
	REG_FUNC(SetSlowattack                  );
	REG_FUNC(SetSoilshield                  );
	REG_FUNC(SetIceblade                    );
	REG_FUNC(SetEnhancegold                 );
	REG_FUNC(SetEnhancewood                 );
	REG_FUNC(SetEnhancewater                );
	REG_FUNC(SetEnhancefire                 );
	REG_FUNC(SetEnhancesoil                 );
	REG_FUNC(SetReducegold                  );
	REG_FUNC(SetReducewood                  );
	REG_FUNC(SetReducewater                 );
	REG_FUNC(SetReducefire                  );
	REG_FUNC(SetReducesoil                  );
	REG_FUNC(SetFireblade                   );
	REG_FUNC(SetToxicblade                  );
	REG_FUNC(SetCleardebuff                 );
	REG_FUNC(SetCleardebuff2                );
	REG_FUNC(SetInvincible                  );
	REG_FUNC(SetInvincible2                 );
	REG_FUNC(SetInvincible3                 );
	REG_FUNC(SetInvincible4                 );
	REG_FUNC(SetInvincible5                 );
	REG_FUNC(SetInvincible6                 );
	REG_FUNC(SetInvincible7                 );
	REG_FUNC(SetFastpray                    );
	REG_FUNC(SetAntiwater                   );
	REG_FUNC(SetPanruo                      );
	REG_FUNC(SetBreak                       );
	REG_FUNC(SetYijin                       );
	REG_FUNC(SetXisui                       );
	REG_FUNC(SetJingji                      );
	REG_FUNC(SetFlower1                     );
	REG_FUNC(SetFlower2                     );
	REG_FUNC(SetFlower3                     );
	REG_FUNC(SetFlower4                     );
	REG_FUNC(SetStoneskin                   );
	REG_FUNC(SetIronshield                  );
	REG_FUNC(SetWingshield                  );
	REG_FUNC(SetFirearrow                   );
	REG_FUNC(SetGiant                       );
	REG_FUNC(SetBlessmagic                  );
	REG_FUNC(SetEaglecurse                  );
	REG_FUNC(SetDevilstate                  );
	REG_FUNC(SetFreemove                    );
	REG_FUNC(SetSelfburning                 );
	REG_FUNC(SetFallen2                     );
	REG_FUNC(SetSealed2                     );
	REG_FUNC(SetFix2                        );
	REG_FUNC(SetDechurt2                    );
	REG_FUNC(SetInchurt2                    );
	REG_FUNC(SetInchurt3                    );
	REG_FUNC(SetInchurt4                    );
	REG_FUNC(SetInchurt5                    );
	REG_FUNC(SetDechurt3                    );
	REG_FUNC(SetInchp2                      );
	REG_FUNC(SetIncattack2                  );
	REG_FUNC(SetIncmagic2                   );
	REG_FUNC(SetFastpray2                   );
	REG_FUNC(SetSpeedup2                    );
	REG_FUNC(SetSkillcooldown               );
	REG_FUNC(SetCommoncooldown              );
	REG_FUNC(SetAurafireattack              );
	REG_FUNC(SetAurabless                   );
	REG_FUNC(SetAuracurse                   );
	REG_FUNC(SetAurabless2                  );
	REG_FUNC(SetAuracurse2                  );
	REG_FUNC(SetAurabless3                  );
	REG_FUNC(SetInvisible                   );
	REG_FUNC(SetIncantiinvisibleactive      );
	REG_FUNC(SetInchpsteal                  );
	REG_FUNC(SetInccritdamage               );
	REG_FUNC(SetIncdamagedodge              );
	REG_FUNC(SetIncdebuffdodge              );
	REG_FUNC(SetRebirth                     );
	REG_FUNC(SetDeepenbless                 );
	REG_FUNC(SetWeakenbless                 );
	REG_FUNC(SetWeakenbless2                );
	REG_FUNC(SetHurtwhenuseskill            );
	REG_FUNC(SetInterruptwhenuseskill       );
	REG_FUNC(SetSoulretort                  );
	REG_FUNC(SetSoulsealed                  );
	REG_FUNC(SetSoulbeatback                );
	REG_FUNC(SetSoulstun                    );
	REG_FUNC(SetFishform                    );
	REG_FUNC(SetGminvisible                 );
	REG_FUNC(SetActivatesharpener           );
	REG_FUNC(SetInchurtphysicgold           );
	REG_FUNC(SetInchurtwoodwater            );
	REG_FUNC(SetInchurtfireearth            );
	REG_FUNC(SetAttackattachstate1          );
	REG_FUNC(SetAttackattachstate2          );
	REG_FUNC(SetAttackattachstate3          );
	REG_FUNC(SetAttackattachstate4          );
	REG_FUNC(SetBeattackattachstate1        );
	REG_FUNC(SetBeattackattachstate2        );
	REG_FUNC(SetBeattackattachstate3        );
	REG_FUNC(SetBeattackattachstate4        );
	REG_FUNC(SetBeattackattachstate5        );
	REG_FUNC(SetBeattackattachstate6        );
	REG_FUNC(SetBeattackattachstate7        );
	REG_FUNC(SetBeattackattachstate8        );
	REG_FUNC(SetTransferbuff                );
	REG_FUNC(SetTransferdebuff              );
	REG_FUNC(SetAbsorbbuff                  );
	REG_FUNC(SetAbsorbdebuff                );
	REG_FUNC(SetSummonpet2                  );
	REG_FUNC(SetSummonplantpet              );
	REG_FUNC(SetPetsacrifice                );
	REG_FUNC(SetPlantsuicide                );
	REG_FUNC(SetPoisionseed                 );
	REG_FUNC(SetHpgenseed                   );
	REG_FUNC(SetPhysichurt                  );
	REG_FUNC(SetGoldhurt                    );
	REG_FUNC(SetWoodhurt                    );
	REG_FUNC(SetWaterhurt                   );
	REG_FUNC(SetFirehurt                    );
	REG_FUNC(SetEarthhurt                   );
	REG_FUNC(SetFastprayincmagic            );
	REG_FUNC(SetIncwoodwaterdefense         );
	REG_FUNC(SetSpecialslow                 );
	REG_FUNC(SetSpecialphysichurt           );
	REG_FUNC(SetIncdefencesmite             );
	REG_FUNC(SetIncresistmagic              );
	REG_FUNC(SetTransportmptopet            );
	REG_FUNC(SetTransportdamagetopet        );
	REG_FUNC(SetAbsorbdamageincdefense      );
	REG_FUNC(SetIncrementalhpgen            );
	REG_FUNC(SetChanceofrebirth             );
	REG_FUNC(SetSpecialphysichurttrigger    );
	REG_FUNC(SetLongjumptospouse            );
	REG_FUNC(SetInccountedsmite             );
	REG_FUNC(SetWeapondisabled              );
	REG_FUNC(SetIncaggroondamage            );
	REG_FUNC(SetEnhanceskilldamage          );
	REG_FUNC(SetDetectinvisible             );
	REG_FUNC(SetDetectinvisible2            );
	REG_FUNC(SetFastmpgen2                  );
	REG_FUNC(SetClearinvisible2             );
	REG_FUNC(SetPositionrollback            );
	REG_FUNC(SetPositionrollback2           );
	REG_FUNC(SetHprollback                  );
	REG_FUNC(SetNofly                       );
	REG_FUNC(SetForceselecttarget           );
	REG_FUNC(SetHealabsorb                  );
	REG_FUNC(SetRepelonnormalattack         );
	REG_FUNC(SetInccritresistance           );
	REG_FUNC(SetDeccritresistance           );
	REG_FUNC(SetExchangeposition            );
	REG_FUNC(SetPullover                    );
	REG_FUNC(SetTransmitskillattack         );
	REG_FUNC(SetAdditionalheal              );
	REG_FUNC(SetAdditionalattack            );
	REG_FUNC(SetTransportdamagetoleader     );
	REG_FUNC(SetForbidbeselected            );
	REG_FUNC(SetEnhanceskilldamage2         );
	REG_FUNC(SetCallupteammember            );
	REG_FUNC(SetDelayearthhurt              );
	REG_FUNC(SetDizzyinchurt                );
	REG_FUNC(SetSoulretort2                 );
	REG_FUNC(SetFixondamage                 );
	REG_FUNC(SetApgen2                      );
	REG_FUNC(SetIncattackondamage           );
	REG_FUNC(SetRebirth2                    );
	REG_FUNC(SetHealsteal                   );
	REG_FUNC(SetDropmoneyondeath            );
	REG_FUNC(SetIncattackrange              );
	REG_FUNC(SetQueryotherinventory         );
	REG_FUNC(SetThunderform                 );
	REG_FUNC(SetDelaytransmit               );
	REG_FUNC(SetDecnormalattackhurt         );
	REG_FUNC(SetFreemoveapgen               );
	REG_FUNC(SetIncatkdefhp                 );
	REG_FUNC(SetDenyattackcmd               );
	REG_FUNC(SetHpmpgennotincombat          );
	REG_FUNC(SetInchpmp                     );
	REG_FUNC(SetEnternonpenaltypvp          );
	REG_FUNC(SetLeavenonpenaltypvp          );
	REG_FUNC(SetIncmaxhpatkdfdlevel         );
	REG_FUNC(SetRetort2                     );
	REG_FUNC(SetKnockup                     );
	REG_FUNC(SetPalsy                       );
	REG_FUNC(SetAddattackdegree             );
	REG_FUNC(SetSubattackdegree             );
	REG_FUNC(SetAdddefencedegree            );
	REG_FUNC(SetSubdefencedegree            );
	REG_FUNC(SetSubdefencedegree2           );
	REG_FUNC(SetIncatkdefhp2                );
	REG_FUNC(SetIncsmite3                   );
	REG_FUNC(SetIncpenres                   );
	REG_FUNC(SetAttachstatetoself           );
	REG_FUNC(SetAttachstatetotarget         );
	REG_FUNC(SetFireshield2                 );
	REG_FUNC(SetIceshield2                  );
	REG_FUNC(SetHealshield                  );
	REG_FUNC(SetIncflyspeed                 );
	REG_FUNC(SetIncvigour                   );
	REG_FUNC(SetIncvigour2                  );
	REG_FUNC(SetShortjump                   );
	REG_FUNC(SetShortjump2                  );
	REG_FUNC(SetMovepunish                  );
	REG_FUNC(SetStandpunish                 );
	REG_FUNC(SetStandpunish2                );
	REG_FUNC(SetChantshield                 );
	REG_FUNC(SetChangeselfaggro             );
	REG_FUNC(SetSummonmobs                  );
	REG_FUNC(SetIntervalpalsy               );
	REG_FUNC(SetInternalinjury              );
	REG_FUNC(SetAtkdamagereduce             );
	REG_FUNC(SetDeathresetcd                );
	REG_FUNC(SetAppendenchant               );
	REG_FUNC(SetAppenddamage                );
	REG_FUNC(SetCooldownaward               );
	REG_FUNC(SetHuntersoul                  );
	REG_FUNC(SetNeverdead                   );
	REG_FUNC(SetChangemodel                 );
	REG_FUNC(SetScreeneffect                );
	REG_FUNC(SetAddfrosteffect              );
	REG_FUNC(SetActivefrosteffect           );
	REG_FUNC(SetIncspecskillcrit            );
	REG_FUNC(SetClearfilterbyid             );
	REG_FUNC(SetMoongod                     );
	REG_FUNC(SetDelayskilleffect            );
	REG_FUNC(SetEnhanceskilldamage3         );
	REG_FUNC(SetCritdamagereduce            );
	REG_FUNC(SetImmunemagical2              );
	REG_FUNC(SetPullover2                   );
	REG_FUNC(SetIncphysicaldamage           );
	REG_FUNC(SetIncmagicaldamage            );
	REG_FUNC(SetRemoveaggro                 );
	REG_FUNC(SetCooldownpunish              );
	REG_FUNC(SetAnticlearbuf                );
	REG_FUNC(SetIncenchantrange             );
	REG_FUNC(SetIncphysicalmagicaldefense   );
	REG_FUNC(SetReducegold3                 );
	REG_FUNC(SetReducewater3                );
	REG_FUNC(SetGenhpap                     );
	REG_FUNC(SetDetaindart                  );
	REG_FUNC(SetExtraexpfactor              );
	REG_FUNC(SetSoloIncAttackAndMagic       );
	REG_FUNC(SetSoloIncDefence              );
	REG_FUNC(SetSoloEnhanceResist           );
	REG_FUNC(SetSoloIncMaxHP                );
	REG_FUNC(SetInvincible8                 );
	REG_FUNC(SetSoloHpGen                   );
	REG_FUNC(SetSoloDecHurt                 );
	REG_FUNC(SetSoloAddAttackRange          );
	REG_FUNC(SetThunder3                    );
	REG_FUNC(SetToxic3                      );
	REG_FUNC(SetFlood3                      );
	REG_FUNC(SetBurning3                    );
	REG_FUNC(SetFallen3                     );
	REG_FUNC(SetShattereddreammob           );
	REG_FUNC(SetReduceSpeeddebuff           );
	REG_FUNC(SetShieldNew1                  );
	REG_FUNC(SetShieldNew2                  );
	REG_FUNC(SetNewSpeedBuff                );
	REG_FUNC(SetIraAtiradora                );
	REG_FUNC(SetFeAtiradora                 );
	REG_FUNC(SetNewRemove                   );
	REG_FUNC(SetIncAntiDefenseDegree        );
	REG_FUNC(SetIncPlusMaxHP                );
	REG_FUNC(SetInvisible2                  );
	REG_FUNC(SetAuracurse4ASN               );
	REG_FUNC(SetIncmagic4                   );
	REG_FUNC(SetDecsoul                     );
	REG_FUNC(SetGiantform                   );
	REG_FUNC(SetTransdmg2pet                );
	REG_FUNC(SetSkillcooldown2              );
	REG_FUNC(SetDecphysicalmagicaldefense   );
	REG_FUNC(SetIncsmitedamage              );
	REG_FUNC(SetDecphysicalmagicaldefense2  );
	REG_FUNC(SetFastpray3                   );
	REG_FUNC(SetIncdebuffdodge2             );
	REG_FUNC(SetIncdamagedodge2             );
	REG_FUNC(SetDebithurt                   );
	REG_FUNC(SetSoloAddAttackLevel          );
	REG_FUNC(SetSoloAddDefendLevel          );
	REG_FUNC(SetUltimatePaladin             );
	REG_FUNC(SetAttackplusAtr               );
	REG_FUNC(SetAddPraga                    );
	REG_FUNC(SetRetort3                     );
}
#undef REG_FUNC

double LuaSkill::GetSLevel					  	(long long skill) { return skill ? ((Skill *)skill)->GetLevel								() : -0; }
double LuaSkill::GetSAttack					  	(long long skill) { return skill ? ((Skill *)skill)->GetAttack								() : -0; }
double LuaSkill::GetSMagicattack				  	(long long skill) { return skill ? ((Skill *)skill)->GetMagicattack							() : -0; }	
double LuaSkill::GetPlus						  	(long long skill) { return skill ? ((Skill *)skill)->GetPlus								() : -0; }
double LuaSkill::GetRatioState				  	(long long skill) { return skill ? ((Skill *)skill)->GetRatio								() : -0; }	
double LuaSkill::GetDamage					  	(long long skill) { return skill ? ((Skill *)skill)->GetDamage								() : -0; }
double LuaSkill::GetGolddamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetGolddamage							() : -0; }
double LuaSkill::GetWooddamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetWooddamage							() : -0; }
double LuaSkill::GetWaterdamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetWaterdamage							() : -0; }
double LuaSkill::GetFiredamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetFiredamage							() : -0; }
double LuaSkill::GetEarthdamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetEarthdamage							() : -0; }
double LuaSkill::GetMagicdamage				  	(long long skill) { return skill ? ((Skill *)skill)->GetMagicdamage							() : -0; }
double LuaSkill::GetDegree					  	(long long skill) { return skill ? ((Skill *)skill)->GetDegree								() : -0; }	
	
double LuaSkill::GetWorldTag               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWorldTag              	() : -0; }
double LuaSkill::GetId		             	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetId		             	() : -0; }
double LuaSkill::GetMp                     	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetMp                    	() : -0; }
double LuaSkill::GetHp                     	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetHp                    	() : -0; }
double LuaSkill::GetSp                     	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetSp                    	() : -0; }
double LuaSkill::GetAp                     	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAp                    	() : -0; }
double LuaSkill::GetCls                    	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCls                   	() : -0; }
double LuaSkill::GetForm                   	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetForm                  	() : -0; }
double LuaSkill::GetMaxhp                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetMaxhp                 	() : -0; }
double LuaSkill::GetMaxmp                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetMaxmp                 	() : -0; }
double LuaSkill::GetLevel                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLevel                 	() : -0; }
double LuaSkill::GetRank                   	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRank                  	() : -0; }
double LuaSkill::GetMoney                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetMoney                 	() : -0; }
double LuaSkill::GetCurWeapon              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCurWeapon             	() : -0; }
double LuaSkill::GetCurweapon              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCurweapon             	() : -0; }
double LuaSkill::GetWeapondamage           	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWeapondamage          	() : -0; }
double LuaSkill::GetWeaponmagicdamage      	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWeaponmagicdamage     	() : -0; }
double LuaSkill::GetInteam                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetInteam                	() : -0; }
double LuaSkill::CanAttack                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->CanAttack                	() : -0; }
double LuaSkill::GetRange                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRange                 	() : -0; }
double LuaSkill::GetAttack                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAttack                	() : -0; }
double LuaSkill::GetMagicattack            	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetMagicattack           	() : -0; }
double LuaSkill::GetPureattack	         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetPureattack	         	() : -0; }
double LuaSkill::GetPuremagicattack        	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetPuremagicattack       	() : -0; }
double LuaSkill::GetDefenddegree           	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetDefenddegree          	() : -0; }
double LuaSkill::GetAttackdegree           	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAttackdegree          	() : -0; }
double LuaSkill::GetDefense	             	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetDefense	            () : -0; }
double LuaSkill::GetGoldresist	         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetGoldresist	         	() : -0; }
double LuaSkill::GetWoodresist	         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWoodresist	         	() : -0; }
double LuaSkill::GetWaterresist            	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWaterresist           	() : -0; }
double LuaSkill::GetFireresist	         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetFireresist	         	() : -0; }
double LuaSkill::GetEarthresist            	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetEarthresist           	() : -0; }
double LuaSkill::GetCrit		             	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCrit		            () : -0; }
double LuaSkill::GetSoulpower	             	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetSoulpower	         	() : -0; }
double LuaSkill::GetHistoricalmaxlevel     	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetHistoricalmaxlevel    	() : -0; }
double LuaSkill::GetRealm                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRealm                 	() : -0; }
double LuaSkill::GetEquipattack            	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetEquipattack           	() : -0; }
double LuaSkill::GetEquipmagicattack       	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetEquipmagicattack      	() : -0; }
double LuaSkill::GetLocalval0              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLocalval0             	() : -0; }
double LuaSkill::GetLocalval1              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLocalval1             	() : -0; }
double LuaSkill::GetLocalval2              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLocalval2             	() : -0; }
double LuaSkill::GetCombat		         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCombat		         	() : -0; }
double LuaSkill::GetElfmp                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfmp                 	() : -0; }
double LuaSkill::GetElfap                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfap                 	() : -0; }
double LuaSkill::GetLanding                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLanding               	() : -0; }
double LuaSkill::GetAiring                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAiring                	() : -0; }
double LuaSkill::GetWatering               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetWatering              	() : -0; }
double LuaSkill::GetRiding                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRiding                	() : -0; }
double LuaSkill::GetSkillenhance2          	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetSkillenhance2         	() : -0; }
double LuaSkill::GetRangetotarget          	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRangetotarget         	() : -0; }
double LuaSkill::GetProduceSkill           	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetProduceSkill          	() : -0; }
double LuaSkill::GetDynskillcounter        	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetDynskillcounter       	() : -0; }
double LuaSkill::GetLvalue                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetLvalue                	() : -0; }
double LuaSkill::GetPrayrangeplus          	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetPrayrangeplus         	() : -0; }
double LuaSkill::GetRand                   	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRand                  	() : -0; }
double LuaSkill::GetBalls                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetBalls                 	() : -0; }
double LuaSkill::GetProbability            	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetProbability           	() : -0; }
double LuaSkill::GetProbabilityInt         	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetProbabilityInt        	() : -0; }
double LuaSkill::GetRatio                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRatio                 	() : -0; }
double LuaSkill::GetValue                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetValue                 	() : -0; }
double LuaSkill::GetAmount                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAmount                	() : -0; }
double LuaSkill::GetRatioInt               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetRatioInt              	() : -0; }
double LuaSkill::GetValueInt               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetValueInt              	() : -0; }
double LuaSkill::GetAmountInt              	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetAmountInt             	() : -0; }
double LuaSkill::GetShowicon               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetShowicon              	() : -0; }
double LuaSkill::GetSuccess                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetSuccess               	() : -0; }
double LuaSkill::GetImmune                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetImmune                	() : -0; }
double LuaSkill::Gettime                   	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetTime                  	() : -0; }
double LuaSkill::GetIntarg                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIntarg                	() : -0; }
double LuaSkill::GetEnable                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetEnable                	() : -0; }
double LuaSkill::GetInvader                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetInvader               	() : -0; }
double LuaSkill::GetElfstr                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfstr                	() : -0; }
double LuaSkill::GetElfagi                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfagi                	() : -0; }
double LuaSkill::GetElfvit                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfvit                	() : -0; }
double LuaSkill::GetElfeng                 	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElfeng                	() : -0; }
double LuaSkill::GetElflevel               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetElflevel              	() : -0; }
double LuaSkill::GetTargetregionplayernum  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetTargetregionplayernum 	() : -0; }
double LuaSkill::GetCharging               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetCharging              	() : -0; }
double LuaSkill::GetDecsp                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetDecsp                 	() : -0; }
double LuaSkill::GetDecmp                  	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetDecmp                 	() : -0; }
double LuaSkill::GetIncgold                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIncgold               	() : -0; }
double LuaSkill::GetIncwood                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIncwood               	() : -0; }
double LuaSkill::GetIncwater               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIncwater              	() : -0; }
double LuaSkill::GetIncfire                	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIncfire               	() : -0; }
double LuaSkill::GetIncearth               	  	(long long skill) { return skill ? ((Skill *)skill)->GetVictim()->GetIncearth              	() : -0; }

void   LuaSkill::SetProbability                 	(long long skill, double value) { if( skill ) ((Skill *)skill)->GetVictim()->SetProbability (value) ; }
void   LuaSkill::SetPlus							(long long skill, double value) { if( skill ) ((Skill *)skill)->SetPlus						(value)	; }
void   LuaSkill::SetRatioState					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetRatio					(value) ; }	
void   LuaSkill::SetDamage						(long long skill, double value) { if( skill ) ((Skill *)skill)->SetDamage					(value) ; }
void   LuaSkill::SetGolddamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetGolddamage				(value) ; }
void   LuaSkill::SetWooddamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetWooddamage				(value) ; }
void   LuaSkill::SetWaterdamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetWaterdamage				(value) ; }
void   LuaSkill::SetFiredamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetFiredamage				(value) ; }
void   LuaSkill::SetEarthdamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetEarthdamage				(value) ; }
void   LuaSkill::SetMagicDamage					(long long skill, double value) { if( skill ) ((Skill *)skill)->SetMagicDamage				(value) ; }
void   LuaSkill::SetDegree						(long long skill, double value) { if( skill ) ((Skill *)skill)->SetDegree					(value) ; }

double LuaSkill::SetPray       					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPray      					(value) : -0; }
double LuaSkill::SetInform     					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInform    					(value) : -0; }
double LuaSkill::SetPerform    					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPerform   					(value) : -0; }
double LuaSkill::SetDecelfmp   					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecelfmp  					(value) : -0; }
double LuaSkill::SetDecelfap   					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecelfap  					(value) : -0; }
double LuaSkill::UseArrow      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->UseArrow     					(value) : -0; }
double LuaSkill::IsUsingWeapon 					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->IsUsingWeapon					(value) : -0; }
double LuaSkill::GetSkilllevel 					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->GetSkilllevel					(value) : -0; }
double LuaSkill::SetShowicon   					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShowicon  					(value) : -0; }
double LuaSkill::SetIntarg     					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIntarg    					(value) : -0; }
double LuaSkill::SetEnable     					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnable    					(value) : -0; }
double LuaSkill::SetInvader    					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvader   					(value) : -0; }
double LuaSkill::SetDecsp      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecsp     					(value) : -0; }
double LuaSkill::SetForm       					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetForm      					(value) : -0; }
double LuaSkill::SetMaxhp      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMaxhp     					(value) : -0; }
double LuaSkill::SetInteam     					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInteam    					(value) : -0; }
double LuaSkill::SetSp         					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSp        					(value) : -0; }
double LuaSkill::SetRange      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRange     					(value) : -0; }
double LuaSkill::SetLevel      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetLevel     					(value) : -0; }
double LuaSkill::SetRank       					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRank      					(value) : -0; }
double LuaSkill::SetHpgen      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHpgen     					(value) : -0; }
double LuaSkill::SetMpgen      					(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMpgen     					(value) : -0; }	

double LuaSkill::SetDecmp                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecmp                        (value) : -0; }
double LuaSkill::SetTime                        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTime                         (value) : -0; }
double LuaSkill::SetRatio                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRatio                        (value) : -0; }
double LuaSkill::SetValue                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetValue                        (value) : -0; }
double LuaSkill::SetAmount                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAmount                       (value) : -0; }
double LuaSkill::SetHp                          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHp                           (value) : -0; }
double LuaSkill::SetMp                          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMp                           (value) : -0; }
double LuaSkill::SetIncswim                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncswim                      (value) : -0; }
double LuaSkill::SetIncgold                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncgold                      (value) : -0; }
double LuaSkill::SetIncwood                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncwood                      (value) : -0; }
double LuaSkill::SetIncwater                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncwater                     (value) : -0; }
double LuaSkill::SetIncfire                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncfire                      (value) : -0; }
double LuaSkill::SetIncearth                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncearth                     (value) : -0; }
double LuaSkill::SetAdddefence                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAdddefence                   (value) : -0; }
double LuaSkill::SetInchitrate                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchitrate                   (value) : -0; }
double LuaSkill::SetIncpethp                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpethp                     (value) : -0; }
double LuaSkill::SetIncpetmp                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetmp                     (value) : -0; }
double LuaSkill::SetIncpetdamage                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetdamage                 (value) : -0; }
double LuaSkill::SetIncpetmagicdamage           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetmagicdamage            (value) : -0; }
double LuaSkill::SetIncpetdefense               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetdefense                (value) : -0; }
double LuaSkill::SetIncpetmagicdefense          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetmagicdefense           (value) : -0; }
double LuaSkill::SetIncpetattackdegree          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetattackdegree           (value) : -0; }
double LuaSkill::SetIncpetdefenddegree          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpetdefenddegree           (value) : -0; }
double LuaSkill::SetAddresistance               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddresistance                (value) : -0; }
double LuaSkill::SetAddskilldamage              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddskilldamage               (value) : -0; }
double LuaSkill::SetAddmaxhp                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddmaxhp                     (value) : -0; }
double LuaSkill::SetIncswimspeed                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncswimspeed                 (value) : -0; }
double LuaSkill::SetIncdefenselevel             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdefenselevel              (value) : -0; }
double LuaSkill::SetIncCritReduce               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncCritReduce                (value) : -0; }
double LuaSkill::SetDirecthurt                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDirecthurt                   (value) : -0; }
double LuaSkill::SetHeal                        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHeal                         (value) : -0; }
double LuaSkill::SetResurrect                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetResurrect                    (value) : -0; }
double LuaSkill::SetSpeedup                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSpeedup                      (value) : -0; }
double LuaSkill::SetIncdefence                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdefence                   (value) : -0; }
double LuaSkill::SetIncattack                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncattack                    (value) : -0; }
double LuaSkill::SetIncsmite                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncsmite                     (value) : -0; }
double LuaSkill::SetIncmagic                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmagic                     (value) : -0; }
double LuaSkill::SetDecmagic                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecmagic                     (value) : -0; }
double LuaSkill::SetAbsorbhp                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAbsorbhp                     (value) : -0; }
double LuaSkill::SetInchp                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchp                        (value) : -0; }
double LuaSkill::SetDechp                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDechp                        (value) : -0; }
double LuaSkill::SetIncmp                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmp                        (value) : -0; }
double LuaSkill::SetIncdodge                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdodge                     (value) : -0; }
double LuaSkill::SetDecdodge                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecdodge                     (value) : -0; }
double LuaSkill::SetRepel                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRepel                        (value) : -0; }
double LuaSkill::SetRepel2                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRepel2                       (value) : -0; }
double LuaSkill::SetRepelAtr                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRepelAtr                     (value) : -0; }
double LuaSkill::SetBlind                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBlind                        (value) : -0; }
double LuaSkill::SetDecresist                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecresist                    (value) : -0; }
double LuaSkill::SetIncresist                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncresist                    (value) : -0; }
double LuaSkill::SetIncresist2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncresist2                   (value) : -0; }
double LuaSkill::SetInchurt                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurt                      (value) : -0; }
double LuaSkill::SetDechurt                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDechurt                      (value) : -0; }
double LuaSkill::SetDecaccuracy                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecaccuracy                  (value) : -0; }
double LuaSkill::SetIncaccuracy                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncaccuracy                  (value) : -0; }
double LuaSkill::SetMagicleak                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMagicleak                    (value) : -0; }
double LuaSkill::SetDecattack                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecattack                    (value) : -0; }
double LuaSkill::SetDecdefence                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecdefence                   (value) : -0; }
double LuaSkill::SetFrighten                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFrighten                     (value) : -0; }
double LuaSkill::SetDizzy                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDizzy                        (value) : -0; }
double LuaSkill::SetSleep                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSleep                        (value) : -0; }
double LuaSkill::SetFix                         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFix                          (value) : -0; }
double LuaSkill::SetSealed                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSealed                       (value) : -0; }
double LuaSkill::SetSlow                        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSlow                         (value) : -0; }
double LuaSkill::SetBleeding                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBleeding                     (value) : -0; }
double LuaSkill::SetThunder                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetThunder                      (value) : -0; }
double LuaSkill::SetToxic                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetToxic                        (value) : -0; }
double LuaSkill::SetBurning                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBurning                      (value) : -0; }
double LuaSkill::SetFallen                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFallen                       (value) : -0; }
double LuaSkill::SetFlood                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlood                        (value) : -0; }
double LuaSkill::SetFeathershield               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFeathershield                (value) : -0; }
double LuaSkill::SetFireshield                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFireshield                   (value) : -0; }
double LuaSkill::SetIceshield                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIceshield                    (value) : -0; }
double LuaSkill::SetRetort                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRetort                       (value) : -0; }
double LuaSkill::SetSlowpray                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSlowpray                     (value) : -0; }
double LuaSkill::SetFastmpgen                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastmpgen                    (value) : -0; }
double LuaSkill::SetScaleinchp                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetScaleinchp                   (value) : -0; }
double LuaSkill::SetScaleincmp                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetScaleincmp                   (value) : -0; }
double LuaSkill::SetScaledecmp                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetScaledecmp                   (value) : -0; }
double LuaSkill::SetScaledechp                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetScaledechp                   (value) : -0; }
double LuaSkill::SetFasthpgen                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFasthpgen                    (value) : -0; }
double LuaSkill::SetFastattack                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastattack                   (value) : -0; }
double LuaSkill::SetSlowattack                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSlowattack                   (value) : -0; }
double LuaSkill::SetSoilshield                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoilshield                   (value) : -0; }
double LuaSkill::SetIceblade                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIceblade                     (value) : -0; }
double LuaSkill::SetEnhancegold                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhancegold                  (value) : -0; }
double LuaSkill::SetEnhancewood                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhancewood                  (value) : -0; }
double LuaSkill::SetEnhancewater                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhancewater                 (value) : -0; }
double LuaSkill::SetEnhancefire                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhancefire                  (value) : -0; }
double LuaSkill::SetEnhancesoil                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhancesoil                  (value) : -0; }
double LuaSkill::SetReducegold                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducegold                   (value) : -0; }
double LuaSkill::SetReducewood                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducewood                   (value) : -0; }
double LuaSkill::SetReducewater                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducewater                  (value) : -0; }
double LuaSkill::SetReducefire                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducefire                   (value) : -0; }
double LuaSkill::SetReducesoil                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducesoil                   (value) : -0; }
double LuaSkill::SetFireblade                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFireblade                    (value) : -0; }
double LuaSkill::SetToxicblade                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetToxicblade                   (value) : -0; }
double LuaSkill::SetCleardebuff                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCleardebuff                  (value) : -0; }
double LuaSkill::SetCleardebuff2                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCleardebuff2                 (value) : -0; }
double LuaSkill::SetInvincible                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible                   (value) : -0; }
double LuaSkill::SetInvincible2                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible2                  (value) : -0; }
double LuaSkill::SetInvincible3                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible3                  (value) : -0; }
double LuaSkill::SetInvincible4                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible4                  (value) : -0; }
double LuaSkill::SetInvincible5                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible5                  (value) : -0; }
double LuaSkill::SetInvincible6                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible6                  (value) : -0; }
double LuaSkill::SetInvincible7                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible7                  (value) : -0; }
double LuaSkill::SetFastpray                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastpray                     (value) : -0; }
double LuaSkill::SetAntiwater                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAntiwater                    (value) : -0; }
double LuaSkill::SetPanruo                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPanruo                       (value) : -0; }
double LuaSkill::SetBreak                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBreak                        (value) : -0; }
double LuaSkill::SetYijin                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetYijin                        (value) : -0; }
double LuaSkill::SetXisui                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetXisui                        (value) : -0; }
double LuaSkill::SetJingji                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetJingji                       (value) : -0; }
double LuaSkill::SetFlower1                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlower1                      (value) : -0; }
double LuaSkill::SetFlower2                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlower2                      (value) : -0; }
double LuaSkill::SetFlower3                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlower3                      (value) : -0; }
double LuaSkill::SetFlower4                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlower4                      (value) : -0; }
double LuaSkill::SetStoneskin                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetStoneskin                    (value) : -0; }
double LuaSkill::SetIronshield                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIronshield                   (value) : -0; }
double LuaSkill::SetWingshield                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWingshield                   (value) : -0; }
double LuaSkill::SetFirearrow                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFirearrow                    (value) : -0; }
double LuaSkill::SetGiant                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetGiant                        (value) : -0; }
double LuaSkill::SetBlessmagic                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBlessmagic                   (value) : -0; }
double LuaSkill::SetEaglecurse                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEaglecurse                   (value) : -0; }
double LuaSkill::SetDevilstate                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDevilstate                   (value) : -0; }
double LuaSkill::SetFreemove                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFreemove                     (value) : -0; }
double LuaSkill::SetSelfburning                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSelfburning                  (value) : -0; }
double LuaSkill::SetFallen2                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFallen2                      (value) : -0; }
double LuaSkill::SetSealed2                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSealed2                      (value) : -0; }
double LuaSkill::SetFix2                        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFix2                         (value) : -0; }
double LuaSkill::SetDechurt2                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDechurt2                     (value) : -0; }
double LuaSkill::SetInchurt2                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurt2                     (value) : -0; }
double LuaSkill::SetInchurt3                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurt3                     (value) : -0; }
double LuaSkill::SetInchurt4                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurt4                     (value) : -0; }
double LuaSkill::SetInchurt5                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurt5                     (value) : -0; }
double LuaSkill::SetDechurt3                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDechurt3                     (value) : -0; }
double LuaSkill::SetInchp2                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchp2                       (value) : -0; }
double LuaSkill::SetIncattack2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncattack2                   (value) : -0; }
double LuaSkill::SetIncmagic2                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmagic2                    (value) : -0; }
double LuaSkill::SetFastpray2                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastpray2                    (value) : -0; }
double LuaSkill::SetSpeedup2                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSpeedup2                     (value) : -0; }
double LuaSkill::SetSkillcooldown               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSkillcooldown                (value) : -0; }
double LuaSkill::SetCommoncooldown              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCommoncooldown               (value) : -0; }
double LuaSkill::SetAurafireattack              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAurafireattack               (value) : -0; }
double LuaSkill::SetAurabless                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAurabless                    (value) : -0; }
double LuaSkill::SetAuracurse                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAuracurse                    (value) : -0; }
double LuaSkill::SetAurabless2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAurabless2                   (value) : -0; }
double LuaSkill::SetAuracurse2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAuracurse2                   (value) : -0; }
double LuaSkill::SetAurabless3                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAurabless3                   (value) : -0; }
double LuaSkill::SetInvisible                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvisible                    (value) : -0; }
double LuaSkill::SetIncantiinvisibleactive      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncantiinvisibleactive       (value) : -0; }
double LuaSkill::SetInchpsteal                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchpsteal                   (value) : -0; }
double LuaSkill::SetInccritdamage               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInccritdamage                (value) : -0; }
double LuaSkill::SetIncdamagedodge              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdamagedodge               (value) : -0; }
double LuaSkill::SetIncdebuffdodge              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdebuffdodge               (value) : -0; }
double LuaSkill::SetRebirth                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRebirth                      (value) : -0; }
double LuaSkill::SetDeepenbless                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDeepenbless                  (value) : -0; }
double LuaSkill::SetWeakenbless                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWeakenbless                  (value) : -0; }
double LuaSkill::SetWeakenbless2                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWeakenbless2                 (value) : -0; }
double LuaSkill::SetHurtwhenuseskill            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHurtwhenuseskill             (value) : -0; }
double LuaSkill::SetInterruptwhenuseskill       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInterruptwhenuseskill        (value) : -0; }
double LuaSkill::SetSoulretort                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoulretort                   (value) : -0; }
double LuaSkill::SetSoulsealed                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoulsealed                   (value) : -0; }
double LuaSkill::SetSoulbeatback                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoulbeatback                 (value) : -0; }
double LuaSkill::SetSoulstun                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoulstun                     (value) : -0; }
double LuaSkill::SetFishform                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFishform                     (value) : -0; }
double LuaSkill::SetGminvisible                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetGminvisible                  (value) : -0; }
double LuaSkill::SetActivatesharpener           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetActivatesharpener            (value) : -0; }
double LuaSkill::SetInchurtphysicgold           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurtphysicgold            (value) : -0; }
double LuaSkill::SetInchurtwoodwater            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurtwoodwater             (value) : -0; }
double LuaSkill::SetInchurtfireearth            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchurtfireearth             (value) : -0; }
double LuaSkill::SetAttackattachstate1          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttackattachstate1           (value) : -0; }
double LuaSkill::SetAttackattachstate2          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttackattachstate2           (value) : -0; }
double LuaSkill::SetAttackattachstate3          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttackattachstate3           (value) : -0; }
double LuaSkill::SetAttackattachstate4          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttackattachstate4           (value) : -0; }
double LuaSkill::SetBeattackattachstate1        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate1         (value) : -0; }
double LuaSkill::SetBeattackattachstate2        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate2         (value) : -0; }
double LuaSkill::SetBeattackattachstate3        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate3         (value) : -0; }
double LuaSkill::SetBeattackattachstate4        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate4         (value) : -0; }
double LuaSkill::SetBeattackattachstate5        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate5         (value) : -0; }
double LuaSkill::SetBeattackattachstate6        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate6         (value) : -0; }
double LuaSkill::SetBeattackattachstate7        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate7         (value) : -0; }
double LuaSkill::SetBeattackattachstate8        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBeattackattachstate8         (value) : -0; }
double LuaSkill::SetTransferbuff                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransferbuff                 (value) : -0; }
double LuaSkill::SetTransferdebuff              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransferdebuff               (value) : -0; }
double LuaSkill::SetAbsorbbuff                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAbsorbbuff                   (value) : -0; }
double LuaSkill::SetAbsorbdebuff                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAbsorbdebuff                 (value) : -0; }
double LuaSkill::SetSummonpet2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSummonpet2                   (value) : -0; }
double LuaSkill::SetSummonplantpet              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSummonplantpet               (value) : -0; }
double LuaSkill::SetPetsacrifice                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPetsacrifice                 (value) : -0; }
double LuaSkill::SetPlantsuicide                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPlantsuicide                 (value) : -0; }
double LuaSkill::SetPoisionseed                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPoisionseed                  (value) : -0; }
double LuaSkill::SetHpgenseed                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHpgenseed                    (value) : -0; }
double LuaSkill::SetPhysichurt                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPhysichurt                   (value) : -0; }
double LuaSkill::SetGoldhurt                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetGoldhurt                     (value) : -0; }
double LuaSkill::SetWoodhurt                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWoodhurt                     (value) : -0; }
double LuaSkill::SetWaterhurt                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWaterhurt                    (value) : -0; }
double LuaSkill::SetFirehurt                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFirehurt                     (value) : -0; }
double LuaSkill::SetEarthhurt                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEarthhurt                    (value) : -0; }
double LuaSkill::SetFastprayincmagic            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastprayincmagic             (value) : -0; }
double LuaSkill::SetIncwoodwaterdefense         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncwoodwaterdefense          (value) : -0; }
double LuaSkill::SetSpecialslow                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSpecialslow                  (value) : -0; }
double LuaSkill::SetSpecialphysichurt           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSpecialphysichurt            (value) : -0; }
double LuaSkill::SetIncdefencesmite             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdefencesmite              (value) : -0; }
double LuaSkill::SetIncresistmagic              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncresistmagic               (value) : -0; }
double LuaSkill::SetTransportmptopet            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransportmptopet             (value) : -0; }
double LuaSkill::SetTransportdamagetopet        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransportdamagetopet         (value) : -0; }
double LuaSkill::SetAbsorbdamageincdefense      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAbsorbdamageincdefense       (value) : -0; }
double LuaSkill::SetIncrementalhpgen            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncrementalhpgen             (value) : -0; }
double LuaSkill::SetChanceofrebirth             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetChanceofrebirth              (value) : -0; }
double LuaSkill::SetSpecialphysichurttrigger    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSpecialphysichurttrigger     (value) : -0; }
double LuaSkill::SetLongjumptospouse            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetLongjumptospouse             (value) : -0; }
double LuaSkill::SetInccountedsmite             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInccountedsmite              (value) : -0; }
double LuaSkill::SetWeapondisabled              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetWeapondisabled               (value) : -0; }
double LuaSkill::SetIncaggroondamage            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncaggroondamage             (value) : -0; }
double LuaSkill::SetEnhanceskilldamage          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhanceskilldamage           (value) : -0; }
double LuaSkill::SetDetectinvisible             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDetectinvisible              (value) : -0; }
double LuaSkill::SetDetectinvisible2            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDetectinvisible2             (value) : -0; }
double LuaSkill::SetFastmpgen2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastmpgen2                   (value) : -0; }
double LuaSkill::SetClearinvisible2             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetClearinvisible2              (value) : -0; }
double LuaSkill::SetPositionrollback            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPositionrollback             (value) : -0; }
double LuaSkill::SetPositionrollback2           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPositionrollback2            (value) : -0; }
double LuaSkill::SetHprollback                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHprollback                   (value) : -0; }
double LuaSkill::SetNofly                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetNofly                        (value) : -0; }
double LuaSkill::SetForceselecttarget           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetForceselecttarget            (value) : -0; }
double LuaSkill::SetHealabsorb                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHealabsorb                   (value) : -0; }
double LuaSkill::SetRepelonnormalattack         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRepelonnormalattack          (value) : -0; }
double LuaSkill::SetInccritresistance           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInccritresistance            (value) : -0; }
double LuaSkill::SetDeccritresistance           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDeccritresistance            (value) : -0; }
double LuaSkill::SetExchangeposition            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetExchangeposition             (value) : -0; }
double LuaSkill::SetPullover                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPullover                     (value) : -0; }
double LuaSkill::SetTransmitskillattack         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransmitskillattack          (value) : -0; }
double LuaSkill::SetAdditionalheal              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAdditionalheal               (value) : -0; }
double LuaSkill::SetAdditionalattack            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAdditionalattack             (value) : -0; }
double LuaSkill::SetTransportdamagetoleader     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransportdamagetoleader      (value) : -0; }
double LuaSkill::SetForbidbeselected            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetForbidbeselected             (value) : -0; }
double LuaSkill::SetEnhanceskilldamage2         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhanceskilldamage2          (value) : -0; }
double LuaSkill::SetCallupteammember            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCallupteammember             (value) : -0; }
double LuaSkill::SetDelayearthhurt              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDelayearthhurt               (value) : -0; }
double LuaSkill::SetDizzyinchurt                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDizzyinchurt                 (value) : -0; }
double LuaSkill::SetSoulretort2                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoulretort2                  (value) : -0; }
double LuaSkill::SetFixondamage                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFixondamage                  (value) : -0; }
double LuaSkill::SetApgen2                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetApgen2                       (value) : -0; }
double LuaSkill::SetIncattackondamage           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncattackondamage            (value) : -0; }
double LuaSkill::SetRebirth2                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRebirth2                     (value) : -0; }
double LuaSkill::SetHealsteal                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHealsteal                    (value) : -0; }
double LuaSkill::SetDropmoneyondeath            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDropmoneyondeath             (value) : -0; }
double LuaSkill::SetIncattackrange              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncattackrange               (value) : -0; }
double LuaSkill::SetQueryotherinventory         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetQueryotherinventory          (value) : -0; }
double LuaSkill::SetThunderform                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetThunderform                  (value) : -0; }
double LuaSkill::SetDelaytransmit               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDelaytransmit                (value) : -0; }
double LuaSkill::SetDecnormalattackhurt         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecnormalattackhurt          (value) : -0; }
double LuaSkill::SetFreemoveapgen               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFreemoveapgen                (value) : -0; }
double LuaSkill::SetIncatkdefhp                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncatkdefhp                  (value) : -0; }
double LuaSkill::SetDenyattackcmd               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDenyattackcmd                (value) : -0; }
double LuaSkill::SetHpmpgennotincombat          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHpmpgennotincombat           (value) : -0; }
double LuaSkill::SetInchpmp                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInchpmp                      (value) : -0; }
double LuaSkill::SetEnternonpenaltypvp          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnternonpenaltypvp           (value) : -0; }
double LuaSkill::SetLeavenonpenaltypvp          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetLeavenonpenaltypvp           (value) : -0; }
double LuaSkill::SetIncmaxhpatkdfdlevel         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmaxhpatkdfdlevel          (value) : -0; }
double LuaSkill::SetRetort2                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRetort2                      (value) : -0; }
double LuaSkill::SetKnockup                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetKnockup                      (value) : -0; }
double LuaSkill::SetPalsy                       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPalsy                        (value) : -0; }
double LuaSkill::SetAddattackdegree             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddattackdegree              (value) : -0; }
double LuaSkill::SetSubattackdegree             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSubattackdegree              (value) : -0; }
double LuaSkill::SetAdddefencedegree            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAdddefencedegree             (value) : -0; }
double LuaSkill::SetSubdefencedegree            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSubdefencedegree             (value) : -0; }
double LuaSkill::SetSubdefencedegree2           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSubdefencedegree2            (value) : -0; }
double LuaSkill::SetIncatkdefhp2                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncatkdefhp2                 (value) : -0; }
double LuaSkill::SetIncsmite3                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncsmite3                    (value) : -0; }
double LuaSkill::SetIncpenres                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncpenres                    (value) : -0; }
double LuaSkill::SetAttachstatetoself           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttachstatetoself            (value) : -0; }
double LuaSkill::SetAttachstatetotarget         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttachstatetotarget          (value) : -0; }
double LuaSkill::SetFireshield2                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFireshield2                  (value) : -0; }
double LuaSkill::SetIceshield2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIceshield2                   (value) : -0; }
double LuaSkill::SetHealshield                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHealshield                   (value) : -0; }
double LuaSkill::SetIncflyspeed                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncflyspeed                  (value) : -0; }
double LuaSkill::SetIncvigour                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncvigour                    (value) : -0; }
double LuaSkill::SetIncvigour2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncvigour2                   (value) : -0; }
double LuaSkill::SetShortjump                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShortjump                    (value) : -0; }
double LuaSkill::SetShortjump2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShortjump2                   (value) : -0; }
double LuaSkill::SetMovepunish                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMovepunish                   (value) : -0; }
double LuaSkill::SetStandpunish                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetStandpunish                  (value) : -0; }
double LuaSkill::SetStandpunish2                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetStandpunish2                 (value) : -0; }
double LuaSkill::SetChantshield                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetChantshield                  (value) : -0; }
double LuaSkill::SetChangeselfaggro             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetChangeselfaggro              (value) : -0; }
double LuaSkill::SetSummonmobs                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSummonmobs                   (value) : -0; }
double LuaSkill::SetIntervalpalsy               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIntervalpalsy                (value) : -0; }
double LuaSkill::SetInternalinjury              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInternalinjury               (value) : -0; }
double LuaSkill::SetAtkdamagereduce             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAtkdamagereduce              (value) : -0; }
double LuaSkill::SetDeathresetcd                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDeathresetcd                 (value) : -0; }
double LuaSkill::SetAppendenchant               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAppendenchant                (value) : -0; }
double LuaSkill::SetAppenddamage                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAppenddamage                 (value) : -0; }
double LuaSkill::SetCooldownaward               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCooldownaward                (value) : -0; }
double LuaSkill::SetHuntersoul                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetHuntersoul                   (value) : -0; }
double LuaSkill::SetNeverdead                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetNeverdead                    (value) : -0; }
double LuaSkill::SetChangemodel                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetChangemodel                  (value) : -0; }
double LuaSkill::SetScreeneffect                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetScreeneffect                 (value) : -0; }
double LuaSkill::SetAddfrosteffect              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddfrosteffect               (value) : -0; }
double LuaSkill::SetActivefrosteffect           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetActivefrosteffect            (value) : -0; }
double LuaSkill::SetIncspecskillcrit            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncspecskillcrit             (value) : -0; }
double LuaSkill::SetClearfilterbyid             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetClearfilterbyid              (value) : -0; }
double LuaSkill::SetMoongod                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetMoongod                      (value) : -0; }
double LuaSkill::SetDelayskilleffect            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDelayskilleffect             (value) : -0; }
double LuaSkill::SetEnhanceskilldamage3         	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetEnhanceskilldamage3          (value) : -0; }
double LuaSkill::SetCritdamagereduce            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCritdamagereduce             (value) : -0; }
double LuaSkill::SetImmunemagical2              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetImmunemagical2               (value) : -0; }
double LuaSkill::SetPullover2                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetPullover2                    (value) : -0; }
double LuaSkill::SetIncphysicaldamage           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncphysicaldamage            (value) : -0; }
double LuaSkill::SetIncmagicaldamage            	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmagicaldamage             (value) : -0; }
double LuaSkill::SetRemoveaggro                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRemoveaggro                  (value) : -0; }
double LuaSkill::SetCooldownpunish              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetCooldownpunish               (value) : -0; }
double LuaSkill::SetAnticlearbuf                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAnticlearbuf                 (value) : -0; }
double LuaSkill::SetIncenchantrange             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncenchantrange              (value) : -0; }
double LuaSkill::SetIncphysicalmagicaldefense   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncphysicalmagicaldefense    (value) : -0; }
double LuaSkill::SetReducegold3                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducegold3                  (value) : -0; }
double LuaSkill::SetReducewater3                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReducewater3                 (value) : -0; }
double LuaSkill::SetGenhpap                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetGenhpap                      (value) : -0; }
double LuaSkill::SetDetaindart                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDetaindart                   (value) : -0; }
double LuaSkill::SetExtraexpfactor              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetExtraexpfactor               (value) : -0; }
double LuaSkill::SetSoloIncAttackAndMagic       	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloIncAttackAndMagic        (value) : -0; }
double LuaSkill::SetSoloIncDefence              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloIncDefence               (value) : -0; }
double LuaSkill::SetSoloEnhanceResist           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloEnhanceResist            (value) : -0; }
double LuaSkill::SetSoloIncMaxHP                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloIncMaxHP                 (value) : -0; }
double LuaSkill::SetInvincible8                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvincible8                  (value) : -0; }
double LuaSkill::SetSoloHpGen                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloHpGen                    (value) : -0; }
double LuaSkill::SetSoloDecHurt                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloDecHurt                  (value) : -0; }
double LuaSkill::SetSoloAddAttackRange          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloAddAttackRange           (value) : -0; }
double LuaSkill::SetThunder3                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetThunder3                     (value) : -0; }
double LuaSkill::SetToxic3                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetToxic3                       (value) : -0; }
double LuaSkill::SetFlood3                      	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFlood3                       (value) : -0; }
double LuaSkill::SetBurning3                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetBurning3                     (value) : -0; }
double LuaSkill::SetFallen3                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFallen3                      (value) : -0; }
double LuaSkill::SetShattereddreammob           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShattereddreammob            (value) : -0; }
double LuaSkill::SetReduceSpeeddebuff           	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetReduceSpeeddebuff            (value) : -0; }
double LuaSkill::SetShieldNew1                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShieldNew1                   (value) : -0; }
double LuaSkill::SetShieldNew2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetShieldNew2                   (value) : -0; }
double LuaSkill::SetNewSpeedBuff                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetNewSpeedBuff                 (value) : -0; }
double LuaSkill::SetIraAtiradora                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIraAtiradora                 (value) : -0; }
double LuaSkill::SetFeAtiradora                 	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFeAtiradora                  (value) : -0; }
double LuaSkill::SetNewRemove                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetNewRemove                    (value) : -0; }
double LuaSkill::SetIncAntiDefenseDegree        	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncAntiDefenseDegree         (value) : -0; }
double LuaSkill::SetIncPlusMaxHP                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncPlusMaxHP                 (value) : -0; }
double LuaSkill::SetInvisible2                  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetInvisible2                   (value) : -0; }
double LuaSkill::SetAuracurse4ASN               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAuracurse4ASN                (value) : -0; }
double LuaSkill::SetIncmagic4                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncmagic4                    (value) : -0; }
double LuaSkill::SetDecsoul                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecsoul                      (value) : -0; }
double LuaSkill::SetGiantform                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetGiantform                    (value) : -0; }
double LuaSkill::SetTransdmg2pet                	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetTransdmg2pet                 (value) : -0; }
double LuaSkill::SetSkillcooldown2              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSkillcooldown2               (value) : -0; }
double LuaSkill::SetDecphysicalmagicaldefense   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecphysicalmagicaldefense    (value) : -0; }
double LuaSkill::SetIncsmitedamage              	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncsmitedamage               (value) : -0; }
double LuaSkill::SetDecphysicalmagicaldefense2  	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDecphysicalmagicaldefense2   (value) : -0; }
double LuaSkill::SetFastpray3                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetFastpray3                    (value) : -0; }
double LuaSkill::SetIncdebuffdodge2             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdebuffdodge2              (value) : -0; }
double LuaSkill::SetIncdamagedodge2             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetIncdamagedodge2              (value) : -0; }
double LuaSkill::SetDebithurt                   	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetDebithurt                    (value) : -0; }
double LuaSkill::SetSoloAddAttackLevel          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloAddAttackLevel           (value) : -0; }
double LuaSkill::SetSoloAddDefendLevel          	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetSoloAddDefendLevel           (value) : -0; }
double LuaSkill::SetUltimatePaladin             	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetUltimatePaladin              (value) : -0; }
double LuaSkill::SetAttackplusAtr               	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAttackplusAtr                (value) : -0; }
double LuaSkill::SetAddPraga                    	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetAddPraga                     (value) : -0; }
double LuaSkill::SetRetort3                     	(long long skill, double value) { return skill ? ((Skill *)skill)->GetVictim()->SetRetort3                      (value) : -0; }

