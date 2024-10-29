/*Skill Parser (c)Deadraky 2022 
35020  "���֧ݧڧܧѧ� ��ӧ�٧�ӧѧ��ѧ� ����֧ݧ�"
35021  "^ff5c00���֧ݧڧܧѧ� ��ӧ�٧�ӧѧ��ѧ� ����֧ݧ� 

^ffcb4a���ѧݧ�ߧ����: ^ffffff�էѧݧ�ߧ�� �ѧ�ѧܧ�
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,5 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,6 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff15,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����اڧ� �էѧݧ�ߧ֧ԧ� �ҧ��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����ѧҧ�����

^ffcb4a����ѧ���: ^ffffff�������
����ӧѧ�ߧ�� �ӧ����֧�, �ߧѧߧ����ڧ� �ҧѧ٧�ӧ�� ��ڧ٧ڧ�֧�ܧڧ� ����� ��ݧ�� ^96f5ff9631^ffffff �֧�.
���ҧ֧٧էӧڧاڧӧѧ֧� �����ڧӧߧڧܧ� �ߧ� ^96f5ff%d^ffffff ��֧�. �� �ߧѧܧݧѧէ�ӧѧ֧� ����֧ܧ� �ާ�ݧ�ѧߧڧ� �ߧ� ^96f5ff%d^ffffff ��֧�.

^a6caf0����֧ҧ�֧���: ^ffffff1^a6caf0 ����֧ݧ� �ڧݧ� ��ߧѧ���.
^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff1^a6caf0 ���.

^ff0000�����֧ܧ� ���ҧڧߧ�ӧ�� ���ߧ�:@1
^ff00001-4 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff2,0^ff0000 ��֧�.
^ff00005-7 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff2,5^ff0000 ��֧�.
^ff00008-9 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff3,0^ff0000 ��֧�.
^ff0000 10 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff3,5^ff0000 ��֧�.@1@2
���ݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff%.1f^ff0000 ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3502 
#define __CPPGEN_GNET_SKILL3502 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3502:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3502 }; 
        Skill3502 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3502Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (45);
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
                return 600;
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
                skill->GetPlayer ()->SetDecmp (180);
                skill->SetPlus (5403);
                skill->SetRatio (0);
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
    Skill3502Stub ():SkillStub (3502) 
    { 
        cls                 = 6; 
        name                = L"������ʸ"; 
        nativename          = "������ʸ"; 
        icon                = "������ʸ��.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1304; 
        allow_forms         = 1; 
        apcost              = 100; 
        apgain              = 0; 
        doenchant           = 1; 
        dobless             = 0; 
        arrowcost           = 1; 
        allow_land          = 1; 
        allow_air           = 1; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 1; 
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
        effect              = "2����ʸ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (13); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 600,600,600,600,600,600,600,600,600,600 }; 
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
        static int aarray[10] = { 92,92,92,92,92,92,92,92,92,92 }; 
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
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 225,225,225,225,225,225,225,225,225,225 }; 
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
            skill->GetVictim ()->SetTime (8500);
            skill->GetVictim ()->SetFix (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
			
			/*
			^ff00001-4 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff2,0^ff0000 ��֧�.
			^ff00005-7 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff2,5^ff0000 ��֧�.
			^ff00008-9 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff3,0^ff0000 ��֧�.
			^ff0000 10 ���.: �էݧڧ�֧ݧ�ߧ���� ����֧ܧ�� �ާ�ݧ�ѧߧڧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff3,5^ff0000 ��֧�.
			*/
			static int aarray[10] = { 2300, 2300, 2300, 2300, 2800, 2800, 2800, 3300, 3300, 5800 };			
            skill->GetVictim ()->SetTime (3500);
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
            return (float) (skill->GetPlayer ()->GetRange () + 5);
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
            return (float) (1.5);
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
