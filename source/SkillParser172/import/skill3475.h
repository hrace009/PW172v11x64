/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
34750  "���֧ݧڧܧڧ� ��էѧ� �ާ�ݧߧڧ�"
34751  "^ff5c00���֧ݧڧܧڧ� ��էѧ� �ާ�ݧߧڧ�

^ffcb4a���ѧݧ�ߧ����: ^ffffff�էѧݧ�ߧ�� �ѧ�ѧܧ�
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,5 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,8 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff8,0 ^ffcb4a��֧�.
^ffcb4a����ݧ��֧ߧڧ� ���: ^ffffff0,15
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����اڧ� �էѧݧ�ߧ֧ԧ� �ҧ��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
�����ѧاѧ֧� �����ڧӧߧڧܧ� ��էѧ��� �ާ�ݧߧڧ�. ���ѧߧ��ڧ� ����� ���ڧ�ڧ֧� �ާ֧�ѧݧݧ�, ��ѧӧߧ�� �ҧѧ٧�ӧ�ާ� ��ڧ٧ڧ�֧�ܧ�ާ� ����ߧ�,
��ݧ�� ^96f5ff150%%^ffffff ����ߧ� ����اڧ� ��ݧ�� ^96f5ff7588^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �ާ֧�ѧݧݧ�.
���� ����ާѧ�ڧӧѧ֧���.

^a6caf0����֧ҧ�֧���: ^ffffff1^a6caf0 ����֧ݧ� �ڧݧ� ��ߧѧ���.

^ffcb4a�����֧ܧ� �٧�ݧ���� ���ߧ�:@1
^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff20%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff30%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff40%%^ffcb4a ����ߧ� ����اڧ�
^ffcb4a 10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff50%%^ffcb4a ����ߧ� ����اڧ�@1@2
����ҧѧӧݧ�֧��� ^96f5ff%d%%^ffcb4a ����ߧ� ����اڧ�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3475 
#define __CPPGEN_GNET_SKILL3475 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3475:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3475 }; 
        Skill3475 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3475Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (67);
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
                return 800;
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
                skill->GetPlayer ()->SetDecmp (268);
                skill->SetPlus (7588);
				
				/*
				^ffcb4a1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff20%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff30%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff40%%^ffcb4a ����ߧ� ����اڧ�
				^ffcb4a 10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff50%%^ffcb4a ����ߧ� ����اڧ�
				*/
				static const float LEVEL_1_4 = 0.2;
				static const float LEVEL_5_7 = 0.3;
				static const float LEVEL_8_9 = 0.4;
				static const float LEVEL_10_10 = 0.5;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetRatio (1.5 + ( aarray[skill->GetLevel () - 1] ));
                skill->SetGolddamage (skill->GetAttack ());
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
    Skill3475Stub ():SkillStub (3475) 
    { 
        cls                 = 6; 
        name                = L"������"; 
        nativename          = "������"; 
        icon                = "�����׻�.dds"; 
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
        showorder           = 1308; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 15; 
        doenchant           = 0; 
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
        effect              = "2����.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "ֱ���˺�����1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
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
        static int aarray[10] = { 800,800,800,800,800,800,800,800,800,800 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 8000,8000,8000,8000,8000,8000,8000,8000,8000,8000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
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
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetRadius (Skill * skill) const
    {
            return (float) (8 + 0.4 * skill->GetLevel ());
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
        static float aarray[10] = { 335,335,335,335,335,335,335,335,335,335 }; 
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
