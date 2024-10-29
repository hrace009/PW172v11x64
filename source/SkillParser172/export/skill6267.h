//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
62670  "Великая душа прилива"62671  "^ff5c00Великая душа прилива^ffcb4aМаг. энергия: ^96f5ff405^ffffff^ffcb4aПодготовка: ^ffffffмгновенно^ffcb4aПерезарядка: ^ffffff60 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffмагическая сфера^ffcb4aХарактеристика: ^ff5c00Храбрость^ffcb4aСтатус: ^ffffffМудрецУвеличивает магический урон от оружия на ^96f5ff100%%^ffffff на ^96f5ff15^ffffff сек.На ^96f5ff9^ffffff сек. увеличивает скорость подготовки заклинаний.Увеличивает шанс нанесения критического удара на ^96f5ff20%%^ffffff на ^96f5ff15^ffffff сек.Это умение конфликтует с умением джиннов 'Благословение радуги'.^a6caf0Дополнительная стоимость: ^ffffff2^a6caf0 ци.^00ffffЭффект сапфировой руны:@1^00ffff1-4 ур.: увеличивает скорость подготовки заклинаний на ^FFFFFF10^00ffff сек.^00ffff5-7 ур.: увеличивает скорость подготовки заклинаний на ^FFFFFF11^00ffff сек.^00ffff8-9 ур.: увеличивает скорость подготовки заклинаний на ^FFFFFF12^00ffff сек. ^00ffff10 ур.: увеличивает скорость подготовки заклинаний на ^FFFFFF13^00ffff сек.@1@2^00ffffУвеличивает скорость подготовки заклинаний на ^FFFFFF%d^00ffff сек.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL6267 
#define __CPPGEN_GNET_SKILL6267 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6267:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6267 }; 
        Skill6267 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6267Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 667;
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
                skill->GetPlayer ()->SetDecmp (81);
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
    Skill6267Stub ():SkillStub (6267) 
    { 
        cls                 = 2; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤳�ϫ����"; 
        nativename          = "�񡤳�ϫ����"; 
        icon                = "�񡤳�ϫ������.dds"; 
#endif 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 4; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1719; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 0; 
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
        long_range          = 1; 
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
        effect              = "��.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(1252, 1)); 
        pre_skills.push_back (std::pair < ID, int >(1253, 1)); 
        restrict_weapons.push_back (25333); 
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
        static int aarray[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 99,99,99,99,99,99,99,99,99,99 }; 
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
        static float aarray[10] = { 405,405,405,405,405,405,405,405,405,405 }; 
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
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetShowicon (0);
            skill->GetVictim ()->SetIncmagic2 (1);
			/*
			^00ffff1-4 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���էԧ���ӧܧ� �٧ѧܧݧڧߧѧߧڧ� �ߧ� ^FFFFFF10^00ffff ��֧�.
			^00ffff5-7 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���էԧ���ӧܧ� �٧ѧܧݧڧߧѧߧڧ� �ߧ� ^FFFFFF11^00ffff ��֧�.
			^00ffff8-9 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���էԧ���ӧܧ� �٧ѧܧݧڧߧѧߧڧ� �ߧ� ^FFFFFF12^00ffff ��֧�.
			^00ffff10 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���էԧ���ӧܧ� �٧ѧܧݧڧߧѧߧڧ� �ߧ� ^FFFFFF13^00ffff ��֧�.
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 11000;
			static const int LEVEL_5_7 = 12000;
			static const int LEVEL_8_9 = 13000;
			static const int LEVEL_10_10 = 14000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };								
            skill->GetVictim ()->SetTime ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetFastpray (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetValue (20);
            skill->GetVictim ()->SetIncsmite (1);	
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const 
    { 
        return 1; 
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
            return 4;
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
