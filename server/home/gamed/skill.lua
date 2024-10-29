--======================================================================================
--Lua manager by Deadraky (C) 2022
--======================================================================================

--======================================================================================
--Константы (не меняйте их, иначе код работать не будет корректно)
--======================================================================================

FUNC_DISTABLE					= 0      
FUNC_STATE1						= 1      
FUNC_STATE2						= 2      
FUNC_STATE3						= 4      
FUNC_STATE4						= 8      
FUNC_STATE5						= 16     
FUNC_STATE6						= 32     
FUNC_STATE7						= 64     
FUNC_STATE8						= 128    
FUNC_STATE9						= 256    
FUNC_SKILL						= 512    
FUNC_CREATE						= 1024	
FUNC_REID						= 2048	

STATE_DISTABLE				   	= 0      
STATE_GETTIME                   = 1      
STATE_QUIT                      = 2      
STATE_LOOP                      = 4      
STATE_BYPASS                    = 8      
STATE_CALCULATE                 = 16     
STATE_INTERRUPT                 = 32     
STATE_CANCEL                    = 64     
STATE_SKIP                      = 128    

SKILL_DISTABLE				   	= 0      
SKILL_GETEXECUTETIME			= 1      
SKILL_GETCOOLINGTIME			= 2      
SKILL_GETENMITY				   	= 4      
SKILL_GETREQUIREDSP			   	= 8      
SKILL_GETREQUIREDLEVEL		   	= 16     
SKILL_GETREQUIREDITEM		   	= 32     
SKILL_GETREQUIREDMONEY		   	= 64     
SKILL_GETMAXABILITY			   	= 128    
SKILL_GETREQUIREDREALMLEVEL	   	= 256    
SKILL_STATEATTACK			   	= 512    
SKILL_BLESSME				   	= 1024   
SKILL_GETRADIUS				   	= 2048   
SKILL_GETATTACKDISTANCE		   	= 4096   
SKILL_GETANGLE				   	= 8192   
SKILL_GETPRAYDISTANCE		   	= 16384  
SKILL_GETEFFECTDISTANCE		   	= 32768  
SKILL_GETTALENT0				= 65536  
SKILL_GETTALENT1				= 131072 
SKILL_GETTALENT2               	= 262144 
SKILL_GETATTACKSPEED           	= 524288 
SKILL_TAKEEFFECT               	= 1048576
SKILL_GETHITRATE				= 2097152

CREATE_DISTABLE					= 0      
CREATE_ID						= 1      
CREATE_CLS                      = 2      
CREATE_MAX_LEVEL                = 3      
CREATE_TYPE                     = 4      
CREATE_ATTR                     = 5      
CREATE_RANK                     = 6      
CREATE_EVENTFLAG                = 7      
CREATE_NPCDELAY                 = 8      
CREATE_SHOWORDER                = 9      
CREATE_APGAIN                   = 10     
CREATE_APCOST                   = 11     
CREATE_ARROWCOST                = 12     
CREATE_IS_SENIOR                = 13     
CREATE_IS_INHERENT              = 14     
CREATE_IS_MOVINGCAST            = 15     
CREATE_ALLOW_LAND               = 16     
CREATE_ALLOW_AIR                = 17     
CREATE_ALLOW_WATER              = 18     
CREATE_ALLOW_RIDE               = 19     
CREATE_NOTUSE_IN_COMBAT         = 20     
CREATE_RESTRICT_CORPSE          = 21     
CREATE_AUTO_ATTACK              = 22     
CREATE_TIME_TYPE                = 23     
CREATE_ALLOW_FORMS              = 24     
CREATE_LONG_RANGE               = 25     
CREATE_POSDOUBLE                = 26     
CREATE_CLSLIMIT                 = 27     
CREATE_RANGE                    = 28     
CREATE_DOENCHANT                = 29     
CREATE_DOBLESS                  = 30     
CREATE_COMMONCOOLDOWN           = 31     
CREATE_COMMONCOOLDOWNTIME       = 32     
CREATE_ITEMCOST                 = 33     
CREATE_COMBOSK_PRESKILL         = 34     
CREATE_COMBOSK_INTERVAL         = 35     
CREATE_COMBOSK_NOBREAK          = 36     
                                        
TYPE_CHAR 						= 0      
TYPE_SHORT 						= 1      
TYPE_INT 						= 2      
TYPE_INT64 						= 3      
TYPE_FLOAT 						= 4      
TYPE_DOUBLE 					= 5      

MAX_SKILL_COUNT 				= 5400             

--======================================================================================
--Используемые функции 
--======================================================================================

--	void game__Patch					(size_t address, int type, double value);
--	double game__Get					(size_t address, int type, size_t offset);
--  static void game__Editor			(size_t skill, int type, double value);
--  static void game__AddSkill			(int ID, int FUNC, int STATE, int SKILL, int REID);	

-- double SetPray       (size_t skill, double value);
-- double SetInform     (size_t skill, double value);
-- double SetPerform    (size_t skill, double value);
-- double SetDecelfmp   (size_t skill, double value);
-- double SetDecelfap   (size_t skill, double value);
-- double UseArrow      (size_t skill, double value);
-- double IsUsingWeapon (size_t skill, double value);
-- double GetSkilllevel (size_t skill, double value);
-- double SetShowicon   (size_t skill, double value);
-- double SetIntarg     (size_t skill, double value);
-- double SetEnable     (size_t skill, double value);
-- double SetInvader    (size_t skill, double value);
-- double SetDecsp      (size_t skill, double value);
-- double SetForm       (size_t skill, double value);
-- double SetMaxhp      (size_t skill, double value);
-- double SetInteam     (size_t skill, double value);
-- double SetSp         (size_t skill, double value);
-- double SetRange      (size_t skill, double value);
-- double SetLevel      (size_t skill, double value);
-- double SetRank       (size_t skill, double value);
-- double SetHpgen      (size_t skill, double value);
-- double SetMpgen      (size_t skill, double value);
--
-- void   SetPlus(size_t skill, double p) 			;
-- void   SetRatioState(size_t skill, double p) 	;
-- void   SetDamage(size_t skill, double p) 		;
-- void   SetGolddamage(size_t skill, double p) 	;
-- void   SetWooddamage(size_t skill, double p) 	;
-- void   SetWaterdamage(size_t skill, double p) 	;
-- void   SetFiredamage(size_t skill, double p) 	;
-- void   SetEarthdamage(size_t skill, double p) 	;
-- void   SetMagicDamage(size_t skill, double p) 	;
-- void   SetDegree(size_t skill, double p) 		;
-- double GetSLevel(size_t skill) 					;
-- double GetSAttack(size_t skill) 				;
-- double GetSMagicattack(size_t skill) 			;
-- double GetPlus(size_t skill) 					;
-- double GetRatioState(size_t skill) 				;
-- double GetDamage(size_t skill) 					;
-- double GetGolddamage(size_t skill) 				;
-- double GetWooddamage(size_t skill) 				;
-- double GetWaterdamage(size_t skill) 			;
-- double GetFiredamage(size_t skill) 				;
-- double GetEarthdamage(size_t skill) 			;
-- double GetMagicdamage(size_t skill) 			;
-- double GetDegree(size_t skill) 					;
--
-- double GetWorldTag               	  (size_t skill);
-- double GetId		             	  	  (size_t skill);
-- double GetMp                     	  (size_t skill);
-- double GetHp                     	  (size_t skill);
-- double GetSp                     	  (size_t skill);
-- double GetAp                     	  (size_t skill);
-- double GetCls                    	  (size_t skill);
-- double GetForm                   	  (size_t skill);
-- double GetMaxhp                  	  (size_t skill);
-- double GetMaxmp                  	  (size_t skill);
-- double GetLevel                  	  (size_t skill);
-- double GetRank                   	  (size_t skill);
-- double GetMoney                  	  (size_t skill);
-- double GetCurWeapon              	  (size_t skill);
-- double GetCurweapon              	  (size_t skill);
-- double GetWeapondamage           	  (size_t skill);
-- double GetWeaponmagicdamage      	  (size_t skill);
-- double GetInteam                 	  (size_t skill);
-- double CanAttack                 	  (size_t skill);
-- double GetRange                  	  (size_t skill);
-- double GetAttack                 	  (size_t skill);
-- double GetMagicattack            	  (size_t skill);
-- double GetPureattack	         	  (size_t skill);
-- double GetPuremagicattack        	  (size_t skill);
-- double GetDefenddegree           	  (size_t skill);
-- double GetAttackdegree           	  (size_t skill);
-- double GetDefense	             	  (size_t skill);
-- double GetGoldresist	         	  (size_t skill);
-- double GetWoodresist	         	  (size_t skill);
-- double GetWaterresist            	  (size_t skill);
-- double GetFireresist	         	  (size_t skill);
-- double GetEarthresist            	  (size_t skill);
-- double GetCrit		             	  (size_t skill);
-- double GetSoulpower	             	  (size_t skill);
-- double GetHistoricalmaxlevel     	  (size_t skill);
-- double GetRealm                  	  (size_t skill);
-- double GetEquipattack            	  (size_t skill);
-- double GetEquipmagicattack       	  (size_t skill);
-- double GetLocalval0              	  (size_t skill);
-- double GetLocalval1              	  (size_t skill);
-- double GetLocalval2              	  (size_t skill);
-- double GetCombat		         	  (size_t skill);
-- double GetElfmp                  	  (size_t skill);
-- double GetElfap                  	  (size_t skill);
-- double GetLanding                	  (size_t skill);
-- double GetAiring                 	  (size_t skill);
-- double GetWatering               	  (size_t skill);
-- double GetRiding                 	  (size_t skill);
-- double GetSkillenhance2          	  (size_t skill);
-- double GetRangetotarget          	  (size_t skill);
-- double GetProduceSkill           	  (size_t skill);
-- double GetDynskillcounter        	  (size_t skill);
-- double GetLvalue                 	  (size_t skill);
-- double GetPrayrangeplus          	  (size_t skill);
-- double GetRand                   	  (size_t skill);
-- double GetBalls                  	  (size_t skill);
-- double GetProbability            	  (size_t skill);
-- double GetProbabilityInt         	  (size_t skill);
-- double GetRatio                  	  (size_t skill);
-- double GetValue                  	  (size_t skill);
-- double GetAmount                 	  (size_t skill);
-- double GetRatioInt               	  (size_t skill);
-- double GetValueInt               	  (size_t skill);
-- double GetAmountInt              	  (size_t skill);
-- double GetShowicon               	  (size_t skill);
-- double GetSuccess                	  (size_t skill);
-- double GetImmune                 	  (size_t skill);
-- double GetTime                   	  (size_t skill);
-- double GetIntarg                 	  (size_t skill);
-- double GetEnable                 	  (size_t skill);
-- double GetInvader                	  (size_t skill);
-- double GetElfstr                 	  (size_t skill);
-- double GetElfagi                 	  (size_t skill);
-- double GetElfvit                 	  (size_t skill);
-- double GetElfeng                 	  (size_t skill);
-- double GetElflevel               	  (size_t skill);
-- double GetTargetregionplayernum  	  (size_t skill);
-- double GetCharging               	  (size_t skill);
-- double GetDecsp                  	  (size_t skill);
-- double GetDecmp                  	  (size_t skill);
-- double GetIncgold                	  (size_t skill);
-- double GetIncwood                	  (size_t skill);
-- double GetIncwater               	  (size_t skill);
-- double GetIncfire                	  (size_t skill);
-- double GetIncearth               	  (size_t skill);
--
-- double SetDecmp                       (size_t skill, double value);
-- double SetProbability                 (size_t skill, double value);
-- double SetTime                        (size_t skill, double value);
-- double SetRatio                       (size_t skill, double value);
-- double SetValue                       (size_t skill, double value);
-- double SetAmount                      (size_t skill, double value);
-- double SetHp                          (size_t skill, double value);
-- double SetMp                          (size_t skill, double value);
-- double SetIncswim                     (size_t skill, double value);
-- double SetIncgold                     (size_t skill, double value);
-- double SetIncwood                     (size_t skill, double value);
-- double SetIncwater                    (size_t skill, double value);
-- double SetIncfire                     (size_t skill, double value);
-- double SetIncearth                    (size_t skill, double value);
-- double SetAdddefence                  (size_t skill, double value);
-- double SetInchitrate                  (size_t skill, double value);
-- double SetIncpethp                    (size_t skill, double value);
-- double SetIncpetmp                    (size_t skill, double value);
-- double SetIncpetdamage                (size_t skill, double value);
-- double SetIncpetmagicdamage           (size_t skill, double value);
-- double SetIncpetdefense               (size_t skill, double value);
-- double SetIncpetmagicdefense          (size_t skill, double value);
-- double SetIncpetattackdegree          (size_t skill, double value);
-- double SetIncpetdefenddegree          (size_t skill, double value);
-- double SetAddresistance               (size_t skill, double value);
-- double SetAddskilldamage              (size_t skill, double value);
-- double SetAddmaxhp                    (size_t skill, double value);
-- double SetIncswimspeed                (size_t skill, double value);
-- double SetIncdefenselevel             (size_t skill, double value);
-- double SetIncCritReduce               (size_t skill, double value);
--
-- double SetDirecthurt                  (size_t skill, double value);
-- double SetHeal                        (size_t skill, double value);
-- double SetResurrect                   (size_t skill, double value);
-- double SetSpeedup                     (size_t skill, double value);
-- double SetIncdefence                  (size_t skill, double value);
-- double SetIncattack                   (size_t skill, double value);
-- double SetIncsmite                    (size_t skill, double value);
-- double SetIncmagic                    (size_t skill, double value);
-- double SetDecmagic                    (size_t skill, double value);
-- double SetAbsorbhp                    (size_t skill, double value);
-- double SetInchp                       (size_t skill, double value);
-- double SetDechp                       (size_t skill, double value);
-- double SetIncmp                       (size_t skill, double value);
-- double SetIncdodge                    (size_t skill, double value);
-- double SetDecdodge                    (size_t skill, double value);
-- double SetRepel                       (size_t skill, double value);
-- double SetRepel2                      (size_t skill, double value);
-- double SetRepelAtr                    (size_t skill, double value);
-- double SetBlind                       (size_t skill, double value);
-- double SetDecresist                   (size_t skill, double value);
-- double SetIncresist                   (size_t skill, double value);
-- double SetIncresist2                  (size_t skill, double value);
-- double SetInchurt                     (size_t skill, double value);
-- double SetDechurt                     (size_t skill, double value);
-- double SetDecaccuracy                 (size_t skill, double value);
-- double SetIncaccuracy                 (size_t skill, double value);
-- double SetMagicleak                   (size_t skill, double value);
-- double SetDecattack                   (size_t skill, double value);
-- double SetDecdefence                  (size_t skill, double value);
-- double SetFrighten                    (size_t skill, double value);
-- double SetDizzy                       (size_t skill, double value);
-- double SetSleep                       (size_t skill, double value);
-- double SetFix                         (size_t skill, double value);
-- double SetSealed                      (size_t skill, double value);
-- double SetSlow                        (size_t skill, double value);
-- double SetBleeding                    (size_t skill, double value);
-- double SetThunder                     (size_t skill, double value);
-- double SetToxic                       (size_t skill, double value);
-- double SetBurning                     (size_t skill, double value);
-- double SetFallen                      (size_t skill, double value);
-- double SetFlood                       (size_t skill, double value);
-- double SetFeathershield               (size_t skill, double value);
-- double SetFireshield                  (size_t skill, double value);
-- double SetIceshield                   (size_t skill, double value);
-- double SetRetort                      (size_t skill, double value);
-- double SetSlowpray                    (size_t skill, double value);
-- double SetFastmpgen                   (size_t skill, double value);
-- double SetScaleinchp                  (size_t skill, double value);
-- double SetScaleincmp                  (size_t skill, double value);
-- double SetScaledecmp                  (size_t skill, double value);
-- double SetScaledechp                  (size_t skill, double value);
-- double SetFasthpgen                   (size_t skill, double value);
-- double SetFastattack                  (size_t skill, double value);
-- double SetSlowattack                  (size_t skill, double value);
-- double SetSoilshield                  (size_t skill, double value);
-- double SetIceblade                    (size_t skill, double value);
-- double SetEnhancegold                 (size_t skill, double value);
-- double SetEnhancewood                 (size_t skill, double value);
-- double SetEnhancewater                (size_t skill, double value);
-- double SetEnhancefire                 (size_t skill, double value);
-- double SetEnhancesoil                 (size_t skill, double value);
-- double SetReducegold                  (size_t skill, double value);
-- double SetReducewood                  (size_t skill, double value);
-- double SetReducewater                 (size_t skill, double value);
-- double SetReducefire                  (size_t skill, double value);
-- double SetReducesoil                  (size_t skill, double value);
-- double SetFireblade                   (size_t skill, double value);
-- double SetToxicblade                  (size_t skill, double value);
-- double SetCleardebuff                 (size_t skill, double value);
-- double SetCleardebuff2                (size_t skill, double value);
-- double SetInvincible                  (size_t skill, double value);
-- double SetInvincible2                 (size_t skill, double value);
-- double SetInvincible3                 (size_t skill, double value);
-- double SetInvincible4                 (size_t skill, double value);
-- double SetInvincible5                 (size_t skill, double value);
-- double SetInvincible6                 (size_t skill, double value);
-- double SetInvincible7                 (size_t skill, double value);
-- double SetFastpray                    (size_t skill, double value);
-- double SetAntiwater                   (size_t skill, double value);
-- double SetPanruo                      (size_t skill, double value);
-- double SetBreak                       (size_t skill, double value);
-- double SetYijin                       (size_t skill, double value);
-- double SetXisui                       (size_t skill, double value);
-- double SetJingji                      (size_t skill, double value);
-- double SetFlower1                     (size_t skill, double value);
-- double SetFlower2                     (size_t skill, double value);
-- double SetFlower3                     (size_t skill, double value);
-- double SetFlower4                     (size_t skill, double value);
-- double SetStoneskin                   (size_t skill, double value);
-- double SetIronshield                  (size_t skill, double value);
-- double SetWingshield                  (size_t skill, double value);
-- double SetFirearrow                   (size_t skill, double value);
-- double SetGiant                       (size_t skill, double value);
-- double SetBlessmagic                  (size_t skill, double value);
-- double SetEaglecurse                  (size_t skill, double value);
-- double SetDevilstate                  (size_t skill, double value);
-- double SetFreemove                    (size_t skill, double value);
-- double SetSelfburning                 (size_t skill, double value);
-- double SetFallen2                     (size_t skill, double value);
-- double SetSealed2                     (size_t skill, double value);
-- double SetFix2                        (size_t skill, double value);
-- double SetDechurt2                    (size_t skill, double value);
-- double SetInchurt2                    (size_t skill, double value);
-- double SetInchurt3                    (size_t skill, double value);
-- double SetInchurt4                    (size_t skill, double value);
-- double SetInchurt5                    (size_t skill, double value);
-- double SetDechurt3                    (size_t skill, double value);
-- double SetInchp2                      (size_t skill, double value);
-- double SetIncattack2                  (size_t skill, double value);
-- double SetIncmagic2                   (size_t skill, double value);
-- double SetFastpray2                   (size_t skill, double value);
-- double SetSpeedup2                    (size_t skill, double value);
-- double SetSkillcooldown               (size_t skill, double value);
-- double SetCommoncooldown              (size_t skill, double value);
-- double SetAurafireattack              (size_t skill, double value);
-- double SetAurabless                   (size_t skill, double value);
-- double SetAuracurse                   (size_t skill, double value);
-- double SetAurabless2                  (size_t skill, double value);
-- double SetAuracurse2                  (size_t skill, double value);
-- double SetAurabless3                  (size_t skill, double value);
-- double SetInvisible                   (size_t skill, double value);
-- double SetIncantiinvisibleactive      (size_t skill, double value);
-- double SetInchpsteal                  (size_t skill, double value);
-- double SetInccritdamage               (size_t skill, double value);
-- double SetIncdamagedodge              (size_t skill, double value);
-- double SetIncdebuffdodge              (size_t skill, double value);
-- double SetRebirth                     (size_t skill, double value);
-- double SetDeepenbless                 (size_t skill, double value);
-- double SetWeakenbless                 (size_t skill, double value);
-- double SetWeakenbless2                (size_t skill, double value);
-- double SetHurtwhenuseskill            (size_t skill, double value);
-- double SetInterruptwhenuseskill       (size_t skill, double value);
-- double SetSoulretort                  (size_t skill, double value);
-- double SetSoulsealed                  (size_t skill, double value);
-- double SetSoulbeatback                (size_t skill, double value);
-- double SetSoulstun                    (size_t skill, double value);
-- double SetFishform                    (size_t skill, double value);
-- double SetGminvisible                 (size_t skill, double value);
-- double SetActivatesharpener           (size_t skill, double value);
-- double SetInchurtphysicgold           (size_t skill, double value);
-- double SetInchurtwoodwater            (size_t skill, double value);
-- double SetInchurtfireearth            (size_t skill, double value);
-- double SetAttackattachstate1          (size_t skill, double value);
-- double SetAttackattachstate2          (size_t skill, double value);
-- double SetAttackattachstate3          (size_t skill, double value);
-- double SetAttackattachstate4          (size_t skill, double value);
-- double SetBeattackattachstate1        (size_t skill, double value);
-- double SetBeattackattachstate2        (size_t skill, double value);
-- double SetBeattackattachstate3        (size_t skill, double value);
-- double SetBeattackattachstate4        (size_t skill, double value);
-- double SetBeattackattachstate5        (size_t skill, double value);
-- double SetBeattackattachstate6        (size_t skill, double value);
-- double SetBeattackattachstate7        (size_t skill, double value);
-- double SetBeattackattachstate8        (size_t skill, double value);
-- double SetTransferbuff                (size_t skill, double value);
-- double SetTransferdebuff              (size_t skill, double value);
-- double SetAbsorbbuff                  (size_t skill, double value);
-- double SetAbsorbdebuff                (size_t skill, double value);
-- double SetSummonpet2                  (size_t skill, double value);
-- double SetSummonplantpet              (size_t skill, double value);
-- double SetPetsacrifice                (size_t skill, double value);
-- double SetPlantsuicide                (size_t skill, double value);
-- double SetPoisionseed                 (size_t skill, double value);
-- double SetHpgenseed                   (size_t skill, double value);
-- double SetPhysichurt                  (size_t skill, double value);
-- double SetGoldhurt                    (size_t skill, double value);
-- double SetWoodhurt                    (size_t skill, double value);
-- double SetWaterhurt                   (size_t skill, double value);
-- double SetFirehurt                    (size_t skill, double value);
-- double SetEarthhurt                   (size_t skill, double value);
-- double SetFastprayincmagic            (size_t skill, double value);
-- double SetIncwoodwaterdefense         (size_t skill, double value);
-- double SetSpecialslow                 (size_t skill, double value);
-- double SetSpecialphysichurt           (size_t skill, double value);
-- double SetIncdefencesmite             (size_t skill, double value);
-- double SetIncresistmagic              (size_t skill, double value);
-- double SetTransportmptopet            (size_t skill, double value);
-- double SetTransportdamagetopet        (size_t skill, double value);
-- double SetAbsorbdamageincdefense      (size_t skill, double value);
-- double SetIncrementalhpgen            (size_t skill, double value);
-- double SetChanceofrebirth             (size_t skill, double value);
-- double SetSpecialphysichurttrigger    (size_t skill, double value);
-- double SetLongjumptospouse            (size_t skill, double value);
-- double SetInccountedsmite             (size_t skill, double value);
-- double SetWeapondisabled              (size_t skill, double value);
-- double SetIncaggroondamage            (size_t skill, double value);
-- double SetEnhanceskilldamage          (size_t skill, double value);
-- double SetDetectinvisible             (size_t skill, double value);
-- double SetDetectinvisible2            (size_t skill, double value);
-- double SetFastmpgen2                  (size_t skill, double value);
-- double SetClearinvisible2             (size_t skill, double value);
-- double SetPositionrollback            (size_t skill, double value);
-- double SetPositionrollback2           (size_t skill, double value);
-- double SetHprollback                  (size_t skill, double value);
-- double SetNofly                       (size_t skill, double value);
-- double SetForceselecttarget           (size_t skill, double value);
-- double SetHealabsorb                  (size_t skill, double value);
-- double SetRepelonnormalattack         (size_t skill, double value);
-- double SetInccritresistance           (size_t skill, double value);
-- double SetDeccritresistance           (size_t skill, double value);
-- double SetExchangeposition            (size_t skill, double value);
-- double SetPullover                    (size_t skill, double value);
-- double SetTransmitskillattack         (size_t skill, double value);
-- double SetAdditionalheal              (size_t skill, double value);
-- double SetAdditionalattack            (size_t skill, double value);
-- double SetTransportdamagetoleader     (size_t skill, double value);
-- double SetForbidbeselected            (size_t skill, double value);
-- double SetEnhanceskilldamage2         (size_t skill, double value);
-- double SetCallupteammember            (size_t skill, double value);
-- double SetDelayearthhurt              (size_t skill, double value);
-- double SetDizzyinchurt                (size_t skill, double value);
-- double SetSoulretort2                 (size_t skill, double value);
-- double SetFixondamage                 (size_t skill, double value);
-- double SetApgen2                      (size_t skill, double value);
-- double SetIncattackondamage           (size_t skill, double value);
-- double SetRebirth2                    (size_t skill, double value);
-- double SetHealsteal                   (size_t skill, double value);
-- double SetDropmoneyondeath            (size_t skill, double value);
-- double SetIncattackrange              (size_t skill, double value);
-- double SetQueryotherinventory         (size_t skill, double value);
-- double SetThunderform                 (size_t skill, double value);
-- double SetDelaytransmit               (size_t skill, double value);
-- double SetDecnormalattackhurt         (size_t skill, double value);
-- double SetFreemoveapgen               (size_t skill, double value);
-- double SetIncatkdefhp                 (size_t skill, double value);
-- double SetDenyattackcmd               (size_t skill, double value);
-- double SetHpmpgennotincombat          (size_t skill, double value);
-- double SetInchpmp                     (size_t skill, double value);
-- double SetEnternonpenaltypvp          (size_t skill, double value);
-- double SetLeavenonpenaltypvp          (size_t skill, double value);
-- double SetIncmaxhpatkdfdlevel         (size_t skill, double value);
-- double SetRetort2                     (size_t skill, double value);
-- double SetKnockup                     (size_t skill, double value);
-- double SetPalsy                       (size_t skill, double value);
-- double SetAddattackdegree             (size_t skill, double value);
-- double SetSubattackdegree             (size_t skill, double value);
-- double SetAdddefencedegree            (size_t skill, double value);
-- double SetSubdefencedegree            (size_t skill, double value);
-- double SetSubdefencedegree2           (size_t skill, double value);
-- double SetIncatkdefhp2                (size_t skill, double value);
-- double SetIncsmite3                   (size_t skill, double value);
-- double SetIncpenres                   (size_t skill, double value);
-- double SetAttachstatetoself           (size_t skill, double value);
-- double SetAttachstatetotarget         (size_t skill, double value);
-- double SetFireshield2                 (size_t skill, double value);
-- double SetIceshield2                  (size_t skill, double value);
-- double SetHealshield                  (size_t skill, double value);
-- double SetIncflyspeed                 (size_t skill, double value);
-- double SetIncvigour                   (size_t skill, double value);
-- double SetIncvigour2                  (size_t skill, double value);
-- double SetShortjump                   (size_t skill, double value);
-- double SetShortjump2                  (size_t skill, double value);
-- double SetMovepunish                  (size_t skill, double value);
-- double SetStandpunish                 (size_t skill, double value);
-- double SetStandpunish2                (size_t skill, double value);
-- double SetChantshield                 (size_t skill, double value);
-- double SetChangeselfaggro             (size_t skill, double value);
-- double SetSummonmobs                  (size_t skill, double value);
-- double SetIntervalpalsy               (size_t skill, double value);
-- double SetInternalinjury              (size_t skill, double value);
-- double SetAtkdamagereduce             (size_t skill, double value);
-- double SetDeathresetcd                (size_t skill, double value);
-- double SetAppendenchant               (size_t skill, double value);
-- double SetAppenddamage                (size_t skill, double value);
-- double SetCooldownaward               (size_t skill, double value);
-- double SetHuntersoul                  (size_t skill, double value);
-- double SetNeverdead                   (size_t skill, double value);
-- double SetChangemodel                 (size_t skill, double value);
-- double SetScreeneffect                (size_t skill, double value);
-- double SetAddfrosteffect              (size_t skill, double value);
-- double SetActivefrosteffect           (size_t skill, double value);
-- double SetIncspecskillcrit            (size_t skill, double value);
-- double SetClearfilterbyid             (size_t skill, double value);
-- double SetMoongod                     (size_t skill, double value);
-- double SetDelayskilleffect            (size_t skill, double value);
-- double SetEnhanceskilldamage3         (size_t skill, double value);
-- double SetCritdamagereduce            (size_t skill, double value);
-- double SetImmunemagical2              (size_t skill, double value);
-- double SetPullover2                   (size_t skill, double value);
-- double SetIncphysicaldamage           (size_t skill, double value);
-- double SetIncmagicaldamage            (size_t skill, double value);
-- double SetRemoveaggro                 (size_t skill, double value);
-- double SetCooldownpunish              (size_t skill, double value);
-- double SetAnticlearbuf                (size_t skill, double value);
-- double SetIncenchantrange             (size_t skill, double value);
-- double SetIncphysicalmagicaldefense   (size_t skill, double value);
-- double SetReducegold3                 (size_t skill, double value);
-- double SetReducewater3                (size_t skill, double value);
-- double SetGenhpap                     (size_t skill, double value);
-- double SetDetaindart                  (size_t skill, double value);
-- double SetExtraexpfactor              (size_t skill, double value);
-- double SetSoloIncAttackAndMagic       (size_t skill, double value);
-- double SetSoloIncDefence              (size_t skill, double value);
-- double SetSoloEnhanceResist           (size_t skill, double value);
-- double SetSoloIncMaxHP                (size_t skill, double value);
-- double SetInvincible8                 (size_t skill, double value);
-- double SetSoloHpGen                   (size_t skill, double value);
-- double SetSoloDecHurt                 (size_t skill, double value);
-- double SetSoloAddAttackRange          (size_t skill, double value);
-- double SetThunder3                    (size_t skill, double value);
-- double SetToxic3                      (size_t skill, double value);
-- double SetFlood3                      (size_t skill, double value);
-- double SetBurning3                    (size_t skill, double value);
-- double SetFallen3                     (size_t skill, double value);
-- double SetShattereddreammob           (size_t skill, double value);
-- double SetReduceSpeeddebuff           (size_t skill, double value);
-- double SetShieldNew1                  (size_t skill, double value);
-- double SetShieldNew2                  (size_t skill, double value);
-- double SetNewSpeedBuff                (size_t skill, double value);
-- double SetIraAtiradora                (size_t skill, double value);
-- double SetFeAtiradora                 (size_t skill, double value);
-- double SetNewRemove                   (size_t skill, double value);
-- double SetIncAntiDefenseDegree        (size_t skill, double value);
-- double SetIncPlusMaxHP                (size_t skill, double value);
-- double SetInvisible2                  (size_t skill, double value);
-- double SetAuracurse4ASN               (size_t skill, double value);
-- double SetIncmagic4                   (size_t skill, double value);
-- double SetDecsoul                     (size_t skill, double value);
-- double SetGiantform                   (size_t skill, double value);
-- double SetTransdmg2pet                (size_t skill, double value);
-- double SetSkillcooldown2              (size_t skill, double value);
-- double SetDecphysicalmagicaldefense   (size_t skill, double value);
-- double SetIncsmitedamage              (size_t skill, double value);
-- double SetDecphysicalmagicaldefense2  (size_t skill, double value);
-- double SetFastpray3                   (size_t skill, double value);
-- double SetIncdebuffdodge2             (size_t skill, double value);
-- double SetIncdamagedodge2             (size_t skill, double value);
-- double SetDebithurt                   (size_t skill, double value);
-- double SetSoloAddAttackLevel          (size_t skill, double value);
-- double SetSoloAddDefendLevel          (size_t skill, double value);
-- double SetUltimatePaladin             (size_t skill, double value);
-- double SetAttackplusAtr               (size_t skill, double value);
-- double SetAddPraga                    (size_t skill, double value);

--======================================================================================
--Глобальные переменные
--======================================================================================

lua_debug	= 0 -- включить режим отладки (Если сервер не является тестовым выключайте!)

MAX_SOUL = 72000 -- максимальная сила духа
MAX_SOUL_SHAMAN = 56000 -- максимальная сила духа скиллов шамана
FREE_SP = 0 -- включить выключить бесплатное изучение скиллов (дух) 
FREE_MONEY = 0 -- включить выключить бесплатное изучение скиллов (монеты) 
FREE_ITEM = 0 -- включить выключить бесплатное изучение скиллов (итемы) 

--======================================================================================
--Математические функции
--======================================================================================

-- Получить время суток
function get_time_dey()
	return int(os.time() / 86400)
end

function strtoint(inputstr)
        if inputstr == nil then
			return 0
        end
		return tonumber(inputstr)
end

-- Конвертировать текст в хекс
function string.fromhex(str)
    return (str:gsub('..', function (cc)
        return string.char(tonumber(cc, 16))
    end))
end

-- конвертировать хекс в текст
function string.tohex(str)
    return (str:gsub('.', function (c)
        return string.format('%02X', string.byte(c))
    end))
end

-- Конвертировать число в int
function int(numb)
	return math.floor(numb)
end

-- получить дату и время
function mydata()
	return os.date("%d/%m/%Y %H:%M:%S")
end

-- Запись в лог файл
function mylogfunc(text)
	local outstr = mydata()..":"..text.."\n"
	local file = io.open("skilllog.txt", "a")
	file:write(outstr)
	file:close()
	io.write(outstr)
end

-- фан чатик
function funnytext (message)
str = message
as = {'а', 'о', 'е', 'ы', 'ё', 'э'}
whereat = {'у', 'а', 'ы', 'а', 'о', 'е'}
if #as == #whereat then
    for i=1,#as do
        str = str:gsub(as[i], whereat[i])
    end
end
	return str

end

-- разбить чатик на слова
function mysplit(inputstr, sep)
        if sep == nil then
                sep = "%s"
        end
        local t={} ; i=1
        for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
                t[i] = str
                i = i + 1
        end
        return t
end

-- проверить таблицу на верный итем
function check_true_item(item , items)

	if items[item] == nil then
		return 0
	end
	return items[item]

end

--======================================================================================
--=====================================[PATCH FUNC]=====================================
--======================================================================================

--Патчинг таблицы из 1 инта
function IntTable(pushd, value)

	game__Patch(pushd,TYPE_INT,value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 1 флоата
function FloatTable(pushd, value)

	game__Patch(pushd,TYPE_FLOAT,value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х интов
function IntIntTable(pushd, value1, value2)

	game__Patch(pushd,TYPE_INT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_INT,value2)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х флоатов
function FloatFloatTable(pushd, value1, value2)

	game__Patch(pushd,TYPE_FLOAT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value2)
	pushd = pushd + 4
	return pushd
end

-- XID++
function HashIDX()
	lua_idx = lua_idx+1
end

--======================================================================================
--Таблицы редактируемых в луа скиллов
--======================================================================================

--светлая стена шипов
function Skill306Stub__StateAttack(skill)
	
	local world_tag = GetWorldTag(skill)
	local skill_level = GetSLevel(skill)
	
    SetProbability (skill, 100)
    SetTime (skill, 600000)
    SetRatio (skill, (0.1 + (0.05 * skill_level)) )
    SetValue (skill, (0.02 * skill_level) )
	SetRetort2(skill, 1)
	
	-- Если tag локации 1(мир) или 127(луна)
	-- if world_tag == 1 or world_tag == 127 then
	-- 	SetRetort3(skill, 1) -- то шипы друида работают.
	-- else
	-- 	SetRetort2(skill, 1) -- если нет, то не дефолт.
	-- end
	
	if lua_debug == 1 then mylogfunc("Skill306Stub__StateAttack: world_tag = "..int(world_tag)) end
	return 1
end

--светлая стена шипов
function Skill648Stub__StateAttack(skill)
	
	local world_tag = GetWorldTag(skill)
	
    SetProbability (skill, 100)
    SetTime (skill, 1200000)
    SetRatio (skill, 0.6)
    SetValue (skill, 0.25)
	SetRetort2(skill, 1)
	
	-- Если tag локации 1(мир) или 127(луна)
	--if world_tag == 1 or world_tag == 127 then
	--	SetRetort3(skill, 1) -- то шипы друида работают.
	--else
	--	SetRetort2(skill, 1) -- если нет, то не дефолт.
	--end
	
	if lua_debug == 1 then mylogfunc("Skill648Stub__StateAttack: world_tag = "..int(world_tag)) end
	return 1
end

--темная стена шипов
function Skill649Stub__StateAttack(skill)
	
	local world_tag = GetWorldTag(skill)
	
	SetProbability(skill, 100)
    SetTime(skill, 900000)
    SetRatio(skill,0.75)
    SetValue(skill,0.25)
	SetRetort2(skill, 1)
	
	-- Если tag локации 1(мир) или 127(луна)
	--if world_tag == 1 or world_tag == 127 then
	--	SetRetort3(skill, 1) -- то шипы друида работают.
	--else
	--	SetRetort2(skill, 1) -- если нет, то не дефолт.
	--end
	
	if lua_debug == 1 then mylogfunc("Skill649Stub__StateAttack: world_tag = "..int(world_tag)) end
	return 1
end

--редактор скиллов 
function LUA_CSKILL_EDITOR()

	-- id , param , value 
	-- param == 0 -- выключить скилл
	-- param == 1 -- добавить скилл в редактор луа 
	-- будет дополнятся 
	
	-- чтобы добавить скилл в редактор нужно создать следующую функцию - game__AddSkill(int ID, int FUNC, int STATE, int SKILL, int REID)
	-- ID(int) - ид скилла ; FUNC(int32 mask) - Выполняемые функции , STATE(int32 mask) -  Хук функции State ; SKILL(int32 mask) - Хук функции SkillStub ; REID(int) - Замена умения на другое

	game__AddSkill(306, FUNC_SKILL, 0, SKILL_STATEATTACK, 0)
	game__AddSkill(648, FUNC_SKILL, 0, SKILL_STATEATTACK, 0)
	game__AddSkill(649, FUNC_SKILL, 0, SKILL_STATEATTACK, 0)

	if lua_debug == 1 then mylogfunc("LUA_CSKILL_EDITOR OK!") end
	return 1
end

--======================================================================================
--Функции выполняемые при инициализации
--======================================================================================

--Инициализация функций конфигураций
function InitLuaConfig()


	LUA_CSKILL_EDITOR()
end


--======================================================================================
--EVENTS ON SERVER
--======================================================================================

--		void Init();
--		void Update();
--		void HeartBeat();

--		double Skill[ID]Stub__StateAttack(size_t skill);
--		double Skill[ID]Stub__BlessMe(size_t skill);
--		double Skill[ID]Stub__GetExecutetime(size_t skill);
--		double Skill[ID]Stub__GetCoolingtime(size_t skill);
--		double Skill[ID]Stub__GetEnmity(size_t skill);
--		double Skill[ID]Stub__GetRequiredSp(size_t skill);
--		double Skill[ID]Stub__GetRequiredLevel(size_t skill);
--		double Skill[ID]Stub__GetRequiredItem(size_t skill);
--		double Skill[ID]Stub__GetRequiredMoney(size_t skill);
--		double Skill[ID]Stub__GetMaxability(size_t skill);
--		double Skill[ID]Stub__GetRequiredRealmLevel(size_t skill);
--		double Skill[ID]Stub__GetRadius(size_t skill);
--		double Skill[ID]Stub__GetAttackdistance(size_t skill);
--		double Skill[ID]Stub__GetAngle(size_t skill);
--		double Skill[ID]Stub__GetPraydistance(size_t skill);
--		double Skill[ID]Stub__GetEffectdistance(size_t skill);
--		double Skill[ID]Stub__GetT0(size_t skill);
--		double Skill[ID]Stub__GetT1(size_t skill);
--		double Skill[ID]Stub__GetT2(size_t skill);
--		double Skill[ID]Stub__GetAttackspeed(size_t skill);
--		double Skill[ID]Stub__TakeEffect(size_t skill);
--		double Skill[ID]Stub__GetHitrate(size_t skill);

-- 		double Skill[ID]Stub__State[STATE_ID]__GetTime(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Quit(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Loop(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Bypass(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Calculate(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Interrupt(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Cancel(size_t skill);
-- 		double Skill[ID]Stub__State[STATE_ID]__Skip(size_t skill);
--		void Skill[ID]__Create(size_t skill)

-- загрузка скрипта
function Init()

	InitLuaConfig()
	if lua_debug == 1 then mylogfunc("LUA: EVENT=Init ") end
end

-- обновление скрипта
function Update()

	InitLuaConfig()
	if lua_debug == 1 then mylogfunc("LUA: EVENT=Update ") end
end

-- счётчик луа движка 
function HeartBeat(tick)

	--if lua_debug == 1 then mylogfunc("LUA: EVENT=HeartBeat , tick="..tick) end
end

