//---------------------------------------------------------------------------------------------------------------------------
//--PW LUA SCRIPT CSKILL (C) DeadRaky 2023 x64
//---------------------------------------------------------------------------------------------------------------------------
#ifndef __GNET_LUASKILL_H
#define __GNET_LUASKILL_H

#include <luabase.h>
#pragma pack(push, 1)

namespace GNET
{
class Skill;
};
class LuaSkill : public LuaBase
{
public:
	enum : size_t
	{
		FUNC_DISTABLE					= 0           ,
		FUNC_STATE1						= 1           ,
		FUNC_STATE2						= 2           ,
		FUNC_STATE3						= 4           ,
		FUNC_STATE4						= 8           ,
		FUNC_STATE5						= 16          ,
		FUNC_STATE6						= 32          ,
		FUNC_STATE7						= 64          ,
		FUNC_STATE8						= 128         ,
		FUNC_STATE9						= 256         ,
		FUNC_SKILL						= 512         ,
		FUNC_CREATE						= 1024		  ,
		FUNC_REID						= 2048		  ,

		STATE_DISTABLE				   	= 0           ,
		STATE_GETTIME                   = 1           ,
		STATE_QUIT                      = 2           ,
		STATE_LOOP                      = 4           ,
		STATE_BYPASS                    = 8           ,
		STATE_CALCULATE                 = 16          ,
		STATE_INTERRUPT                 = 32          ,
		STATE_CANCEL                    = 64          ,
		STATE_SKIP                      = 128         ,

		SKILL_DISTABLE				   	= 0           ,
		SKILL_GETEXECUTETIME			= 1           ,
		SKILL_GETCOOLINGTIME			= 2           ,
		SKILL_GETENMITY				   	= 4           ,
		SKILL_GETREQUIREDSP			   	= 8           ,
		SKILL_GETREQUIREDLEVEL		   	= 16          ,
		SKILL_GETREQUIREDITEM		   	= 32          ,
		SKILL_GETREQUIREDMONEY		   	= 64          ,
		SKILL_GETMAXABILITY			   	= 128         ,
		SKILL_GETREQUIREDREALMLEVEL	   	= 256         ,
		SKILL_STATEATTACK			   	= 512         ,
		SKILL_BLESSME				   	= 1024        ,
		SKILL_GETRADIUS				   	= 2048        ,
		SKILL_GETATTACKDISTANCE		   	= 4096        ,
		SKILL_GETANGLE				   	= 8192        ,
		SKILL_GETPRAYDISTANCE		   	= 16384       ,
		SKILL_GETEFFECTDISTANCE		   	= 32768       ,
		SKILL_GETTALENT0				= 65536       ,
		SKILL_GETTALENT1				= 131072      ,
		SKILL_GETTALENT2               	= 262144      ,
		SKILL_GETATTACKSPEED           	= 524288      ,
		SKILL_TAKEEFFECT               	= 1048576     ,
		SKILL_GETHITRATE				= 2097152	  ,
		SKILL_GETTALENT3               	= 4194304     ,
		SKILL_GETTALENT4               	= 8388608     ,

		CREATE_DISTABLE					= 0           ,
		CREATE_ID						= 1           ,
		CREATE_CLS                      = 2           ,
		CREATE_MAX_LEVEL                = 3           ,
		CREATE_TYPE                     = 4           ,
		CREATE_ATTR                     = 5           ,
		CREATE_RANK                     = 6           ,
		CREATE_EVENTFLAG                = 7           ,
		CREATE_NPCDELAY                 = 8           ,
		CREATE_SHOWORDER                = 9           ,
		CREATE_APGAIN                   = 10          ,
		CREATE_APCOST                   = 11          ,
		CREATE_ARROWCOST                = 12          ,
		CREATE_IS_SENIOR                = 13          ,
		CREATE_IS_INHERENT              = 14          ,
		CREATE_IS_MOVINGCAST            = 15          ,
		CREATE_ALLOW_LAND               = 16          ,
		CREATE_ALLOW_AIR                = 17          ,
		CREATE_ALLOW_WATER              = 18          ,
		CREATE_ALLOW_RIDE               = 19          ,
		CREATE_NOTUSE_IN_COMBAT         = 20          ,
		CREATE_RESTRICT_CORPSE          = 21          ,
		CREATE_AUTO_ATTACK              = 22          ,
		CREATE_TIME_TYPE                = 23          ,
		CREATE_ALLOW_FORMS              = 24          ,
		CREATE_LONG_RANGE               = 25          ,
		CREATE_POSDOUBLE                = 26          ,
		CREATE_CLSLIMIT                 = 27          ,
		CREATE_RANGE                    = 28          ,
		CREATE_DOENCHANT                = 29          ,
		CREATE_DOBLESS                  = 30          ,
		CREATE_COMMONCOOLDOWN           = 31          ,
		CREATE_COMMONCOOLDOWNTIME       = 32          ,
		CREATE_ITEMCOST                 = 33          ,
		CREATE_COMBOSK_PRESKILL         = 34          ,
		CREATE_COMBOSK_INTERVAL         = 35          ,
		CREATE_COMBOSK_NOBREAK          = 36          ,
		                                        
		TYPE_CHAR 						= 0           ,
		TYPE_SHORT 						= 1           ,
		TYPE_INT 						= 2           ,
		TYPE_INT64 						= 3           ,
		TYPE_FLOAT 						= 4           ,
		TYPE_DOUBLE 					= 5           ,
		
		MAX_SKILL_COUNT 				= 5400        ,
		MAX_STATE_COUNT					= 9			  ,
	};
public:
	struct CSKILL
	{
		struct 
		{
			long long FUNC;
			long long STATE;
			long long SKILL;
			long long REID;
		}	S[MAX_SKILL_COUNT];
		
		CSKILL();
		void INIT();
		void SET_SKILL(int ID, long long FUNC, long long state, long long SKILL, long long REID);
		long long GET_SKILL(int ID, long long & FUNC, long long & STATE, long long & SKILL, long long & REID);
		long long GET_STATE(int STATE_INDEX, long long FUNC);
		
	};
	
	struct CONFIG
	{
		int MAX_SOUL;
		int MAX_SOUL_SHAMAN;
		int FREE_SP;
		int FREE_MONEY;
		int FREE_ITEM;
		CONFIG();
		void INIT();
	};
	
	struct MEMSPACE
	{
		CONFIG config;
		CSKILL cskill;
		MEMSPACE();
		void INIT();
	};
	
public:
	static MEMSPACE data;
	static LuaSkill * instance;
public:
	LuaSkill();
	~LuaSkill();
	CSKILL * GetCskill() { return &data.cskill; }
	CONFIG * GetConfig() { return &data.config; }
	static LuaSkill * GetInstance();
public:
	virtual void FunctionsRegister();
	virtual void FunctionsExecute();
	virtual void GetItem();
	virtual void SetItem();
	
public:
	virtual void EventInit();
	virtual void EventUpdate();
	virtual void EventHeartBeat();
	
public:

	static void game__Editor(long long skill, int type, double value);
	static void game__AddSkill(int ID, long long FUNC, long long state, long long SKILL, long long REID);

public:
	
	static GNET::Skill * Create(int id);
	
	double StateAttack(GNET::Skill * skill, int id);
	double BlessMe(GNET::Skill * skill, int id);
	double GetExecutetime(GNET::Skill * skill, int id);
	double GetCoolingtime(GNET::Skill * skill, int id);
	double GetEnmity(GNET::Skill * skill, int id);
	double GetRequiredSp(GNET::Skill * skill, int id);
	double GetRequiredLevel(GNET::Skill * skill, int id);
	double GetRequiredItem(GNET::Skill * skill, int id);
	double GetRequiredMoney(GNET::Skill * skill, int id);
	double GetMaxability(GNET::Skill * skill, int id);
	double GetRequiredRealmLevel(GNET::Skill * skill, int id);
	double GetRadius(GNET::Skill * skill, int id);
	double GetAttackdistance(GNET::Skill * skill, int id);
	double GetAngle(GNET::Skill * skill, int id);
	double GetPraydistance(GNET::Skill * skill, int id);
	double GetEffectdistance(GNET::Skill * skill, int id);
	double GetT0(GNET::Skill * skill, int id);
	double GetT1(GNET::Skill * skill, int id);
	double GetT2(GNET::Skill * skill, int id);
	double GetT3(GNET::Skill * skill, int id);
	double GetAttackspeed(GNET::Skill * skill, int id);
	double TakeEffect(GNET::Skill * skill, int id);
	double GetHitrate(GNET::Skill * skill, int id);

	double GetTime(GNET::Skill * skill, int id, unsigned int state);
	double Quit(GNET::Skill * skill, int id, unsigned int state);
	double Loop(GNET::Skill * skill, int id, unsigned int state);
	double Bypass(GNET::Skill * skill, int id, unsigned int state);
	double Calculate(GNET::Skill * skill, int id, unsigned int state);
	double Interrupt(GNET::Skill * skill, int id, unsigned int state);
	double Cancel(GNET::Skill * skill, int id, unsigned int state);
	double Skip(GNET::Skill * skill, int id, unsigned int state);
	
public:
	static double GetSLevel						 (long long skill);
	static double GetSAttack					 (long long skill);
	static double GetSMagicattack				 (long long skill);
	static double GetPlus						 (long long skill);
	static double GetRatioState					 (long long skill);
	static double GetDamage						 (long long skill);
	static double GetGolddamage					 (long long skill);
	static double GetWooddamage					 (long long skill);
	static double GetWaterdamage				 (long long skill);
	static double GetFiredamage					 (long long skill);
	static double GetEarthdamage				 (long long skill);
	static double GetMagicdamage				 (long long skill);
	static double GetDegree						 (long long skill);
	static double GetWorldTag               	 (long long skill);
	static double GetId		             	  	 (long long skill);
	static double GetMp                     	 (long long skill);
	static double GetHp                     	 (long long skill);
	static double GetSp                     	 (long long skill);
	static double GetAp                     	 (long long skill);
	static double GetCls                    	 (long long skill);
	static double GetForm                   	 (long long skill);
	static double GetMaxhp                  	 (long long skill);
	static double GetMaxmp                  	 (long long skill);
	static double GetLevel                  	 (long long skill);
	static double GetRank                   	 (long long skill);
	static double GetMoney                  	 (long long skill);
	static double GetCurWeapon              	 (long long skill);
	static double GetCurweapon              	 (long long skill);
	static double GetWeapondamage           	 (long long skill);
	static double GetWeaponmagicdamage      	 (long long skill);
	static double GetInteam                 	 (long long skill);
	static double CanAttack                 	 (long long skill);
	static double GetRange                  	 (long long skill);
	static double GetAttack                 	 (long long skill);
	static double GetMagicattack            	 (long long skill);
	static double GetPureattack	         	  	 (long long skill);
	static double GetPuremagicattack        	 (long long skill);
	static double GetDefenddegree           	 (long long skill);
	static double GetAttackdegree           	 (long long skill);
	static double GetDefense	             	 (long long skill);
	static double GetGoldresist	         	  	 (long long skill);
	static double GetWoodresist	         	     (long long skill);
	static double GetWaterresist            	 (long long skill);
	static double GetFireresist	         	  	 (long long skill);
	static double GetEarthresist            	 (long long skill);
	static double GetCrit		             	 (long long skill);
	static double GetSoulpower	             	 (long long skill);
	static double GetHistoricalmaxlevel     	 (long long skill);
	static double GetRealm                  	 (long long skill);
	static double GetEquipattack            	 (long long skill);
	static double GetEquipmagicattack       	 (long long skill);
	static double GetLocalval0              	 (long long skill);
	static double GetLocalval1              	 (long long skill);
	static double GetLocalval2              	 (long long skill);
	static double GetCombat		         	     (long long skill);
	static double GetElfmp                  	 (long long skill);
	static double GetElfap                  	 (long long skill);
	static double GetLanding                	 (long long skill);
	static double GetAiring                 	 (long long skill);
	static double GetWatering               	 (long long skill);
	static double GetRiding                 	 (long long skill);
	static double GetSkillenhance2          	 (long long skill);
	static double GetRangetotarget          	 (long long skill);
	static double GetProduceSkill           	 (long long skill);
	static double GetDynskillcounter        	 (long long skill);
	static double GetLvalue                 	 (long long skill);
	static double GetPrayrangeplus          	 (long long skill);
	static double GetRand                   	 (long long skill);
	static double GetBalls                  	 (long long skill);
	static double GetProbability            	 (long long skill);
	static double GetProbabilityInt         	 (long long skill);
	static double GetRatio                  	 (long long skill);
	static double GetValue                  	 (long long skill);
	static double GetAmount                 	 (long long skill);
	static double GetRatioInt               	 (long long skill);
	static double GetValueInt               	 (long long skill);
	static double GetAmountInt              	 (long long skill);
	static double GetShowicon               	 (long long skill);
	static double GetSuccess                	 (long long skill);
	static double GetImmune                 	 (long long skill);
	static double Gettime                   	 (long long skill);
	static double GetIntarg                 	 (long long skill);
	static double GetEnable                 	 (long long skill);
	static double GetInvader                	 (long long skill);
	static double GetElfstr                 	 (long long skill);
	static double GetElfagi                 	 (long long skill);
	static double GetElfvit                 	 (long long skill);
	static double GetElfeng                 	 (long long skill);
	static double GetElflevel               	 (long long skill);
	static double GetTargetregionplayernum  	 (long long skill);
	static double GetCharging               	 (long long skill);
	static double GetDecsp                  	 (long long skill);
	static double GetDecmp                  	 (long long skill);
	static double GetIncgold                	 (long long skill);
	static double GetIncwood                	 (long long skill);
	static double GetIncwater               	 (long long skill);
	static double GetIncfire                	 (long long skill);
	static double GetIncearth               	 (long long skill);
	static void   SetProbability                 (long long skill, double value);
	static void   SetPlus						 (long long skill, double value);
	static void   SetRatioState					 (long long skill, double value);
	static void   SetDamage						 (long long skill, double value);
	static void   SetGolddamage					 (long long skill, double value);
	static void   SetWooddamage					 (long long skill, double value);
	static void   SetWaterdamage				 (long long skill, double value);
	static void   SetFiredamage					 (long long skill, double value);
	static void   SetEarthdamage				 (long long skill, double value);
	static void   SetMagicDamage				 (long long skill, double value);
	static void   SetDegree						 (long long skill, double value);
	static double SetPray       				 (long long skill, double value);
	static double SetInform     				 (long long skill, double value);
	static double SetPerform    				 (long long skill, double value);
	static double SetDecelfmp   				 (long long skill, double value);
	static double SetDecelfap   				 (long long skill, double value);
	static double UseArrow      				 (long long skill, double value);
	static double IsUsingWeapon 				 (long long skill, double value);
	static double GetSkilllevel 				 (long long skill, double value);
	static double SetShowicon   				 (long long skill, double value);
	static double SetIntarg     				 (long long skill, double value);
	static double SetEnable     				 (long long skill, double value);
	static double SetInvader    				 (long long skill, double value);
	static double SetDecsp      				 (long long skill, double value);
	static double SetForm       				 (long long skill, double value);
	static double SetMaxhp      				 (long long skill, double value);
	static double SetInteam     				 (long long skill, double value);
	static double SetSp         				 (long long skill, double value);
	static double SetRange      				 (long long skill, double value);
	static double SetLevel      				 (long long skill, double value);
	static double SetRank       				 (long long skill, double value);
	static double SetHpgen      				 (long long skill, double value);
	static double SetMpgen      				 (long long skill, double value);
	static double SetDecmp                       (long long skill, double value);
	static double SetTime                        (long long skill, double value);
	static double SetRatio                       (long long skill, double value);
	static double SetValue                       (long long skill, double value);
	static double SetAmount                      (long long skill, double value);
	static double SetHp                          (long long skill, double value);
	static double SetMp                          (long long skill, double value);
	static double SetIncswim                     (long long skill, double value);
	static double SetIncgold                     (long long skill, double value);
	static double SetIncwood                     (long long skill, double value);
	static double SetIncwater                    (long long skill, double value);
	static double SetIncfire                     (long long skill, double value);
	static double SetIncearth                    (long long skill, double value);
	static double SetAdddefence                  (long long skill, double value);
	static double SetInchitrate                  (long long skill, double value);
	static double SetIncpethp                    (long long skill, double value);
	static double SetIncpetmp                    (long long skill, double value);
	static double SetIncpetdamage                (long long skill, double value);
	static double SetIncpetmagicdamage           (long long skill, double value);
	static double SetIncpetdefense               (long long skill, double value);
	static double SetIncpetmagicdefense          (long long skill, double value);
	static double SetIncpetattackdegree          (long long skill, double value);
	static double SetIncpetdefenddegree          (long long skill, double value);
	static double SetAddresistance               (long long skill, double value);
	static double SetAddskilldamage              (long long skill, double value);
	static double SetAddmaxhp                    (long long skill, double value);
	static double SetIncswimspeed                (long long skill, double value);
	static double SetIncdefenselevel             (long long skill, double value);
	static double SetIncCritReduce               (long long skill, double value);
	static double SetDirecthurt                  (long long skill, double value);
	static double SetHeal                        (long long skill, double value);
	static double SetResurrect                   (long long skill, double value);
	static double SetSpeedup                     (long long skill, double value);
	static double SetIncdefence                  (long long skill, double value);
	static double SetIncattack                   (long long skill, double value);
	static double SetIncsmite                    (long long skill, double value);
	static double SetIncmagic                    (long long skill, double value);
	static double SetDecmagic                    (long long skill, double value);
	static double SetAbsorbhp                    (long long skill, double value);
	static double SetInchp                       (long long skill, double value);
	static double SetDechp                       (long long skill, double value);
	static double SetIncmp                       (long long skill, double value);
	static double SetIncdodge                    (long long skill, double value);
	static double SetDecdodge                    (long long skill, double value);
	static double SetRepel                       (long long skill, double value);
	static double SetRepel2                      (long long skill, double value);
	static double SetRepelAtr                    (long long skill, double value);
	static double SetBlind                       (long long skill, double value);
	static double SetDecresist                   (long long skill, double value);
	static double SetIncresist                   (long long skill, double value);
	static double SetIncresist2                  (long long skill, double value);
	static double SetInchurt                     (long long skill, double value);
	static double SetDechurt                     (long long skill, double value);
	static double SetDecaccuracy                 (long long skill, double value);
	static double SetIncaccuracy                 (long long skill, double value);
	static double SetMagicleak                   (long long skill, double value);
	static double SetDecattack                   (long long skill, double value);
	static double SetDecdefence                  (long long skill, double value);
	static double SetFrighten                    (long long skill, double value);
	static double SetDizzy                       (long long skill, double value);
	static double SetSleep                       (long long skill, double value);
	static double SetFix                         (long long skill, double value);
	static double SetSealed                      (long long skill, double value);
	static double SetSlow                        (long long skill, double value);
	static double SetBleeding                    (long long skill, double value);
	static double SetThunder                     (long long skill, double value);
	static double SetToxic                       (long long skill, double value);
	static double SetBurning                     (long long skill, double value);
	static double SetFallen                      (long long skill, double value);
	static double SetFlood                       (long long skill, double value);
	static double SetFeathershield               (long long skill, double value);
	static double SetFireshield                  (long long skill, double value);
	static double SetIceshield                   (long long skill, double value);
	static double SetRetort                      (long long skill, double value);
	static double SetSlowpray                    (long long skill, double value);
	static double SetFastmpgen                   (long long skill, double value);
	static double SetScaleinchp                  (long long skill, double value);
	static double SetScaleincmp                  (long long skill, double value);
	static double SetScaledecmp                  (long long skill, double value);
	static double SetScaledechp                  (long long skill, double value);
	static double SetFasthpgen                   (long long skill, double value);
	static double SetFastattack                  (long long skill, double value);
	static double SetSlowattack                  (long long skill, double value);
	static double SetSoilshield                  (long long skill, double value);
	static double SetIceblade                    (long long skill, double value);
	static double SetEnhancegold                 (long long skill, double value);
	static double SetEnhancewood                 (long long skill, double value);
	static double SetEnhancewater                (long long skill, double value);
	static double SetEnhancefire                 (long long skill, double value);
	static double SetEnhancesoil                 (long long skill, double value);
	static double SetReducegold                  (long long skill, double value);
	static double SetReducewood                  (long long skill, double value);
	static double SetReducewater                 (long long skill, double value);
	static double SetReducefire                  (long long skill, double value);
	static double SetReducesoil                  (long long skill, double value);
	static double SetFireblade                   (long long skill, double value);
	static double SetToxicblade                  (long long skill, double value);
	static double SetCleardebuff                 (long long skill, double value);
	static double SetCleardebuff2                (long long skill, double value);
	static double SetInvincible                  (long long skill, double value);
	static double SetInvincible2                 (long long skill, double value);
	static double SetInvincible3                 (long long skill, double value);
	static double SetInvincible4                 (long long skill, double value);
	static double SetInvincible5                 (long long skill, double value);
	static double SetInvincible6                 (long long skill, double value);
	static double SetInvincible7                 (long long skill, double value);
	static double SetFastpray                    (long long skill, double value);
	static double SetAntiwater                   (long long skill, double value);
	static double SetPanruo                      (long long skill, double value);
	static double SetBreak                       (long long skill, double value);
	static double SetYijin                       (long long skill, double value);
	static double SetXisui                       (long long skill, double value);
	static double SetJingji                      (long long skill, double value);
	static double SetFlower1                     (long long skill, double value);
	static double SetFlower2                     (long long skill, double value);
	static double SetFlower3                     (long long skill, double value);
	static double SetFlower4                     (long long skill, double value);
	static double SetStoneskin                   (long long skill, double value);
	static double SetIronshield                  (long long skill, double value);
	static double SetWingshield                  (long long skill, double value);
	static double SetFirearrow                   (long long skill, double value);
	static double SetGiant                       (long long skill, double value);
	static double SetBlessmagic                  (long long skill, double value);
	static double SetEaglecurse                  (long long skill, double value);
	static double SetDevilstate                  (long long skill, double value);
	static double SetFreemove                    (long long skill, double value);
	static double SetSelfburning                 (long long skill, double value);
	static double SetFallen2                     (long long skill, double value);
	static double SetSealed2                     (long long skill, double value);
	static double SetFix2                        (long long skill, double value);
	static double SetDechurt2                    (long long skill, double value);
	static double SetInchurt2                    (long long skill, double value);
	static double SetInchurt3                    (long long skill, double value);
	static double SetInchurt4                    (long long skill, double value);
	static double SetInchurt5                    (long long skill, double value);
	static double SetDechurt3                    (long long skill, double value);
	static double SetInchp2                      (long long skill, double value);
	static double SetIncattack2                  (long long skill, double value);
	static double SetIncmagic2                   (long long skill, double value);
	static double SetFastpray2                   (long long skill, double value);
	static double SetSpeedup2                    (long long skill, double value);
	static double SetSkillcooldown               (long long skill, double value);
	static double SetCommoncooldown              (long long skill, double value);
	static double SetAurafireattack              (long long skill, double value);
	static double SetAurabless                   (long long skill, double value);
	static double SetAuracurse                   (long long skill, double value);
	static double SetAurabless2                  (long long skill, double value);
	static double SetAuracurse2                  (long long skill, double value);
	static double SetAurabless3                  (long long skill, double value);
	static double SetInvisible                   (long long skill, double value);
	static double SetIncantiinvisibleactive      (long long skill, double value);
	static double SetInchpsteal                  (long long skill, double value);
	static double SetInccritdamage               (long long skill, double value);
	static double SetIncdamagedodge              (long long skill, double value);
	static double SetIncdebuffdodge              (long long skill, double value);
	static double SetRebirth                     (long long skill, double value);
	static double SetDeepenbless                 (long long skill, double value);
	static double SetWeakenbless                 (long long skill, double value);
	static double SetWeakenbless2                (long long skill, double value);
	static double SetHurtwhenuseskill            (long long skill, double value);
	static double SetInterruptwhenuseskill       (long long skill, double value);
	static double SetSoulretort                  (long long skill, double value);
	static double SetSoulsealed                  (long long skill, double value);
	static double SetSoulbeatback                (long long skill, double value);
	static double SetSoulstun                    (long long skill, double value);
	static double SetFishform                    (long long skill, double value);
	static double SetGminvisible                 (long long skill, double value);
	static double SetActivatesharpener           (long long skill, double value);
	static double SetInchurtphysicgold           (long long skill, double value);
	static double SetInchurtwoodwater            (long long skill, double value);
	static double SetInchurtfireearth            (long long skill, double value);
	static double SetAttackattachstate1          (long long skill, double value);
	static double SetAttackattachstate2          (long long skill, double value);
	static double SetAttackattachstate3          (long long skill, double value);
	static double SetAttackattachstate4          (long long skill, double value);
	static double SetBeattackattachstate1        (long long skill, double value);
	static double SetBeattackattachstate2        (long long skill, double value);
	static double SetBeattackattachstate3        (long long skill, double value);
	static double SetBeattackattachstate4        (long long skill, double value);
	static double SetBeattackattachstate5        (long long skill, double value);
	static double SetBeattackattachstate6        (long long skill, double value);
	static double SetBeattackattachstate7        (long long skill, double value);
	static double SetBeattackattachstate8        (long long skill, double value);
	static double SetTransferbuff                (long long skill, double value);
	static double SetTransferdebuff              (long long skill, double value);
	static double SetAbsorbbuff                  (long long skill, double value);
	static double SetAbsorbdebuff                (long long skill, double value);
	static double SetSummonpet2                  (long long skill, double value);
	static double SetSummonplantpet              (long long skill, double value);
	static double SetPetsacrifice                (long long skill, double value);
	static double SetPlantsuicide                (long long skill, double value);
	static double SetPoisionseed                 (long long skill, double value);
	static double SetHpgenseed                   (long long skill, double value);
	static double SetPhysichurt                  (long long skill, double value);
	static double SetGoldhurt                    (long long skill, double value);
	static double SetWoodhurt                    (long long skill, double value);
	static double SetWaterhurt                   (long long skill, double value);
	static double SetFirehurt                    (long long skill, double value);
	static double SetEarthhurt                   (long long skill, double value);
	static double SetFastprayincmagic            (long long skill, double value);
	static double SetIncwoodwaterdefense         (long long skill, double value);
	static double SetSpecialslow                 (long long skill, double value);
	static double SetSpecialphysichurt           (long long skill, double value);
	static double SetIncdefencesmite             (long long skill, double value);
	static double SetIncresistmagic              (long long skill, double value);
	static double SetTransportmptopet            (long long skill, double value);
	static double SetTransportdamagetopet        (long long skill, double value);
	static double SetAbsorbdamageincdefense      (long long skill, double value);
	static double SetIncrementalhpgen            (long long skill, double value);
	static double SetChanceofrebirth             (long long skill, double value);
	static double SetSpecialphysichurttrigger    (long long skill, double value);
	static double SetLongjumptospouse            (long long skill, double value);
	static double SetInccountedsmite             (long long skill, double value);
	static double SetWeapondisabled              (long long skill, double value);
	static double SetIncaggroondamage            (long long skill, double value);
	static double SetEnhanceskilldamage          (long long skill, double value);
	static double SetDetectinvisible             (long long skill, double value);
	static double SetDetectinvisible2            (long long skill, double value);
	static double SetFastmpgen2                  (long long skill, double value);
	static double SetClearinvisible2             (long long skill, double value);
	static double SetPositionrollback            (long long skill, double value);
	static double SetPositionrollback2           (long long skill, double value);
	static double SetHprollback                  (long long skill, double value);
	static double SetNofly                       (long long skill, double value);
	static double SetForceselecttarget           (long long skill, double value);
	static double SetHealabsorb                  (long long skill, double value);
	static double SetRepelonnormalattack         (long long skill, double value);
	static double SetInccritresistance           (long long skill, double value);
	static double SetDeccritresistance           (long long skill, double value);
	static double SetExchangeposition            (long long skill, double value);
	static double SetPullover                    (long long skill, double value);
	static double SetTransmitskillattack         (long long skill, double value);
	static double SetAdditionalheal              (long long skill, double value);
	static double SetAdditionalattack            (long long skill, double value);
	static double SetTransportdamagetoleader     (long long skill, double value);
	static double SetForbidbeselected            (long long skill, double value);
	static double SetEnhanceskilldamage2         (long long skill, double value);
	static double SetCallupteammember            (long long skill, double value);
	static double SetDelayearthhurt              (long long skill, double value);
	static double SetDizzyinchurt                (long long skill, double value);
	static double SetSoulretort2                 (long long skill, double value);
	static double SetFixondamage                 (long long skill, double value);
	static double SetApgen2                      (long long skill, double value);
	static double SetIncattackondamage           (long long skill, double value);
	static double SetRebirth2                    (long long skill, double value);
	static double SetHealsteal                   (long long skill, double value);
	static double SetDropmoneyondeath            (long long skill, double value);
	static double SetIncattackrange              (long long skill, double value);
	static double SetQueryotherinventory         (long long skill, double value);
	static double SetThunderform                 (long long skill, double value);
	static double SetDelaytransmit               (long long skill, double value);
	static double SetDecnormalattackhurt         (long long skill, double value);
	static double SetFreemoveapgen               (long long skill, double value);
	static double SetIncatkdefhp                 (long long skill, double value);
	static double SetDenyattackcmd               (long long skill, double value);
	static double SetHpmpgennotincombat          (long long skill, double value);
	static double SetInchpmp                     (long long skill, double value);
	static double SetEnternonpenaltypvp          (long long skill, double value);
	static double SetLeavenonpenaltypvp          (long long skill, double value);
	static double SetIncmaxhpatkdfdlevel         (long long skill, double value);
	static double SetRetort2                     (long long skill, double value);
	static double SetKnockup                     (long long skill, double value);
	static double SetPalsy                       (long long skill, double value);
	static double SetAddattackdegree             (long long skill, double value);
	static double SetSubattackdegree             (long long skill, double value);
	static double SetAdddefencedegree            (long long skill, double value);
	static double SetSubdefencedegree            (long long skill, double value);
	static double SetSubdefencedegree2           (long long skill, double value);
	static double SetIncatkdefhp2                (long long skill, double value);
	static double SetIncsmite3                   (long long skill, double value);
	static double SetIncpenres                   (long long skill, double value);
	static double SetAttachstatetoself           (long long skill, double value);
	static double SetAttachstatetotarget         (long long skill, double value);
	static double SetFireshield2                 (long long skill, double value);
	static double SetIceshield2                  (long long skill, double value);
	static double SetHealshield                  (long long skill, double value);
	static double SetIncflyspeed                 (long long skill, double value);
	static double SetIncvigour                   (long long skill, double value);
	static double SetIncvigour2                  (long long skill, double value);
	static double SetShortjump                   (long long skill, double value);
	static double SetShortjump2                  (long long skill, double value);
	static double SetMovepunish                  (long long skill, double value);
	static double SetStandpunish                 (long long skill, double value);
	static double SetStandpunish2                (long long skill, double value);
	static double SetChantshield                 (long long skill, double value);
	static double SetChangeselfaggro             (long long skill, double value);
	static double SetSummonmobs                  (long long skill, double value);
	static double SetIntervalpalsy               (long long skill, double value);
	static double SetInternalinjury              (long long skill, double value);
	static double SetAtkdamagereduce             (long long skill, double value);
	static double SetDeathresetcd                (long long skill, double value);
	static double SetAppendenchant               (long long skill, double value);
	static double SetAppenddamage                (long long skill, double value);
	static double SetCooldownaward               (long long skill, double value);
	static double SetHuntersoul                  (long long skill, double value);
	static double SetNeverdead                   (long long skill, double value);
	static double SetChangemodel                 (long long skill, double value);
	static double SetScreeneffect                (long long skill, double value);
	static double SetAddfrosteffect              (long long skill, double value);
	static double SetActivefrosteffect           (long long skill, double value);
	static double SetIncspecskillcrit            (long long skill, double value);
	static double SetClearfilterbyid             (long long skill, double value);
	static double SetMoongod                     (long long skill, double value);
	static double SetDelayskilleffect            (long long skill, double value);
	static double SetEnhanceskilldamage3         (long long skill, double value);
	static double SetCritdamagereduce            (long long skill, double value);
	static double SetImmunemagical2              (long long skill, double value);
	static double SetPullover2                   (long long skill, double value);
	static double SetIncphysicaldamage           (long long skill, double value);
	static double SetIncmagicaldamage            (long long skill, double value);
	static double SetRemoveaggro                 (long long skill, double value);
	static double SetCooldownpunish              (long long skill, double value);
	static double SetAnticlearbuf                (long long skill, double value);
	static double SetIncenchantrange             (long long skill, double value);
	static double SetIncphysicalmagicaldefense   (long long skill, double value);
	static double SetReducegold3                 (long long skill, double value);
	static double SetReducewater3                (long long skill, double value);
	static double SetGenhpap                     (long long skill, double value);
	static double SetDetaindart                  (long long skill, double value);
	static double SetExtraexpfactor              (long long skill, double value);
	static double SetSoloIncAttackAndMagic       (long long skill, double value);
	static double SetSoloIncDefence              (long long skill, double value);
	static double SetSoloEnhanceResist           (long long skill, double value);
	static double SetSoloIncMaxHP                (long long skill, double value);
	static double SetInvincible8                 (long long skill, double value);
	static double SetSoloHpGen                   (long long skill, double value);
	static double SetSoloDecHurt                 (long long skill, double value);
	static double SetSoloAddAttackRange          (long long skill, double value);
	static double SetThunder3                    (long long skill, double value);
	static double SetToxic3                      (long long skill, double value);
	static double SetFlood3                      (long long skill, double value);
	static double SetBurning3                    (long long skill, double value);
	static double SetFallen3                     (long long skill, double value);
	static double SetShattereddreammob           (long long skill, double value);
	static double SetReduceSpeeddebuff           (long long skill, double value);
	static double SetShieldNew1                  (long long skill, double value);
	static double SetShieldNew2                  (long long skill, double value);
	static double SetNewSpeedBuff                (long long skill, double value);
	static double SetIraAtiradora                (long long skill, double value);
	static double SetFeAtiradora                 (long long skill, double value);
	static double SetNewRemove                   (long long skill, double value);
	static double SetIncAntiDefenseDegree        (long long skill, double value);
	static double SetIncPlusMaxHP                (long long skill, double value);
	static double SetInvisible2                  (long long skill, double value);
	static double SetAuracurse4ASN               (long long skill, double value);
	static double SetIncmagic4                   (long long skill, double value);
	static double SetDecsoul                     (long long skill, double value);
	static double SetGiantform                   (long long skill, double value);
	static double SetTransdmg2pet                (long long skill, double value);
	static double SetSkillcooldown2              (long long skill, double value);
	static double SetDecphysicalmagicaldefense   (long long skill, double value);
	static double SetIncsmitedamage              (long long skill, double value);
	static double SetDecphysicalmagicaldefense2  (long long skill, double value);
	static double SetFastpray3                   (long long skill, double value);
	static double SetIncdebuffdodge2             (long long skill, double value);
	static double SetIncdamagedodge2             (long long skill, double value);
	static double SetDebithurt                   (long long skill, double value);
	static double SetSoloAddAttackLevel          (long long skill, double value);
	static double SetSoloAddDefendLevel          (long long skill, double value);
	static double SetUltimatePaladin             (long long skill, double value);
	static double SetAttackplusAtr               (long long skill, double value);
	static double SetAddPraga                    (long long skill, double value);
	static double SetInsertvstate                (long long skill, double value);
	static double SetRetort3                     (long long skill, double value);

public:

	void SetFuncALLData();
};






















#pragma pack(pop)
#endif