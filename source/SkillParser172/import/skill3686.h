/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
36860  "���֧ݧڧܧڧ� �٧��ҧ��ڧ� ��֧���"
36861  "^ff5c00���֧ݧڧܧڧ� �٧��ҧ��ڧ� ��֧���

^ffcb4a���ѧݧ�ߧ����: ^96f5ff%d^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff1,8 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff1 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff10 ^ffcb4a��֧�.
^ffcb4a����ݧ��֧ߧڧ� ���: ^ffffff0,2
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧ�� ����اڧ�, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff�������
���ѧ� �٧ѧ�ѧ��ӧ��ӧѧ֧� �٧֧ާݧ� ���� �ߧ�ԧѧާ� �����ڧӧߧڧܧ� �� ���֧ӧ�ѧ�ѧ֧� �֧� �� �٧��ҧ��ڧ� ��֧���.
���ѧߧ��ڧ� �ҧѧ٧�ӧ��� �ާѧԧڧ�֧�ܧڧ� �����, ��ݧ�� ^96f5ff200%%^ffffff ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff6560^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �٧֧ާݧ�.
���� ^96f5ff9^ffffff ��֧�. ��ߧڧاѧ֧� �ާ֧�ܧ���� �����ڧӧߧڧܧ� �ߧ� ^96f5ff50%%^ffffff, �ߧѧߧ��ڧ� �֧�� ^96f5ff600%%^ffffff ����ߧ� ����اڧ� ��ݧ�� ^96f5ff7021^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �٧֧ާݧ�.
�� �ӧ֧����ߧ����� ^96f5ff33%%^ffffff ��ҧ֧٧էӧڧاڧӧѧ֧� �����ڧӧߧڧܧ� �ߧ� ^96f5ff3^ffffff ��֧�.

^00ff00�����֧ܧ� �ڧ٧�ާ��էߧ�� ���ߧ�:@1
^00ff001-4 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,6^00ff00 ��֧�.
^00ff005-7 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,5^00ff00 ��֧�.
^00ff008-9 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,4^00ff00 ��֧�.
^00ff00 10 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,3^00ff00 ��֧�.@1@2
^00ff00����էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff%.1f^00ff00 ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3686 
#define __CPPGEN_GNET_SKILL3686 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3686:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3686 }; 
        Skill3686 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3686Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
				/*
				^00ff001-4 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,6^00ff00 ��֧�.
				^00ff005-7 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,5^00ff00 ��֧�.
				^00ff008-9 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,4^00ff00 ��֧�.
				^00ff00 10 ���.: ���էԧ���ӧܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff1,3^00ff00 ��֧�.
				*/
				static const int LEVEL_1_4 = 1600;
				static const int LEVEL_5_7 = 1500;
				static const int LEVEL_8_9 = 1400;
				static const int LEVEL_10_10 = 1300;
				static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };				
				return aarray[skill->GetLevel () - 1]; 
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
                skill->GetPlayer ()->SetDecmp (64);
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return skill->GetRand () < 5;
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
                skill->GetPlayer ()->SetDecmp (256);
                skill->SetPlus (6560);
                skill->SetRatio (2);
                skill->SetEarthdamage (skill->GetMagicattack ());
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
    Skill3686Stub ():SkillStub (3686) 
    { 
        cls                 = 1; 
        name                = L"��ɳ��"; 
        nativename          = "��ɳ��"; 
        icon                = "��ɳ����.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 6; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1220; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 20; 
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
        effect              = "��ʦ_ɳʯ��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "����ʱ������.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 106; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 10000,10000,10000,10000,10000,10000,10000,10000,10000,10000 }; 
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
            return (float) (30);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 320,320,320,320,320,320,320,320,320,320 }; 
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
            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetAmount (skill->GetT1 () *
                                            (1 +
                                             0.01 * (skill->GetT0 () - skill->GetPlayer ()->GetDefenddegree () >
                                                     0 ? skill->GetT0 () - skill->GetPlayer ()->GetDefenddegree () : 0)));
            skill->GetVictim ()->SetFallen (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetDecaccuracy (1);
            skill->GetVictim ()->SetProbability (1.0 * 33);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetFix (1);
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
            return (float) (36);
        }		
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetAttackdegree ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (6 * player->GetEquipattack () + 7021);
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
