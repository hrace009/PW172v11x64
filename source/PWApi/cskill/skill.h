#ifndef __SKILL_SKILL_H
#define __SKILL_SKILL_H

#pragma warning(disable:4786)
#include "hash_stl.h"
#include "gnstring.h"
#include <vector>
#include "playerwrapper.h"
#include "skillwrapper.h"
#include "ElementSkill.h"
#include <map>
#include <vector>
#include <unordered_map>

#pragma pack(1)

namespace GNET
{

enum // Í¬gs/playertemplate.h
{
	USER_CLASS_SWORDSMAN,       //WR
	USER_CLASS_MAGE,            //MG
	USER_CLASS_NEC,             //WB
	USER_CLASS_HAG,             //WF
	USER_CLASS_ORGE,            //PSY
	USER_CLASS_ASN,             //MC
	USER_CLASS_ARCHER,          //EA
	USER_CLASS_ANGEL,           //EP
	USER_CLASS_BLADE,           //SK
	USER_CLASS_GENIE,           //MS
	USER_CLASS_SHADOW,          //RT
	USER_CLASS_FAIRY,           //TM
	USER_CLASS_SHOOTER,           //ATR
	USER_CLASS_PALADIN,           //PAL
	USER_CLASS_COUNT
};

typedef GnetString wsstream;

class Skill;

class Range
{
public:
    char    type;   // 0µг 1ПЯ 2ЧФЙнЗт 3Дї±кЗт 4ФІЧ¶РО 5ЧФЙн
public:
    Range(char t=1) : type(t) { }
    Range& operator = (const Range& rhs)
    {
        return *this;
    }
    bool IsPoint() const { return 0 == type; }
    bool IsLine() const { return 1 == type; }
    bool IsSelfBall() const { return 2 == type; } 
    bool IsTargetBall() const { return 3 == type; }
    bool IsSector() const { return 4 == type; }
    bool IsSelf() const { return 5 == type; }
	bool NoTarget() const { return 2 == type || 5 == type; }
};

class SkillStub
{
public:
	typedef unsigned int ID;
	enum { MIN_LEVEL = 1, MAX_LEVEL = 10 };

public:
	// base info
	ID				id;					// ОЁТ»КэЧЦ±кК¶
	int				cls;				// Ц°Тµ
	const wchar_t*  name;               // јјДЬГыЧЦ
	const char*		nativename;			// јјДЬГы
	const char*		icon;				// јјДЬНј±к
	int				max_level;			// јјДЬЧоґуј¶±р
	char            type;               // јјДЬАа±р 1Цч¶Ї№Ґ»ч 2Цч¶ЇёЁЦъ 3Цч¶ЇХЩ»Ѕ 4±»¶Ї 5ј¤»о

	// execute condition
	bool			allow_ride;			// ЖпіЛУРР§
    short           attr;               // ЦчјјДЬКфРФ, 1ОпАнЎў2ЅрЎў3ДѕЎў4Л®Ўў5»рЎў6НБ БщСЎТ» Д¬ИПЈЁОпАнЈ©
    int             rank;               // РЮХжј¶±р
	int             eventflag;
	char            is_senior;
	bool			is_inherent;		//МмЙъјјДЬЈ¬І»УГС§ѕНДЬУГ
	bool			is_movingcast;		//ТЖ¶ЇК©·Ё
	int             npcdelay;
	int             showorder;
	char            allow_forms;
	int             apcost;
	int             apgain;
	char            doenchant;
	char            dobless;
	int             arrowcost;

	int				d_reserve1;
	int				d_reserve2;
	int				d_reserve3;

	std::vector<std::pair<unsigned int,int> > pre_skills;

    // execute condition
    bool            allow_land;             // ВЅµШУРР§
    bool            allow_air;              // їХЦРУРР§
    bool            allow_water;            // Л®ЦРУРР§
	bool			notuse_in_combat;	//ХЅ¶·ЧґМ¬І»їЙУГ
	int             restrict_corpse;        // Ц»¶ФК¬МеУРР§
    bool            restrict_change;        // КЗ·с±ШРл±дЙнєу
    bool            restrict_attach;        // КЗ·с±ШРлёЅМеєу
	bool            auto_attack;            // К№УГєуКЗ·сЧФ¶Ї№Ґ»ч
	char            time_type;              // ЛІ·ўјјДЬ
	char            long_range;
	char			posdouble;				// їХµШСЎФс
	int				clslimit;				// Ц°ТµПЮЦЖ
	
	int				commoncooldown;					//№«№ІАдИґmask bit0-4 јјДЬАдИґ0-4 bit5-9 ОпЖ·АдИґ0-4
	int				commoncooldowntime;			//АдИґК±јдЈ¬µҐО»єБГл
	
	int				itemcost;		//ТчіЄК±ЛщРиОпЖ· >0УРР§
	//Б¬Ршјј
	int				combosk_preskill;
	int				combosk_interval;
	int				combosk_nobreak;

	int				d_reserve4;

	const char*		effect;
	const char*		aerial_effect;

	Range			range;
	bool			has_stateattack;
	bool			b_reserve1;

	void*			o_reserve1;
	void*			o_reserve2;

	char			reserve[9];

	std::vector<int> restrict_weapons;  

	typedef std::unordered_map<ID, SkillStub*, _hash_function> Map;
	static Map& GetMap();

	typedef std::vector<ID> ID_LIST;
	static ID_LIST & GetInherentSkillList(int cls);

	typedef std::map<ID, ID_LIST> COMBOSK_MAP;
	static COMBOSK_MAP & GetComboSkMap();

protected:
	SkillStub(ID i) : id(i), is_inherent(false),is_movingcast(false), itemcost(0), combosk_preskill(0), combosk_interval(0),combosk_nobreak(0)
	{ 
		if(!GetStub(id)) 
			GetMap().insert(Map::value_type(id, this)); 
	}
	
	~SkillStub();

public:

	static const SkillStub *GetStub(ID i)
	{
		Map::iterator it = GetMap().find(i);
		return it == GetMap().end() ? NULL : it->second;
	}

	static void InitStaticData()
	{
		Map & m = GetMap();
		for(Map::iterator it = m.begin(); it != m.end(); ++it)
		{
			SkillStub & sk = *(it->second);
			if(sk.is_inherent) GetInherentSkillList(sk.cls).push_back(sk.id);
			if(sk.combosk_preskill) GetComboSkMap()[sk.combosk_preskill].push_back(sk.id);
		}
	}

	static ID_LIST & GetPostComboSkill(ID id)
	{
		static ID_LIST null_list;
		COMBOSK_MAP & m = GetComboSkMap();
		COMBOSK_MAP::iterator it = m.find(id);
		if(it == m.end()) return null_list;
		return it->second;
	}

	ID GetId() const { return id; }
	int GetCls() const { return cls; }
	const wchar_t* GetName() const { return name; }
	const char* GetIcon() const { return icon; }
	int GetMaxLevel() const { return max_level; }
	const Range & GetRange() const { return range; }
	int GetItemCost() { return itemcost; }
	bool IsMovingSkill() const { return is_movingcast; }

	char GetType() const { return type; }
	
	virtual int GetCoolingtime(Skill *skill) const = 0;
	virtual int GetRequiredSp(Skill *skill) const { return 0; }
	virtual int GetRequiredLevel(Skill *skill) const { return 0; }
	virtual int GetMaxAbility(Skill* skill) const { return 0; }
	virtual int GetRequiredItem(Skill* skill) const { return 0; }
	virtual int GetRequiredMoney(Skill* skill) const { return 0; }
	virtual int GetRequiredRealmLevel(Skill* skill) const { return 0; }
	virtual float GetPraydistance(Skill *skill) const = 0;
	virtual float GetMpcost(Skill* skill) const{ return 0;}
	virtual int GetExecutetime(Skill *skill) const { return 1000; }
	virtual bool CheckHpCondition(int hp, int max_hp) const{ return true; }
	virtual bool CheckComboSkExtraCondition(Skill* skill) const { return true; }
	virtual int GetIntroduction(Skill*,wchar_t*,int,wchar_t*) const {return 0;}
	
	bool ValidWeapon(int weapon) const
	{
		unsigned int i;
		for(i=0; i<restrict_weapons.size(); i++ )
		{
			if( weapon == restrict_weapons[i] )
				return true;
		}   
		if( i>0 && i >= restrict_weapons.size() )
			return false;
		return true;
	}
};

class Skill : public ElementSkill
{
protected:
	const SkillStub * stub;
	PlayerWrapper player;

	ID id;
	unsigned int level;

	Skill(ID i, const SkillStub* s) : stub(s), id(i) 
	{	
	}
	
	virtual ~Skill() { }
public:

	static Skill* Create(ID id, int n)
	{
		const SkillStub * stub = SkillStub::GetStub(id);
		if(!stub)
			return NULL;
		Skill* skill = new Skill(id, stub);
		int max = skill->GetMaxLevel();
		if(n>max)
			skill->SetLevel(max);
		else
			skill->SetLevel(n);
		return skill;
	}

	void Destroy() 
	{ 
		delete this; 
	}


	bool ReSetStub() { 
		stub = SkillStub::GetStub(id); 
		return NULL != stub; 
	}
	
	const SkillStub * GetStub() const {	return stub; }
	PlayerWrapper * GetPlayer()  { return &player; }

	ID GetId() const { return id; }
	int SetLevel(int l) 
	{
		int tmp = level;
		level = l; 
		return tmp;
	}
	int GetLevel() const { return level; }
	void SetPerform(int p) { }
	int GetPerform() { return 0; }

	char GetType() const { return stub->type; }
	const wchar_t* GetName() { return stub->GetName();}

	float GetPrayRange(float range, float prayplus) {
		player.SetRange(range);
		player.SetPrayrangeplus(prayplus);
		if(stub->type==TYPE_ATTACK || stub->type==TYPE_CURSE)
		{
			if(stub->auto_attack)
			{
				float r = 0.3f * stub->GetPraydistance(this);
				if(r>=1.0)
					return stub->GetPraydistance(this) - 1.0f;
				else
					return (float)0.7*stub->GetPraydistance(this);
			}
			else
				return stub->GetPraydistance(this);
		}
		if(stub->type==TYPE_JUMP)
			return stub->GetPraydistance(this); 
		if(stub->GetRange().NoTarget())
			return -1;
		else
			return stub->GetPraydistance(this); 
	}

	const char* GetIcon() { return stub->GetIcon(); }
	int GetRangeType() { return stub->GetRange().type; }
	int GetCls() const { return stub->GetCls(); }
	int GetCoolingTime() { return stub->GetCoolingtime(this); }
	int GetArrowCost () { return stub->arrowcost; }
	int GetMaxLevel()  { return stub->GetMaxLevel(); }
	int GetShowOrder() { return stub->showorder; }
	int GetRand() { return 100; }
	int GetRank() { return stub->rank; }
	int GetMpCost() { return (int)stub->GetMpcost(this); }
	int GetApCost() { return stub->apcost; }
	int GetAbility() { return SkillWrapper::Instance()->GetAbility(id);}

	char GetAllowForms() { return stub->allow_forms; }
	int GetMaxability() { return stub->GetMaxAbility(this); }
	int GetRequiredSp() { return stub->GetRequiredSp(this); }
	int GetRequiredLevel() { return  stub->GetRequiredLevel(this); } 
	int GetRequiredBook() { return stub->GetRequiredItem(this); }
	int GetRequiredMoney() { return  stub->GetRequiredMoney(this); }
	int GetRequiredRealmLevel() { return stub->GetRequiredRealmLevel(this); }
	const std::vector<std::pair<unsigned int, int> > & GetRequiredSkill() { return stub->pre_skills; }
	std::vector<std::pair<unsigned int, int> > GetJunior() { return stub->is_senior ? stub->pre_skills : std::vector<std::pair<unsigned int, int> >(); }
	int GetClsLimit() { return stub->clslimit; }
	int GetCommonCoolDown() { return stub->commoncooldown; }
	int GetCommonCoolDownTime() { return stub->commoncooldowntime; }
	int GetItemCost() { return stub->itemcost; }
	int GetComboSkPreSkill(){ return stub->combosk_preskill; }
	int GetComboSkInterval(){ return stub->combosk_interval; }
		//јмІйК©·ЕК±hpПЮЦЖ
	bool CheckHpCondition(int hp, int max_hp) { return stub->CheckHpCondition(hp, max_hp); }
	bool CheckComboSkExtraCondition() { return stub->CheckComboSkExtraCondition(this); }

	bool IsWarmup()     { return stub->time_type==3; }
	bool IsInstant()    { return stub->time_type==1; }
	bool IsDurative()   { return stub->time_type==2; }
	bool IsAutoAttack() { return stub->auto_attack; }
	
	bool IsAllowLand()  { return stub->allow_land; }
	bool IsAllowWater() { return stub->allow_water; }
	bool IsAllowAir()   { return stub->allow_air; }
	bool GetNotuseInCombat() { return stub->notuse_in_combat; }
	bool IsMovingSkill() { return stub->IsMovingSkill(); }
 
	int GetTargetType()
	{
		if(stub->restrict_corpse==1)
			return 2;
		if(stub->restrict_corpse==2)
			return 3;
		if(stub->type==TYPE_ATTACK || stub->type==TYPE_CURSE)
			return 1;
		if(stub->type==TYPE_BLESSPET)
			return 4;
		if(stub->GetRange().NoTarget())
			return 0;
		return 1;
	}
	
	int GetCastEnv()
	{
		int iRet = 0;
		if(stub->allow_land)
			iRet += 1;
		if(stub->allow_air)
			iRet += 2;
		if(stub->allow_water)
			iRet += 4;

		return iRet;
	}
	
	int* GetRequiredGenius(int idSkill)
	{
		int* iGenius = new int[5];
		if(!iGenius || stub->cls != 258)
			return NULL;
			
		//  iReqLevelОЄ7О»ХыКэЈ¬ЧоєуБЅО»ОЄµИј¶Ј¬З°5О»ОЄМмёіµгРиЗуЈ¬ЧоёЯО»ОЄЅр
		int iLevelReq = GetRequiredLevel()/100;

		for(int i=0;i<5;i++)
		{
			iGenius[4-i] = iLevelReq%10;
			iLevelReq /= 10;
		}

		return iGenius;
	}

	int GetExecuteTime()
	{
		return stub->GetExecutetime(this);
	}

	const wchar_t* GetIntroduction(wchar_t* buf,int len,const SkillStr& table)
	{
		int n = stub->GetIntroduction(this,buf,len,table.Find(stub->id*10+1)); 
		if(n<0)
			return L"";
		return buf;
	}

	int GetAbilityPercent()
	{
		int now = SkillWrapper::Instance()->GetAbility(id);
		int max = 0;
		if(level>0)
			max = GetMaxability();
		int min = 0;
		if(level>1)
		{
			SetLevel(level-1);
			min = GetMaxability();
			SetLevel(level);
		}
		if(max==min)
			return 100;
		return 100*(now-min)/(max-min);
	}

	bool ValidWeapon(int w) const { return stub->ValidWeapon(w); }
	const char* GetEffect() { return stub->effect;}
	const char* GetElseEffect() { return stub->aerial_effect;}
	const char* GetNativeName() { return stub->nativename;}
};

class VisibleStateImp : public VisibleState
{
	int id;
	const wchar_t*	name;
	const char* effect;
	const char* hh;
	typedef std::unordered_map<int, const VisibleState*, _hash_function> Map;
	static Map stubmap;
public:
	VisibleStateImp(int i, const wchar_t* n, const char* e, const char* h):id(i), name(n), effect(e), hh(h)
	{
		stubmap.insert(Map::value_type(id, this));  
	}
	static const VisibleState* Query(int prof, int id);
	const int GetID() const { return id; }
	const wchar_t* GetName() const {  return name; }
	const char* GetHH() const { return hh; }
	const char* GetEffect() const {  return effect; }
};

class TeamStateImp : public TeamState
{
	int id;
	const wchar_t* name;
	const char*   icon;
	typedef std::unordered_map<int, const TeamState*, _hash_function> Map;
	static Map stubmap;
public:
	TeamStateImp(int i, const wchar_t* n, const char* c):id(i), name(n), icon(c)
	{
		stubmap.insert(Map::value_type(id, this)); 
	}
	static const TeamState* Query(int id);
	const int GetID() const { return id; }
	const wchar_t* GetName() const {  return name; }
	const char* GetIcon() const { return icon; }
};

};
#pragma pack()

#endif

