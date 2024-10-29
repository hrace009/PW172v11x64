/*Skill Parser (c)Deadraky 2022 
38450  "���֧ݧڧܧڧ� ������֧��ߧߧ�� �ާ�ݧ��"
38451  "^ff5c00���֧ݧڧܧڧ� ������֧��ߧߧ�� �ާ�ݧ��

^ffcb4a���ѧݧ�ߧ����: ^ffffff�ҧݧڧاߧڧ� �ҧ��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,2^ffcb4a ��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,9^ffcb4a ��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff6,0^ffcb4a ��֧�.
^ffcb4a����ݧ��֧ߧڧ� ���: ^ffffff0,15
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff������� �� �ާ�ݧ���
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ѧ٧ާѧ�ڧ���� ��էѧ�, ���ܧ���ѧ��ڧ� �����ڧӧߧڧܧ�.
���ѧߧ��ڧ� �ҧѧ٧�ӧ�� ��ڧ٧ڧ�֧�ܧڧ� ����� ��ݧ�� ^96f5ff3836^ffffff �֧�. ��ڧ٧ڧ�֧�ܧ�ԧ� ����ߧ�.
�� �ӧ֧����ߧ����� ^96f5ff100%%^ffffff ��ѧ�ѧݧڧ٧�֧� �����ڧӧߧڧܧ� �ߧ� ^96f5ff4^ffffff ��֧�.

���� ����ާѧ�ڧӧѧ֧���.

^ff0000�����֧ܧ� ���ҧڧߧ�ӧ�� ���ߧ�:@1
^ff00001-4 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff18^ff0000 ��֧�.
^ff00005-7 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff16^ff0000 ��֧�.
^ff00008-9 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff14^ff0000 ��֧�.
^ff0000 10 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff12^ff0000 ��֧�.@1@2
^ff0000���֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff%d^ff0000 ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3845 
#define __CPPGEN_GNET_SKILL3845 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3845:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3845 }; 
        Skill3845 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3845Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (27);
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
                skill->GetPlayer ()->SetDecmp (108);
                skill->SetPlus (3836);
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
    Skill3845Stub ():SkillStub (3845) 
    { 
        cls                 = 4; 
        name                = L"��ǧ�ﴸ"; 
        nativename          = "��ǧ�ﴸ"; 
        icon                = "��ǧ�ﴸ��.dds"; 
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
        showorder           = 1504; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 15; 
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
        effect              = "����_��ǧ�ﴸ_����.sgc"; 
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
        restrict_weapons.push_back (9); 
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
		/*
		^ff00001-4 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff18^ff0000 ��֧�.
		^ff00005-7 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff16^ff0000 ��֧�.
		^ff00008-9 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff14^ff0000 ��֧�.
		^ff0000 10 ���.: ��֧�֧٧ѧ��էܧ� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff12^ff0000 ��֧�
		*/
		static const int LEVEL_1_4 = 18000;
		static const int LEVEL_5_7 = 16000;
		static const int LEVEL_8_9 = 14000;
		static const int LEVEL_10_10 = 12000;
		static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };
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
            return (float) (0);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (20 + 2.5 * skill->GetLevel ()));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 135,135,135,135,135,135,135,135,135,135 }; 
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
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime (5000);
            skill->GetVictim ()->SetValue (2);
            skill->GetVictim ()->SetPalsy (1);
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
            return (float) (13);
        }		
#endif 
#ifdef _SKILL_SERVER 
                float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetRand ());
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
            return (float) (1.7);
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
