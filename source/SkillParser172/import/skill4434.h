/*Skill Parser (c)Deadraky 2022 
44340  "Великое сияние меча"
44341  "^ff5c00Великое сияние меча

^ffcb4aМаг. энергия: ^96f5ff50^ffffff
^ffcb4aПодготовка: ^ffffffмгновенно
^ffcb4aПерезарядка: ^ffffff60,0^ffcb4a сек.
^ffcb4aПолучение ци: ^ffffff0,1
^ffcb4aХарактеристика: ^ff5c00Храбрость

^ffcb4aСтатус: ^ffffffМудрец
Сокращает время подготовки заклинаний на ^96f5ff85%%^ffffff и повышает меткость на ^96f5ff300%%^ffffff на ^96f5ff11^ffffff сек.
В течение ^96f5ff5^ffffff сек. вероятность избежать наложения негативных эффектов повышается на ^96f5ff50%%^ffffff.

^ff0000Эффект рубиновой руны:@1
^ff00001-4 ур.: сокращает время подготовки заклинаний в течение ^96f5ff18^ff0000 сек.,
вероятность избежать наложения негативных эффектов действует в течение ^96f5ff8^ff0000 сек.
^ff00005-7 ур.: сокращает время подготовки заклинаний в течение ^96f5ff20^ff0000 сек.,
вероятность избежать наложения негативных эффектов действует в течение ^96f5ff9^ff0000 сек.
^ff00008-9 ур.: сокращает время подготовки заклинаний в течение ^96f5ff22^ff0000 сек.,
вероятность избежать наложения негативных эффектов действует в течение ^96f5ff10^ff0000 сек.
 ^ff000010 ур.: сокращает время подготовки заклинаний в течение ^96f5ff24^ff0000 сек.,
вероятность избежать наложения негативных эффектов действует в течение ^96f5ff11^ff0000 сек.@1@2
^ff0000Сокращает время подготовки заклинаний в течение ^96f5ff%d^ff0000 сек.,
вероятность избежать наложения негативных эффектов действует в течение ^96f5ff%d^ff0000 сек.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4434 
#define __CPPGEN_GNET_SKILL4434 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4434:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4434 }; 
        Skill4434 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4434Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 0;
            }
            bool Quit (Skill * skill) const
            {
                return false;
            }
            bool Loop (Skill * skill) const
            {
                return false;
            }
            bool Bypass (Skill * skill) const
            {
                return false;
            }
            void Calculate (Skill * skill) const
            {
                skill->GetPlayer ()->SetDecmp (50);
                skill->GetPlayer ()->SetPerform (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return false;
            }
            bool Cancel (Skill * skill) const
            {
                return 0;
            }
            bool Skip (Skill * skill) const
            {
                return 0;
            }
        };
#endif 
    Skill4434Stub ():SkillStub (4434) 
    { 
        cls                 = 8; 
        name                = L"神·剑心通明"; 
        nativename          = "神·剑心通明"; 
        icon                = "神剑心通明红.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1105; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 10; 
        doenchant           = 1; 
        dobless             = 0; 
        arrowcost           = 0; 
        allow_land          = 1; 
        allow_air           = 1; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 0; 
        time_type           = 1; 
        long_range          = 0; 
        posdouble           = 0; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        itemcostcount       = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
        effect              = "剑灵_剑心通明.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "状态持续时间增长1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (1); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetRadius (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (0));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 50,50,50,50,50,50,50,50,50,50 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCoolDownLimit (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCostShieldEnergy (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
#ifdef _SKILL_CLIENT 
    int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format);
        }
#endif 
#ifdef _SKILL_SERVER 
    int GetEnmity (Skill * skill) const
        {
            return 0;
        }    
#endif 
#ifdef _SKILL_SERVER 
    int GetMaxAbility (Skill * skill) const 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
		bool StateAttack (Skill * skill) const
        {
			/**
			^ff00001-4 ур.: сокращает время подготовки заклинаний в течение ^96f5ff18^ff0000 сек.,
			вероятность избежать наложения негативных эффектов действует в течение ^96f5ff8^ff0000 сек.
			^ff00005-7 ур.: сокращает время подготовки заклинаний в течение ^96f5ff20^ff0000 сек.,
			вероятность избежать наложения негативных эффектов действует в течение ^96f5ff9^ff0000 сек.
			^ff00008-9 ур.: сокращает время подготовки заклинаний в течение ^96f5ff22^ff0000 сек.,
			вероятность избежать наложения негативных эффектов действует в течение ^96f5ff10^ff0000 сек.
			^ff000010 ур.: сокращает время подготовки заклинаний в течение ^96f5ff24^ff0000 сек.,
			вероятность избежать наложения негативных эффектов действует в течение ^96f5ff11^ff0000 сек.@1@2
			^ff0000Сокращает время подготовки заклинаний в течение ^96f5ff%d^ff0000 сек.,
			вероятность избежать наложения негативных эффектов действует в течение ^96f5ff%d^ff0000 сек.
			*/
			static const int LEVEL_1_4 = 7000;
			static const int LEVEL_5_7 = 9000;
			static const int LEVEL_8_9 = 11000;
			static const int LEVEL_10_10 = 13000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (11010 + ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetRatio (0.85);			
            skill->GetVictim ()->SetFastpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (11000);
            skill->GetVictim ()->SetRatio (3.0);
            skill->GetVictim ()->SetIncaccuracy (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4a = 2000;
			static const int LEVEL_5_7a = 3000;
			static const int LEVEL_8_9a = 4000;
			static const int LEVEL_10_10a = 5000;
			static int aarray123[10] = { LEVEL_1_4a, LEVEL_1_4a, LEVEL_1_4a, LEVEL_1_4a, LEVEL_5_7a, LEVEL_5_7a, LEVEL_5_7a, LEVEL_8_9a, LEVEL_8_9a, LEVEL_10_10a };				
            skill->GetVictim ()->SetTime (6000 + ( aarray123[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetIncdebuffdodge (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
bool BlessMe (Skill * skill) const
        {            
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
        }		
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent0 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent1 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent2 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent3 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent4 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    int GetAttackspeed (Skill * skill) const 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetHitrate (Skill * skill) const
        {
            return (float) (0);
        }
#endif 
#ifdef _SKILL_SERVER 
    void ComboSkEndAction (Skill * skill) const 
    { 
        return; 
    } 
#endif 
    }; 
} 
#endif 
