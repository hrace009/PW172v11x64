
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>

#include <ASSERT.h>
#include "playerwrapper.h"
#include "targetwrapper.h"
#include "skill.h"
#include "skillwrapper.h"
#include "skillfilter.h"
#include "skilllevel.h"
#include "statedef.h"
#include "skilllua.h"

namespace GNET
{

int SkillLevel::GetValue(int index)
{
	if( skillwrapper )
		return skillwrapper->GetLevel(index,cls);
	return 0;
}

void SkillLevel::SetValue(int index, int value)
{
	if( skillwrapper )
		skillwrapper->SetLevel(index, value);
}

int BuffLevel::GetValue(int index)
{
	return object.QueryFilter(index,filter::FILTER_QUERY_LEVEL);
}

int ComboArg::GetValue(int index)
{
	if( skillwrapper )
		return skillwrapper->GetComboSkillArg(index);
	return 0;
}

void ComboArg::SetValue(int index, int value)
{
	if( skillwrapper )
		skillwrapper->SetComboSkillArg(index, value);
}

int SkillWrapper::BlackWhiteBall::UpdateVstate(int& oldv)
{
	static const int BWB_VSTATES[BWB_VALUE_MAX + 1] = 
	{	0,VSTATE_WHITE1,VSTATE_WHITE2,VSTATE_WHITE3,0,
		VSTATE_BLACK1,VSTATE_WHITE1BLACK1,VSTATE_WHITE2BLACK1,0,0,
		VSTATE_BLACK2,VSTATE_WHITE1BLACK2,0,0,0,VSTATE_BLACK3 
	};
	oldv = vstate;
	vstate = GetIndex() > BWB_VALUE_MAX ? BWB_VSTATES[0] : BWB_VSTATES[GetIndex()];
	return vstate;
}

bool SkillWrapper::Initialize()
{
	LuaSkill::GetInstance()->Init("skill.lua");
	SkillStub::Initialize();
	return true;
}

int SkillWrapper::Learn( ID id, object_interface player )
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;

	int level = 1;

	StorageMap::iterator it = map.find(id);
	if( it != map.end() )
	{
		if(it->second.overridden)
			return -1;
		level =  (*it).second.level;
		if(level>=skill->GetMaxLevel())
			return -1;
		skill->SetLevel(level++);
		int ability = skill->GetMaxability();
		if(ability>0 && (*it).second.ability<ability)
			return -1;
	}
	skill->SetLevel(level);

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);

	if( skill->Learn() )
	{
		SetLevel(id,level);
		if(skill->IsSenior())
			OverrideSkill(skill->GetJunior());
		return level;
	}
	return -1;
}

int SkillWrapper::Learn( ID id, object_interface player, int level )
{
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
	{
		//LOG_TRACE( "�޴˼���: %d\n", id);
		return -1;
	}
	int slevel = 0;
	StorageMap::iterator it = map.find(id);
	if( it != map.end() )
	{
		if(it->second.overridden)
			return -1;
		slevel =  (*it).second.level;
		if(slevel>=skill->GetMaxLevel())
			return -1;
		
		skill->SetLevel(slevel);
		int ability = skill->GetMaxability();
		if(ability>0 && (*it).second.ability<ability)
			return -1;
	}
	if(level!=slevel+1)
		return -1;
	
	skill->SetLevel(level);

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);

	if( skill->Learn() )
	{
		SetLevel(id,level);
		if(skill->IsSenior())
			OverrideSkill(skill->GetJunior());
		return level;
	}
	return -1;
}

int SkillWrapper::Push( ID id, object_interface player, int level )
{
	SkillKeeper skill = Skill::Create(id);
	if( !skill ) return -1;

	int slevel = 0;
	StorageMap::iterator it = map.find(id);
	if( it != map.end() )
	{
		if(it->second.overridden)
			return -1;
			slevel = (*it).second.level;
		if( slevel>= skill->GetMaxLevel())
			slevel = skill->GetMaxLevel();
		
		skill->SetLevel(slevel);
		int ability = skill->GetMaxability();
		if(ability>0 && (*it).second.ability<ability)
			return -1;
	}
	skill->SetLevel(level);

	PlayerWrapper     w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	if( skill->Push() )
	{
		SetLevel(id,level);
		if(skill->IsSenior())
			OverrideSkill(skill->GetJunior());
		return level;
	}
	return -1;	
}



int SkillWrapper::Condition( ID id, object_interface player, const XID * target, int size )
{
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return 1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	skill->SetPlayer(&w_player);
	skill->SetLevel( GetLevel(id,player.GetClass()) );

	int ret = skill->Condition();
	if(ret==0 && (!player.TestCoolDown(id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player)))
		ret = 1;

	return ret;
}

int SkillWrapper::StartSkill( SKILL::Data & skilldata, object_interface player, const A3DVECTOR& target_pos,const XID * target, int size, int & next_interval)
{
	next_interval = -1;
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;
	int level = GetLevel(skilldata.id,player.GetClass(), true);
	if(level<=0)
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);

	int ret = skill->Condition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
		return -1;
	
	const A3DVECTOR pos = player.GetPos();
	float range = skill->GetPraydistance() + player.GetBodySize();
	if(!skill->GetRange().NoTarget())
	{
		//��Ŀ���˲�Ƽ���Ŀ��������С
		A3DVECTOR tpos;
		float tbody;
		if(player.QueryObject(*target, tpos, tbody) == 0) return -1;
		range += tbody;
	}
	if(pos.squared_distance(target_pos) > range*range || skill->GetType()!=TYPE_JUMP)
		return -1;
	
	ret = skill->FirstRun( next_interval, prayspeed + GetDynPrayspeed(skilldata.id) );
	if(ret>=0)
	{
		if(player.SkillMove(target_pos, skill->GetRange().NoTarget()))
			player.SendClientCastPosSkill(target_pos, size>0?*target:XID(0,0), skilldata.id, ret, level);
		else
			player.SendClientCastPosSkill(pos, size>0?*target:XID(0,0), skilldata.id, ret, level);
	}
	return ret;
}

int SkillWrapper::Run( SKILL::Data & skilldata, object_interface player, const A3DVECTOR& target_pos, const XID * target, int size, int & next_interval )
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel( GetLevel(skilldata.id,player.GetClass()) );
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);
	int ret = skill->Run( next_interval );

	if(!w_player.GetSuccess())
	{
		ret = -1;
		player.SendClientMsgSkillInterrupted(2);
	}
	else
	{
		if(skill->IsStateEnd() && SkillStub::IsComboPreskill(skilldata.id))
		{			
			OnComboPreSkillEnd(skill,player);
		}
	}

	return ret;
}

int SkillWrapper::StartSkill( SKILL::Data & skilldata, object_interface player, const XID * target, 
		int size, int & next_interval)
{
	//printf("StartSkill_s1: id = %d \n", skilldata.id );
	
	next_interval = -1;
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
	{
		//printf("StartSkill_s1: id = %d , !skill \n", skilldata.id );
		return -1;
	}
	int level = GetLevel(skilldata.id,player.GetClass(), true);
	if(level<=0)
	{
		//printf("StartSkill_s1: id = %d , level<=0 \n", skilldata.id );
		return -1;
	}

	PlayerWrapper		w_player(player,this,skill,target,size);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);

	int ret = skill->Condition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
	{
		//printf("StartSkill Error: sid=%d err=%d\n", skilldata.id, ret);
		return -1;
	}

	ret = skill->FirstRun( next_interval, prayspeed + GetDynPrayspeed(skilldata.id) );
	if(ret>=0)
	{
		if(skill->IsCastSelf())
			player.SendClientMsgSkillCasting(player.GetSelfID(), skilldata.id, ret, level);
		else
			player.SendClientMsgSkillCasting(size>0?*target:XID(0,0), skilldata.id, ret, level);
	}
	
	//printf("StartSkill_s1: id = %d , ret = %d \n", skilldata.id , ret );
	return ret;
}

int SkillWrapper::Run( SKILL::Data & skilldata, object_interface player, const XID * target, int size , int& next_interval)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel( GetLevel(skilldata.id,player.GetClass()) );
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);

	int ret = skill->Run( next_interval );

	if(!w_player.GetSuccess())
	{
		ret = -1;
		player.SendClientMsgSkillInterrupted(2);
	}
	else
	{
		if(skill->IsStateEnd() && SkillStub::IsComboPreskill(skilldata.id))
		{			
			OnComboPreSkillEnd(skill,player);
		}
	}
	
	return ret;
}

int SkillWrapper::Continue( SKILL::Data& skilldata, object_interface player, const XID* target, int size, int& next_interval, int elapse_time )
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel( GetLevel(skilldata.id,player.GetClass()) );
	skill->SetData(&skilldata);
	skill->SetCharging(elapse_time);
	skill->PrepareTalent(&w_player);

	next_interval = -1;
	int time = skill->Run( next_interval );

	if(skill->IsStateEnd() && SkillStub::IsComboPreskill(skilldata.id))
	{			
		OnComboPreSkillEnd(skill,player);
	}
	return time;
}

int SkillWrapper::CastRune(SKILL::Data & skilldata, object_interface player, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill || !skill->IsRune())
		return -1;

	PlayerWrapper w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	skill->SetVictim(&w_player);
	TargetWrapper		w_target(&player);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->SetPerformerid(XID(-1,-1));
	skill->SetPlayerlevel(w_player.GetLevel());
	skill->SetMagicDamage(w_player.GetMagicattack());
	skill->StateAttack();
	return 0;
}

int SkillWrapper::InstantSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill || !skill->IsInstant())
		return -1;

	int level = GetLevel(skilldata.id,player.GetClass(), true);
	if(level<=0)
		return -1;
			
	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);

	int ret = skill->Condition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
		return -1;

	if(skill->InstantRun())
	{
		player.SendClientInstantSkill(size>0?*target:XID(0,0), skilldata.id, level);
		if(skill->IsStateEnd() && SkillStub::IsComboPreskill(skilldata.id))
		{			
			OnComboPreSkillEnd(skill,player);
		}
	}

	return ret;
}

bool SkillWrapper::Interrupt( SKILL::Data & skilldata, object_interface player )
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	if(ignore_interrupt) 
		return false;

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player);
	skill->SetTarget(&w_target);
	skill->SetLevel( GetLevel(skilldata.id,player.GetClass()) );
	skill->SetData(&skilldata);

	bool ret = false;
	ret = skill->Interrupt();

	if(!ret)
	{
		if((rand()%100) < interrupt_prob) ret = true;	
	}

	if( ret )
	{
#ifndef _SKILL_TEST
		player.SendClientMsgSkillInterrupted(1);
#endif
	}
	return ret;
}

bool SkillWrapper::Cancel( SKILL::Data & skilldata, object_interface player )
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player);
	skill->SetTarget(&w_target);
	skill->SetLevel( GetLevel(skilldata.id,player.GetClass()) );
	skill->SetData(&skilldata);

	bool ret = false;
	ret = skill->Cancel();

	if( ret )
	{
#ifndef _SKILL_TEST
		player.SendClientMsgSkillInterrupted(2);
#endif
	}
	return ret;
}


bool SkillWrapper::Attack(object_interface victim,const XID& attacker,const A3DVECTOR& src,const attack_msg& msg,bool invader)
{
	if(immune_buff_debuff > 0)		//lgc
	{
		victim.SendClientEnchantResult(attacker,msg.attached_skill.skill, 
				msg.attached_skill.level,invader,msg._attack_state|0x80, msg.section);
		return false;
	}
	
	int id = msg.attached_skill.skill;
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return false;
	PlayerWrapper		w_victim(victim,this,skill);
	w_victim.SetInvader(invader);

	skill->SetVictim(&w_victim);
	TargetWrapper		w_target(&victim,&attacker,1);
	skill->SetTarget(&w_target);
	skill->SetLevel( msg.attached_skill.level );
	skill->SetPerformerid( attacker );
	skill->SetMessage(&msg);
	skill->SetPerformerpos( src );
	SetSkillTalent(skill, msg.skill_modify);

	bool ret = skill->StateAttack();
	int aggro = skill->GetEnmity();
	if(aggro>0)
		w_victim.SetEnmity(aggro);
	if(skill->GetType()!=TYPE_ATTACK && (skill->GetType()!=TYPE_ENABLED||w_victim.GetProbability()>99))
	{
		short immune = w_victim.GetImmune();
		victim.SendClientEnchantResult(attacker,msg.attached_skill.skill, 
				msg.attached_skill.level,invader,immune,msg.section);
	}
	return ret;
}
bool SkillWrapper::Infect(object_interface victim,const XID& attacker,const A3DVECTOR& src,const attack_msg& msg,bool invader)
{
	if(immune_buff_debuff > 0)		//lgc
	{
		return false;
	}
	
	int id = msg.infected_skill.skill;
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return false;
	PlayerWrapper		w_victim(victim,this,skill);
	w_victim.SetInvader(invader);

	skill->SetVictim(&w_victim);
	TargetWrapper		w_target(&victim,&attacker,1);
	skill->SetTarget(&w_target);
	skill->SetLevel( msg.infected_skill.level );
	skill->SetPerformerid( attacker );
	skill->SetMessage(&msg);
	skill->SetPerformerpos( src );

	bool ret = skill->StateAttack();
	int aggro = skill->GetEnmity();
	if(aggro>0)
		w_victim.SetEnmity(aggro);
	return ret;
}


bool SkillWrapper::Attack(object_interface victim,const XID& attacker,const A3DVECTOR& src,const enchant_msg& msg,bool invader)
{
	if(immune_buff_debuff > 0)		//lgc
	{
		victim.SendClientEnchantResult(attacker,msg.skill, 
				msg.skill_level,invader,msg._attack_state|0x80,msg.section);
		return false;
	}

	SkillKeeper skill = Skill::Create(msg.skill);
	if( !skill )
		return false;

	char type = skill->GetType();
	if(type==TYPE_BLESSPET && !victim.IsPet())
		return false;
	if( (type==TYPE_BLESS||type==TYPE_NEUTRALBLESS||type==TYPE_NEUTRALBLESS2) && victim.IsPet())
		return false;

	PlayerWrapper		w_victim(victim,this,skill);
	w_victim.SetInvader(invader);

	skill->SetVictim(&w_victim);
	TargetWrapper		w_target(&victim,&attacker,1);
	skill->SetTarget(&w_target);
	skill->SetLevel( msg.skill_level );
	skill->SetPerformerid( attacker );
	skill->SetMessage(&msg);
	skill->SetPerformerpos( src );
	SetSkillTalent(skill, msg.skill_modify);

	bool ret = skill->StateAttack();
	int aggro = skill->GetEnmity();
	if(aggro>0)
		w_victim.SetEnmity(aggro);
	if(type!=TYPE_ATTACK && (type!=TYPE_ENABLED||w_victim.GetProbability()>99))
	{
		short immune = w_victim.GetImmune();
		victim.SendClientEnchantResult(attacker,msg.skill, 
				msg.skill_level,invader,immune,msg.section);
	}
	return ret;
}
bool SkillWrapper::Infect(object_interface victim,const XID& attacker,const A3DVECTOR& src,const enchant_msg& msg,bool invader)
{
	if(immune_buff_debuff > 0)		//lgc
	{
		return false;
	}

	int id = msg.infected_skill.skill;
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return false;

	PlayerWrapper		w_victim(victim,this,skill);
	w_victim.SetInvader(invader);

	skill->SetVictim(&w_victim);
	TargetWrapper		w_target(&victim,&attacker,1);
	skill->SetTarget(&w_target);
	skill->SetLevel( msg.infected_skill.level );
	skill->SetPerformerid( attacker );
	skill->SetMessage(&msg);
	skill->SetPerformerpos( src );

	bool ret = skill->StateAttack();
	int aggro = skill->GetEnmity();
	if(aggro>0)
		w_victim.SetEnmity(aggro);
	return ret;
}

bool SkillWrapper::EventChange(object_interface player, int from, int to)
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_CHANGE)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if(skill)
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				if(from!=FORM_CLASS&&to==FORM_CLASS)
					skill->TakeEffect( &w_player, 0);
				else if(from==FORM_CLASS&&to!=FORM_CLASS)
					skill->UndoEffect( &w_player, 0);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventReset(object_interface player)
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_RESET)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if(skill)
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->TakeEffect( &w_player, 0);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventUnreset(object_interface player)
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_RESET)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if(skill)
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->UndoEffect( &w_player, 0);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventWield(object_interface player, int weapon_class )
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_WIELD)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if( skill )
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->TakeEffect(&w_player, weapon_class);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventUnwield(object_interface player, int weapon_class )
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_WIELD)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if( skill )
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->UndoEffect(&w_player, weapon_class);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventEnter(object_interface player, int worldtag )
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_ENTER)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if( skill )
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->TakeEffect(&w_player, worldtag);
			}
		}
	}
	return true;
}
bool SkillWrapper::EventLeave(object_interface player, int worldtag )
{
	PlayerWrapper w_player(player,this,NULL);
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->IsPassive() && stub->GetEventFlag()==EVENT_ENTER)
		{
			SkillKeeper skill = Skill::Create((*it).first);
			if( skill )
			{
				w_player.SetSkill(skill);
				skill->SetLevel( (*it).second.level );
				skill->SetPlayer( &w_player);
				skill->UndoEffect(&w_player, worldtag);
			}
		}
	}
	return true;
}

SkillWrapper::SkillWrapper()
{
	memset( skillinc, 0, sizeof(skillinc) );
	memset( &combo_state, 0, sizeof(combo_state) ); 
	memset( &black_white_ball, 0, sizeof(black_white_ball) );
	prayspeed = 0;
	memset( as, 0, sizeof(as) );
	//asid = 0;
	immune_buff_debuff = 0;
	interrupt_prob = 0;
	ignore_interrupt = 0;
	cd_adjust = 0;
	cd_adjust_count = 0;
	pray_distance_adjust = 0;
}

void SkillWrapper::Load( archive & ar )
{
	map.clear();
	unsigned int size;
	for (ar >> size; size > 0; --size)
	{
		ID id;
		PersistentData data;
		ar >> id;
		ar >> data.ability;
		ar >> data.level;
		ar >> data.overridden;
		map[id] = data;
	}
	dyn_map.clear();
	for (ar >> size; size > 0; --size)
	{
		ID id;
		PersistentData data;
		ar >> id;
		ar >> data.ability;
		ar >> data.level;
		ar >> data.overridden;
		dyn_map[id] = data;
	}
	
	glyph_map.clear();
	for (ar >> size; size > 0; --size)
	{
		ID id;
		PersistentData data;
		ar >> id;
		ar >> data.ability;
		ar >> data.level;
		ar >> data.overridden;
		glyph_map[id] = data;
	}
	
	dynpray_map.clear();
	for (ar >> size; size > 0; --size)
	{
		ID id;
		DynamicPray data;
		ar >> id;
		ar >> data.speed;
		ar >> data.times;
		dynpray_map[id] = data;
	}

	ar.pop_back( skillinc, sizeof(skillinc) );
	ar.pop_back( as, sizeof(as) );
	//ar >> asid;
	//ar >> aslevel;
	ar >> prayspeed;
	ar >> immune_buff_debuff;	//lgc
	ar >> interrupt_prob;
	ar >> ignore_interrupt;
	ar >> cd_adjust;
	ar >> cd_adjust_count;
	ar >> pray_distance_adjust;
	black_white_ball.Load(ar);
	combo_state.Load(ar);
}

void SkillWrapper::Store( archive & ar )
{
	unsigned int size = 0;
	size = map.size();
	ar << size;
	for( StorageMap::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		ar << (*it).first;
		ar << (*it).second.ability;
		ar << (*it).second.level;
		ar << (*it).second.overridden;
	}
	
	size = dyn_map.size();
	ar << size;
	for( StorageMap::const_iterator it = dyn_map.begin(); it != dyn_map.end(); ++it )
	{
		ar << (*it).first;
		ar << (*it).second.ability;
		ar << (*it).second.level;
		ar << (*it).second.overridden;
	}
	size = glyph_map.size();
	ar << size;
	for( StorageMap::const_iterator it = glyph_map.begin(); it != glyph_map.end(); ++it )
	{
		ar << (*it).first;
		ar << (*it).second.ability;
		ar << (*it).second.level;
		ar << (*it).second.overridden;
	}
	size = dynpray_map.size();
	ar << size;
	for( DynPrayMap::const_iterator it = dynpray_map.begin(); it != dynpray_map.end(); ++it )
	{
		ar << (*it).first;
		ar << (*it).second.speed;
		ar << (*it).second.times;		
	}

	ar.push_back( skillinc, sizeof(skillinc) );
	ar.push_back( as, sizeof(as) );
	//ar << asid;
	//ar << aslevel;
	ar << prayspeed;
	ar << immune_buff_debuff;	//lgc
	ar << interrupt_prob;
	ar << ignore_interrupt;
	ar << cd_adjust;
	ar << cd_adjust_count;
	ar << pray_distance_adjust;

	black_white_ball.Save(ar);
	combo_state.Save(ar);
}

void SkillWrapper::LoadDatabase( archive & ar )
{
	map.clear();
	unsigned int size = 0;
	for (ar >> size; size > 0; --size)
	{
		ID id;
		PersistentData data;
		ar >> id;
		ar >> data.ability;
		ar >> data.level;
		if(id) map[id] = data;	//20120419 �������һ����Ҽ����б��д���id=0
	}
	StorageMap::iterator is;
	for( StorageMap::iterator it = map.begin(),ie=map.end(); it!=ie; ++it )
	{
		const SkillStub* stub =  SkillStub::GetStub(it->first);
		if(!stub)
		{
			it->second.overridden = 1;
			continue;
		}
		if(stub->is_senior)
			OverrideSkill(stub->pre_skills);
	}
}

void SkillWrapper::StoreDatabase( archive & ar )
{
	unsigned int size = 0;
	size = map.size();
	ar << size;
	for( StorageMap::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		ar << (*it).first;
		ar << (*it).second.ability;
		ar << (*it).second.level;
	}
}

unsigned int SkillWrapper::StoreDatabaseSize()
{
	return sizeof(unsigned int) + map.size()*(sizeof(unsigned int)+sizeof(int)+sizeof(int));
}

void SkillWrapper::StorePartial( archive & ar )
{
	unsigned int count=0;
	unsigned int reserve1=0; // 172
	for( StorageMap::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		if(!it->second.overridden)
			count++;
	}
	ar << count;
	ar << reserve1; // 172
	for( StorageMap::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		if(!it->second.overridden)
		{
			ar << (short)((*it).first);
			ar << (char)((*it).second.level);
			ar << (short)((*it).second.ability);
		}
	}
}

int SkillWrapper::GetLevel(ID id, int cls, bool use)
{
	StorageMap::iterator it = map.find(id);
	if(it!=map.end())
	{
		if(it->second.overridden)
			return 0;
		return (*it).second.level;
	}
	
	it = dyn_map.find(id);
	if(it!=dyn_map.end())
	{
		return (*it).second.level;
	}
	
	it = glyph_map.find(id);
	if(it!=glyph_map.end())
	{
		return (*it).second.level;
	}
	
	if(cls >= 0 && cls < USER_CLASS_COUNT && SkillStub::IsClsInherent(id,cls))
	{
		return 1;
	}

	return 0;
}

void SkillWrapper::SetLevel(ID id, int level)
{
	map[id].level = level;
}

int SkillWrapper::GetSkillLevel(ID id)
{
	StorageMap::iterator it = map.find(id);
	if( it != map.end() )
	{
		return (*it).second.level;
	}
	it = dyn_map.find(id);
	if(it!=dyn_map.end())
	{
		return (*it).second.level;
	}
	it = glyph_map.find(id);
	if(it!=glyph_map.end())
	{
		return (*it).second.level;
	}
	return 0;
}

int SkillWrapper::GetProduceSkillLevel(ID id)
{
	StorageMap::iterator it = map.find(id);
	if(it == map.end()) return 0;
	SkillKeeper skill = Skill::Create(id);
	if(!skill || !skill->IsProduceSkill()) return 0;
	return it->second.level;
}

bool SkillWrapper::SetSkillInc(int magic, float inc)
{
	if( magic >= 0 && magic < MAGIC_CLASS )
	{
		skillinc[magic] = inc;
		return true;
	}
	return false;
}

float SkillWrapper::GetSkillInc(int magic)
{
	if( magic >= 0 && magic < MAGIC_CLASS )
		return skillinc[magic];
	return 0;
}

int SkillWrapper::NpcStart(ID id,object_interface npc, int level, const XID * target, int size, int& next)
{
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return -1;
	PlayerWrapper		w_npc(npc,this,skill,target,size);
	skill->SetPlayer(&w_npc);
	TargetWrapper		w_target(&npc,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(NULL);
	//�ж���������
	if(!skill->GetRange().NoTarget())
	{
		int tinvisible_degree,tanti_invisible_degree;
		int ret = npc.QueryObject(*target, tinvisible_degree, tanti_invisible_degree);
		if(ret == 0 || npc.GetAntiInvisibleDegree() < tinvisible_degree) 
			return -1;
	}

	skill->NpcFirstRun();
	
	int time = skill->GetStub()->GetState(0)->GetTime(NULL);
	next = skill->GetStub()->GetState(1)->GetTime(NULL);
	if(skill->IsCastSelf())
		npc.SendClientMsgSkillCasting(npc.GetSelfID(), id, time, 1 );
	else
		npc.SendClientMsgSkillCasting(size>0?*target:XID(0,0), id, time, 1 );
	
	return time;
}

void SkillWrapper::NpcEnd(ID id,object_interface npc, int level, const XID * target, int size )
{
	SkillKeeper skill = Skill::Create(id);
	if( !skill )
		return;
	PlayerWrapper		w_npc(npc,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_npc);
	TargetWrapper		w_target(&npc,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(NULL);
	skill->PrepareTalent(&w_npc);

	skill->NpcRun();

	if(!w_npc.GetSuccess())
		npc.SendClientMsgSkillInterrupted(2);
	return;
}

bool SkillWrapper::NpcInterrupt(ID id, object_interface npc, int level )
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return true;

	if(ignore_interrupt)
		return false;

	skill->SetLevel(level);
	bool ret =  SkillStub::GetStub(id)->GetState(0)->Interrupt(skill);
	
	if(!ret)
	{
		if((rand()%100) < interrupt_prob) ret = true;	
	}

	if(ret)
	{
#ifndef _SKILL_TEST
		npc.SendClientMsgSkillInterrupted(1);
#endif
	}
	return ret;
}

float SkillWrapper::NpcCastRange(ID id, int level)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return 0;
	skill->SetLevel(level);
	float range = skill->GetPraydistance();
	return range;
}

int SkillWrapper::ActivateSkill(object_interface player, ID id, int level, int type)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return 0;

	if(skill->IsDurative())
	{
		PlayerWrapper		w_player(player,this,skill, 0 , 0);
		w_player.SetEnable(true);
		skill->SetVictim(&w_player);
		skill->SetLevel( level );
		skill->StateAttack();
	}
	else if (type)
	{
		if (type == 1)
		{
		as[1].id = id;
		as[1].level = level;
		player.AddFilter(new filter_Activateskill2(player));
		}
	}
	else
	{
		as[0].id = id;
		as[0].level = level;
		player.AddFilter(new filter_Activateskill(player));
	}
	return 0;
}

int SkillWrapper::DeactivateSkill(object_interface player, ID id, int level, int type)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return 0;

	if(skill->IsDurative())
	{
		PlayerWrapper		w_player(player,this,skill);
		w_player.SetEnable(false);
		skill->SetVictim(&w_player);
		skill->SetLevel( level );
		skill->StateAttack();
	}
	else if(type || as[0].id != id)
	{
		if (type == 1 || as[1].id == id)
		{
			as[1].id = 0;
			as[1].level = 0;
			player.RemoveFilter(FILTER_ACTIVATESKILL2);
		}
	}
	else
	{
		as[0].id = 0;
		as[0].level = 0;
		player.RemoveFilter(FILTER_ACTIVATESKILL);
	}
	return 0;
}

int SkillWrapper::ActivateReboundSkill(object_interface player, ID id, int level, int trigger_prob, int period)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return 0;
	if(skill->IsDurative())
		return 0;       //��������Ӧ��ʹ��ActivateSkill
	
	as[2].id = id;
	as[2].level = level;
	player.AddFilter(new filter_Activatereboundskill(player, trigger_prob, period));
	return 0;
}

int SkillWrapper::DeactivateReboundSkill(object_interface player, ID id, int /*level*/, int /*trigger_prob*/ , int /*period*/)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return 0;

	if(skill->IsDurative())
	{
    	return 0;       //��������Ӧ��ʹ��DeactivateSkill
	} 
	else if( as[2].id == id )
	{
		as[2].id = 0;
		as[2].level = 0;
		player.RemoveFilter(FILTER_ACTIVATESKILL);
	}
	return 0;
}

int SkillWrapper::IncPrayTime(int inc)
{
	prayspeed -= inc;  
	return 0;
}

int SkillWrapper::DecPrayTime(int dec)
{
	prayspeed += dec;  
	return 0;
}

void SkillWrapper::Swap(SkillWrapper& sw)
{
	sw.map.swap(map);
	sw.dyn_map.swap(dyn_map);
	sw.glyph_map.swap(glyph_map);
	sw.dynpray_map.swap(dynpray_map);
	
	for(unsigned int i = 0; i < MAGIC_CLASS; i ++)
	{
		std::swap(skillinc[i], sw.skillinc[i]);
	}
	
	//std::swap(skillinc[0], sw.skillinc[0]);
	//std::swap(skillinc[1], sw.skillinc[1]);
	//std::swap(skillinc[2], sw.skillinc[2]);
	//std::swap(skillinc[3], sw.skillinc[3]);
	//std::swap(skillinc[4], sw.skillinc[4]);
	std::swap(prayspeed, sw.prayspeed);
	
	for(unsigned int i = 0; i < MAX_ABILITY_SKILL; i ++)
	{
		std::swap(as[i].id, 	sw.as[i].id		);
		std::swap(as[i].level, 	sw.as[i].level	);
	}
	
	//std::swap(asid, sw.asid);
	//std::swap(aslevel, sw.aslevel);
	std::swap(immune_buff_debuff, sw.immune_buff_debuff);
	std::swap(interrupt_prob, sw.interrupt_prob);
	std::swap(ignore_interrupt, sw.ignore_interrupt);
	std::swap(cd_adjust, sw.cd_adjust);
	std::swap(cd_adjust_count, sw.cd_adjust);
	std::swap(pray_distance_adjust, sw.pray_distance_adjust);
	black_white_ball.Swap(sw.black_white_ball);
	combo_state.Swap(sw.combo_state);
}

int SkillWrapper::Remove(ID id)
{
	StorageMap::iterator it = map.find(id);
	if(it!=map.end())
	{
		const SkillStub * stub = SkillStub::GetStub(id);
		if( stub && stub->GetType()==TYPE_PRODUCE)
		{
			map.erase(it);
			return 0;
		}
		return 2;
	}
	return 1;
}

void SkillWrapper::GodEvilConvert(std::unordered_map<int,int>& convert_table, object_interface player, int weapon_class, int form, int worldtag)
{
	//����������ܲ�����Ч��
	EventUnreset(player);
	EventLeave(player,worldtag);
	if(weapon_class > 0) EventUnwield(player, weapon_class);
	if(form == FORM_CLASS) EventChange(player, form, 0); 	

	StorageMap tmp_map;
	StorageMap::iterator it = map.begin(), ite = map.end();
	for(; it!=ite; )
	{
		it->second.overridden = 0;	//�����Ǳ�־����
		
		const SkillStub * stub = SkillStub::GetStub(it->first);
		if(!stub || stub->rank < 20) //��ͨ���ܲ���
		{
			++it;
			continue;	
		}
		std::unordered_map<int,int>::iterator c_it = convert_table.find(it->first);
		if(c_it == convert_table.end())
		{
			//ת������û�е���ħ������ɾ��	
			map.erase(it++);		
		}
		else
		{
			//ת�����д��ڵ�������ת��	
			PersistentData data;
			data.level = it->second.level;
			map.erase(it++);		
			tmp_map.insert(std::make_pair(c_it->second,data));
		}
	}

	map.insert(tmp_map.begin(), tmp_map.end());
	
	//���㱻���Ǳ�־
	StorageMap::iterator is;
	it = map.begin(), ite = map.end();
	for(; it!=ite; ++it)
	{
		const SkillStub* stub =  SkillStub::GetStub(it->first);
		if(!stub)
		{
			it->second.overridden = 1;
			continue;
		}
		if(stub->is_senior)
			OverrideSkill(stub->pre_skills);
	}
	
	//���¼�������ܲ�����Ч��
	EventReset(player);
	EventEnter(player,worldtag);
	if(weapon_class > 0) EventWield(player, weapon_class);
	if(form == FORM_CLASS) EventChange(player, 0, form); 
}

void SkillWrapper::ActivateDynSkill(ID id, int counter)
{
	StorageMap::iterator it = dyn_map.find(id);
	if(it == dyn_map.end())
	{
		PersistentData data;
		data.ability = counter;
		data.level = 1;
		data.overridden = 0;
		dyn_map[id] = data;
		//��֪ͨ��
		//֪ͨ�ͻ����������¼���
		return;
	}

	it->second.ability += counter;
}

void SkillWrapper::ResurrectByCashAddFilter(object_interface player, int buff_period, const float* buff_ratio, int buff_size)
{
	if ( buff_period > 0 && buff_ratio && buff_size == 6 )
	{
		PlayerWrapper		w_player(player, 0, 0, 0, 0);

		w_player.SetTime(1000.0f * buff_period);
		w_player.SetProbability(100.0);
		w_player.SetRatio(*buff_ratio);
		w_player.SetGiant(1);
		w_player.SetRatio(buff_ratio[1]);
		w_player.SetBlessmagic(1);
		w_player.SetRatio(buff_ratio[2]);
		w_player.SetStoneskin(1);
		w_player.SetRatio(buff_ratio[3]);
		w_player.SetIncresist(1);
		w_player.SetRatio(buff_ratio[4]);
		w_player.SetInchp(1);
		w_player.SetRatio(buff_ratio[5]);
		w_player.SetIronshield(1);	
	}
}


void SkillWrapper::MnFactionAddFilter(object_interface player, float ratio)
{
	PlayerWrapper		w_player(player, 0, 0, 0, 0);
	w_player.SetRatio(ratio);
	w_player.SetMnfactionDecresist(1);
}


void SkillWrapper::DeactivateDynSkill(ID id, int counter)
{
	StorageMap::iterator it = dyn_map.find(id);
	if(it == dyn_map.end())
	{
		ASSERT(false);
		return;
	}
	
	it->second.ability -= counter;
	ASSERT(it->second.ability >= 0);
	if(it->second.ability == 0)
	{
		//��֪ͨ��
		//֪ͨ�ͻ��˼����˼���
		dyn_map.erase(it);
	}
}

int SkillWrapper::GetDynSkillCounter(ID id)
{
	StorageMap::iterator it = dyn_map.find(id);
	if(it != dyn_map.end())
		return it->second.ability;
	return 0;
}

int SkillWrapper::GetProduceSkill()
{
	for( StorageMap::iterator it = map.begin(); it != map.end(); ++ it )
	{
		const SkillStub * stub = SkillStub::GetStub((*it).first);
		if( stub && stub->GetType()==TYPE_PRODUCE)
		{
			return stub->GetId();
		}
 	}
	return 0;
}

int SkillWrapper::IncAbility(object_interface player, ID id, int inc)
{
	StorageMap::iterator it = map.find(id);
	if(it==map.end())
		return -1;
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;
	int max = 0;
	int level = (*it).second.level;
	if(level>=1 && level<=skill->GetMaxLevel())
	{
		skill->SetLevel(level);
		max = skill->GetMaxability();
	}

	int ability = (*it).second.ability;
	if(ability==max)
		return -1;
	ability += inc;
	if(ability>max)
		ability = max;
	(*it).second.ability = ability;
	player.SendClientSkillAbility(id, ability);
	return ability;
}

int SkillWrapper::GetAbility(ID id)
{
	StorageMap::iterator it = map.find(id);
	if(it==map.end())
		return 0;
	return (*it).second.ability;
}

float SkillWrapper::GetAbilityRatio(ID id)
{
	StorageMap::iterator it = map.find(id);
	if(it == map.end())
		return -1;
	int ability = (*it).second.ability;
	int level = (*it).second.level;

	SkillKeeper skill = Skill::Create(id);
	if(!skill) return -1;
	if(level<1 || level > skill->GetMaxLevel())
		return -1;
	skill->SetLevel(level);
	int max_ability = skill->GetMaxability();
	if(max_ability == 0) 
		return -1;

	return ability/max_ability;
}

int SkillWrapper::IncAbilityRatio(object_interface player, ID id, float ratio)
{
	StorageMap::iterator it = map.find(id);
	if(it==map.end())
		return -1;
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;
	int max = 0;
	int level = (*it).second.level;
	if(level>=1 && level<=skill->GetMaxLevel())
	{
		skill->SetLevel(level);
		max = skill->GetMaxability();
	}

	int ability = (*it).second.ability;
	if(ability==max)
		return -1;
	ability += (int)(max*ratio);
	if(ability>max)
		ability = max;
	(*it).second.ability = ability;
	player.SendClientSkillAbility(id, ability);
	return ability;
}

char SkillWrapper::GetType( ID id) 
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub)
		return -1;
	return stub->GetType();
}

char SkillWrapper::RangeType( ID id)
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub)
		return -1;
	return stub->GetRange().type;
}

int SkillWrapper::SetSealed(object_interface player, int second)
{
	player.AddFilter(new filter_Sealed(player,second,0));
	return 0;
}

int SkillWrapper::SetFix(object_interface player, int second)
{
	player.AddFilter(new filter_Fix(player,second));
	return 0;
}

int SkillWrapper::SetFlager(object_interface player, float hurt_ratio, float hurt_ratio2, float speed_ratio, float max_hp_ratio)
{
	player.AddFilter(new filter_Flager(player, hurt_ratio, hurt_ratio2, speed_ratio, max_hp_ratio));
	return 0;
}

int SkillWrapper::UnSetFlager(object_interface player)
{
	player.RemoveFilter(FILTER_FLAGER);
	return 0;
}

int SkillWrapper::OnCountryBattleRevive(object_interface player, int time, int ap, float physic_ratio, float magic_ratio, int time2, float incresist, float incdefense, float inchp)
{
	player.ModifyAP(ap);
	player.AddFilter(new filter_Incattack(player, int (physic_ratio*100+1e-6), time));
	player.AddFilter(new filter_Incmagic(player, int (magic_ratio*100+1e-6), time));
	player.AddFilter(new filter_Incresist(player,int (incresist*100+1e-6), time2));
	player.AddFilter(new filter_Ironshield(player, int (incdefense*100+1e-6), time2));
	player.AddFilter(new filter_Inchp(player, int (inchp*100+1e-6), time2));
	return 0;
}

void SkillWrapper::CountryBattleWeakProtect(object_interface player, int time, int inc_atk_degree, int inc_def_degree)
{
	player.AddFilter(new filter_Addattackdefenddegree(player, time, inc_atk_degree, inc_def_degree));
}

void SkillWrapper::SetChariotFilter(object_interface player, int shape, int inc_hp, int inc_defence, int inc_magic_defence[5], int inc_damage, int inc_magic_damage, float inc_speed, float inc_hp_ratio, int dyn_skill[4])
{
	//���һЩӰ��ƽ���buf
	player.RemoveFilter(FILTER_SOULRETORT);
	player.RemoveFilter(FILTER_SOULSEALED);
	player.RemoveFilter(FILTER_SOULBEATBACK);
	player.RemoveFilter(FILTER_SOULSTUN);
	player.RemoveFilter(FILTER_SOULRETORT2);
	player.RemoveFilter(FILTER_REBIRTH);
	player.RemoveFilter(FILTER_REBIRTH2);
	player.RemoveFilter(FILTER_INCATKDEFHP);
	
	int form = player.GetForm();
	if(form==FORM_CLASS)
	{
		player.RemoveFilter(FILTER_TIGERFORM);
		player.RemoveFilter(FILTER_FOXFORM);
		player.RemoveFilter(FILTER_FISHFORM);
		player.RemoveFilter(FILTER_THUNDERFORM);
        player.RemoveFilter(FILTER_SHADOWFORM);
        player.RemoveFilter(FILTER_FAIRYFORM);
		player.RemoveFilter(FILTER_CANNONFORM);
		player.RemoveFilter(FILTER_MONKEYFORM);
	}
	player.AddFilter(new filter_Chariotform(player, shape, inc_hp, inc_defence, inc_magic_defence, inc_damage, inc_magic_damage, inc_speed, 
				(int)(inc_hp_ratio*100+1e-6), dyn_skill));
}

void SkillWrapper::OverrideSkill(const std::vector<std::pair<ID,int> > & pre_skills)
{
	for(unsigned int i=0; i<pre_skills.size(); i++)
	{
		ID pre_id = pre_skills[i].first;
		if(pre_id <= 0) continue;
		StorageMap::iterator is = map.find(pre_id);
		if(is != map.end())
			is->second.overridden = 1;
	}
}

int SkillWrapper::GetCooldownID(ID id)
{
	return id+COOLINGID_BEGIN;
}

int SkillWrapper::GetMpCost(ID id, object_interface npc, int level)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;
	PlayerWrapper w_npc(npc, NULL, skill);
	skill->SetPlayer(&w_npc);
	skill->SetLevel(level);
	
	return (int)(skill->GetStub()->GetMpcost(skill));
}

int SkillWrapper::PetLearn(ID id,int petlevel,object_interface owner,unsigned int *skills,int size)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;
	const SkillStub * stub = skill->GetStub();
	unsigned int level = 1;
	for(int i=0;i<size;i+=2)
	{
		if(skills[i]==id)
		{
			level = skills[i+1]+1;
			break;
		}
	}
	if(level>(unsigned int)stub->max_level)
		return -1;

	skill->SetLevel(level);

	if(stub->cls != 127)
		return -1;
	
	for(unsigned int i=0; i<stub->pre_skills.size(); i++)
	{
		ID pre_id = stub->pre_skills[i].first;
		int pre_level = stub->pre_skills[i].second;
		if(pre_id > 0)
		{
			int curlevel = 0;
			for(int i=0;i<size;i+=2)
			{
				if(skills[i]==pre_id)
				{
					curlevel = skills[i+1];
					break;
				}
			}
			if(pre_level>curlevel)
				return -1;
		}
	}
	if(petlevel < skill->GetRequiredLevel())
		return -1;
	
	int sp = skill->GetRequiredSp();
	int item = skill->GetRequiredItem();

	if(sp>owner.GetBasicProp().skill_point)
		return -1;
	
	if(item && owner.TakeOutItem(item)<0)
		return -1;
	
	if(sp>0)
		owner.DecSkillPoint(sp);
	return level;
}
int SkillWrapper::ElfLearnSkill(int id, int level, SKILL::elf_requirement& elf, object_interface player)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return -1;
	const SkillStub * stub = skill->GetStub();
	skill->SetLevel(level);
	if(level>stub->max_level)
		return -1;
	if(stub->cls != 258)
		return -1;
	int sp = skill->GetRequiredSp();
	int mask = skill->GetRequiredLevel();
	int item = skill->GetRequiredItem();

	short req_level = mask%100;
	if(elf.elf_level < req_level)	
		return -1;
	mask /= 100;
	int type = 4;
	int cost = 0;
	while(mask)
	{
		cost = mask%10;
		if(elf.genius[type]<cost)
			return -1;
		mask /= 10;
		if(--type < 0)
			break;		
	}
	if(sp>player.GetBasicProp().skill_point)
		return -1;
	if(item && player.TakeOutItem(item)<0)
		return -1;
	if(sp>0)
		player.DecSkillPoint(sp);
	return level;
}
bool SkillWrapper::IsElfSkillActive(int id, int level, SKILL::elf_requirement& elf, object_interface player)
{
	SkillKeeper skill = Skill::Create(id);
	if(!skill)
		return false;
	const SkillStub * stub = skill->GetStub();
	skill->SetLevel(level);
	if(stub->cls != 258)
		return false;
	if(stub->clslimit && ((1<<player.GetClass())&stub->clslimit)==0)
		return false;
	int mask = skill->GetRequiredLevel();
	short req_level = mask%100;
	if(elf.elf_level < req_level)	
		return false;
	mask /= 100;
	int type = 4;
	int cost = 0;
	while(mask)
	{
		cost = mask%10;
		if(elf.genius[type]<cost)
			return false;
		mask /= 10;
		if(--type < 0)
			break;		
	}
	return true;
}

int SkillWrapper::RunElfSkill( SKILL::Data & skilldata, int level, object_interface player, const XID* target, int size)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill || !skill->IsInstant())
		return -1;
	const SkillStub * stub = skill->GetStub();
	if(stub->cls != 258)
		return -1;
	if(stub->clslimit && ((1<<player.GetClass())&stub->clslimit)==0)
		return -1;
	PlayerWrapper w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);
	int ret = skill->ElfCondition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
	{
		return -1;
	}
	if(skill->InstantRun())
	{
		player.SendClientElfSkill(size>0?*target:XID(0,0), skilldata.id, level);
	}
	
	return ret;
}

void SkillWrapper::SetSkillTalent(Skill* skill, const int* list)
{
	for(int i=0;i<3;i++)
		skill->SetTalent(i,list[i]);
}

bool SkillWrapper::IsInstant(ID id)
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub || !stub->IsInstant())
		return false;
	return true;
}

bool SkillWrapper::IsPosSkill(ID id)
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub || stub->GetType()!=TYPE_JUMP) 
		return false;
	return true;
}

bool SkillWrapper::IsMovingSkill(ID id)
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub || !stub->IsMovingSkill())
		return false;
	return true;
}

int SkillWrapper::StartRuneSkill( SKILL::Data & skilldata, object_interface player, const XID * target, 
		int size, int & next_interval, int level)
{
	next_interval = -1;
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);

	int ret = skill->Condition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
	{
		//printf("StartSkill Error: sid=%d err=%d\n", skilldata.id, ret);
		return -1;
	}

	ret = skill->FirstRun( next_interval, prayspeed + GetDynPrayspeed(skilldata.id) );
	if(ret>=0)
	{
		if(skill->IsCastSelf())
			player.SendClientMsgRuneSkillCasting(player.GetSelfID(), skilldata.id, ret, level);
		else
			player.SendClientMsgRuneSkillCasting(size>0?*target:XID(0,0), skilldata.id, ret, level);
	}

	return ret;
}

int SkillWrapper::RunRuneSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size , int& next_interval, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);

	int ret = skill->Run( next_interval );

	if(!w_player.GetSuccess())
	{
		ret = -1;
		player.SendClientMsgSkillInterrupted(2);
	}
	return ret;
}

int SkillWrapper::ContinueRuneSkill( SKILL::Data& skilldata, object_interface player, const XID* target, int size, int& next_interval, int elapse_time, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->SetCharging(elapse_time);
	skill->PrepareTalent(&w_player);

	next_interval = -1;
	int time = skill->Run( next_interval );

	return time;
}

bool SkillWrapper::InterruptRuneSkill( SKILL::Data & skilldata, object_interface player, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	if( ignore_interrupt )
		return false;

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);

	bool ret = false;
	ret = skill->Interrupt();

	if(!ret)
	{
		if((rand()%100) < interrupt_prob) ret = true;	
	}

	if( ret )
	{
#ifndef _SKILL_TEST
		player.SendClientMsgSkillInterrupted(1);
#endif
	}
	return ret;
}

bool SkillWrapper::CancelRuneSkill( SKILL::Data & skilldata, object_interface player, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill )
		return -1;

	PlayerWrapper		w_player(player,this,skill);
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);

	bool ret = false;
	ret = skill->Cancel();

	if( ret )
	{
#ifndef _SKILL_TEST
		player.SendClientMsgSkillInterrupted(2);
#endif
	}
	return ret;
}

int SkillWrapper::RuneInstantSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size, int level)
{
	SkillKeeper skill = Skill::Create(skilldata.id);
	if( !skill || !skill->IsInstant())
		return -1;

	PlayerWrapper		w_player(player,this,skill,target,size);
	Skill* s_skill;
	skill->SetPlayer(&w_player);
	TargetWrapper		w_target(&player,target,size);
	skill->SetTarget(&w_target);
	skill->SetLevel(level);
	skill->SetData(&skilldata);
	skill->PrepareTalent(&w_player);

	int ret = skill->Condition();
	if(ret!=0 || !player.TestCoolDown(skilldata.id+COOLINGID_BEGIN) || !TestCommonCoolDown(skill->GetCommonCoolDown(),player))
		return -1;

	//�ͻ���Ҫ���ȷ��������Ϣ
	player.SendClientRuneInstantSkill(size>0?*target:XID(0,0), skilldata.id, level);
	skill->InstantRun();

	return ret;
}

bool SkillWrapper::TestCommonCoolDown(int cd_mask, object_interface player)
{
	int i = 0;
	while(cd_mask)
	{
		if(cd_mask & 1)
		{
			if(!player.TestCommonCoolDown(i)) return false;
		}
		i++;
		cd_mask >>= 1;
	}
	return true;	
}

void SkillWrapper::ModifyDynamicPray(ID id, float ratio, int times)
{
	if(times)
	{
		dynpray_map[id].speed = int(ratio*100);
		dynpray_map[id].times = times;
	}
	else
	{
		dynpray_map.erase(id);
	}
}

int SkillWrapper::GetDynamicPrayTimes(ID id)
{
	DynPrayMap::iterator iter = dynpray_map.find(id);
	if(iter != dynpray_map.end())
	{
		return iter->second.times;
	}
	return 0;
}

void SkillWrapper::OnComboPreSkillEnd(Skill* skill, object_interface player)
{
	int now = player.GetSystime();
	if(CheckComboBreak(now,true))
	{
		SetComboState(skill->GetId(),now,skill->GetComboBreakType(),skill->GetComboExpire());
		skill->ComboSkEndAction();
		SyncComboState(player);
	}
}

void SkillWrapper::OnSkillPerform(ID id, ID perid, object_interface player)
{
	if(GetComboState() && (perid || CheckComboBreak(player.GetSystime(),false)))
	{
		ClearComboState();
		SyncComboState(player);
	}
}

void SkillWrapper::SyncComboState(object_interface player)
{
	player.SendClientComboSkillPerpare(combo_state.skillid, combo_state.timestamp,
  						combo_state.arg[0],combo_state.arg[1],combo_state.arg[2]);
}

bool SkillWrapper::AddBlackWhiteBalls(int ball, int& new_vstate, int& old_vstate, int& hstate)
{
	if(!black_white_ball.Add(ball)) return false;
	new_vstate = black_white_ball.UpdateVstate(old_vstate);
	hstate = black_white_ball.balls;
	return true;
}

bool SkillWrapper::FlipBlackWhiteBalls(int& new_vstate, int& old_vstate, int& hstate)
{
	black_white_ball.Flip();
	new_vstate = black_white_ball.UpdateVstate(old_vstate);
	hstate = black_white_ball.balls;
	return true;
}


void SkillWrapper::SoloChallengeAddFilter(object_interface player, int filter_id, float *param)
{
	PlayerWrapper w_player(player);
	switch(filter_id)
	{
		case FILTER_SOLO_INCATTACKANDMAGIC:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			w_player.SetValue(param[3]);
			
			w_player.SetSoloIncAttackAndMagic(true);
		}
		break;
		case FILTER_SOLO_INCDEFENCE:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloIncDefence(true);
		}
		break;
		case FILTER_SOLO_ENHANCERESIST:
		{	
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloEnhanceResist(true);
		}
		break;
		case FILTER_SOLO_INCMAXHP:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloIncMaxHP(true);
		}
		break;
		case FILTER_SOLO_INVINCIBLE:
		{
			w_player.SetTime(param[0]);
			w_player.SetProbability(param[1]);
			
			w_player.SetInvincible8(true);
		}
		break;
		case FILTER_SOLO_HPGEN:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloHpGen(true);
		}
		break;
		case FILTER_SOLO_DECHURT:
		{
			w_player.SetTime(param[0]);
			w_player.SetRatio(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloDecHurt(true);
		}
		break;
		case FILTER_SOLO_ADDATTACKRANGE:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			w_player.SetSoloAddAttackRange(true);
		}
		break;
		case FILTER_SOLO_ADDATTACKDEGREE:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloAddAttackLevel(true);
		}
		break;
		case FILTER_SOLO_ADDDEFENCEDEGREE:
		{
			w_player.SetTime(param[0]);
			w_player.SetAmount(param[1]);
			w_player.SetProbability(param[2]);
			
			w_player.SetSoloAddDefendLevel(true);
		}
		break;
	}
}

void SkillWrapper::DoubleCleaner(int rank)
{
	for( StorageMap::const_iterator it = map.begin(); it != map.end(); ++it )
	{
		const SkillStub * stub = SkillStub::GetStub(it->first);
		if (stub)
		{
			int srank = (int)( stub->rank *0.1);
			int prank = (int)( rank *0.1);
			
			if (srank != prank && srank > 0 && srank < 4 )
			{
				map.erase(it);
				DoubleCleaner(rank);
				return;
			}
		}
	}
	
	StorageMap::iterator it = map.begin(), ite = map.end();
	for(; it!=ite; ++it)
	{
		const SkillStub* stub =  SkillStub::GetStub(it->first);
		if(!stub)
		{
			it->second.overridden = 1;
			continue;
		}
		if(stub->is_senior)
			OverrideSkill(stub->pre_skills);
	}
	
}

// glyph

int SkillWrapper::GetSkillRuneAttr(ID id)
{
	StorageMap::iterator it = map.find(id);
	if( it != map.end() )
	{
		SkillKeeper skill = Skill::Create(id);
		if(skill)
		{
			return skill->GetGlyphType();
		}
	}
	return 0;
}

void SkillWrapper::ActivateGlyphSkill(ID id, ID pre_id, int level)
{ 
	if ( id > 0 && pre_id > 0 && level >= 1 && level <= 10)
	{
		//printf("ActivateGlyphSkill: id = %d , pre_id = %d , level = %d \n", id, pre_id, level);
		
		StorageMap::iterator it_pre = map.find(pre_id);
		// если скилла нет у персонажа
		if ( it_pre==map.end() )
		{
			return;
		}
		
		//если скилл у персонажа уже занят другой руной
		if ( (*it_pre).second.overridden == 2 )
		{
			return;
		}
		
		StorageMap::iterator it = glyph_map.find(id);
		//если руна уже существует
		if( it != glyph_map.end() )
		{
			return;
		}
		
		//добавляем скилл в мапу
		PersistentData data;
		data.ability = pre_id;
		data.level = level;
		data.overridden = 0;
		glyph_map[id] = data;
		// занимаем дефолтный скилл руной
		(*it_pre).second.overridden = 2;
	}
}

void SkillWrapper::DeactivateGlyphSkill(ID id, ID pre_id)
{
	if ( id > 0 && pre_id > 0 )
	{
		//printf("DeactivateGlyphSkill: id = %d , pre_id = %d , \n", id, pre_id);
		
		StorageMap::iterator it = map.find(pre_id);
		if(it!=map.end())
		{
			(*it).second.overridden = 0;
		}
		
		it = glyph_map.find(id);
		if(it != glyph_map.end())
		{
			glyph_map.erase(it);
		}
	}
}

void SkillWrapper::ClearGlyphSkill()
{
	glyph_map.clear();
	
	StorageMap::iterator it=map.begin(), ite=map.end();
	for ( ;it!=ite;++it )
	{
		if ( (*it).second.overridden == 2 )
		{
			(*it).second.overridden = 0;
		}
	}
}

// cooldown limit

int SkillWrapper::GetCoolDownLimit( ID id )
{
	if (id)
	{
		int level = GetSkillLevel(id);
		if (level >= 1 && level <= 10)
		{
			SkillKeeper skill = Skill::Create(id);
			if(skill)
			{
				skill->SetLevel( level );
				return skill->GetCoolDownLimit();
			}
		}
	}
	return 0;
}

// cooldown limit end

//++++++++++++++++++172++++++++++++++++++++

bool SkillWrapper::IsImmineCasting(ID id)
{
	const SkillStub * stub = SkillStub::GetStub(id);
	if(!stub || !stub->IsImmineCasting())
		return false;
	return true;
}

int SkillWrapper::SetFreemoveMonkey(object_interface player, int second)
{
	player.AddFilter(new filter_FreemoveMonkey(player, second));
	return 0;
}

}

