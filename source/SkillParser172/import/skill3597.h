/*Skill Parser (c)Deadraky 2022 
35970  "���֧ݧڧܧ�� ����ܧݧ��ڧ� �է���� �٧֧ާݧ�"
35971  "^ff5c00���֧ݧڧܧ�� ����ܧݧ��ڧ� �է���� �٧֧ާݧ�

^ffcb4a���ѧݧ�ߧ����: ^96f5ff28,5^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff680^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff1 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff20 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff�������
����٧�ӧѧ֧� �է���� �٧֧ާݧ�, �ܧ������ �ߧѧ�ѧէѧ�� �ߧ� �����ڧӧߧڧܧ�� �� ��ѧէڧ��� ^96f5ff6^ffffff ��
�� �ߧѧߧ���� �ڧ� �ҧѧ٧�ӧ�� �ާѧԧڧ�֧�ܧڧ� �����, ��ݧ�� ^96f5ff200%%^ffffff
����ߧ� ����اڧ�, ��ݧ�� ^96f5ff3987^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �٧֧ާݧ�.
^ffffff���ԧݧ��ѧ֧� �����ڧӧߧڧܧ�� �ߧ� ^96f5ff4^ffffff ��֧�. �� �ߧѧܧݧѧէ�ӧѧ֧� �ߧ� �ߧڧ� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �ӧ�֧ާ�, �ܧ������ �٧ѧӧڧ�ڧ� ��� ����ӧߧ� ���ߧ�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff1^a6caf0 ���.
^a6caf0�����ݧ� ���ڧާ֧ߧ֧ߧڧ� �ӧ����ѧߧѧӧݧڧӧѧ֧��� ^ffffff0,5^a6caf0 ���.

^00ffff�����֧ܧ� ��ѧ��ڧ��ӧ�� ���ߧ�:@1
^00ffff1-4 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff0,5^00ffff ��֧�.
^00ffff5-7 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff1,5^00ffff ��֧�.
^00ffff8-9 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff2,5^00ffff ��֧�.
^00ffff 10 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff3,5^00ffff ��֧�.@1@2
���ѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff%.1f^00ffff ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3597 
#define __CPPGEN_GNET_SKILL3597 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3597:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3597 }; 
        Skill3597 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3597Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (136);
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
                skill->GetPlayer ()->SetDecmp (544);
                skill->SetPlus (3987.1);
                skill->SetRatio (2);
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
    Skill3597Stub ():SkillStub (3597) 
    { 
        cls                 = 2; 
        name                = L"�񡤴��������"; 
        nativename          = "�񡤴��������"; 
        icon                = "�񡤴����������.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 6; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1721; 
        allow_forms         = 1; 
        apcost              = 100; 
        apgain              = 50; 
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
        effect              = "��ʦ_����.sgc"; 
        aerial_effect       = ""; 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "����״̬Ч����ǿ2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
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
        static int aarray[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 20000,20000,20000,20000,20000,20000,20000,20000,20000,20000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 }; 
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
        static float aarray[10] = { 680,680,680,680,680,680,680,680,680,680 }; 
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
			/*
			^00ffff1-4 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff0,5^00ffff ��֧�.
			^00ffff5-7 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff1,5^00ffff ��֧�.
			^00ffff8-9 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff2,5^00ffff ��֧�.
			^00ffff 10 ���.: �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� �����ڧӧߧڧܧ�� �ߧ� ^ffffff3,5^00ffff ��֧�
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (5000);
            skill->GetVictim ()->SetDizzy (1);
				static const int LEVEL_1_4 = 1500;
				static const int LEVEL_5_7 = 2500;
				static const int LEVEL_8_9 = 3500;
				static const int LEVEL_10_10 = 4500;
				static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };								
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetSealed (1);
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
            return (float) (40.6);
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
