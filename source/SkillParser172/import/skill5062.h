 //Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/*50620  "���֧ݧڧܧڧ� ��ѧߧ֧� ��ݧѧާ֧ߧ�"
50621  "^ff5c00���֧ݧڧܧڧ� ��ѧߧ֧� ��ݧѧާ֧ߧ�

^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff210^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff�ާԧߧ�ӧ֧ߧߧ�
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff15,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����ߧѧ� ����ܧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff�������
�����֧ݧ�� �ާԧߧ�ӧ֧ߧߧ� ��֧�֧ާ֧�ѧ֧��� �ߧ� ^96f5ff25^ffffff �� �ӧ�֧�֧�.
�����ާ� ���ԧ�, �ߧ� ^96f5ff0,5^ffffff ��֧�. ��� ���ݧ��ѧ֧� �ڧާާ�ߧڧ�֧� �� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�.

^ffeaab�����֧ܧ� ��֧�֧ҧ��ߧ�� ���ߧ�:@1
����٧ӧ�ݧ�֧� �ڧ���ݧ�٧�ӧѧ�� ��ާ֧ߧڧ� ���ڧاէ� �� ��ӧ֧ݧڧ�ڧӧѧ֧� �էݧڧ�֧ݧ�ߧ���� �ڧާާ�ߧڧ�֧��
�� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�.
^ffeaab1-4 ���.: �ڧާާ�ߧڧ�֧� �է֧ۧ��ӧ�֧� ^96f5ff1,5^ffeaab ��֧�.
^ffeaab5-7 ���.: �ڧާާ�ߧڧ�֧� �է֧ۧ��ӧ�֧� ^96f5ff2,0^ffeaab ��֧�.
^ffeaab8-9 ���.: �ڧާާ�ߧڧ�֧� �է֧ۧ��ӧ�֧� ^96f5ff2,5^ffeaab ��֧�.
^ffeaab 10 ���.: �ڧާާ�ߧڧ�֧� �է֧ۧ��ӧ�֧� ^96f5ff3,0^ffeaab ��֧�.@1@2
����٧ӧ�ݧ�֧� �ڧ���ݧ�٧�ӧѧ�� ��ާ֧ߧڧ� ���ڧاէ�.
���ާާ�ߧڧ�֧� �� ����֧ܧ�ѧ�, ��ԧ�ѧߧڧ�ڧӧѧ��ڧ� ��֧�֧էӧڧا֧ߧڧ�, �է֧ۧ��ӧ�֧� ^96f5ff%.1f^ffeaab ��֧�.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL5062 
#define __CPPGEN_GNET_SKILL5062 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5062:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5062 }; 
        Skill5062 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5062Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (10);
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
                skill->GetPlayer ()->SetDecmp (200);
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
    Skill5062Stub ():SkillStub (5062) 
    { 
        cls                 = 12; 
#ifdef _SKILL_CLIENT 
        name                = L"������Ʈɱ"; 
        nativename          = "������Ʈɱ"; 
        icon                = "������Ʈɱ��.dds"; 
#endif 
        max_level           = 1; 
        type                = 8; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 0; 
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
#ifdef _SKILL_CLIENT 
        effect              = ""; 
        aerial_effect       = ""; 
#endif 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "����״̬Ч����ǿ1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        restrict_weapons.push_back (59831); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 601,601,601,601,601,601,601,601,601,601 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 }; 
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
            return (float) (25);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 210,210,210,210,210,210,210,210,210,210 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCoolDownLimit (Skill * skill) const 
    { 
        static int aarray[10] = { 3,3,3,3,3,3,3,3,3,3 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 1);
            skill->GetVictim ()->SetTime (0);
            skill->GetVictim ()->SetRatio (0.65);
            skill->GetVictim ()->SetIncdebuffdodge (1);
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
            return (float) (25);
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
