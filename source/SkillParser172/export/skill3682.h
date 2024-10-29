//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
36820  "Великий ливень"36821  "^ff5c00Великий ливень^ffcb4aДальность: ^96f5ff%d^ffffff ^ffcb4aм^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffff1,8 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,2 ^ffcb4aсек.^ffcb4aПерезарядка: ^ff5c0015 ^ffcb4aсек.^ffcb4aПолучение ци: ^ffffff0,05^ffcb4aОграничение по оружию: ^ffffffмагическое оружие, без оружия^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffМудрецМаг обрушивает на окружающих противников смертоносный ливень,нанося базовый магический урон плюс ^96f5ff4740^ffffff ед. урона стихией воды.С вероятностью ^96f5ff50%%^ffffff обездвиживает противников на ^96f5ff4^ffffff сек.^ff0000Эффект рубиновой руны:@1^ff00001-4 ур.: в течение ^96f5ff6^ff0000 сек. скорость подготовки ^96f5ffВеликих крыльев феникса^ff0000 сокращается на ^96f5ff40%%^ff00005-7 ур.: в течение ^96f5ff6^ff0000 сек. скорость подготовки ^96f5ffВеликих крыльев феникса^ff0000 сокращается на ^96f5ff60%%^ff00008-9 ур.: в течение ^96f5ff6^ff0000 сек. скорость подготовки ^96f5ffВеликих крыльев феникса^ff0000 сокращается на ^96f5ff80%%^ff0000 10 ур.: в течение ^96f5ff6^ff0000 сек. скорость подготовки ^96f5ffВеликих крыльев феникса^ff0000 сокращается на ^96f5ff100%%@1@2^ff0000В течение ^96f5ff6^ff0000 сек. скорость подготовки ^96f5ffВеликих крыльев феникса^ff0000 сокращается на ^96f5ff%d%%.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3682 
#define __CPPGEN_GNET_SKILL3682 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3682:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3682 }; 
        Skill3682 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3682Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1800;
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
                skill->GetPlayer ()->SetDecmp (64);
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
                return 1200;
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
                skill->GetPlayer ()->SetDecmp (256);
                skill->SetPlus (4740);
                skill->SetRatio (0);
                skill->SetWaterdamage (skill->GetMagicattack ());
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
    Skill3682Stub ():SkillStub (3682) 
    { 
        cls                 = 1; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤱���"; 
        nativename          = "�񡤱���"; 
        icon                = "�񡤱�����.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 4; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1211; 
        allow_forms         = 3; 
        apcost              = 0; 
        apgain              = 5; 
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
#ifdef _SKILL_CLIENT 
        effect              = "�±���.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
#endif 
        gfxtarget           = 0; 
        feature             = 105; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (292); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1200,1200,1200,1200,1200,1200,1200,1200,1200,1200 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
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
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
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
            return (float) (4 + 0.4 * skill->GetLevel ());
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
        static float aarray[10] = { 320,320,320,320,320,320,320,320,320,320 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 50);
            skill->GetVictim ()->SetTime (5000);
            skill->GetVictim ()->SetFix (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
bool BlessMe (Skill * skill) const
        {       
			/**
			^ff00001-4 ���.: �� ��֧�֧ߧڧ� ^96f5ff6^ff0000 ��֧�. ��ܧ������ ���էԧ���ӧܧ� ^96f5ff���֧ݧڧܧڧ� �ܧ���ݧ�֧� ��֧ߧڧܧ��^ff0000 ���ܧ�ѧ�ѧ֧��� �ߧ� ^96f5ff40%%
			^ff00005-7 ���.: �� ��֧�֧ߧڧ� ^96f5ff6^ff0000 ��֧�. ��ܧ������ ���էԧ���ӧܧ� ^96f5ff���֧ݧڧܧڧ� �ܧ���ݧ�֧� ��֧ߧڧܧ��^ff0000 ���ܧ�ѧ�ѧ֧��� �ߧ� ^96f5ff60%%
			^ff00008-9 ���.: �� ��֧�֧ߧڧ� ^96f5ff6^ff0000 ��֧�. ��ܧ������ ���էԧ���ӧܧ� ^96f5ff���֧ݧڧܧڧ� �ܧ���ݧ�֧� ��֧ߧڧܧ��^ff0000 ���ܧ�ѧ�ѧ֧��� �ߧ� ^96f5ff80%%
			^ff0000 10 ���.: �� ��֧�֧ߧڧ� ^96f5ff6^ff0000 ��֧�. ��ܧ������ ���էԧ���ӧܧ� ^96f5ff���֧ݧڧܧڧ� �ܧ���ݧ�֧� ��֧ߧڧܧ��^ff0000 ���ܧ�ѧ�ѧ֧��� �ߧ� ^96f5ff100%
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
            skill->GetVictim ()->SetValue (3672);
            skill->GetVictim ()->SetModifyspecskillpray (1);

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3673);
            skill->GetVictim ()->SetModifyspecskillpray (1);		

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3674);
            skill->GetVictim ()->SetModifyspecskillpray (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3677);
            skill->GetVictim ()->SetModifyspecskillpray (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3675);
            skill->GetVictim ()->SetModifyspecskillpray (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);		
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (3676);
            skill->GetVictim ()->SetModifyspecskillpray (1);				
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (36);
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
