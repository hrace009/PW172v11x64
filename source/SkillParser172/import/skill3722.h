/*Skill Parser (c)Deadraky 2022 
37220  "���֧ݧڧܧ�� �ܧѧާ֧ߧߧ�� ����ܧݧ��ڧ�"
37221  "^ff5c00���֧ݧڧܧ�� �ܧѧާ֧ߧߧ�� ����ܧݧ��ڧ�

^ffcb4a���ѧݧ�ߧ����: ^96f5ff%d^ffffff ^ffcb4a��
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff1,5 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,8 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff150,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧ�� ����اڧ�, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����է�����

^ffcb4a����ѧ���: ^ffffff�������
���ѧߧ��ڧ� �����ڧӧߧڧܧ� �ҧѧ٧�ӧ�� �ާѧԧڧ�֧�ܧڧ� �����,
��ݧ�� ^96f5ff300%%^ffffff ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff3578^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �է֧�֧ӧ�.
���� ^96f5ff10^ffffff ��֧�. ��֧ݧ� �է���ݧߧڧ�֧ݧ�ߧ� �ߧѧߧ��ڧ��� ^96f5ff600%%^ffffff ����ߧ� ����اڧ�
��ݧ�� ^96f5ff6427^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� ��ԧߧ�. ����ݧ� ��֧ݧ� - �ڧԧ���, ��� �֧ԧ� �٧ѧ�ڧ��
�� ��֧�֧ߧڧ� ����ԧ� �ӧ�֧ާ֧ߧ� �ҧ�է֧� ��ߧڧا֧ߧ� ^96f5ff�է� �ߧ�ݧ�^ffffff.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���.

^00ff00�����֧ܧ� �ڧ٧�ާ��էߧ�� ���ߧ�:@1
^00ff001-4 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff135^00ff00 ��֧�.
^00ff005-7 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff120^00ff00 ��֧�.
^00ff008-9 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff105^00ff00 ��֧�.
 ^00ff0010 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff90^00ff00 ��֧�.@1@2
^00ff00����֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff%d ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3722 
#define __CPPGEN_GNET_SKILL3722 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3722:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3722 }; 
        Skill3722 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3722Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1500;
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
                skill->GetPlayer ()->SetDecmp (35);
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
                skill->GetPlayer ()->SetDecmp (140);
                skill->SetPlus (3578);
                skill->SetRatio (3);
                skill->SetWooddamage (skill->GetMagicattack ());
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
    Skill3722Stub ():SkillStub (3722) 
    { 
        cls                 = 3; 
        name                = L"�񡤳��ҹ�"; 
        nativename          = "�񡤳��ҹ�"; 
        icon                = "�񡤳��ҹ���.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 3; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1602; 
        allow_forms         = 1; 
        apcost              = 200; 
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
        effect              = "����_���ҹƸ�_����.sgc"; 
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
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (292); 
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
		/*
		^00ff001-4 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff135^00ff00 ��֧�.
		^00ff005-7 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff120^00ff00 ��֧�.
		^00ff008-9 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff105^00ff00 ��֧�.
		^00ff0010 ���.: �ӧ�֧ާ� ��֧�֧٧ѧ��էܧ� ���ܧ�ѧ�ѧ֧��� �է� ^96f5ff90^00ff00 ��֧�
		*/
		static const int LEVEL_1_4 = 135000;
		static const int LEVEL_5_7 = 120000;
		static const int LEVEL_8_9 = 105000;
		static const int LEVEL_10_10 = 90000;
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
            return (float) (1 - 0.0111111 * (0));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (27);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 175,175,175,175,175,175,175,175,175,175 }; 
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
			// ����ݧ� ��֧ݧ� - �ڧԧ���, ��� �֧ԧ� �٧ѧ�ڧ�� �� ��֧�֧ߧڧ� ����ԧ� �ӧ�֧ާ֧ߧ� �ҧ�է֧� ��ߧڧا֧ߧ� ^96f5ff�է� �ߧ�ݧ�
            skill->GetVictim ()->SetProbability (1.0 * skill->GetPlayer ()->GetCls () == -1 ? 100 : 0);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (9999);
            skill->GetVictim ()->SetDecdefence (1);
			
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetAmount (skill->GetT0 () *
                                            (1 +
                                             0.01 * (skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () >
                                                     0 ? skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () : 0)));
            skill->GetVictim ()->SetBurning (1);
            skill->GetVictim ()->SetTime (skill->GetT2 () > 0 ? 3000 : 1000);
            skill->GetVictim ()->SetRatio (0);
            skill->GetVictim ()->SetAmount (112);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetInsertvstate (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const 
    { 
        return 1; 
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
            return (float) (6 * player->GetEquipattack () + 6427);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetAttackdegree ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent2 (PlayerWrapper * player) const
        {
            return (float) (player->GetRand () < 25 ? 9 : 0);
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
            return 26;
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
