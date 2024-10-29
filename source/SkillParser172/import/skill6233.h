/*Skill Parser (c)Deadraky 2022 
62330  "���֧ݧڧܧڧ� �ӧ�٧��"
62331  "^ff5c00���֧ݧڧܧڧ� �ӧ�٧��

^ffcb4a���ѧݧ�ߧ����: ^96f5ff%d^ffffff^ffcb4a ��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,2^ffcb4a ��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1,1^ffcb4a ��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff8^ffcb4a ��֧�.
^ffcb4a����ݧ��֧ߧڧ� ���: ^ffffff0,1
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff������� �� �ާ�ݧ���
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
����ҧ�ѧ� �ӧ�ݧ� �� �ܧ�ݧѧ�, ��ҧ����֧ߧ� �ҧ���ѧ֧��� �ߧ� �����ڧӧߧڧܧ� �� ��ѧ�����ߧڧ� �է� ^96f5ff12^ffffff ��.
���էѧ� �ߧѧߧ��ڧ� �ҧѧ٧�ӧ�� �����, ��ݧ�� ^96f5ff100%%^ffffff ��ڧ٧ڧ�֧�ܧ�ԧ� ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff5516^ffffff �֧�. ��ڧ٧ڧ�֧�ܧ�ԧ� ����ߧ�
�� ��ߧڧاѧ֧� ������ҧߧ���� ��֧ݧ� �� ��ܧݧ�ߧ֧ߧڧ� �ߧ� ^96f5ff50%%^ffffff �ߧ� ^96f5ff8^ffffff ��֧�.
���� ^96f5ff6^ffffff ��֧�. ���ӧ��ѧ֧� ��ѧߧ� �ܧ�ڧ�ڧ�֧�ܧ�ԧ� ��էѧ�� �ߧ� ^96f5ff40%%^ffffff.
����ڧާ֧ߧ֧ߧڧ� �ߧѧӧ�ܧ� '���ӧ֧�ڧߧ�� �ާ�ݧ��' �� ��֧�֧ߧڧ� ^96f5ff6^ffffff ��֧�. �ߧѧߧ��ڧ� �ܧ�ڧ�ڧ�֧�ܧڧ� �����.

���� ����ާѧ�ڧӧѧ֧���.

^00ffff�����֧ܧ� ��ѧ��ڧ��ӧ�� ���ߧ�:@1
^00ffff1-4 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,15^00ffff
^00ffff5-7 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,2^00ffff
^00ffff8-9 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,25^00ffff
^00ffff 10 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,3^00ffff@1@2
^00ffff����ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,%d^00ffff.@2"
*/
#ifndef __CPPGEN_GNET_SKILL6233 
#define __CPPGEN_GNET_SKILL6233 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6233:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6233 }; 
        Skill6233 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6233Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 200;
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
                skill->GetPlayer ()->SetDecmp (24);
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return false;
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
                return 1100;
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
                skill->GetPlayer ()->SetDecmp (96);
                skill->SetPlus (5516);
                skill->SetRatio (1);
                skill->SetDamage (skill->GetAttack ());
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
    Skill6233Stub ():SkillStub (6233) 
    { 
        cls                 = 4; 
        name                = L"�������޵�"; 
        nativename          = "�������޵�"; 
        icon                = "�������޵���.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1508; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 10; 
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
        effect              = "1�����޵�.sgc"; 
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
        pre_skills.push_back (std::pair < ID, int >(2420, 1)); 
        pre_skills.push_back (std::pair < ID, int >(2421, 1)); 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1100,1100,1100,1100,1100,1100,1100,1100,1100,1100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 8000,8000,8000,8000,8000,8000,8000,8000,8000,8000 }; 
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
        static int aarray[10] = { 68912,68912,68912,68912,68912,68912,68912,68912,68912,68912 }; 
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
            return (float) (skill->GetPlayer ()->GetRange () + 0.2 * skill->GetLevel ());
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 4 + 0.3 * skill->GetLevel ());
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1 - 0.0111111 * (20 + 2.5 * skill->GetLevel ()));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (12 + skill->GetPlayer ()->GetRange () - 3.5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 120,120,120,120,120,120,120,120,120,120 }; 
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
            return _snwprintf (buffer, length, format, 12, 120);

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
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetDecdodge (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        bool BlessMe (Skill * skill) const
        {
			/*
			^00ffff1-4 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,15^00ffff
			^00ffff5-7 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,2^00ffff
			^00ffff8-9 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,25^00ffff
			^00ffff 10 ���.: ���ݧ��֧ߧڧ� ��� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^ffffff0,3^00ffff
			*/
			static const int LEVEL_1_4 = 5;
			static const int LEVEL_5_7 = 10;
			static const int LEVEL_8_9 = 15;
			static const int LEVEL_10_10 = 20;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetValue ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetAp (1);				
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetValue (40);
            skill->GetVictim ()->SetIncsmite (1);
			
			// �� ��֧�֧ߧڧ� 7 ��֧� ��ܧڧݧ� "���֧ݧڧܧڧ� �٧ӧ֧�ڧߧ�� �ާ�ݧ��" (�� �ܧѧاէ�� ���ߧ��) 100% �ܧ�ڧ��֧�
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3835);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3836);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3837);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3838);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);		

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3839);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);	

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (3840);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (200);
            skill->GetVictim ()->SetInccountedsmite (1);				
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (25 + skill->GetPlayer ()->GetRange () - 3.5);
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
            return 5;
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
            return (float) (2.5);
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
