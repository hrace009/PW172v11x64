/*Skill Parser (c)Deadraky 2022 
54700  "���֧ݧڧܧѧ� ���֧ӧ�ԧ� �է���"
54701  "^ff5c00���֧ݧڧܧѧ� ���֧ӧ�ԧ� �է���

^ffcb4a���ѧݧ�ߧ����: ^96f5ff28,5^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff285^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff1,6 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1,2 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff30,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
����ڧӧ�էڧ� �����ڧӧߧڧܧ� �� ��ާ��֧ߧڧ�. ���ѧߧ��ڧ� ��֧ݧ� �ҧѧ٧�ӧ�� �ާѧԧڧ�֧�ܧڧ� �����,
��ݧ�� ^96f5ff220%%^ffffff ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff9736^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �ӧ�է�.
���ӧ֧ݧڧ�ڧӧѧ֧� �ӧ�֧ާ� ���էԧ���ӧܧ� ��ާ֧ߧڧ� �����ڧӧߧڧܧ� �ߧ� ^96f5ff100%%^ffffff �ߧ� ^96f5ff15^ffffff ��֧�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff0,3^a6caf0 ���.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff50%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff100%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff150%%^ffcb4a ����ߧ� ����اڧ�
 ^ffcb4a10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff200%%^ffcb4a ����ߧ� ����اڧ�@1@2
�� �ߧѧߧ��ڧާ�ާ� ����ߧ� �է�ҧѧӧݧ�֧��� ^96f5ff%d%%^ffcb4a ����ߧ� ����اڧ�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL5470 
#define __CPPGEN_GNET_SKILL5470 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5470:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5470 }; 
        Skill5470 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5470Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1600;
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
                skill->GetPlayer ()->SetDecmp (57);
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return skill->GetRand () <= 4;
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
				^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff50%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff100%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff150%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff200%%^ffcb4a ����ߧ� ����اڧ�
				*/
                skill->GetPlayer ()->SetDecmp (228);
                skill->SetPlus(9736);
				static const float LEVEL_1_4 = 0.5;
				static const float LEVEL_5_7 = 1.0;
				static const float LEVEL_8_9 = 1.5;
				static const float LEVEL_10_10 = 2.0;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };					
                skill->SetRatio(2.2 + ( aarray[skill->GetLevel () - 1] ));
                skill->SetWaterdamage(skill->GetMagicattack());
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
    Skill5470Stub ():SkillStub (5470) 
    { 
        cls                 = 2; 
        name                = L"�������"; 
        nativename          = "�������"; 
        icon                = "�������ƻ�.dds"; 
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
        showorder           = 1718; 
        allow_forms         = 1; 
        apcost              = 30; 
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
        effect              = "��ʦ_��������.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(3252, 1)); 
        pre_skills.push_back (std::pair < ID, int >(3253, 1)); 
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
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
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
            return (float) (28.5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 285,285,285,285,285,285,285,285,285,285 }; 
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
            skill->GetVictim ()->SetTime (15000);
            skill->GetVictim ()->SetRatio (1.0);
            skill->GetVictim ()->SetSlowpray (1);
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
            return (float) (43.9);
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
