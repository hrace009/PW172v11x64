/*Skill Parser (c)Deadraky 2022 
44350  "���֧ݧڧܧ�� ��ڧ�ߧڧ� �ާ֧��"
44351  "^ff5c00���֧ݧڧܧ�� ��ڧ�ߧڧ� �ާ֧��

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff50^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff30,0^ffcb4a ��֧�.
^ffcb4a����ݧ��֧ߧڧ� ���: ^ffffff0,1
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff�ާ֧�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00����ѧҧ�����

^ffcb4a����ѧ���: ^ffffff����է�֧�
�����ѧا� �ߧ֧ӧ�٧ާ�اߧ� �ӧ�է֧ݧڧ�� �ܧѧ� ��֧ݧ� �� ��֧�֧ߧڧ� ^96f5ff1^ffffff ��֧�.
���ԧ� �ާ֧�ܧ���� ���ӧ��ѧ֧��� �ߧ� ^96f5ff300%%^ffffff �ߧ� ^96f5ff11^ffffff ��֧�.

^ffeaab�����֧ܧ� ��֧�֧ҧ��ߧ�� ���ߧ�:@1
^ffeaab1-4 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff2^ffeaab ��֧�.
^ffeaab5-7 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff3^ffeaab ��֧�.
^ffeaab8-9 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff4^ffeaab ��֧�.
 ^ffeaab10 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff5^ffeaab ��֧�.@1@2
^ffeaab����ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff%d^ffeaab ��֧�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4435 
#define __CPPGEN_GNET_SKILL4435 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4435:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4435 }; 
        Skill4435 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4435Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (50);
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
    Skill4435Stub ():SkillStub (4435) 
    { 
        cls                 = 8; 
        name                = L"�񡤽���ͨ��"; 
        nativename          = "�񡤽���ͨ��"; 
        icon                = "����ͨ����.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1105; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 10; 
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
        effect              = "����_����ͨ��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "״̬����ʱ������2.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (1); 
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
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
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
        static int aarray[10] = { 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000 }; 
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
        static float aarray[10] = { 50,50,50,50,50,50,50,50,50,50 }; 
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
			^ffeaab1-4 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff2^ffeaab ��֧�.
			^ffeaab5-7 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff3^ffeaab ��֧�.
			^ffeaab8-9 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff4^ffeaab ��֧�.
			^ffeaab10 ���.: ���ߧ�ӧߧ�� ����֧ܧ� �էݧڧ��� ^96f5ff5^ffeaab ��֧�.
			*/			
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 1000;
			static const int LEVEL_5_7 = 2000;
			static const int LEVEL_8_9 = 3000;
			static const int LEVEL_10_10 = 4000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };					
            skill->GetVictim ()->SetTime(1000 + ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetForbidbeselected (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (11000);
            skill->GetVictim ()->SetRatio (3.0);
            skill->GetVictim ()->SetIncaccuracy (1);			
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
            return (float) (0);
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
            return (float) (0);
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
