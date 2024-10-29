//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
54860  "Великие когти небес"54861  "^ff5c00Великие когти небес^ffcb4aДальность: ^ffffffдальняя атака^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffff1,0 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff0,8 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff30 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffоружие дальнего боя^ffcb4aХарактеристика: ^ff5c00Мощь^ffcb4aСтатус: ^ffffffМудрецЛучник призывает волшебную птицу, которая бросается на противника и наносит емубазовый физический урон, плюс ^96f5ff100%%^ffffff урона оружия, плюс ^96f5ff8343^ffffff ед. урона стихией металла.В течение ^96f5ff15^ffffff сек. физическая и магическая защита противника снижаются на ^96f5ff50%%^ffffff,а скорость его передвижения - на ^96f5ff80%%^ffffff.^a6caf0Требуется ^ffffff1^a6caf0 стрела или снаряд.^a6caf0Дополнительная стоимость: ^ffffff2^a6caf0 ци.^00ffffЭффект сапфировой руны:@1^00ffff1-4 ур.: время подготовки сокращается до ^ffffff0,8^00ffff сек.,физическая и магическая защита противника снижаются на ^ffffff60%%^00ffff^00ffff5-7 ур.: время подготовки сокращается до ^ffffff0,7^00ffff сек.,физическая и магическая защита противника снижаются на ^ffffff65%%^00ffff^00ffff8-9 ур.: время подготовки сокращается до ^ffffff0,6^00ffff сек.,физическая и магическая защита противника снижаются на ^ffffff70%%^00ffff^00ffff 10 ур.: время подготовки сокращается до ^ffffff0,5^00ffff сек.,физическая и магическая защита противника снижаются на ^ffffff75%%^00ffff@1@2Время подготовки сокращается до ^ffffff%.1f^00ffff сек.,физическая и магическая защита противника снижаются на ^ffffff%d%%^00ffff.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL5486 
#define __CPPGEN_GNET_SKILL5486 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5486:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5486 }; 
        Skill5486 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5486Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
				/*
				^00ffff1-4 ��.: ����� ���������� ����������� �� ^ffffff0,8^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff60%%^00ffff
				^00ffff5-7 ��.: ����� ���������� ����������� �� ^ffffff0,7^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff65%%^00ffff
				^00ffff8-9 ��.: ����� ���������� ����������� �� ^ffffff0,6^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff70%%^00ffff
				^00ffff 10 ��.: ����� ���������� ����������� �� ^ffffff0,5^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff75%%^00ffff@1@2
				����� ���������� ����������� �� ^ffffff%.1f^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff%d%%^00ffff.@2
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
                skill->GetPlayer ()->SetDecmp (110);
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
                skill->GetPlayer ()->SetDecmp (440);
                skill->SetPlus (8343);
                skill->SetRatio (1.0);
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
    Skill5486Stub ():SkillStub (5486) 
    { 
        cls                 = 6; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤿�����ӥ"; 
        nativename          = "�񡤿�����ӥ"; 
        icon                = "�������ӥ��.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 2; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1311; 
        allow_forms         = 1; 
        apcost              = 200; 
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
        effect              = "1������ӥ.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
        return (float) (0); 
    } 
    float GetPraydistance (Skill * skill) const 
    { 
        static float aarray[10] = { 0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 550,550,550,550,550,550,550,550,550,550 }; 
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
    int GetIntroduction (Skill * skill, const wchar_t * buffer, int length, const wchar_t * format) const 
    { 
        return 0; 
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
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio (0.3);
				skill->GetVictim ()->SetAmount (skill->GetT0 () *
												(1 +
												 0.01 * (skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () >
														 0 ? skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () : 0)));
				skill->GetVictim ()->SetEaglecurse (1);
				
				/*
				^00ffff1-4 ��.: ����� ���������� ����������� �� ^ffffff0,8^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff60%%^00ffff
				^00ffff5-7 ��.: ����� ���������� ����������� �� ^ffffff0,7^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff65%%^00ffff
				^00ffff8-9 ��.: ����� ���������� ����������� �� ^ffffff0,6^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff70%%^00ffff
				^00ffff 10 ��.: ����� ���������� ����������� �� ^ffffff0,5^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff75%%^00ffff@1@2
				����� ���������� ����������� �� ^ffffff%.1f^00ffff ���.,
				���������� � ���������� ������ ���������� ��������� �� ^ffffff%d%%^00ffff.@2
				*/
				static float aarray[10] = { 0.6, 0.6, 0.6, 0.6, 0.65, 0.65, 0.65, 0.7, 0.7, 0.75 };				
				skill->GetVictim ()->SetProbability (1.0 * 100);
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
				skill->GetVictim ()->SetDecdefence (1);
				skill->GetVictim ()->SetProbability (1.0 * 100);
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
				skill->GetVictim ()->SetDecresist (1);

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
            return (float) (skill->GetPlayer ()->GetRange () + 5);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (6 * player->GetWeapondamage () + 12000);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetAttackdegree ());
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
        return 1; 
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
