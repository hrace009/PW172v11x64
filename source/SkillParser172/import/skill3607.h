/*Skill Parser (c)Deadraky 2022 
36070  "���֧ݧڧܧ�� ��اѧ�ߧ�� ����ܧݧ��ڧ�"
36071  "^ff5c00���֧ݧڧܧ�� ��اѧ�ߧ�� ����ܧݧ��ڧ�

^ffcb4a���ѧݧ�ߧ����: ^96f5ff28,5^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff750^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff2 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff60 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
����ڧ٧��ӧѧ� �է���� �ԧ��, ��ѧާѧ� �٧ѧ��ѧӧݧ�֧� ��ѧާ� �٧֧ާݧ� ���� �ߧ�ԧѧާ� �����ڧӧߧڧܧ�� ��ҧ�ѧ�ڧ���� �����ڧ� �ߧڧ�.
���ѧߧ��ڧ� �����ڧӧߧڧܧѧ� �� ��ѧէڧ��� ^96f5ff8^ffffff �� �ҧѧ٧�ӧ��� �����, ��ݧ�� ^96f5ff400%%^ffffff ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff15345^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �٧֧ާݧ�.
���ߧڧاѧ֧� ��ܧ������ �ѧ�ѧܧ� �� �ӧ�֧ާ� ���էԧ���ӧܧ� ��ާ֧ߧڧ� �����ڧӧߧڧܧ�� �ߧ� ^96f5ff30%%^ffffff �ߧ� ^96f5ff8^ffffff ��֧�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff70%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff140%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff210%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a 10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff280%%^ffcb4a ����ߧ� ����اڧ�@1@2
�� �ߧѧߧ��ڧާ�ާ� ����ߧ� �է�ҧѧӧݧ�֧��� ^96f5ff%d%%^ffcb4a ����ߧ� ����اڧ�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3607 
#define __CPPGEN_GNET_SKILL3607 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3607:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3607 }; 
        Skill3607 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3607Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 2000;
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
                skill->GetPlayer ()->SetDecmp (150);
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
                skill->GetPlayer ()->SetDecmp (600);
                skill->SetPlus (10253.1);
				/*
				^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff70%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff140%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff210%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a 10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff280%%^ffcb4a ����ߧ� ����اڧ�
				*/
				static const float LEVEL_1_4 = 0.7;
				static const float LEVEL_5_7 = 1.4;
				static const float LEVEL_8_9 = 2.1;
				static const float LEVEL_10_10 = 2.8;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetRatio (4.0 + ( aarray[skill->GetLevel () - 1] ));
                skill->SetEarthdamage (skill->GetMagicattack ());
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
    Skill3607Stub ():SkillStub (3607) 
    { 
        cls                 = 2; 
        name                = L"����ʯ����"; 
        nativename          = "����ʯ����"; 
        icon                = "����ʯ�����.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 6; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2454; 
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
        effect              = "��ʦ_��ʯ����.sgc"; 
        aerial_effect       = ""; 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "ֱ���˺�����1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (25333); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1400,1400,1400,1400,1400,1400,1400,1400,1400,1400 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000 }; 
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
        static int aarray[10] = { 3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000 }; 
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
            return (float) (28.5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 750,750,750,750,750,750,750,750,750,750 }; 
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
            skill->GetVictim ()->SetTime (8000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetSlowpray (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetSlowattack (1);
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
            return (float) (35);
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
