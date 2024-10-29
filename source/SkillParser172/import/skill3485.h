/*Skill Parser (c)Deadraky 2022 
34850  "���֧ݧڧܧ�� �ԧ��٧�ӧ�� �ߧ֧ҧ�"
34851  "^ff5c00���֧ݧڧܧ�� �ԧ��٧�ӧ�� �ߧ֧ҧ�

^ffcb4a���ѧݧ�ߧ����: ^ffffff�էѧݧ�ߧ�� �ѧ�ѧܧ�
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: �ܧ�ߧ�֧ߧ��ѧ�ڧ� ��ڧݧ�
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,8 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff6,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����اڧ� �էѧݧ�ߧ֧ԧ� �ҧ��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00�ާ���

^ffcb4a����ѧ���: ^ffffff����է�֧�
�����ѧاѧ֧� �����ڧӧߧڧܧ� ��ݧ֧ܧ��ڧ�֧�ܧڧ� ��ѧ٧��է��, �ߧѧߧ��� ����� ���ڧ�ڧ֧� �ާ֧�ѧݧݧ�, ��ѧӧߧ�� �ҧѧ٧�ӧ�ާ� ��ڧ�. ����ߧ� ��ݧ�� ^96f5ff9020^ffffff ����ߧ� ���ڧ�ڧ֧� �ާ֧�ѧݧݧ�.
���ߧڧاѧ֧� �٧ѧ�ڧ�� ��֧ݧ� ��� ���ڧ�ڧ� �ާ֧�ѧݧݧ� �ߧ� ^96f5ff80%%^ffffff �ߧ� ^96f5ff20^ffffff ��֧�.
�� �ӧ֧����ߧ����� ^96f5ff10%%^ffffff ��֧�ѧ�ѧ֧� �����ڧӧߧڧܧ� �ߧ� ^96f5ff3^ffffff ��֧�.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff1^a6caf0 ����֧ݧ� �ڧݧ� ��ߧѧ���.
^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff0,3^a6caf0 ���.

^ffeaab�����֧ܧ� ��֧�֧ҧ��ߧ�� ���ߧ�:@1
����ߧ�֧ߧ��ڧ��֧� ��ڧݧ� �� ��֧�֧ߧڧ� ^96f5ff2^ffeaab ��֧�., �ߧѧߧ��� ^96f5ff120%%^ffeaab ����ߧ� ����اڧ�.
����� �ާڧߧڧާѧݧ�ߧ�� �ܧ�ߧ�֧ߧ��ѧ�ڧ� �ߧѧߧ��ڧ��� ^96f5ff70%%^ffeaab ����ߧ� ����اڧ�.
^ffeaab1-4 ���.: �ާѧܧ�ڧާѧݧ�ߧ� �է�ҧѧӧݧ�֧��� �է� ^96f5ff80%%^ffeaab ����ߧ� ����اڧ�
^ffeaab5-7 ���.: �ާѧܧ�ڧާѧݧ�ߧ� �է�ҧѧӧݧ�֧��� �է� ^96f5ff120%%^ffeaab ����ߧ� ����اڧ�
^ffeaab8-9 ���.: �ާѧܧ�ڧާѧݧ�ߧ� �է�ҧѧӧݧ�֧��� �է� ^96f5ff160%%^ffeaab ����ߧ� ����اڧ�
^ffeaab 10 ���.: �ާѧܧ�ڧާѧݧ�ߧ� �է�ҧѧӧݧ�֧��� �է� ^96f5ff200%%^ffeaab ����ߧ� ����اڧ�@1@2
����� ���ݧߧ�� �ܧ�ߧ�֧ߧ��ѧ�ڧ� ����� ��ӧ֧ݧڧ�ڧӧѧ֧��� �֧�� �ߧ� ^96f5ff%d%%^ffeaab ����ߧ� ����اڧ�.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3485 
#define __CPPGEN_GNET_SKILL3485 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3485:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3485 }; 
        Skill3485 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3485Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
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
                skill->GetPlayer ()->SetDecmp (74);
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
                skill->GetPlayer ()->SetDecmp (296);
                skill->SetPlus (500);
				
				
				static const float LEVEL_1_4 = 0.8;
				static const float LEVEL_5_7 = 1.2;
				static const float LEVEL_8_9 = 1.6;
				static const float LEVEL_10_10 = 2.0;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };	
				
                skill->SetRatio (( aarray[skill->GetLevel () - 1] ) * skill->GetCharging () / 2000);
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
    Skill3485Stub ():SkillStub (3485) 
    { 
        cls                 = 6; 
        name                = L"�񡤾���"; 
        nativename          = "�񡤾���"; 
        icon                = "�񡤾��װ�.dds"; 
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
        showorder           = 1309; 
        allow_forms         = 1; 
        apcost              = 30; 
        apgain              = 0; 
        doenchant           = 1; 
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
        time_type           = 3; 
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
        gfxfilename         = "ֱ���˺�����2.gfx"; 
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
        static int aarray[10] = { 6000,6000,6000,6000,6000,6000,6000,6000,6000,6000 }; 
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
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 370,370,370,370,370,370,370,370,370,370 }; 
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
            skill->GetVictim ()->SetTime (20000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetReducegold (1);
            skill->GetVictim ()->SetProbability (1.0 * 10);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetFix (1);
            skill->GetVictim ()->SetProbability (1.0 * -1);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetSealed (1);
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
