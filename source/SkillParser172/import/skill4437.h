/*Skill Parser (c)Deadraky 2022 
44370  "���֧ݧڧܧڧ� �٧�� �ӧ֧���"
44371  "^ff5c00���֧ݧڧܧڧ� �٧�� �ӧ֧���

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff237^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff90,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����ѧҧ�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� ^ff5c00��ѧާѧߧ�^ffffff �ߧ� ����� �� �� �ӧ�٧է���
�ߧ� ^96f5ff60%%^ffffff, �� ��ܧ������ �� �ӧ�է� �ߧ� ^96f5ff100%%^ffffff �ߧ� ^96f5ff15^ffffff ��֧�. �����ާ� ���ԧ�, �ߧ� ^96f5ff5^ffffff ��֧�.
��ѧާѧ� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff80^ffcb4a ��֧�.
^ffcb4a5-7 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff70^ffcb4a ��֧�.
^ffcb4a8-9 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff60^ffcb4a ��֧�.
 ^ffcb4a10 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff50^ffcb4a ��֧�.@1@2
^ffcb4a����֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff%d^ffcb4a ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4437 
#define __CPPGEN_GNET_SKILL4437 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4437:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4437 }; 
        Skill4437 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4437Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 500;
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
                skill->GetPlayer ()->SetDecmp (47);
                skill->GetPlayer ()->SetPerform (1);
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
                return 500;
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
                skill->GetPlayer ()->SetDecmp (190);
                skill->GetPlayer ()->SetPray (1);
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
    Skill4437Stub ():SkillStub (4437) 
    { 
        cls                 = 2; 
        name                = L"�񡤺����ٻ�"; 
        nativename          = "�񡤺����ٻ�"; 
        icon                = "�񺣷��ٻ���.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 0; 
        rank                = 41; 
        eventflag           = 1; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2451; 
        allow_forms         = 1; 
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
        time_type           = 1; 
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
        effect              = "��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (25333); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
		/*
		^ffcb4a1-4 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff80^ffcb4a ��֧�.
		^ffcb4a5-7 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff70^ffcb4a ��֧�.
		^ffcb4a8-9 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff60^ffcb4a ��֧�.
		^ffcb4a10 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff50^ffcb4a ��֧�
		*/
		static const int LEVEL_1_4 = 80000;
		static const int LEVEL_5_7 = 70000;
		static const int LEVEL_8_9 = 60000;
		static const int LEVEL_10_10 = 50000;
		static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };			
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
        static float aarray[10] = { 237,237,237,237,237,237,237,237,237,237 }; 
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
            skill->GetVictim ()->SetRatio (1.0);
            skill->GetVictim ()->SetFastfly (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (0.6);
            skill->GetVictim ()->SetSpeedup (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (0.6);
            skill->GetVictim ()->SetFastswim (1);
			// ��ѧާѧ� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�
            skill->GetVictim ()->SetProbability (1.0 * 100);
			skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetFreemove (1);			
            
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
            return (float) (45);
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
        {
            skill->GetPlayer ()->SetIncmpgen (2 * skill->GetLevel ());
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
