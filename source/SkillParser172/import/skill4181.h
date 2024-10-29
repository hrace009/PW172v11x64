/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
41810  "���֧ݧڧܧڧ� �ܧ��ݧѧ��� �ӧ֧�֧�"
41811  "^ff5c00���֧ݧڧܧڧ� �ܧ��ݧѧ��� �ӧ֧�֧�

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff3^ffcb4a �ާڧ�
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ߧ֧�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ��֧�֧էӧڧا֧ߧڧ� ��֧ݧ� �է� �ާѧܧ�ڧާ�ާ� �� �ߧѧէ֧ݧ�֧� �֧�
�ߧ֧ӧ����ڧڧާ�ڧӧ����� �� �٧ѧާ֧էݧ���ڧ� ����֧ܧ�ѧ�.
����֧ާ� �է֧ۧ��ӧڧ� - ^96f5ff10^ffffff ��֧�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff1^a6caf0 ���.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff40%%
^ffcb4a5-7 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff60%%
^ffcb4a8-9 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff80%%
 ^ffcb4a10 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff100%%@1@2
^ffcb4a������ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff%d%%^ffcb4a.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4181 
#define __CPPGEN_GNET_SKILL4181 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4181:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4181 }; 
        Skill4181 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4181Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
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
                skill->GetPlayer ()->SetDecmp (200);
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
    Skill4181Stub ():SkillStub (4181) 
    { 
        cls                 = 6; 
        name                = L"�����"; 
        nativename          = "�����"; 
        icon                = "������.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2551; 
        allow_forms         = 1; 
        apcost              = 100; 
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
        effect              = "���.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 3500,3500,3500,3500,3500,3500,3500,3500,3500,3500 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 180000,180000,180000,180000,180000,180000,180000,180000,180000,180000 }; 
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
            return (float) (16);
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
            return (float) (30);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 200,200,200,200,200,200,200,200,200,200 }; 
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
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetFreemove (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (2);
            skill->GetVictim ()->SetSpeedup (1);
			
			/*
			^ffcb4a1-4 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff40%%
			^ffcb4a5-7 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff60%%
			^ffcb4a8-9 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff80%%
			^ffcb4a10 ���.: �է���ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff100%%@1@2
			^ffcb4a������ݧߧڧ�֧ݧ�ߧ� ��ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ���ݧ֧�� �ߧ� ^96f5ff%d%%^ffcb4a.@2
			*/
			static float aarray[10] = { 0.4, 0.4, 0.4, 0.4, 0.6, 0.6, 0.6, 0.8, 0.8, 1.0 };			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetFastfly (1);
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
