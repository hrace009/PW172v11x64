/*Skill Parser (c)Deadraky 2022 
38070  "���֧ݧڧܧѧ� �է�֧ӧߧ�� �����ާ�"
38071  "^ff5c00���֧ݧڧܧѧ� �է�֧ӧߧ�� �����ާ�

^ffcb4a���ѧݧ�ߧ����: ^ffffff4,5 ��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff290
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,4 ^ffcb4a��֧�.
����ڧާ֧ߧ֧ߧڧ�: ^ffffff2,5 ^ffcb4a��֧�.
���֧�֧٧ѧ��էܧ�: ^ffffff30,0 ^ffcb4a��֧�.
���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ܧڧߧاѧݧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
�����ѧ�ߧ�� ��էѧ� ��ԧݧ��ѧ֧� �����ڧӧߧڧܧ� �ߧ� ^96f5ff6^ffffff ��֧�.
�� �ߧѧߧ��ڧ� �֧ާ� ^96f5ff2-�ܧ�ѧ�ߧ��^ffffff �ҧѧ٧�ӧ�� ��ڧ�. �����,
^96f5ff375%%^ffffff ����ߧ� ����اڧ� �� ^96f5ff7497^ffffff �֧�. ��ڧ�. ����ߧ�.
���� ^96f5ff10^ffffff ��֧�. ��ߧڧاѧ֧� ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �����ڧӧߧڧܧ� �ߧ� 60%%.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2,0^a6caf0 ���.
�����ݧ� ���ڧާ֧ߧ֧ߧڧ� �ӧ����ѧߧѧӧݧڧӧѧ֧��� 0,5 ���.

^d618e7���ާ֧ߧڧ� ���ڧݧڧӧѧ֧��� �� �����ӧ֧���ӧڧ� �� �ܧ��-�� �����ѧ�֧ߧߧ�� ���ܧ�� �ܧ�ާҧ�.
����� �ާѧܧ�ڧާ�ާ� �ܧ�ާҧ�-���ܧ�� �էѧ֧� �է��. 1 ���ܧ� �ܧ�ާҧ�.

^00ff00�����֧ܧ� �ڧ٧�ާ��էߧ�� ���ߧ�:@1
^00ff001-4 ���.: �է��. �ߧѧߧ��ڧ� ^96f5ff240%%^00ff00 �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
��ݧ�� ^96f5ff6%%^00ff00 �٧� �ܧѧاէ�� �����ѧ�֧ߧߧ�� ���ܧ� �ܧ�ާҧ�.
^00ff005-7 ���.: �է��. �ߧѧߧ��ڧ� ^96f5ff260%%^00ff00 �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
��ݧ�� ^96f5ff9%%^00ff00 �٧� �ܧѧاէ�� �����ѧ�֧ߧߧ�� ���ܧ� �ܧ�ާҧ�.
^00ff008-9 ���.: �է��. �ߧѧߧ��ڧ� ^96f5ff280%%^00ff00 �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
��ݧ�� ^96f5ff12%%^00ff00 �٧� �ܧѧاէ�� �����ѧ�֧ߧߧ�� ���ܧ� �ܧ�ާҧ�.
^00ff00 10 ���.: �է��. �ߧѧߧ��ڧ� ^96f5ff300%%^00ff00 �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
��ݧ�� ^96f5ff15%%^00ff00 �٧� �ܧѧاէ�� �����ѧ�֧ߧߧ�� ���ܧ� �ܧ�ާҧ�.@1@2
���ѧߧ��ڧ� ^96f5ff%d%%^00ff00 �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
��ݧ�� ^96f5ff%d%%^00ff00 �٧� �ܧѧاէ�� �����ѧ�֧ߧߧ�� ���ܧ� �ܧ�ާҧ�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3807 
#define __CPPGEN_GNET_SKILL3807 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3807:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3807 }; 
        Skill3807 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3807Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 400;
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
                skill->GetPlayer ()->SetDecmp (90);
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
                return 50;
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
                skill->GetPlayer ()->SetPerform (2);
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
                skill->SetSection (1);
                skill->SetPlus (14994);
                skill->SetRatio (7.5);
                skill->SetDamage (0.25 * skill->GetAttack ());
                skill->GetPlayer ()->SetPerform (0);
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
        class State4:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 300;
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
                skill->SetSection (2);
                skill->SetPlus (14994);
                skill->SetRatio (7.5);
                skill->SetDamage (0.1 * skill->GetAttack ());
                skill->GetPlayer ()->SetPerform (0);
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
        class State5:public SkillStub::State
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
                skill->SetSection (3);
                skill->SetPlus (14994);
                skill->SetRatio (7.5);
                skill->SetDamage (0.15 * skill->GetAttack ());
                skill->GetPlayer ()->SetPerform (0);
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
        class State6:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1250;
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
                skill->SetSection (4);
                skill->SetPlus (14994);
                skill->SetRatio (7.5);
                skill->SetDamage (0.5 * skill->GetAttack ());
                skill->GetPlayer ()->SetPerform (0);
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
        class State7:public SkillStub::State
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
    Skill3807Stub ():SkillStub (3807) 
    { 
        cls                 = 5; 
        name                = L"��������"; 
        nativename          = "��������"; 
        icon                = "������������.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1622; 
        allow_forms         = 1; 
        apcost              = 200; 
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
        effect              = "�̿�_ʮ��ն.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "����������������.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (23749); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
        statestub.push_back (new State4 ()); 
        statestub.push_back (new State5 ()); 
        statestub.push_back (new State6 ()); 
        statestub.push_back (new State7 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
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
            return (float) (1 - 0.0111111 * (0));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (4.5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 290,290,290,290,290,290,290,290,290,290 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * (skill->GetSection () == 1 ? 100 : 0));
            skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetDizzy (1);
            skill->GetVictim ()->SetProbability (1.0 * (skill->GetSection () == 1 ? 100 : 0));
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (0.6);
            skill->GetVictim ()->SetSlow (1);
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
            return (float) (12);
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
