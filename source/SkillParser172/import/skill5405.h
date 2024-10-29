/*Skill Parser (c)Deadraky 2022 
54050  "���֧ݧڧܧѧ� ������ �� �է���"
54051  "^ff5c00���֧ݧڧܧѧ� ������ �� �է���

^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff60,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާѧԧڧ�֧�ܧ�� ����اڧ�, �ҧ֧� ����اڧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
���֧�֧ӧ�էڧ� 2 ��� �� ^96f5ff20%%^ffffff ��� �ާѧܧ�ڧާѧݧ�ߧ�ԧ� �٧ѧ�ѧ�� ���� �ާѧԧ�.
�� ��֧�֧ߧڧ� ^96f5ff6^ffffff ��֧�. ���էԧ���ӧܧ� �ӧ�֧� �٧ѧܧݧڧߧѧߧڧ� �ާѧԧ� ���ѧߧ�ӧڧ��� ���ѧܧ�ڧ�֧�ܧ� �ާԧߧ�ӧ֧ߧߧ��,
�� ��ѧ� ��� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �ܧ� �ӧ�֧� �ߧ֧ԧѧ�ڧӧߧ�� ����֧ܧ�ѧ�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���.

^00ff00�����֧ܧ� �ڧ٧�ާ��էߧ�� ���ߧ�:@1
^00ff001-4 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff40%%^00ff00;
^00ff005-7 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff60%%^00ff00;
^00ff008-9 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff80%%^00ff00;
 ^00ff0010 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff100%%^00ff00.@1@2
^00ff00�������ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff%d%%^00ff00.@2"
*/
#ifndef __CPPGEN_GNET_SKILL5405 
#define __CPPGEN_GNET_SKILL5405 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5405:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5405 }; 
        Skill5405 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5405Stub:public SkillStub 
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
    Skill5405Stub ():SkillStub (5405) 
    { 
        cls                 = 1; 
        name                = L"�񡤰����ľ�"; 
        nativename          = "�񡤰����ľ�"; 
        icon                = "������ľ���.dds"; 
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
        showorder           = 1217; 
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
        effect              = "�����ľ�.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(183, 1)); 
        restrict_weapons.push_back (292); 
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
        static int aarray[10] = { 120000,120000,120000,120000,120000,120000,120000,120000,120000,120000 }; 
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
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 }; 
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
            return (float) (0);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
			^00ff001-4 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff40%%^00ff00;
			^00ff005-7 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff60%%^00ff00;
			^00ff008-9 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff80%%^00ff00;
			^00ff0010 ���.: �ӧ����ѧߧ�ӧݧ֧ߧڧ� ���� ��ӧ֧ݧڧ�ڧӧѧ֧��� �է� ^96f5ff100%%
			*/			
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetImmuneall (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);			
			static const float LEVEL_1_4 = 0.2;
			static const float LEVEL_5_7 = 0.4;
			static const float LEVEL_8_9 = 0.6;
			static const float LEVEL_10_10 = 0.8;
			static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };				
            skill->GetVictim ()->SetRatio (0.2 + ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetScaleincmp (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetFastpray (1);
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
            return (float) (30);
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
