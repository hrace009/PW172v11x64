/*Skill Parser (c)Deadraky 2022 
44400  "���֧ݧڧܧڧ� �٧�� �ӧ֧���"
44401  "^ff5c00���֧ݧڧܧڧ� �٧�� �ӧ֧���

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff237^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff90,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧѧ� ���֧��, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����ѧҧ�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ӧ֧ݧڧ�ڧӧѧ֧� ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� ^ff5c00��ѧާѧߧ�^ffffff �է� ^96f5ff�ާѧܧ�ڧާѧݧ�ߧ��^ffffff �ߧ� ^96f5ff3^ffffff ��֧�.
�����ާ� ���ԧ�, �ߧ� ^96f5ff5^ffffff ��֧�. ��ѧާѧ� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�.

^ff0000�����֧ܧ� ���ҧڧߧ�ӧ�� ���ߧ�:@1
^ff00001-4 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff4^ff0000 ��֧�.
^ff00005-7 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff6^ff0000 ��֧�.
^ff00008-9 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff8^ff0000 ��֧�.
 ^ff000010 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff10^ff0000 ��֧�.@1@2
^ff0000���ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff%d^ff0000 ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4440 
#define __CPPGEN_GNET_SKILL4440 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4440:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4440 }; 
        Skill4440 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4440Stub:public SkillStub 
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
    Skill4440Stub ():SkillStub (4440) 
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
        gfxfilename         = "����״̬Ч����ǿ2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (25333); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 90000,90000,90000,90000,90000,90000,90000,90000,90000,90000 }; 
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
			/*
			^ff00001-4 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff4^ff0000 ��֧�.
			^ff00005-7 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff6^ff0000 ��֧�.
			^ff00008-9 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff8^ff0000 ��֧�.
			^ff000010 ���.: ��ܧ������ ��֧�֧ާ֧�֧ߧڧ� �ӧ�٧�ѧ��ѧ֧� �է� �ާѧܧ�ڧާ�ާ� �ߧ� ^96f5ff10^ff0000 ��֧�.
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 1000;
			static const int LEVEL_5_7 = 3000;
			static const int LEVEL_8_9 = 5000;
			static const int LEVEL_10_10 = 7000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };					
            skill->GetVictim ()->SetTime (4000 + ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetRatio (9.9);
            skill->GetVictim ()->SetSpeedup (1);
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
