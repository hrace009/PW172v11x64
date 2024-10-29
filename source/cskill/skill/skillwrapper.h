#ifndef __SKILL_SKILLWRAPPER_H
#define __SKILL_SKILLWRAPPER_H

#include <map>
#include <vector>
#include <list>

#include "common/types.h"
#include "common/base_wrapper.h"
#include "obj_interface.h"

namespace SKILL
{
#pragma pack(1)
	struct Data
	{
		unsigned int id;

		char	forceattack;    // ����������Ƿ�ǿ�ƹ���
		bool	skippable;      // ������������ǰ״̬�Ƿ����ǰ����
		int	stateindex;     // ��ǰ״̬ID
		int	nextindex;      // �¸�״̬ID
		int	warmuptime;     // ����ʱ��
		unsigned char section; // ���ܶ���
		int		lvalue;		// �߻�����ʱ������state�䴫��״̬ʱʹ��
		Data(unsigned int i) : id(i),forceattack(0),skippable(false),stateindex(-1),nextindex(-1),warmuptime(-1),section(0),lvalue(0)
		{ 
		}
	};
	struct elf_requirement
	{
		short elf_level;
		short str;
		short agi;
		short vit;
		short eng;
		short genius[5];
	};
#pragma pack()

}

namespace GNET
{
enum error_code{
	SKILL_SUCCESS = 0,
	SKILL_INVALIDID = 1,
	SKILL_WRONGPOSITION = 2,
	SKILL_OUTOFRANGE = 3,
	SKILL_WRONGWEAPON = 4,
	SKILL_UNUSABLE = 5,
};

enum WeaponClass {
	WEAPONCLASS_SWORD    = 1,
	WEAPONCLASS_SPEAR    = 5,
	WEAPONCLASS_AXE      = 9,
	WEAPONCLASS_BOW      = 13,
	WEAPONCLASS_BOXING   = 182,
	WEAPONCLASS_WAND	 = 292,
	WEAPONCLASS_DAGGER	 = 23749,
	WEAPONCLASS_TALISMAN = 25333,
	WEAPONCLASS_SCIMITAR = 44878,
	WEAPONCLASS_SCYTHE	 = 44879,
	WEAPONCLASS_SWORDSHIELD = 59830, // Paladino
	WEAPONCLASS_FIREARM	 = 59831, // Atiradora
	WEAPONCLASS_CUDGEL	 = 69843, // Andarilho
	WEAPONCLASS_FEATHER  = 65535
};

enum CashResurrectBuff
{
    GIANT,
    BLESSMAGIC,
    STONESKIN,
    INCRESIST,
    INCHP,
    IRONSHIELD,

    BUFF_COUNT,
};

enum MAIN
{
    MAX_MULTICOOLDOWN_SKILL = 4,
	MAX_ABILITY_SKILL = 16,
};

#define IS_RANGE_WEAPON(wt)	(wt == WEAPONCLASS_BOW || wt == WEAPONCLASS_WAND || wt ==  WEAPONCLASS_TALISMAN || wt == WEAPONCLASS_SCYTHE || wt == WEAPONCLASS_FIREARM)

class Skill;
class SkillWrapper
{
public:
	typedef unsigned int	ID;


protected:
	struct PersistentData
	{
		int 	ability;    // ������
		int		level;      // ����
		char	overridden; // ���߼����ܸ���

		PersistentData(int __t = 0, int __l = 1) : ability(__t), level(__l), overridden(0){ }
		int GetLevel() const { return level; }
	};

	struct DynamicPray
	{
		int   speed;
		int	  times;	
	};

	typedef std::unordered_map<ID,PersistentData>	StorageMap;
	typedef std::unordered_map<ID,DynamicPray> DynPrayMap;

	StorageMap	   map;
	StorageMap	   dyn_map;		//��̬����
	StorageMap	glyph_map;

	DynPrayMap	dynpray_map; //��̬��������	

	int prayspeed;  
	
	struct 
	{
		ID id;						//ид навыка оружия 
		int level;					//лвл навыка оружия
	}	as[MAX_ABILITY_SKILL];		//массив навыков
	
	/*
	ID  asid;                      // �����ID
	int aslevel;                   // ����ܼ���
	ID  asid2;                      // �����ID
	int aslevel2;                   // ����ܼ���  
	ID  asid3;                      // �����ID
	int aslevel3;                   // ����ܼ��� 
	*/
	
	float  skillinc[MAGIC_CLASS];  // 0�� 1ľ 2ˮ 3�� 4��
	int immune_buff_debuff;		//����ֵ, 0 ������ >=1 ��������״̬,lgc
	int interrupt_prob;			//������ʱ���ܵĶ����жϸ���
	int ignore_interrupt;		// ���Ա�����ʱ�ж�
	int cd_adjust;				// cd���� ����
	int cd_adjust_count;		// cd��������
	float pray_distance_adjust;	// �����������(��)

	struct ComboSkill
	{
		enum { MAX_COMBO_ARG = 3, TOLERANCE = 2};
		enum {
			CBREAK_ALL,				//���м��ܶ����жϵ�ǰ�ü�׼��
			CBREAK_IGNORE_NORMAL,	//ֻ��ǰ�ü��ܲ����жϵ�ǰ�ü�׼��
			CBREAK_IGNORE			//�޷��жϵ�ǰ�ü�׼��
		};

		ID  skillid;
		int timestamp;
		int breaktype;
		int expire;
		int arg[MAX_COMBO_ARG];
		bool Condition(ID id, int interval, int now)
		{
			return id == skillid && (timestamp + interval + TOLERANCE >= now);
		}
		void SetState(ID s, int st, int type, int ex) 
		{ 
			skillid = s; timestamp = st; breaktype = type; expire = ex;
		}
		void Clear()
		{
			skillid = timestamp = breaktype = expire = 0;
			memset(arg,0,sizeof(arg));
		}
		bool Break(int now, bool sflag)
		{
			if(skillid == 0 || breaktype == CBREAK_ALL) 
				return true;
			if(timestamp + expire <= now)
				return true;
			if(sflag && breaktype == CBREAK_IGNORE_NORMAL)
				return true;
			return false;
		}
		int	 GetArg(int i) { return i < MAX_COMBO_ARG ? arg[i] : 0;}
		bool SetArg(int i,int v) { if(i >= MAX_COMBO_ARG) return false; arg[i] = v; return true;}
		
		void Swap(ComboSkill& cs) 
		{ 
			std::swap(skillid,cs.skillid); 
			std::swap(timestamp,cs.timestamp); 
			std::swap(breaktype,cs.breaktype);
			std::swap(expire,cs.expire);
			for(int i = 0 ; i < MAX_COMBO_ARG; ++ i) std::swap(arg[i],cs.arg[i]);
		}
		void Save( archive & ar )
		{
			ar << skillid << timestamp << breaktype << expire;
			for(int i = 0 ; i < MAX_COMBO_ARG; ++ i) ar << arg[i];
		}
		void Load( archive & ar )
		{
			ar >> skillid >> timestamp >> breaktype >> expire;
			for(int i = 0 ; i < MAX_COMBO_ARG; ++ i) ar >> arg[i];
		}

	}combo_state;
	
	
	struct BlackWhiteBall
	{
		enum
		{
			BWB_BLACK = 1,
			BWB_WHITE = 5,
			BWB_VALUE_MAX = 15,
			BWB_COUNT_MAX = 3,
		};
		int UpdateVstate(int& oldv);
		bool Add(int type)	
		{
			if(type != BWB_BLACK && type != BWB_WHITE) return false;
			balls = (balls*10)%1000 + type;
			return true;
		}
		void Flip()
		{
			int ba[BWB_COUNT_MAX] = { balls%10,(balls%100)/10,balls/100 };
			for(int i = 0; i < BWB_COUNT_MAX; ++i)
			{
				switch(ba[i])
				{
					case BWB_BLACK:
						ba[i] = BWB_WHITE;	
						break;
					case BWB_WHITE:
						ba[i] = BWB_BLACK;
						break;
					default:
						ba[i] = 0;
						break;
				}
			}
			balls = ba[2]*100 + ba[1]*10 + ba[0];
		}
		int GetIndex() const	{ return balls/100+(balls%100)/10+(balls%10);	}

		void Swap(BlackWhiteBall& bw) 
		{ 
			std::swap(balls,bw.balls); 
			std::swap(vstate,bw.vstate); 
		}
		void Save( archive & ar )
		{
			ar << balls << vstate;
		}
		void Load( archive & ar )
		{
			ar >> balls >> vstate;
		}

		int balls; 
		int vstate;
	}black_white_ball;

private:
	int GetDynPrayspeed(ID id)
	{
		DynPrayMap::iterator iter = dynpray_map.find(id);
		int speed = 0;
		if(iter != dynpray_map.end())
		{
			speed = iter->second.speed;
			if(--iter->second.times <= 0) dynpray_map.erase(iter);
		}

		return speed;		
	}

public:
	SkillWrapper();

	// ������� 1.����������2.����ף����3.�������䣬4.�ٻ���5.������6.����, 7.���8.˲��, 9.����
	static char GetType(ID id); 	
	// ���ܹ�����Χ��0�� 1�� 2������ 3Ŀ���� 4Բ׶�� 5����
	static char RangeType(ID id);
	static bool Initialize();
	static bool IsInstant(ID id);		//�Ƿ�˲��
	static bool IsPosSkill(ID id);		//�Ƿ�˲��
	static bool IsMovingSkill(ID id);	//�Ƿ��ƶ�����
	
	int Learn( ID id, object_interface player );	// �����µļ��𣬴��󷵻�-1
	int Learn( ID id, object_interface player, int level );
	int Push( ID id, object_interface player, int level );
	void DoubleCleaner(int rank);
	int Remove(ID id);   // 0 �ɹ��� 1 δ�ҵ��� 2 ����ɾ��
	void GodEvilConvert(std::unordered_map<int,int>& convert_table, object_interface player, int weapon_class, int form, int worldtag);	//��ħת��
	void ActivateDynSkill(ID id, int counter);
	void DeactivateDynSkill(ID id, int counter);
	int GetDynSkillCounter(ID id);

	int Condition( ID id, object_interface player, const XID * target, int size ); // ���� error_code

	// ����ֵΪ�´ε���ʱ����(����),-1��ʾ����
	int StartSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size, int & next_interval);
	int Run( SKILL::Data & skilldata, object_interface player, const XID * target, int size, int & next_interval );
	int StartSkill( SKILL::Data & skilldata, object_interface player, const A3DVECTOR& pos,const XID * target, int size, int & next_interval);
	int Run( SKILL::Data & skilldata, object_interface player, const A3DVECTOR& pos, const XID * target, int size, int & next_interval );
	// ��ϣ��ܹ���ʱ����
	bool Interrupt( SKILL::Data & skilldata, object_interface player );
	// �������ȡ������ִ�еļ���
	bool Cancel( SKILL::Data & skilldata, object_interface player );
	// ��ǰ������ǰ״̬����������
	int Continue( SKILL::Data& skilldata, object_interface player, const XID* target,int size, int& next_interval,int elapse_time);

	// ʹ��˲������, 0 �ɹ���-1 ʧ��
	int InstantSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size);

	// ʹ����Ʒ���Ӽ���, 0 �ɹ�, -1 ʧ��
	int CastRune(SKILL::Data & skilldata, object_interface player, int level);

	//ʹ����Ʒ���Ӽ���
	int StartRuneSkill(SKILL::Data& skilldata, object_interface player, const XID* target, int size, int& next_interval, int level);
	int RunRuneSkill( SKILL::Data & skilldata, object_interface player, const XID * target, int size , int& next_interval, int level);
	int ContinueRuneSkill( SKILL::Data& skilldata, object_interface player, const XID* target, int size, int& next_interval, int elapse_time, int level);
	bool InterruptRuneSkill( SKILL::Data & skilldata, object_interface player, int level);
	bool CancelRuneSkill( SKILL::Data & skilldata, object_interface player, int level);
	int RuneInstantSkill(SKILL::Data& skilldata, object_interface player, const XID * target, int size, int level);

	// ��ȡ�ͱ���PersistentData
	void LoadDatabase( archive & ar );
	void StoreDatabase( archive & ar );
	unsigned int StoreDatabaseSize();

	void Load( archive & ar );
	void Store( archive & ar );

	void StorePartial( archive & ar );

	int ActivateSkill(object_interface player, ID id, int level, int type);
	int DeactivateSkill(object_interface player, ID id, int level, int type);
	int ActivateReboundSkill(object_interface player, ID id, int level, int trigger_prob, int period);
	int DeactivateReboundSkill(object_interface player, ID id, int level, int trigger_prob, int period);

	int GetSkillLevel(ID id);

	// ��������Ч������
	bool Attack(object_interface target, const XID&, const A3DVECTOR&,const attack_msg& msg, bool invader);
	bool Attack(object_interface target, const XID&, const A3DVECTOR&,const enchant_msg& msg, bool invader );
	// �������ӵ�״̬��
	bool Infect(object_interface target, const XID&, const A3DVECTOR&,const attack_msg& msg, bool invader);
	bool Infect(object_interface target, const XID&, const A3DVECTOR&,const enchant_msg& msg, bool invader );

	// �������ܣ������ʼ��
	bool EventReset(object_interface player);
	// �������ܣ������ʼ��
	bool EventUnreset(object_interface player);
	// �������ܣ�װ������
	bool EventWield(object_interface player, int weapon_class );
	// �������ܣ�ж������
	bool EventUnwield(object_interface player, int weapon_class );
	// �������ܣ�����
	bool EventChange(object_interface player, int from, int to);
	// �������ܣ���������
	bool EventEnter(object_interface player,int worldtag );
	bool EventLeave(object_interface player,int worldtag );

	// ����ֵΪ�´ε���ʱ����(����),-1��ʾ����
	int NpcStart(ID id, object_interface npc, int level, const XID * target, int size, int& next_interval);
	void NpcEnd(ID id, object_interface npc, int level, const XID * target, int size );
	// ��ϣ��ܹ���ʱ����
	bool NpcInterrupt(ID id, object_interface npc, int level);
	float NpcCastRange(ID id, int level);

	// �޸��������
	int IncPrayTime(int inc);
	int DecPrayTime(int dec);
	// �޸���ȴʱ������ֵ
	void IncCDAdjust(int v) { cd_adjust += v; }
	void DecCDAdjust(int v) { cd_adjust -= v; }
	int  GetCDAdjust() { if(cd_adjust_count) { --cd_adjust_count; return cd_adjust;} else return 0; }
	int  GetCDAdjustCount() const { return cd_adjust_count; }
	void SetCDAdjustCount(int count) { cd_adjust_count = count; }
	// �޸��������븽��ֵ
	float IncPrayDisAdjust(float pd) { pray_distance_adjust += pd; return pray_distance_adjust; }
	float DecPrayDisAdjust(float pd) { pray_distance_adjust -= pd; return pray_distance_adjust; }
	float GetPrayDisAdjust() const { return pray_distance_adjust; }

	int IncAbility(object_interface player, ID id, int inc);
	int GetAbility(ID id);
	float GetAbilityRatio(ID id);	//-1 ���� 0-1 ��ǰ�����ȱ���
	int IncAbilityRatio(object_interface player, ID id, float ratio);
	int SetSealed(object_interface player, int second);
	int SetFix(object_interface player, int second);	
	int SetFlager(object_interface player, float hurt_ratio, float hurt_ratio2/*��ս�չ�*/, float speed_ratio, float max_hp_ratio);//���ӹ�ս����filter
	int UnSetFlager(object_interface player);//ɾ����ս����filter
	int OnCountryBattleRevive(object_interface player, int time, int ap, float physic_ratio, float magic_ratio, int time2, float incresist, float incdefense, float inchp);
	void CountryBattleWeakProtect(object_interface player, int time, int inc_atk_degree, int inc_def_degree);
	void SetChariotFilter(object_interface player, int shape, int inc_hp, int inc_defence, int inc_magic_defence[5], int inc_damage, int inc_magic_damage, float inc_speed, float inc_hp_ratio, int dyn_skill[4]);
	static int GetCooldownID(ID id);
	static int GetMpCost(ID id, object_interface npc, int level);
	static int PetLearn(ID id,int petlevel,object_interface owner,unsigned int *skills,int size); // �����µļ��𣬴��󷵻�-1
	static int ElfLearnSkill(int skill_id, int skill_level, struct SKILL::elf_requirement& elf, object_interface player); 
	static bool IsElfSkillActive(int skill_id, int skill_level, struct SKILL::elf_requirement& elf, object_interface player); 
	int RunElfSkill( SKILL::Data & skilldata, int skill_level, object_interface player, const XID *target, int size);
	
public:
	void SetSkillTalent(Skill* skill, const int* list);

	void IncImmuneBuffDebuff(){	immune_buff_debuff ++;}	//lgc
	void DecImmuneBuffDebuff(){	immune_buff_debuff --;}

	void IncInterruptProb(int prob) { interrupt_prob += prob; }
	void DecInterruptProb(int prob) { interrupt_prob -= prob; }

	void IncIgnoreInterrupt(int ignore) { ignore_interrupt += ignore; }
	void DecIgnoreInterrupt(int ignore) { ignore_interrupt -= ignore; }

	int GetPraySpeed(){ return prayspeed; }
	void SetPraySpeed( int v ) { prayspeed = v; }
	
	// Following interfaces are intended for internal use
	
	int GetAsid(unsigned int pos) { return pos < MAX_ABILITY_SKILL ? as[pos].id : 0; }
	int GetAslevel(unsigned int pos) { return pos < MAX_ABILITY_SKILL ? as[pos].level : 0; }
	
	/*
	int GetAsid() { return asid; }
	int GetAslevel() { return aslevel; }
	
	int GetAsid2() { return asid2; }
	int GetAslevel2() { return aslevel2; }
	
	int GetAsid3() { return asid3; }
	int GetAslevel3() { return aslevel3; }
	*/
	
	void SetLevel(ID id, int level);
	void OverrideSkill(const std::vector<std::pair<ID,int> > & pre_skills);

	bool SetSkillInc(int magic, float inc);
	float GetSkillInc(int magic);
	void Swap(SkillWrapper&);
	int  GetProduceSkill();

	int  GetLevel(ID id, int cls ,bool use=false);
	bool TestCommonCoolDown(int cd_mask, object_interface player);

	int  GetProduceSkillLevel(ID id);

	void ModifyDynamicPray(ID id, float ratio, int times);
	int  GetDynamicPrayTimes(ID id); 

	void OnSkillPerform(ID id, ID perid, object_interface player);
	void OnComboPreSkillEnd(Skill* skill, object_interface player);
	bool SetComboSkillArg(int index, int arg) { return combo_state.SetArg(index,arg);} 
	int  GetComboSkillArg(int index) { return combo_state.GetArg(index);}
	void SetComboState(ID id, int stime,int type,int ex) { combo_state.SetState(id,stime,type,ex); }
	void SetComboState(ID id) { combo_state.skillid = id; }
	ID   GetComboState() const { return combo_state.skillid; }
	void SyncComboState(object_interface player);
	void ClearComboState() { combo_state.Clear();}
	bool CheckComboBreak(int now, bool sflag) { return combo_state.Break(now,sflag);}
	bool CheckComboState(ID id, int interval, int now) { return combo_state.Condition(id,interval,now);}

	int  GetBlackWhiteBalls() { return black_white_ball.GetIndex(); }
	bool AddBlackWhiteBalls(int ball, int& new_vstate, int& old_vstate, int& hstate); 
	bool FlipBlackWhiteBalls(int& new_vstate, int& old_vstate, int& hstate);


	
	void SoloChallengeAddFilter(object_interface player, int filter_id, float *param);
	void MnFactionAddFilter(object_interface player, float ratio);
    void ResurrectByCashAddFilter(object_interface player, int buff_period, const float* buff_ratio, int buff_size);
	
	//glyph
	int GetSkillRuneAttr(ID id);
	void ActivateGlyphSkill(ID id, ID pre_id, int level);
	void DeactivateGlyphSkill(ID id, ID pre_id);
	void ClearGlyphSkill();
	
	//172
	bool IsImmineCasting(ID id);
	int SetFreemoveMonkey(object_interface player, int second);
	
	// Segment
	int GetCoolDownLimit(ID id );
	
	virtual ~SkillWrapper(){}
};

};

#endif

