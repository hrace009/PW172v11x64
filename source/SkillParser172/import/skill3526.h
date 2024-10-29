/*Skill Parser (c)Deadraky 2022 
35260  "���֧ݧڧܧڧ� ����ا�� �ӧݧ֧ӧ�"
35261  "^ff5c00���֧ݧڧܧڧ� ����ا�� �ӧݧ֧ӧ� 

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ff5c00120 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����اڧ� �էѧݧ�ߧ֧ԧ� �ҧ��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff�������
�����ߧڧ� �ާԧߧ�ӧ֧ߧߧ� ��֧�֧ާ֧�ѧ֧��� �ӧݧ֧ӧ� �ߧ� ^96f5ff30^ffffff ��, ���ݧ��ѧ� �ڧާާ�ߧڧ�֧� �� ��ԧ�ѧߧڧ�֧ߧڧ� �էӧڧا֧ߧڧ� �ߧ� ^96f5ff3^ffffff ��֧�. 

^ff0000�����֧ܧ� ���ҧڧߧ�ӧ�� ���ߧ�:@1
^ff00001-4 ���.: �� ��ѧߧ��� ^96f5ff40%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
^ff00005-7 ���.: �� ��ѧߧ��� ^96f5ff60%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
^ff00008-9 ���.: �� ��ѧߧ��� ^96f5ff80%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
^ff0000 10 ���.: �� ��ѧߧ��� ^96f5ff100%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000@1@2
�� ��ѧߧ��� ^96f5ff%d%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3526 
#define __CPPGEN_GNET_SKILL3526 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3526:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3526 }; 
        Skill3526 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3526Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (66);
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
        class State2:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 900;
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
                skill->GetPlayer ()->SetDecmp (100);
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
    Skill3526Stub ():SkillStub (3526) 
    { 
        cls                 = 6; 
        name                = L"������֮��"; 
        nativename          = "������֮��"; 
        icon                = "������֮���.dds"; 
        max_level           = 1; 
        type                = 8; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2904; 
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
        effect              = ""; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
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
        static int aarray[10] = { 900,900,900,900,900,900,900,900,900,900 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 120000,120000,120000,120000,120000,120000,120000,120000,120000,120000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
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
            return (float) (12);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (30);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (180));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (30);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 166,166,166,166,166,166,166,166,166,166 }; 
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
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetFreemove (1);
			
			/*
			^ff00001-4 ���.: �� ��ѧߧ��� ^96f5ff40%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
			^ff00005-7 ���.: �� ��ѧߧ��� ^96f5ff60%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
			^ff00008-9 ���.: �� ��ѧߧ��� ^96f5ff80%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
			^ff0000 10 ���.: �� ��ѧߧ��� ^96f5ff100%%^ff0000 �ѧܧ�ڧӧڧ��֧� ��ާ֧ߧڧ� ^96f5ff'�����ܧ�ۧ��ӧڧ�'^ff0000
			*/
			static int aarray[10] = { 40, 40, 40, 40, 60, 60, 60, 80, 80, 100 };			
            skill->GetVictim ()->SetProbability (1.0 * ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetTime (3000);
            skill->GetVictim ()->SetRatio (0);
            skill->GetVictim ()->SetAmount (0);
            skill->GetVictim ()->SetValue (31);
            skill->GetVictim ()->SetInvisible (1);
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
            return (float) (15);
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
