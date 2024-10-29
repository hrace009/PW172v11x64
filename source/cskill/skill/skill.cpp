
#include "skill.h"
#include "playerwrapper.h"
#include "skillwrapper.h"
#include "range.h"

#ifdef INTEPRETED_EXPR 
#include "skillexpr.h"
#endif

namespace GNET
{

bool SkillStub::ReqSecLevel(Skill * skill ) const
{
	PlayerWrapper * player = skill->GetPlayer();
	unsigned int cur = player->GetRank();
	unsigned int flag = player->GetFlag();
	unsigned int req = rank;

	if(cur < req) 
	{
		return false;
	}
	
	if( req >= 20 && req < 40 && ( (req/10-1) != flag) )
	{
		return false;
	}

	return true;
}

bool SkillStub::ReqPreSKill(Skill * skill ) const
{
	PlayerWrapper * player = skill->GetPlayer();
	
	if (rank >= 40)
	{
		unsigned int valid = 0;
		for(unsigned int i=0; i<pre_skills.size(); i++)
		{
			ID pre_id = pre_skills[i].first;
			int pre_level = pre_skills[i].second;
			if(pre_id > 0 && player->GetSkilllevel(pre_id) >= pre_level)
			{
				valid++;
				break;
			}
		}
		if(!valid)
		{
			return false;
		}
	}
	else
	{
		for(unsigned int i=0; i<pre_skills.size(); i++)
		{
			ID pre_id = pre_skills[i].first;
			int pre_level = pre_skills[i].second;
			if(pre_id > 0 && player->GetSkilllevel(pre_id) < pre_level)
			{
				return false;
			}
		}
	}
	return true;
}

bool SkillStub::LearnCondition(Skill * skill ) const
{
	PlayerWrapper * player = skill->GetPlayer();

	int next_level = skill->GetLevel();
	if( next_level < MIN_LEVEL || next_level > max_level )
	{
		return false;
	}

	if( player->GetHistoricalmaxlevel() < GetRequiredLevel(skill))
	{
		return false;
	}
	
	if(player->GetRealm() < GetRequiredRealmLevel(skill))
	{
		return false;	
	}

	if( cls != 255 && cls != player->GetCls() )
	{
		return false;
	}
	
	if (!ReqSecLevel(skill))
	{
		return false;
	}

	if (!ReqPreSKill(skill))
	{
		return false;
	}

	return true;
}

bool SkillStub::Learn(Skill * skill) const
{
	LuaSkill * lua = LuaSkill::GetInstance();
	
	PlayerWrapper * player = skill->GetPlayer();
	int next_level = skill->GetLevel();

	int Sp = GetRequiredSp(skill);
	if (!lua->GetConfig()->FREE_SP && player->GetSp() < Sp)
	{
		return false;
	}
	
	int money = GetRequiredMoney(skill);
	if( !lua->GetConfig()->FREE_MONEY && player->GetMoney() < money)
	{
		return false;
	}

	if( !LearnCondition(skill) )
	{
		return false;
	}

	int item = GetRequiredItem(skill);
	if( !lua->GetConfig()->FREE_ITEM && item != 0 && !player->SetUseitem(item))
	{
		return false;
	}
	
	if( !lua->GetConfig()->FREE_MONEY )
	{
		player->SetUsemoney(money);
	}
	
	if( !lua->GetConfig()->FREE_SP )
	{
		player->SetDecsp(Sp);
	}

	if(IsPassive())
	{
		if(GetEventFlag()==EVENT_RESET
			|| GetEventFlag()==EVENT_WIELD
			|| GetEventFlag()==EVENT_CHANGE && player->GetForm()==FORM_CLASS)
		{
			if(next_level>1)
			{
				skill->SetLevel(next_level-1);
				skill->UndoEffect(player, -1);
				skill->SetLevel(next_level);
			}
			skill->TakeEffect(player, -1);
		}
		else if( GetEventFlag() == EVENT_ENTER)
		{
			int worldtag = player->GetWorldTag();
			if(next_level>1)
			{
				skill->SetLevel(next_level-1);
				skill->UndoEffect(player, worldtag);
				skill->SetLevel(next_level);
			}
			skill->TakeEffect(player, worldtag);
		}
	}
	return true;
}

bool SkillStub::Push(Skill *skill) const
{
	PlayerWrapper * player = skill->GetPlayer();
	int next_level = skill->GetLevel();
	if (next_level < MIN_LEVEL) next_level = MIN_LEVEL;
	if (next_level > max_level) next_level = max_level;

	if(IsPassive())
	{
		if(GetEventFlag()==EVENT_RESET
			|| GetEventFlag()==EVENT_WIELD
			|| GetEventFlag()==EVENT_CHANGE && player->GetForm()==FORM_CLASS)
		{
			if(next_level>1)
			{
				skill->SetLevel(next_level-1);
				skill->UndoEffect(player, -1);
				skill->SetLevel(next_level);
			}
			skill->TakeEffect(player, -1);
		}
		else if( GetEventFlag() == EVENT_ENTER)
		{
			int worldtag = player->GetWorldTag();
			if(next_level>1)
			{
				skill->SetLevel(next_level-1);
				skill->UndoEffect(player, worldtag);
				skill->SetLevel(next_level);
			}
			skill->TakeEffect(player, worldtag);
		}
	}
	return true;
}

int SkillStub::Condition(Skill *skill) const
{
	if(GetType()==TYPE_PASSIVE)
		return 2;
	if(skill->GetPlayer()->GetMp()<(int)(GetMpcost(skill)))
		return 3;

	if(skill->GetPlayer()->GetAp()<apcost)
		return 4;

	if((allow_forms & (1 << skill->GetPlayer()->GetForm()))==0)
		return 5;

	if(!allow_land && skill->GetPlayer()->GetLanding())
		return 7;
		
	if(!allow_air && skill->GetPlayer()->GetAiring())
		return 7;
		
	if(!allow_water && skill->GetPlayer()->GetWatering())
		return 7;
		
	if(!allow_ride && skill->GetPlayer()->GetRiding())
		return 8;
	
	if(notuse_in_combat && skill->GetPlayer()->GetCombat())
		return 9;
	
	if(itemcost > 0 && !skill->GetPlayer()->SetCheckitem(itemcost, itemcostcount))	
		return 10;
	
	if(!CheckHpCondition(skill->GetPlayer()->GetHp(), skill->GetPlayer()->GetMaxhp()))
		return 11;

	if( !(range.IsSelf() || range.IsSelfBall()&&!IsAttack()&&!IsCurse() ))
	{
		if(skill->GetPlayer()->CheckTarget(1.0f+GetPraydistance(skill), restrict_corpse)==false) 
			return 6;
	}

	if(!skill->CanAttackCondition(false))
		return 12;

	if(GetComboPreSkill() && (!skill->GetPlayer()->CheckComboState(GetComboPreSkill(),GetComboPreInterval()) || !CheckComboSkExtraCondition(skill)))
		return 13;

	if ( GetCostShieldEnergy(skill) && !skill->GetPlayer()->UseSheild(GetCostShieldEnergy(skill)) )
		return 14;
	return SKILL_SUCCESS;
}

int SkillStub::ElfCondition(Skill *skill) const
{
	if(GetType()==TYPE_PASSIVE)
		return 2;
	if(skill->GetPlayer()->GetElfmp()<(int)(GetMpcost(skill)))
		return 3;
	//С����������㷨:apcost����λ��ϵ������λΪ��ֵ�����۳�Ϊ ��ֵ+ϵ��*(skilllevel-1)
	if(skill->GetPlayer()->GetElfap()< (apcost/1000+apcost%1000*(skill->GetLevel()-1)))
		return 4;
	
	if(!allow_land && skill->GetPlayer()->GetLanding())
		return 7;
		
	if(!allow_air && skill->GetPlayer()->GetAiring())
		return 7;
		
	if(!allow_water && skill->GetPlayer()->GetWatering())
		return 7;
		
	if(!allow_ride && skill->GetPlayer()->GetRiding())
		return 8;

	if(notuse_in_combat && skill->GetPlayer()->GetCombat())
		return 9;
	
	if(itemcost > 0 && !skill->GetPlayer()->SetCheckitem(itemcost, itemcostcount))	
		return 10;
	
	//if( !range.NoTarget()) 
	if( !(range.IsSelf() || range.IsSelfBall()&&!IsAttack()&&!IsCurse() ))
	{
		if(skill->GetPlayer()->CheckTarget(1.0f+GetPraydistance(skill), restrict_corpse)==false) 
			return 6;
	}

	return SKILL_SUCCESS;
}

void SkillStub::Clear()
{
	for( unsigned int i=0; i<statestub.size(); i++ )
		delete statestub[i];
	statestub.clear();
}


bool Skill::CanAttackCondition(bool usearrow) 
{
	if(stub->IsAttack() && !player->CanAttack())
		return false;
	
	
	if ( !player->BugSkillRelease( GetId() , player->GetCls() ) )
	{
		unsigned int i;
		for( i=0; i<stub->restrict_weapons.size(); i++ )
		{
			if( player->IsUsingWeapon(stub->restrict_weapons[i]) )
				break;
		}
		if( i>0 && i >= stub->restrict_weapons.size() )
			return false;
	}
	
	if(usearrow && stub->arrowcost>0 && !player->UseArrow(stub->arrowcost))
		return false;
	return true;
}


bool Skill::CanAttack(bool usearrow) 
{
	if(stub->IsAttack() && !player->CanAttack())
		return false;
	
	unsigned int i;
	for( i=0; i<stub->restrict_weapons.size(); i++ )
	{
		if( player->IsUsingWeapon(stub->restrict_weapons[i]) )
			break;
	}
	if( i>0 && i >= stub->restrict_weapons.size() )
		return false;
	
	if(usearrow && stub->arrowcost>0 && !player->UseArrow(stub->arrowcost))
		return false;
	return true;
}

#ifdef INTEPRETED_EXPR 

void SkillStub::GetExprKey( int skillid, const char * key, std::string & result )
{
	char buffer[128];
	sprintf( buffer, "skill%d.%s", skillid, key );
	result = buffer;
}

void SkillStub::GetExprKey( int skillid, int stateid, const char * key, std::string & result )
{
	char buffer[128];
	sprintf( buffer, "skill%d.state%d.%s", skillid, stateid, key );
	result = buffer;
}

void SkillStub::GetExprKey( int skillid, const char * key, int index, std::string & result )
{
	char buffer[128];
	sprintf( buffer, "skill%d.%s%d", skillid, key, index );
	result = buffer;
}


Marshal::OctetsStream& SkillStub::marshal(Marshal::OctetsStream &os)	const
{
	unsigned int i;
	os << id << cls <<  name << icon << max_level << type << attr << practice_level;

	os << eventflag;
	for( i=MIN_LEVEL; i<=MAX_LEVEL; i++ )
		os << learncond_exp[i] << learn_exp[i];

	os << allow_land << allow_air << allow_water << allow_ride;
	os << restrict_corpse << allow_changestatus;
	os << MarshalContainer(restrict_weapons) << MarshalContainer(allow_skills);
	os << effect;

	os << executetime_exp << coolingtime_exp << has_stateattack << stateattack_exp;
	os << takeeffect_exp;
	os << enmity_exp << requiredsp_exp << requiredlevel_exp;

	os << range;
	
	unsigned int statesize;
	statesize = statestub.size();
	os << statesize;
	for( i=0; i<statestub.size(); i++ )
		os << (*(statestub[i]));
	return os;
}

const Marshal::OctetsStream& SkillStub::unmarshal(const Marshal::OctetsStream &os)
{
	Clear();

	std::string key;
	unsigned int i;
	os >> id >> cls >>  name >> icon >> max_level >> type >> attr >> practice_level;

	os >> eventflag;
	for( i=MIN_LEVEL; i<=MAX_LEVEL; i++ )
	{
		os >> learncond_exp[i] >> learn_exp[i];

		GetExprKey( GetId(), "learncond", i, key );
		SkillExpr::UpdateExpr( key, learncond_exp[i] );
		GetExprKey( GetId(), "learn", i, key );
		SkillExpr::UpdateExpr( key, learn_exp[i] );
	}

	os >> allow_land >> allow_air >> allow_water >> allow_ride;
	os >> restrict_corpse >> allow_changestatus;
	os >> MarshalContainer(restrict_weapons) >> MarshalContainer(allow_skills);
	os >> effect;

	os >> executetime_exp >> coolingtime_exp >> has_stateattack >> stateattack_exp;
	os >> takeeffect_exp;
	os >> enmity_exp >> requiredsp_exp >> requiredlevel_exp;

	os >> range;

	GetExprKey( GetId(), "executetime", key );
	SkillExpr::UpdateExpr( key, executetime_exp );
	GetExprKey( GetId(), "coolingtime", key );
	SkillExpr::UpdateExpr( key, coolingtime_exp );
	GetExprKey( GetId(), "stateattack", key );
	SkillExpr::UpdateExpr( key, stateattack_exp );
	GetExprKey( GetId(), "takeeffect", key );
	SkillExpr::UpdateExpr( key, takeeffect_exp );
	GetExprKey( GetId(), "enmity", key );
	SkillExpr::UpdateExpr( key, enmity_exp );
	GetExprKey( GetId(), "requiredsp", key );
	SkillExpr::UpdateExpr( key, requiredsp_exp );
	GetExprKey( GetId(), "requiredlevel", key );
	SkillExpr::UpdateExpr( key, requiredlevel_exp );

	GetExprKey( GetId(), "range_radius", key );
	SkillExpr::UpdateExpr( key, range.radius_exp );
	GetExprKey( GetId(), "attack_distance", key );
	SkillExpr::UpdateExpr( key, range.attackdistance_exp );
	GetExprKey( GetId(), "range_angle", key );
	SkillExpr::UpdateExpr( key, range.angle_exp );
	GetExprKey( GetId(), "range_praydistance", key );
	SkillExpr::UpdateExpr( key, range.praydistance_exp );
	GetExprKey( GetId(), "range_effectdistance", key );
	SkillExpr::UpdateExpr( key, range.effectdistance_exp );

	GetExprKey( GetId(), "effect_ratio", key );
	SkillExpr::UpdateExpr( key, effect.effect_raito_exp );
	GetExprKey( GetId(), "effect_parameter", key );
	SkillExpr::UpdateExpr( key, effect.effect_parameter_exp );
	GetExprKey( GetId(), "effect_time", key );
	SkillExpr::UpdateExpr( key, effect.effect_raito_exp );
	GetExprKey( GetId(), "act_ratio", key );
	SkillExpr::UpdateExpr( key, effect.act_raito_exp );

	unsigned int statesize;
	os >> statesize;
	for( i=0; i<statesize; i++ )
	{
		State * p = new State();
		os >> (*p);
		statestub.push_back(p);

		GetExprKey( GetId(), p->stateid, "time", key );
		SkillExpr::UpdateExpr( key, p->time_exp );
		GetExprKey( GetId(), p->stateid, "interrupt", key );
		SkillExpr::UpdateExpr( key, p->interrupt_exp );
		GetExprKey( GetId(), p->stateid, "loop", key );
		SkillExpr::UpdateExpr( key, p->loop_exp );
		GetExprKey( GetId(), p->stateid, "bypass", key );
		SkillExpr::UpdateExpr( key, p->bypass_exp );
		GetExprKey( GetId(), p->stateid, "calculate", key );
		SkillExpr::UpdateExpr( key, p->calculate_exp );

	}
	return os;
}

void SkillStub::Store( std::string filename )
{
	unsigned int size = 0;
	Marshal::OctetsStream os;
	size = GetMap().size();
	os << size;
	for( Map::iterator it = GetMap().begin(); it != GetMap().end(); ++ it )
	{
		os << (*it).first << *((*it).second);
	}

	std::ofstream ofs(filename.c_str());
	size = os.size();
	ofs << size
	ofs.write( (const char *)os.begin(), size );
}

bool SkillStub::Load( std::string filename )
{
	if (filename.length()>0 && access(filename.c_str(), R_OK) == 0)
	{
		std::ifstream ifs(filename.c_str());
		Marshal::OctetsStream os;

		unsigned int size;
		ifs >> size;
		char * p = (char*)malloc(size+4);
		ifs.read( p, size );
		os.replace( p, size );
		free(p);

		for( Map::iterator it=GetMap().begin(); it != GetMap().end(); ++ it )
			delete (*it).second;
		GetMap().clear();

		for( Skill::Map::iterator sit=Skill::GetMap().begin(); sit != Skill::GetMap().end(); ++ sit )
			delete (*sit).second;
		Skill::GetMap().clear();

		os >> size;
		for( unsigned int i=0; i<size; i++ )
		{
			ID id;
			os >> id;
			SkillStub * s = new SkillStub(id);
			os >> (*s);
			new CommonSkill(id);
		}
		return true;
	}

	return false;
}

int  SkillStub::State::GetTime(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "time", key );
	return SkillExpr::intValue(key,skill);
}

bool SkillStub::State::Quit(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "quit", key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::State::Loop(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "loop", key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::State::Bypass(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "bypass", key );
	return SkillExpr::boolValue(key,skill);
}

void SkillStub::State::Calculate(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "calculate", key );
	SkillExpr::Transact(key,skill);
}

bool SkillStub::State::Interrupt(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "interrupt", key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::State::Cancel(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "cancel", key );
	return SkillExpr::boolValue(key,skill);
}
bool SkillStub::State::Skip(Skill * skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), stateid, "skip", key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition1(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 1, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition2(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 2, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition3(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 3, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition4(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 4, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition5(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 5, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition6(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 6, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition7(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 7, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition8(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 8, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition9(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 9, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::LearnCondition10(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learncond", 10, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn1(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 1, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn2(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 2, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn3(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 3, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn4(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 4, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn5(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 5, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn6(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 6, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn7(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 7, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn8(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 8, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn9(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 9, key );
	return SkillExpr::boolValue(key,skill);
}

bool SkillStub::Learn10(Skill* skill) const
{
	std::string key;
	GetExprKey( GetId(), "learn", 10, key );
	return SkillExpr::boolValue(key,skill);
}

int SkillStub::GetExecutetime(Skill *skill) const
{
	std::string key;
	GetExprKey( GetId(), "executetime", key );
	return SkillExpr::intValue(key,skill);
}

int SkillStub::GetCoolingtime(Skill *skill) const
{
	std::string key;
	GetExprKey( GetId(), "coolingtime", key );
	return SkillExpr::intValue(key,skill);
}

bool SkillStub::StateAttack(Skill * skill) const
{
	std::string key;
	GetExprKey( GetId(), "stateattack", key );
	SkillExpr::Transact(key,skill);
	return true;
}

bool SkillStub::TakeEffect(Skill * skill) const
{
	std::string key;
	GetExprKey( GetId(), "takeeffect", key );
	SkillExpr::Transact(key,skill);
	return true;
}

int SkillStub::GetEnmity(Skill *skill) const
{
	std::string key;
	GetExprKey( GetId(), "enmity", key );
	return SkillExpr::intValue(key,skill);
}

int SkillStub::GetRequiredSp(Skill *skill) const
{
	std::string key;
	GetExprKey( GetId(), "requiredsp", key );
	return SkillExpr::intValue(key,skill);
}

int SkillStub::GetRequiredLevel(Skill *skill) const
{
	std::string key;
	GetExprKey( GetId(), "requiredlevel", key );
	return SkillExpr::intValue(key,skill);
}

float SkillStub::GetRadius(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "range_radius", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetAttackdistance(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "range_attackdistance", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetAngle(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "range_angle", key );
	return SkillExpr::floatValue(key,skill);

}

float SkillStub::GetPraydistance(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "range_praydistance", key );
	return SkillExpr::floatValue(key,skill);

}

float SkillStub::GetEffectdistance(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "range_effectdistance", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetEffectRatio(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "effect_ratio", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetEffectParameter(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "effect_parameter", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetEffectTime(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "effect_time", key );
	return SkillExpr::floatValue(key,skill);
}

float SkillStub::GetActRatio(Skill *skill) const
{
	std::string key;
	GetExprKey( skill->GetId(), "act_ratio", key );
	return SkillExpr::floatValue(key,skill);
}


#endif

bool Skill::TakeEffect(PlayerWrapper* player, int arg )
{
	player->SetEnable(true);
	player->SetIntarg(arg);
	double res = LuaSkill::GetInstance()->TakeEffect(this, id) ; 
	res != -0 ? res = true : res = GetStub()->TakeEffect(this);
	return res;
}

bool Skill::UndoEffect(PlayerWrapper* player, int arg)
{
	player->SetEnable(false);
	player->SetIntarg(arg);
	double res = LuaSkill::GetInstance()->TakeEffect(this, id) ; 
	res != -0 ? res = true : res = GetStub()->TakeEffect(this);
	return res;
}

char Skill::GetForceattack()
{ 
	return (pdata?pdata->forceattack:0); 
}

void Skill::SetCharging(int w) 
{ 
	if(pdata->warmuptime<0 || pdata->warmuptime>w)
	{
		pdata->warmuptime = w; 
	}
}

void Skill::SetSection(int s)
{
	if(pdata)
		pdata->section = (unsigned char)s;
}

void Skill::SetLvalue(int v)
{
	if(pdata)
		pdata->lvalue = v;
}

int  Skill::GetLvalue()
{
	return pdata ? pdata->lvalue : 0;
}

unsigned int Skill::GetSection()
{
	if(pdata)
		return pdata->section;
	if(attackmsg)
		return attackmsg->section;
	if(enchantmsg)
		return enchantmsg->section;
	return 0;
}

unsigned int Skill::GetCharging() 
{ 
	return pdata->warmuptime; 
}

int Skill::FirstRun( int & next_interval, int prayspeed )
{
	next_interval = -1;
	int nextindex = NextState(-1);
	SetStateindex(nextindex);
	if( nextindex < 0 )
		return -1;
	//const SkillStub::State * state = stub->GetState(0);
	//Run( state );
	
	r_Calculate(0);
	int time = r_GetTime(0);
	
	pdata->skippable = IsWarmup();

	if(pdata->skippable)
		SetCharging(time);
	else
	{
		prayspeed = GetPlayer()->FirstRunRelease(player->GetCls(), prayspeed);
		time = (int)(time*0.01f*(100 - prayspeed) + 0.01f);
	}

	nextindex = NextState(nextindex);
	if( nextindex >= 0 )
		next_interval = r_GetTime(nextindex); //stub->GetState(nextindex)->GetTime(this);
	else
		time = -1;
	SetNextindex(nextindex);
	return  time;
}

int Skill::Run( int & next_interval )
{
	next_interval = -1;
	int newindex = GetNextindex();
	SetStateindex(newindex);
	ASSERT(newindex < int(stub->GetStateSize()));
	if( newindex < 0 )
		return -1;

	//const SkillStub::State * state = stub->GetState(newindex);
	//Run( state );
	
	r_Calculate(newindex);
	int time = r_GetTime(newindex);

 	pdata->skippable = IsWarmup();
	if(pdata->skippable)
		SetCharging(time);
	
	int nextindex = NextState(newindex);
	if( nextindex >= 0 )
		next_interval = r_GetTime(nextindex); //stub->GetState(nextindex)->GetTime(this);
	else // over
		time = -1;

	SetNextindex(nextindex);
	return time;
}

bool Skill::InvalidState()
{
	return (pdata->stateindex < 0 ||  pdata->stateindex >= (int)stub->GetStateSize());
}

void Skill::SetStateindex(int s) { pdata->stateindex = s; }
int Skill::GetStateindex() { return pdata->stateindex; }

void Skill::SetNextindex(int s) { pdata->nextindex = s; }
int Skill::GetNextindex() { return pdata->nextindex; }

int Skill::NextState( int index )
{
	int statesize = stub->GetStateSize();
	if( index >= statesize )
		return -1;
	if( index < 0 )
		index = -1;
	if( index >=0 && r_Loop(index) )
	{	
		if( r_Quit(index)) 
			return -1;
		else 
			return index;
	}
	else
	{
		while( ++ index < statesize )
		{
			if( r_Quit(index) )
				return -1;
			if( !r_Bypass(index) )
				return index;
		}
	}
	return -1;
}
void Skill::PrepareTalent(PlayerWrapper* player)
{
	t0 = (int)stub->GetTalent0(player);
	t1 = (int)stub->GetTalent1(player);
	t2 = (int)stub->GetTalent2(player);
}




int Skill::GetAttack()        { return player->GetAttack((int)ratio, (int)plus); }
int Skill::GetMagicattack()   { return player->GetMagicattack((int)ratio,(int)plus); }
void Skill::SetGolddamage(int attack)  { magicdamage[0] = (int)(attack * (1.0+player->GetIncgold())); }
void Skill::SetWooddamage(int attack)  { magicdamage[1] = (int)(attack * (1.0+player->GetIncwood())); }
void Skill::SetWaterdamage(int attack) { magicdamage[2] = (int)(attack * (1.0+player->GetIncwater()));}
void Skill::SetFiredamage(int attack)  { magicdamage[3] = (int)(attack * (1.0+player->GetIncfire())); }
void Skill::SetEarthdamage(int attack) { magicdamage[4] = (int)(attack * (1.0+player->GetIncearth()));}

};

