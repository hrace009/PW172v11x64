#ifndef __ELEMENT_SKILL_H
#define __ELEMENT_SKILL_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ELEMENTSKILL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ELEMENTSKILL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ELEMENTSKILL_EXPORTS
#define ELEMENTSKILL_API __declspec(dllexport)
#else
#define ELEMENTSKILL_API __declspec(dllimport)
#endif

#include <vector>
#include <utility>

namespace GNET
{
enum skill_type{
    TYPE_ATTACK   = 1,  // Цч¶Ї№Ґ»ч
    TYPE_BLESS    = 2,  // Цч¶ЇЧЈёЈ
    TYPE_CURSE    = 3,  // Цч¶ЇЧзЦд
    TYPE_SUMMON   = 4,  // ОпЖ·јјДЬ
    TYPE_PASSIVE  = 5,  // ±»¶Ї
    TYPE_ENABLED  = 6,  // ОдЖчёЅјУ
    TYPE_LIVE     = 7,  // Йъ»о
    TYPE_JUMP     = 8,  // ЛІТЖ
	TYPE_PRODUCE  = 9,  // ЙъІъ(»Ґів)
	TYPE_BLESSPET = 10,  // іиОпЧЈёЈ
	TYPE_NEUTRALBLESS = 11,	//ЦРРФЧЈёЈ
};

enum range_type{
	TYPE_POINT = 0,          // µг 
	TYPE_LINE  = 1,          // ПЯ 
	TYPE_SELFSPHERE  = 2,    // ЧФЙнОЄЦРРДµДЗт
	TYPE_TARGETSPHERE = 3,   // Дї±кОЄЦРРДµДЗт
	TYPE_TAPER  = 4,         // ФІЧ¶
	TYPE_SLEF  = 5,          // ЧФЙн
};

enum form{
	FORM_MASK_HIGH	= 0xC0,
	FORM_NORMAL		= 0,	//ЖХНЁРОМ¬
	FORM_CLASS		= 1,	//Ц°Тµ±дЙн
	FORM_BEASTIE	= 2,	//±дРЎ¶ЇОп
};

struct LearnRequirement
{
	int level;		//НжјТј¶±р
	int sp;         //јјДЬµг
	int money;      //ЅрЗ®
	int profession; //Ц°Тµ
	int rank;       //РЮХжј¶±р
	int realm_level;//ѕіЅзµИј¶
};

struct PetRequirement
{
	int  level;		 //іиОпј¶±р
	int  sp;         //ЦчИЛјјДЬµг
	int* list;       //ПЦУРјјДЬБР±н
	int  lsize;      //БР±нґуРЎ
};

struct GoblinRequirement
{
	int  genius[5];	  //РЎѕ«БйјјДЬМмёіµг
	int  profession;  //Ц°Тµ
	int  sp;		  //ЦчИЛФЄЙс
	int  money;		  //ЦчИЛЅрЗ®
	int  level;		  //РЎѕ«БйµИј¶
	int  mp;		  //РЎѕ«Бйµ±З°ДЬБїЙППЮ
};

struct ComboSkillState
{
	enum{ MAX_COMBO_ARG = 3 };
	unsigned int skillid;
	int arg[MAX_COMBO_ARG];
	ComboSkillState():skillid(0)
	{
		memset(arg, 0, sizeof(arg));
	}
};

struct UseRequirement
{
	int mp;            //Д§·Ё
	int ap;            //Е­ЖшЦµ
	int form;          //±дЙнЧґМ¬
	int weapon;        //ОдЖч
	int freepackage;   //°ь№ьАёКЈУаКэДї
	int arrow;         //Ч°±ёјэЦ§КэДї
	int move_env;	//ТЖ¶Ї»·ѕі
	bool is_combat;   //КЗ·сХЅ¶·ЧґМ¬
	int hp;				//µ±З°hp
	int max_hp;			//Чоґуhp
	ComboSkillState combo_state;	//Б¬РшјјКэѕЭ
};

struct GoblinUseRequirement
{
	int mp;			//ДЬБї(ФЄЖш)
	int ap;			//МеБ¦(ДНБ¦)
	int genius[5];	//РЎѕ«БйјјДЬМмёіµг
	int profession; //ЦчИЛЦ°Тµ
	int level;		//РЎѕ«БйµИј¶Ј¬УГУЪјЖЛгДНБ¦ПыєД
	int move_env;	//ЦчИЛµ±З°ТЖ¶Ї»·ѕі 
};

#pragma pack(push, 1)

struct Range
{
	char    type;
};

struct CSkill
{
	void* SkillStub__vftable;
	unsigned int	id;
	int				cls;
	const wchar_t*	name;
	const char*		nativename;
	const char*		icon;
	int				max_level;
	char            type;
	bool			allow_ride;
	short           attr;
	int             rank;
	int             eventflag;
	char            is_senior;
	char			is_inherent;
	char			is_movingcast;
	int             npcdelay;
	int             showorder;
	char            allow_forms;
	int             apcost;
	int             apgain;
	char            doenchant;
	char            dobless;
	int             arrowcost;
	std::vector<std::pair<unsigned int, int> > pre_skills;
	bool            allow_land;
	bool            allow_air;
	bool            allow_water;
	bool			notuse_in_combat;
	int             restrict_corpse;
	bool            restrict_change;
	bool            restrict_attach;
	bool            auto_attack;
	char            time_type;
	char            long_range;
	char			posdouble;
	int				clslimit;
	int				commoncooldown;
	int				commoncooldowntime;
	int				itemcost;
	int				itemcostcount;
	int				combosk_preskill;
	int				combosk_interval;
	int				combosk_nobreak;
	const char*		effect;
	const char*		aerial_effect;
	Range 			range;
	bool 			has_stateattack;
	char 			runes_attr;
	const char*		gfxfilename;
	const char*		gfxhangpoint;
	char  			gfxtarget;
	int 			feature;
	int 			extra_effect;
	int				immune_casting; // ^ffa4a9Во время применения персонаж невосприимчив к наложению негативных эффектов. Умение нельзя отменить."
	std::vector<int> restrict_weapons;
	int				cstub_num; //номер хранилища умений ???
	int				reserve1; //2904 - используется только тут
};

#pragma pack(pop)

class SkillStub;

class ELEMENTSKILL_API SkillStr
{
public:
	virtual const wchar_t* Find(int id) const {  return L""; }
};

class ELEMENTSKILL_API ElementSkill
{
public:
	enum {
		SKILL_PERFORM,
		SKILL_DONE,
	};
	typedef unsigned int ID;
	
	static ID NextSkill(ID id = 0);

	// јјДЬГыіЖ
	virtual const wchar_t* GetName() { return NULL;}
	virtual const char* GetNativeName() { return NULL;}
	// јјДЬАа±р,јыskill_type
	virtual char GetType() const { return 1; }        
	// јјДЬНј±к
	virtual const char* GetIcon() { return NULL; }
	// јјДЬЛµГч
	virtual const wchar_t* GetIntroduction(wchar_t* buf,int len,const SkillStr& table) { return L""; }
	// јјДЬЦ°ТµПЮЦЖ
	virtual int GetCls() const { return -1; }
	// јјДЬАдИґК±јдЈ¬µҐО»єБГл
	virtual int GetCoolingTime() { return 5000; }
	// јјДЬЦґРРК±јдЈ¬µҐО»єБГл
	virtual int GetExecuteTime() { return 1000; }
	// Дї±кАаРНПЮЦЖ, 0:ОЮРиДї±кЈ¬1:РиТЄДї±кЈ¬2:Дї±кЅцПЮУЪК¬Ме, 3:Дї±к±ШРлОЄ№ЦОп, 4:Дї±к±ШРлОЄіиОп 
	virtual int GetTargetType(){return 0;}
	// јјДЬУРР§КН·ЕѕаАл: <-0.001ОЮРиДї±к -0.001-0.001 Д¬ИП№Ґ»чѕаАлЈ¬>0.001 КН·ЕѕаАл
	virtual float GetPrayRange(float range, float prayplus, float, int, int) { return 0; }

	// јјДЬРЮХжј¶±р
	virtual int GetRank() { return 0; }
	// С§П°nј¶јјДЬТЄЗуµДНжјТј¶±р
	virtual int GetRequiredLevel() { return 0;}
	// С§П°nј¶јјДЬРиТЄµДјјДЬµг
	virtual int GetRequiredSp() { return 0;}
	// С§П°nј¶РиТЄµДјјДЬКй
	virtual int GetRequiredBook() { return 0;}
	// С§П°РиТЄЅрЗ®
	virtual int GetRequiredMoney() { return 0;}
	// С§П°РиЗуѕіЅзµИј¶
	virtual int GetRequiredRealmLevel() { return 0; }
	// З°МбјјДЬ

	virtual const std::vector<std::pair<unsigned int, int> >& GetRequiredSkill_nop1() = 0;
	virtual const std::vector<std::pair<unsigned int, int> >& GetRequiredSkill_nop2() = 0;
	virtual const std::vector<std::pair<unsigned int, int> > & GetRequiredSkill() = 0;
	// ПФКѕЛіРт
	virtual int GetShowOrder() { return 0; }
	// ЙиЦГјјДЬј¶±р
	virtual int SetLevel(int) { return 0; } 
	// јјДЬЧоґуј¶±р
	virtual int GetMaxLevel() { return 0; }

	// КЗ·сРоБ¦јјДЬ
	virtual bool IsWarmup() { return false; }
	// К№УГєуКЗ·сЧФ¶Ї№Ґ»ч
	virtual bool IsAutoAttack(){return false;}
	// ЛІ·ўјјДЬ
	virtual bool IsInstant(){return false;}
	// КЗ·сіЦРшјјДЬ
	virtual bool IsDurative() { return false; }

	//162
	virtual bool IsIndependent(void) { return false; }

	// Й±ЙЛ·¶О§µДАаРН
	virtual int  GetRangeType() { return 0; }
	// КН·Е»·ѕіЈєїХЦРЎўµШГжЎўЛ®ЦР
	virtual int  GetCastEnv() { return 0; }
	// »сИЎРЎѕ«БйС§П°єНКН·ЕјјДЬЛщРиМмёіµг
	virtual int* GetRequiredGenius(int idSkill) { return NULL; }

	// Р§№ыОДјюГы
	virtual const char* GetEffect() { return NULL;}
	virtual const char* GetElseEffect() { return NULL;}

	// К№УГРиТЄMP
	virtual int GetMpCost(){return 1;}

	// К№УГРиТЄAP
	virtual int GetApCost(){return 0;}

	// 162
	virtual int GetRealApCost(int) { return 0; }

	// јэЦ§ПыєД
	virtual int GetArrowCost(){return 0;}

	// ОдЖчМхјюЕР¶П
	virtual bool ValidWeapon(int w) const { return true; }
	// 0, іЙ№¦Ј»1Ј¬ОдЖчІ»ЖҐЕдЈ»2, mpІ»ЧгЈ»3Ј¬О»ЦГМхјюІ»ВъЧгЈ»4Ј¬ЖпіЛМхјюІ»ВъЧгЈ»5Ј¬ґнОуID, 6Ј¬ОґСЎФсДї±к
	int Condition(UseRequirement& info);

	virtual bool IsAllowLand(){ return true; }
	virtual bool IsAllowWater(){ return true; }
	virtual bool IsAllowAir(){ return true; }
	virtual bool GetNotuseInCombat(){ return false; }
	//КЗ·сТЖ¶ЇК©·Ё
	virtual bool IsMovingSkill() { return false; }
	// јјДЬДЬ·сФЪµ±З°±дЙнЧґМ¬ПВК№УГ
	bool IsValidForm(char form);


	virtual char GetAllowForms() { return 0; }
	virtual bool Interrupt() { return true; } //++


	int GetAbilityPercent();


	virtual int GetReserve1() { return 0; }
	virtual int GetReserve2(int) { return 0; }


	// »сИЎПа¶ФУ¦µДіхј¶јјДЬ
	virtual std::vector<std::pair<unsigned int, int> > GetJunior() { return std::vector<std::pair<unsigned int, int> >(); };

	// »сИЎРЎѕ«БйјјДЬЦ°ТµПЮЦЖ
	virtual int GetClsLimit() { return 0; }
	
	//»сИЎ№«№ІАдИґmask bit0-4 јјДЬАдИґ0-4 bit5-9 ОпЖ·АдИґ0-4
	virtual int GetCommonCoolDown() { return 0; }

	//»сИЎ№«№ІАдИґК±јдЈ¬µҐО»єБГл
	virtual int GetCommonCoolDownTime() { return 0; }

	//»сИЎТчіЄЛщРиОпЖ·
	virtual int GetItemCost() { return 0; }

	//162
	virtual int GetCDLimit(void) { return 0; }

	//»сИЎБ¬РшјјК©·ЕЗ°Мб
	virtual int GetComboSkPreSkill(){ return 0; }

	//јмІйК©·ЕК±hpПЮЦЖ
	virtual bool CheckHpCondition(int hp, int max_hp) { return true; }

	//јмІйБ¬Ршјј¶оНвМхјю
	virtual bool CheckComboSkExtraCondition(){ return true; } 
	
	//162
	virtual float GetFixPointCallRadius(void) { return 0.0f; }

	//162
	virtual int GetFixPointCallSummonPetMouseIconID(void) { return 0; }

	//162
	virtual int Reserve3(void) { return 0; }

	//162
	virtual int GetFeature(void) { return 0; }

	//162
	virtual void SetRuneLevel(int) {}
	//162
	virtual void SetDefForm(int) {}
	//162
	virtual int GetCoolDownLimit(void) { return 0; }
	//172
	virtual void SetImmuneCasting(int) {}
	//162
	virtual int GetCostShieldEnergy(void) { return 0; }

	// 0:іЙ№¦            1:SPІ»Чг            2:ј¶±рІ»№»
	// 3:Въј¶            4:ЦЦЧеІ»ЖҐЕд        5:ґнОуID
	// 6:ЅрЗ®І»Чг        7:РЮХжј¶±рІ»ВъЧг    8:Г»УРјјДЬКй
	// 9:Г»УРЗ°МбјјДЬ    10:КмБ·¶ИІ»Чг       11:ТСѕ­С§µЅБЛёЯј¶јјДЬ
	// 12:ѕіЅзМхјюІ»ВъЧг
	static int LearnCondition(ID id, LearnRequirement& info, int level ); 

	// 0:іЙ№¦            1:ОдЖчІ»ЖҐЕд        2:mpІ»Чг
	// 3:О»ЦГМхјюІ»ВъЧг  4:ЖпіЛМхјюІ»ВъЧг    5:ґнОуID
	// 6:ОґСЎФсДї±к      7:±дЙнЧґМ¬ґнОу      8:Е­ЖшЦµІ»Чг
	// 9:јэЦ§І»Чг        10:°ь№ьАёГ»УРКЈУаО»ЦГ 11: І»ДЬФЪХЅ¶·ЦРК№УГ
	// 12:HPМхјюІ»ВъЧг   13:Б¬РшјјЗ°МбІ»ВъЧг
	static int Condition(ID id, UseRequirement& performer, int level );

	// 0:іЙ№¦            1:ЦчИЛSPІ»Чг        2:ј¶±рІ»№»
	// 3:Въј¶            9:З°МбјјДЬј¶±рІ»№»  5:ґнОуID
	static int PetLearn(ID id, PetRequirement& info, int level); 

	// 0:іЙ№¦            1:ЦчИЛSPІ»Чг        2:јјДЬМмёіµгІ»Чг
	// 3:Въј¶            4:јјДЬёцКэПЮЦЖ		 5:ґнОуID
	// 6:ЅрЗ®І»Чг		 7:·ЗРЎѕ«БйјјДЬ		 8:Г»УРјјДЬКй
	// 9:µИј¶І»Чг       10:ДЬБїЙППЮІ»Чг     11:Ц°ТµІ»ЖҐЕд
    // 12:ДЬБїЙППЮІ»ЧгЈ¬ЗТЦ°ТµІ»ЖҐЕд
	static int GoblinLearn(ID id, GoblinRequirement& info, int level); 

	// 0:іЙ№¦            1:Ц°ТµІ»ЖҐЕд        2:mpІ»Чг
	// 3:APІ»Чг			 4:МмёіµгІ»Чг		 5:ґнОуID
	// 6:ОґСЎФсДї±к      7:·ЗРЎѕ«БйјјДЬ      8:ТЖ¶Ї»·ѕіІ»ВъЧг
	static int GoblinCondition(ID id, GoblinUseRequirement& info, int level );

	//»сИЎЦ°ТµМмЙъјјДЬ
	static const std::vector<ID>& GetInherentSkills(int cls);

	//»сИЎј¤»оµДБ¬РшјјБР±н
	static void GetComboSkActivated(const ComboSkillState & combo_state, std::vector<std::pair<ID, int> >& list);
	//КЗ·сТЖ¶ЇК©·Ё
	static bool IsMovingSkill(ID id);

	static char GetType(ID id);  
	static const char* GetIcon(ID id);
	static const wchar_t* GetName(ID id);
	static const char* GetNativeName(ID id);
	static const char* GetEffect(ID id);
	static const char* GetElseEffect(ID id);
	static const wchar_t* GetIntroduction(ID id, int level, wchar_t* buf, unsigned int len, const SkillStr& table);
	static int GetRequiredLevel(ID id, int level);
	static int GetRequiredSp(ID id, int level);
	static int GetRequiredBook(ID id, int level);
	static int GetRequiredMoney(ID id, int level);
	static int GetRequiredRealmLevel(ID id, int level);
	static bool IsValidForm(ID id, char form);
	static int GetExecuteTime(ID id, int level);
	static int GetAbilityPercent(ID id);
	static std::vector<std::pair<unsigned int, int> > GetJunior(ID id);
	static int GetCommonCoolDown(ID id);
	static int GetCommonCoolDownTime(ID id);
	static int GetItemCost(ID id);
	
	static bool IsGoblinSkill(ID id);
	static int GetComboSkPreSkill(ID id);
	
	//ЦчЅЗјјДЬКмБ·¶И  <0Г»УРС§»бґЛјјДЬ >=0 КмБ·¶И
	static int GetAbility(ID id); 
	static int SetAbility(ID id, int ability);
	static int SetLevel(ID id, int level);
	static int GetLevel(ID id);
	static bool IsOverridden(ID id);
	static int GetMaxAbility(ID id, int level);

	static int GetSkillRuneAttr(int); // glyph attr

	static void LoadSkillData(void * data);

	static ElementSkill* Create(ID id, int level);
	void Destroy();

	static int GetVersion();
	
	//
	// іхКј»ЇјјДЬДЪІїѕІМ¬КэѕЭЈ¬ФЪК№УГївЦ®З°µчУГЈЎЈЎЈЎ
	//
	static void InitStaticData();

	static int GetCoolingTime(ID id, int level);
	static float GetPraydistance(ID id, int level);
	static float GetMpcost(ID id, int level);
	static int GetCoolDownLimit(ID id, int level);
	static int GetCostShieldEnergy(ID id, int level);
	static int GetCoolingTime(ID id, int level, int defform);

public:

	CSkill* skill;

};

class ELEMENTSKILL_API VisibleState
{
public:
	virtual const int GetID() const { return 0; }
	virtual const wchar_t* GetName() const {  return NULL; }
	virtual const char* GetHH() const { return NULL; }
	virtual const char* GetEffect() const {  return NULL; }
	static const VisibleState* Query(int profession, int id);
};

class ELEMENTSKILL_API TeamState
{
public:
	virtual const int GetID() const { return 0; }
	virtual const wchar_t* GetName() const {  return NULL; }
	virtual const char* GetIcon() const { return NULL; }
	static const TeamState* Query(int id);
};

}

#endif
