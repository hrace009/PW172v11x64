/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
38690  "���֧ݧڧܧڧ� �٧ѧԧߧѧߧߧ�� �٧ӧ֧��"
38691  "^ff5c00���֧ݧڧܧڧ� �٧ѧԧߧѧߧߧ�� �٧ӧ֧�� 

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff252^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,4^ffcb4a ��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1,6^ffcb4a ��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff300 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff������� �� �ާ�ݧ���
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
���� ^96f5ff5^ffffff ��֧�. ��֧���ߧѧ� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �ܧ� �ӧ�֧� �ߧ֧ԧѧ�ڧӧߧ�� ����֧ܧ�ѧ�.
^ffcb4a����اߧ� ���ڧާ֧ߧڧ�� �� ��ҧݧڧܧ� ��ڧԧ�� �� ��ѧߧէ�.

^ff0000�����֧ܧ� ���ҧڧߧ�ӧ�� ���ߧ�:@1
^ff00001-4 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff40^ff0000 ��֧�.
^ff00005-7 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff50^ff0000 ��֧�.
^ff00008-9 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff60^ff0000 ��֧�.
^ff0000 10 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff70^ff0000 ��֧�.@1@2
^ff0000���ݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff%d^ff0000 ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3869 
#define __CPPGEN_GNET_SKILL3869 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3869:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3869 }; 
        Skill3869 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3869Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 450;
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
                return 2300;
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
                skill->GetPlayer ()->SetDecmp (202);
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
    Skill3869Stub ():SkillStub (3869) 
    { 
        cls                 = 4; 
        name                = L"�񡤲���ս��"; 
        nativename          = "�񡤲���ս��"; 
        icon                = "�񡤲���ս���.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2904; 
        allow_forms         = 3; 
        apcost              = 0; 
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
        effect              = "����_��Х.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "����״̬Ч����ǿ2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 2300,2300,2300,2300,2300,2300,2300,2300,2300,2300 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 300000,300000,300000,300000,300000,300000,300000,300000,300000,300000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000 }; 
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
            return (float) (7);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (180));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (15);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 252,252,252,252,252,252,252,252,252,252 }; 
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
            return 100;
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
			���� ^96f5ff5^ffffff ��֧�. ��֧���ߧѧ� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �ܧ� �ӧ�֧� �ߧ֧ԧѧ�ڧӧߧ�� ����֧ܧ�ѧ�			
			^ff00001-4 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff40^ff0000 ��֧�.
			^ff00005-7 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff50^ff0000 ��֧�.
			^ff00008-9 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff60^ff0000 ��֧�.
			^ff0000 10 ���.: �էݧڧ�֧ݧ�ߧ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff70^ff0000 ��֧�.
			*/
            skill->GetVictim ()->SetProbability (100);
			static int aarray[10] = { 40000, 40000, 40000, 40000, 50000, 50000, 50000, 60000, 60000, 70000 };			
            skill->GetVictim ()->SetTime ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetImmuneall (1);
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
            return (float) (22);
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
            return (float) (2);
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
