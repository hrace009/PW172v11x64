/*Skill Parser (c)Deadraky 2022 
62690  "���֧ݧڧܧѧ� �է��� ���ڧݧڧӧ�"
62691  "^ff5c00���֧ݧڧܧѧ� �է��� ���ڧݧڧӧ�

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff405^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff60 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����ѧҧ�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ӧ֧ݧڧ�ڧӧѧ֧� �ާѧԧڧ�֧�ܧڧ� ����� ��� ����اڧ� �ߧ� ^96f5ff100%%^ffffff �ߧ� ^96f5ff15^ffffff ��֧�.
���� ^96f5ff9^ffffff ��֧�. ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���էԧ���ӧܧ� �٧ѧܧݧڧߧѧߧڧ�.
���ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff20%%^ffffff �ߧ� ^96f5ff15^ffffff ��֧�.
����� ��ާ֧ߧڧ� �ܧ�ߧ�ݧڧܧ��֧� �� ��ާ֧ߧڧ֧� �էاڧߧߧ�� '���ݧѧԧ��ݧ�ӧ֧ߧڧ� ��ѧէ�ԧ�'.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���.

^ffeaab�����֧ܧ� ��֧�֧ҧ��ߧ�� ���ߧ�:@1
^ffeaab1-4 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff25%%^ffeaab
^ffeaab5-7 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff30%%^ffeaab
^ffeaab8-9 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff35%%^ffeaab
^ffeaab 10 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff40%%^ffeaab@1@2
���ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff%d%%^ffeaab.@2"
*/
#ifndef __CPPGEN_GNET_SKILL6269 
#define __CPPGEN_GNET_SKILL6269 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6269:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6269 }; 
        Skill6269 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6269Stub:public SkillStub 
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
    Skill6269Stub ():SkillStub (6269) 
    { 
        cls                 = 2; 
        name                = L"�񡤳�ϫ����"; 
        nativename          = "�񡤳�ϫ����"; 
        icon                = "�񡤳�ϫ�����.dds"; 
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
        effect              = "��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetFastpray (1);						
			/*
			^ffeaab1-4 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff25%%^ffeaab
			^ffeaab5-7 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff30%%^ffeaab
			^ffeaab8-9 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff35%%^ffeaab
			^ffeaab 10 ���.: ��ӧ֧ݧڧ�ڧӧѧ֧� ��ѧߧ� �ߧѧߧ֧�֧ߧڧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff40%%^ffeaab
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (16000);
			static const int LEVEL_1_4 = 5;
			static const int LEVEL_5_7 = 10;
			static const int LEVEL_8_9 = 15;
			static const int LEVEL_10_10 = 20;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };					
            skill->GetVictim ()->SetValue (20 + ( aarray[skill->GetLevel () - 1] ));
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
