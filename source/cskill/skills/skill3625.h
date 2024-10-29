//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
36250  "Великий водный удар"36251  "^ff5c00Великий водный удар^ffcb4aДальность: ^96f5ff28,5^ffffff^ffcb4a м^ffcb4aМаг. энергия: ^96f5ff320^ffffff^ffcb4aПодготовка: ^ffffff0,5 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,2 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff2 ^ffcb4aсек.^ffcb4aПолучение ци: ^ffffff0,1^ffcb4aОграничение по оружию: ^ffffffмагическая сфера^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffМудрецНаносит базовый магический урон, плюс ^96f5ff100%%^ffffff урона оружия,плюс ^96f5ff3573^ffffff ед. урона стихией воды. Снижает скорость противника на ^96f5ff50%%^ffffff на ^96f5ff8^ffffff сек.С вероятностью ^96f5ff20%%^ffffff снижает ци цели на ^96f5ff0,3^ffffff.Увеличивает шанс нанести монстрам критический удар на ^96f5ff15%%^ffffff.^ffcb4aЭффект золотой руны:@1^ffcb4a1-4 ур.: добавляется ^96f5ff40%%^ffcb4a урона оружия и ^96f5ff1560^ffcb4a ед. урона^ffcb4a5-7 ур.: добавляется ^96f5ff60%%^ffcb4a урона оружия и ^96f5ff2340^ffcb4a ед. урона^ffcb4a8-9 ур.: добавляется ^96f5ff80%%^ffcb4a урона оружия и ^96f5ff3120^ffcb4a ед. урона^ffcb4a 10 ур.: добавляется ^96f5ff100%%^ffcb4a урона оружия и ^96f5ff3900^ffcb4a ед. урона@1@2К наносимому урону добавляется ^96f5ff%d%%^ffcb4a урона оружия и ^96f5ff%d^ffcb4a ед. урона.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3625 
#define __CPPGEN_GNET_SKILL3625 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3625:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3625 }; 
        Skill3625 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3625Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 500;
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
				/*
				^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff40%%^ffcb4a ����ߧ� ����اڧ� �� ^96f5ff1560^ffcb4a �֧�. ����ߧ�
				^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff60%%^ffcb4a ����ߧ� ����اڧ� �� ^96f5ff2340^ffcb4a �֧�. ����ߧ�
				^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff80%%^ffcb4a ����ߧ� ����اڧ� �� ^96f5ff3120^ffcb4a �֧�. ����ߧ�
				^ffcb4a 10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff100%%^ffcb4a ����ߧ� ����اڧ� �� ^96f5ff3900^ffcb4a �֧�. �����
				*/
                skill->GetPlayer ()->SetDecmp (256);				
				static const int LEVEL_1_4 = 1560;
				static const int LEVEL_5_7 = 2340;
				static const int LEVEL_8_9 = 3100;
				static const int LEVEL_10_10 = 3900;
				static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };									
                skill->SetPlus (7573 + ( aarray[skill->GetLevel () - 1] ));				
				static const float LEVEL_1_4A = 0.4;
				static const float LEVEL_5_7B = 0.6;
				static const float LEVEL_8_9C = 0.8;
				static const float LEVEL_10_10D = 1.0;
				static float aarrayB[10] = { LEVEL_1_4A, LEVEL_1_4A, LEVEL_1_4A, LEVEL_1_4A, LEVEL_5_7B, LEVEL_5_7B, LEVEL_5_7B, LEVEL_8_9C, LEVEL_8_9C, LEVEL_10_10D };				
                skill->SetRatio (1.0 + ( aarrayB[skill->GetLevel () - 1] ));
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
    Skill3625Stub ():SkillStub (3625) 
    { 
        cls                 = 2; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤳����"; 
        nativename          = "�񡤳����"; 
        icon                = "�񡤳������.dds"; 
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
        showorder           = 1701; 
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
        effect              = "��_�弼��_����.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "ֱ���˺�����1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (25333); 
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
        static int aarray[10] = { 2000,2000,2000,2000,2000,2000,2000,2000,2000,2000 }; 
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
            return (float) (0);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (120));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (28.5);
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetRatio (0.4);
            skill->GetVictim ()->SetSlow (1);
            skill->GetVictim ()->SetProbability (1.0 * skill->GetPlayer ()->GetCls () == -1 ? 100 : 0);
            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetAmount (15);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetIncbecritrate (1);
            skill->GetVictim ()->SetProbability (1.0 * 20);
            skill->GetVictim ()->SetValue (-30);
            skill->GetVictim ()->SetAp (1);
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
            return (float) (39.5);
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
            return (float) (1.0);
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
