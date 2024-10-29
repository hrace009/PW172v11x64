/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
38550  "���֧ݧڧܧڧ� ��ҧڧ��� �է�ѧܧ��"
38551  "^ff5c00���֧ݧڧܧڧ� ��ҧڧ��� �է�ѧܧ�� 

^ffcb4a���ѧݧ�ߧ����: ^96f5ff35^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff303^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,6^ffcb4a ��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1,5^ffcb4a ��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff60,0^ffcb4a ��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff������� �� �ާ�ݧ���
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff�������
���ѧߧ��ڧ� �ӧ�֧� �����ڧӧߧڧܧѧ� �� ��ѧէڧ��� ^96f5ff20^ffffff �� ^96f5ff120%%^ffffff �ҧѧ٧�ӧ�ԧ� ��ڧ٧ڧ�֧�ܧ�ԧ� ����ߧ�.
���֧�ѧ��ڧ� �����ڧӧߧڧܧѧ� �ߧѧߧ��ڧ� ^96f5ff����ۧߧ��^ffffff ����� �� �� �ӧ֧����ߧ����� ^96f5ff100%%^ffffff
��ҧڧӧѧ֧� �ڧ� �ߧ� �٧֧ާݧ�, ����ݧ� ��֧ԧ� ��ߧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff30^ffffff ��֧�.
���� ����ާѧ�ڧӧѧ֧���.
^a6caf0���ѧӧ�� �ߧ֧ݧ�٧� ���ڧާ֧ߧڧ�� �� ���ݧ֧��.
������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���.

^00ff00�����֧ܧ� �ڧ٧�ާ��էߧ�� ���ߧ�:@1
^00ff001-4 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff36^00ff00 ��֧�.
^00ff005-7 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff39^00ff00 ��֧�.
^00ff008-9 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff42^00ff00 ��֧�.
^00ff00 10 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff45^00ff00 ��֧�.@1@2
^00ff00������ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff%d^00ff00 ��֧�.@2"
38560  "���֧ݧڧܧڧ� ��ҧڧ��� �է�ѧܧ��"
*/
#ifndef __CPPGEN_GNET_SKILL3855 
#define __CPPGEN_GNET_SKILL3855 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3855:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3855 }; 
        Skill3855 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3855Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 650;
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
                skill->GetPlayer ()->SetDecmp (61);
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
                return 1450;
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
                skill->GetPlayer ()->SetDecmp (242);
                skill->SetPlus (0);
                skill->SetRatio (0);
                skill->SetDamage (1.2 * skill->GetAttack ());
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
    Skill3855Stub ():SkillStub (3855) 
    { 
        cls                 = 4; 
        name                = L"�����ɾ�"; 
        nativename          = "�����ɾ�"; 
        icon                = "�����ɾ���.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2905; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 0; 
        doenchant           = 1; 
        dobless             = 0; 
        arrowcost           = 0; 
        allow_land          = 1; 
        allow_air           = 0; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 1; 
        time_type           = 0; 
        long_range          = 0; 
        posdouble           = 2; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        itemcostcount       = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
        effect              = "����_����֮��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
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
        static int aarray[10] = { 1450,1450,1450,1450,1450,1450,1450,1450,1450,1450 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 500000,500000,500000,500000,500000,500000,500000,500000,500000,500000 }; 
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetRadius (Skill * skill) const
    {
            return (float) (20);
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
            return (float) (35);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 240,240,240,240,240,240,240,240,240,240 }; 
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
			^00ff001-4 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff36^00ff00 ��֧�.
			^00ff005-7 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff39^00ff00 ��֧�.
			^00ff008-9 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff42^00ff00 ��֧�.
			^00ff00 10 ���.: �����ڧӧߧڧܧ� �ߧ� �ާ�ԧ�� �ӧ٧ݧ֧�֧�� �� ��֧�֧ߧڧ� ^96f5ff45^00ff00 ��֧�.
			*/
			static int aarray[10] = { 36000, 36000, 36000, 36000, 39000, 39000, 39000, 42000, 42000, 45000 };			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetNofly (1);
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
            return (float) (50);
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
            return (float) (4);
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
