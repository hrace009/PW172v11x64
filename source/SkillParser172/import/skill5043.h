/*Skill Parser (c)Deadraky 2022 
50430  "���֧ݧڧܧڧ� �է֧ӧ��� ���ݧߧ�"
50431  "^ff5c00���֧ݧڧܧڧ� �է֧ӧ��� ���ݧߧ�

^ffcb4a���ѧݧ�ߧ����: ^ffffff�էѧݧ�ߧ�� �ѧ�ѧܧ�
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff167^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff0,1 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff3,0 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff45,0 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����ߧѧ� ����ܧ�
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
���ڧ�ߧڧ� �٧ѧݧڧӧѧ֧� �ߧ֧ҧ��ӧ��. �� �����ڧӧߧڧܧ� ��էߧ� �٧� �է��ԧ�� �����֧ާݧ����� �է֧ӧ��� ��ѧܧ֧�,
�ܧ������ �ߧѧߧ���� �֧ާ� ���ާާѧ�ߧ�� ����� �� ��ѧ٧ާ֧�� ^96f5ff400%%^ffffff ��� �ҧѧ٧�ӧ�ԧ� ��ڧ٧ڧ�֧�ܧ�ԧ� ����ߧ�.
����ݧ� �����ڧӧߧڧ� �ߧѧ��էڧ��� �� ���֧է֧ݧѧ� ^96f5ff10^ffffff �� ��� ����֧ݧܧ�, ��� �֧ԧ� ����ѧݧܧڧӧѧ֧� �ߧѧ٧ѧ� �ߧ� ^96f5ff15^ffffff ��.

^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff1^a6caf0 ���.

^ffeaab�����֧ܧ� ��֧�֧ҧ��ߧ�� ���ߧ�:@1
����٧ӧ�ݧ�֧� �ڧ���ݧ�٧�ӧѧ�� ��ާ֧ߧڧ� �էӧѧاէ� �� �ߧѧߧ��ڧ� �է���ݧߧڧ�֧ݧ�ߧ�� �����.
^ffeaab1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff36%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
^ffeaab5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff54%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
^ffeaab8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff72%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
 ^ffeaab10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff90%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�@1@2
^ffeaab����٧ӧ�ݧ�֧� �ڧ���ݧ�٧�ӧѧ�� ��ާ֧ߧڧ� �էӧѧاէ� �� �է���ݧߧڧ�֧ݧ�ߧ� �ߧѧߧ��ڧ� ^96f5ff%d%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�.@2
*/
#ifndef __CPPGEN_GNET_SKILL5043 
#define __CPPGEN_GNET_SKILL5043 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5043:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5043 }; 
        Skill5043 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5043Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (0.2 * (167));
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
                skill->GetPlayer ()->SetDecmp (0.8 * (167));
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
                return 202;
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
				/*
				^ffeaab1-4 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff36%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
				^ffeaab5-7 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff54%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
				^ffeaab8-9 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff72%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
				^ffeaab10 ���.: �է�ҧѧӧݧ�֧��� ^96f5ff90%%^ffeaab �ҧѧ٧�ӧ�ԧ� ��ڧ�. ����ߧ�
				*/
                skill->SetSection (1);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
                return 212;
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
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
                return 402;
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
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
                return 422;
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
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
                return 602;
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
                skill->SetSection (5);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
        class State8:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 650;
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
                skill->SetSection (6);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
        class State9:public SkillStub::State
       {
          public:
            int GetTime (Skill * skill) const
            {
                return 700;
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
                skill->SetSection (7);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
        class State10:public SkillStub::State
       {
          public:
            int GetTime (Skill * skill) const
            {
                return 700;
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
                skill->SetSection (8);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
        class State11:public SkillStub::State
       {
          public:
            int GetTime (Skill * skill) const
            {
                return 700;
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
                skill->SetSection (9);
                skill->SetPlus (0);
                skill->SetRatio (0);
				static const float LEVEL_1_4 = 0.04;
				static const float LEVEL_5_7 = 0.06;
				static const float LEVEL_8_9 = 0.08;
				static const float LEVEL_10_10 = 0.1;
				static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };						
                skill->SetDamage ((0.44 + ( aarray[skill->GetLevel () - 1] )) * skill->GetAttack ());
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
        class State12:public SkillStub::State
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
    Skill5043Stub ():SkillStub (5043) 
    { 
        cls                 = 12; 
        name                = L"��һ��̰��"; 
        nativename          = "��һ��̰��"; 
        icon                = "��һ��̰����.dds"; 
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
        showorder           = 1012; 
        allow_forms         = 1; 
        apcost              = 100; 
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
        effect              = "ҹӰ_���粨_����.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "ֱ���˺�����2.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 1301; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (59831); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
        statestub.push_back (new State4 ()); 
        statestub.push_back (new State5 ()); 
        statestub.push_back (new State6 ()); 
        statestub.push_back (new State7 ()); 
        statestub.push_back (new State8 ()); 
        statestub.push_back (new State9 ()); 
        statestub.push_back (new State10 ()); 
        statestub.push_back (new State11 ()); 
        statestub.push_back (new State12 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 45000,45000,45000,45000,45000,45000,45000,45000,45000,45000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 89,89,89,89,89,89,89,89,89,89 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 167,167,167,167,167,167,167,167,167,167 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCoolDownLimit (Skill * skill) const 
    { 
        static int aarray[10] = { 2,2,2,2,2,2,2,2,2,2 }; 
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
            return 100;
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
            float rapel = 0.0f;
			if(skill->GetSection () == 1) rapel = 100.0f; // ����ѧݧܧڧӧѧ֧� ���ݧ�ܧ� ��֧�ӧ�� ��էѧ���

			// ����ѧݧܧڧӧѧ֧� �֧�ݧ� ��֧ݧ� �ߧѧ��էڧ��� �ߧ� ��ѧ�����ߧڧ� �է� 10 �ާ֧����
            skill->GetVictim ()->SetProbability (1.0 * skill->GetT0 () < 11 ? rapel : 0);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetAmount (1000);
            skill->GetVictim ()->SetValue (15);
            skill->GetVictim ()->SetRepel2 (1);
            skill->GetVictim ()->SetProbability (1.0 * skill->GetT0 () < 11 ? rapel : 0);
            skill->GetVictim ()->SetValue (15);
            skill->GetVictim ()->SetRepel (1);
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
        return 5; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const // ��ѧ�����ߧڧ� �է� ��֧ݧ�
        {
            return (float) (player->GetRangetotarget ());
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
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
    float GetHitrate (Skill * skill) const 
    { 
        return 1; 
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
