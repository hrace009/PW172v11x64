/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
34890  "������� ���� � ������"
34891  "^ff5c00������� ���� � ������

^ffcb4a���������: ^ffffff������� �����
^ffcb4a���. �������: ^96f5ff%d^ffffff
^ffcb4a����������: ^ffffff1,0 ^ffcb4a���.
^ffcb4a����������: ^ffffff0,8 ^ffcb4a���.
^ffcb4a�����������: ^ffffff8,0 ^ffcb4a���.
^ffcb4a��������� ��: ^ffffff0,1
^ffcb4a����������� �� ������: ^ffffff������ �������� ���
^ffcb4a��������������: ^ff5c00����

^ffcb4a������: ^ffffff������
������ �������� ������ �������� ���� � ���� ����������� � ������� ^96f5ff8^ffffff � �� ���, ������ ���� ������� �������,
������ �������� ����������� ����� ���� ^96f5ff7717^ffffff ��.

^a6caf0�������������� ���������: ^ffffff2^a6caf0 ������ ��� �������.

^00ffff������ ���������� ����:@1
^00ffff1-4 ��.: ���������� ����������� �� ^ffffff0,8^00ffff ���., ����������� ^ffffff40%%^00ffff ����� ������.
^00ffff5-7 ��.: ���������� ����������� �� ^ffffff0,7^00ffff ���., ����������� ^ffffff60%%^00ffff ����� ������.
^00ffff8-9 ��.: ���������� ����������� �� ^ffffff0,6^00ffff ���., ����������� ^ffffff80%%^00ffff ����� ������.
^00ffff 10 ��.: ���������� ����������� �� ^ffffff0,5^00ffff ���., ����������� ^ffffff100%%^00ffff ����� ������.@1@2
���������� ����������� �� ^ffffff%.1f^00ffff ���., ����������� ^ffffff%d%%^00ffff �����
*/
#ifndef __CPPGEN_GNET_SKILL3489 
#define __CPPGEN_GNET_SKILL3489 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3489:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3489 }; 
        Skill3489 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3489Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
				/*
				^00ffff1-4 ��.: ���������� ����������� �� ^ffffff0,8^00ffff ���., ����������� ^ffffff40%%^00ffff ����� ������.
				^00ffff5-7 ��.: ���������� ����������� �� ^ffffff0,7^00ffff ���., ����������� ^ffffff60%%^00ffff ����� ������.
				^00ffff8-9 ��.: ���������� ����������� �� ^ffffff0,6^00ffff ���., ����������� ^ffffff80%%^00ffff ����� ������.
				^00ffff 10 ��.: ���������� ����������� �� ^ffffff0,5^00ffff ���., ����������� ^ffffff100%%^00ffff ����� ������.
				*/
				static int aarray[10] = { 800,800,800,800,700,700,700,600,600,500 }; 
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
                skill->SetPlus (4819);
				
				/*
				^00ffff1-4 ��.: ���������� ����������� �� ^ffffff0,8^00ffff ���., ����������� ^ffffff40%%^00ffff ����� ������.
				^00ffff5-7 ��.: ���������� ����������� �� ^ffffff0,7^00ffff ���., ����������� ^ffffff60%%^00ffff ����� ������.
				^00ffff8-9 ��.: ���������� ����������� �� ^ffffff0,6^00ffff ���., ����������� ^ffffff80%%^00ffff ����� ������.
				^00ffff 10 ��.: ���������� ����������� �� ^ffffff0,5^00ffff ���., ����������� ^ffffff100%%^00ffff ����� ������.
				*/
				static float aarray[10] = { 0.4, 0.4, 0.4, 0.4, 0.6, 0.6, 0.6, 0.8, 0.8, 1.0 };				
                skill->SetRatio ( aarray[skill->GetLevel () - 1] );
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
    Skill3489Stub ():SkillStub (3489) 
    { 
        cls                 = 6; 
        name                = L"��ը��"; 
        nativename          = "��ը��"; 
        icon                = "��ը����.dds"; 
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
        showorder           = 1310; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 10; 
        doenchant           = 0; 
        dobless             = 0; 
        arrowcost           = 2; 
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
        effect              = "2ը��.sgc"; 
        aerial_effect       = ""; 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "����ʱ������.gfx"; 
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
        static int aarray[10] = { 7000,7000,7000,7000,7000,7000,7000,7000,7000,7000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 99,99,99,99,99,99,99,99,99,99 }; 
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
            return (float) (8);
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
