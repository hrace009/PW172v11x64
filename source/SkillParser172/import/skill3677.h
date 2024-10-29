/*Skill Parser (c)Deadraky 2022 
36770  "Великие крылья феникса"
36771  "^ff5c00Великие крылья феникса

^ffcb4aДальность: ^ff5c0030 ^ffcb4aм
^ffcb4aМаг. энергия: ^96f5ff%d^ffffff
^ffcb4aПодготовка: ^ffffff1 ^ffcb4aсек.
^ffcb4aПрименение: ^ffffff1 ^ffcb4aсек.
^ffcb4aПерезарядка: ^ff5c0015 ^ffcb4aсек.
^ffcb4aПолучение ци: ^ffffff0,15
^ffcb4aОграничение по оружию: ^ffffffмагическое оружие, без оружия
^ffcb4aХарактеристика: ^ff5c00Мудрость

^ffcb4aСтатус: ^ffffffАсура
Маг призывает феникса, который атакует противника и отбрасывает его на ^96f5ff18^ffffff м.
Наносит базовый магический урон, плюс ^96f5ff100%%^ffffff урона оружия,
плюс ^96f5ff5395^ffffff ед. урона стихией огня.

Отталкивание не действует на игроков.

^ffeaabЭффект серебряной руны:@1
^ffeaab1-4 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff40%%
^ffeaab5-7 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff60%%
^ffeaab8-9 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff80%%
^ffeaab 10 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff100%%@1@2
^ffeaabВ течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff%d%%.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3677 
#define __CPPGEN_GNET_SKILL3677 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3677:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3677 }; 
        Skill3677 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3677Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1000;
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
                skill->GetPlayer ()->SetDecmp (89);
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return skill->GetRand () < 5;
            }
            bool Cancel (Skill * skill) const
            {
                return 1;
            }
            bool Skip (Skill * skill) const
            {
                return 0;
            }
        };
#endif 
#ifdef _SKILL_SERVER 
        class State2:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1000;
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
                skill->GetPlayer ()->SetDecmp (356);
                skill->SetPlus (5395);
                skill->SetRatio (1);
                skill->SetFiredamage (skill->GetMagicattack ());
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
#ifdef _SKILL_SERVER 
        class State3:public SkillStub::State
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
    Skill3677Stub ():SkillStub (3677) 
    { 
        cls                 = 1; 
        name                = L"ЙсЎ¤БТ»рігТн"; 
        nativename          = "ЙсЎ¤БТ»рігТн"; 
        icon                = "ЙсЎ¤БТ»рігТн°Ч.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 5; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1206; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 15; 
        doenchant           = 1; 
        dobless             = 1; 
        arrowcost           = 0; 
        allow_land          = 1; 
        allow_air           = 1; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 0; 
        time_type           = 0; 
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
        effect              = "1СЧЛч.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "ХэГжЧґМ¬Р§№ыФцЗї2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 104; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
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
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetRadius (Skill * skill) const
    {
            return (float) (8);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (38);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (0));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (30);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 445,445,445,445,445,445,445,445,445,445 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetValue (18);
            skill->GetVictim ()->SetRepel (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
bool BlessMe (Skill * skill) const
        {            
			/**
			^ffeaab1-4 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff40%%
			^ffeaab5-7 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff60%%
			^ffeaab8-9 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff80%%
			^ffeaab 10 ур.: в течение ^96f5ff6^ffeaab сек. скорость подготовки ^96f5ffВеликого зыбучего песка^ffeaab сокращается на ^96f5ff100%%
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);
			static const float LEVEL_1_4 = 0.6;
			static const float LEVEL_5_7 = 0.4;
			static const float LEVEL_8_9 = 0.2;
			static const float LEVEL_10_10 = 0.001;
			static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };				
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3684);
            skill->GetVictim ()->SetModifyspecskillpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);			
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3685);
            skill->GetVictim ()->SetModifyspecskillpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);			
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3686);
            skill->GetVictim ()->SetModifyspecskillpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3687);
            skill->GetVictim ()->SetModifyspecskillpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3688);
            skill->GetVictim ()->SetModifyspecskillpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3689);
            skill->GetVictim ()->SetModifyspecskillpray (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (20);
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
            return (float) (1);
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
