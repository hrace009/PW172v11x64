/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
38660  "���֧ݧڧܧڧ� �٧ѧԧߧѧߧߧ�� �٧ӧ֧��"
38661  "^ff5c00���֧ݧڧܧڧ� �٧ѧԧߧѧߧߧ�� �٧ӧ֧�� 

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff252^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,4^ffcb4a ��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1,6^ffcb4a ��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff300 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff������� �� �ާ�ݧ���
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
����ݧ� ��ҧ����֧ߧ� �� ��֧�֧ߧڧ� ^96f5ff150^ffffff ��֧�. ���ݧ��ڧ� ��ާ֧��֧ݧ�ߧ�� ��էѧ�, ��� �ӧ����ѧߧ�ӧڧ�
^96f5ff45%%^ffffff �ާѧܧ�ڧާѧݧ�ߧ�ԧ� �٧է���ӧ�� �� �ڧ٧ҧѧӧڧ��� ��� �ߧ֧ԧѧ�ڧӧߧ�� ����֧ܧ���.
^ffcb4a����اߧ� ���ڧާ֧ߧڧ�� �� ��ҧݧڧܧ� ��ڧԧ�� �� ��ѧߧէ�.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff63%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��
^ffcb4a5-7 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff72%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��
^ffcb4a8-9 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff81%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��.
^ffcb4a 10 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff90%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��@1@2
^ffcb4a����� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff%d%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3866 
#define __CPPGEN_GNET_SKILL3866 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3866:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3866 }; 
        Skill3866 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3866Stub:public SkillStub 
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
    Skill3866Stub ():SkillStub (3866) 
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
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(0, 1)); 
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
            skill->GetVictim ()->SetTime (150000);
			/*
			^ffcb4a1-4 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff63%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��
			^ffcb4a5-7 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff72%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��
			^ffcb4a8-9 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff81%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��.
			^ffcb4a 10 ���.: ���� ���ݧ��֧ߧڧ� ��ާ֧��֧ݧ�ߧ�ԧ� ��էѧ�� �ӧ����ѧߧѧӧݧڧӧѧ֧� �٧է���ӧ�� �� ��ѧ٧ާ֧�� ^96f5ff90%%^ffcb4a ��� �ާѧܧ�ڧާ�ާ� �٧է���ӧ��			
			*/
			static float aarray[10] = { 0.63, 0.63, 0.63, 0.63, 0.72, 0.72, 0.72, 0.81, 0.81, 0.9 };			
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetRebirth2 (1);
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
