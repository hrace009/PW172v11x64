/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
63500  "Великая сила грозы"
63501  "^ff5c00Великая сила грозы

^ffcb4aМаг. энергия: ^96f5ff%d^ffffff
^ffcb4aПодготовка: ^ffffff0,7^ffcb4a сек.
^ffcb4aПрименение: ^ffffff1,0^ffcb4a сек.
^ffcb4aПерезарядка: ^ffffff180^ffcb4a сек.
^ffcb4aОграничение по оружию: ^ffffffоружие дальнего боя
^ffcb4aХарактеристика: ^ff5c00Храбрость

^ffcb4aСтатус: ^ffffffМудрец
Лучник заряжается силой грозы, и на ^96f5ff30^ffffff сек. дальность стрельбы увеличивается на ^96f5ff6^ffffff м,
а шанс критического удара для ^96f5ff9^ffffff атак - на ^96f5ff50%%^ffffff.

В течение ^96f5ff10^ffffff сек. постепенно восстанавливает ^96f5ff1^ffffff ци.

^a6caf0Дополнительная стоимость: ^ffffff2^a6caf0 ци.

^ffcb4aЭффект золотой руны@1
^ffcb4a1-4 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff20%%^ffcb4a урона оружия
^ffcb4a5-7 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff30%%^ffcb4a урона оружия
^ffcb4a8-9 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff40%%^ffcb4a урона оружия
^ffcb4a 10 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff50%%^ffcb4a урона оружия@1@2
^ffcb4aНа ^96f5ff30^ffcb4a сек. к наносимому урону добавляется ^96f5ff%d%%^ffcb4a урона оружия.@2"
*/
#ifndef __CPPGEN_GNET_SKILL6350 
#define __CPPGEN_GNET_SKILL6350 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6350:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6350 }; 
        Skill6350 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6350Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1450;
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
                skill->GetPlayer ()->SetDecmp (100);
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
                skill->GetPlayer ()->SetDecmp (172);
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
    Skill6350Stub ():SkillStub (6350) 
    { 
        cls                 = 6; 
        name                = L"ЙсЎ¤ІФАЧЖЖ"; 
        nativename          = "ЙсЎ¤ІФАЧЖЖ"; 
        icon                = "ЙсЎ¤ЗжМмАЧГщ»Ж.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2906; 
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
        effect              = "УрГў_ЗжМмАЧГщ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(1841, 1)); 
        restrict_weapons.push_back (13); 
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
        static int aarray[10] = { 180000,180000,180000,180000,180000,180000,180000,180000,180000,180000 }; 
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
            return (float) (12);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (25);
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1 - 0.0111111 * (180));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 272,272,272,272,272,272,272,272,272,272 }; 
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
            return _snwprintf (buffer, length, format, 272);

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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetValue (6);
            skill->GetVictim ()->SetIncattackrange (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetRatio (0);
            skill->GetVictim ()->SetAmount (9);
            skill->GetVictim ()->SetValue (50);
            skill->GetVictim ()->SetInccountedsmite (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetShowicon (0);
            skill->GetVictim ()->SetAmount (100);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetApgencont (1);
			
			/*
			^ffcb4a1-4 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff20%%^ffcb4a урона оружия
			^ffcb4a5-7 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff30%%^ffcb4a урона оружия
			^ffcb4a8-9 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff40%%^ffcb4a урона оружия
			^ffcb4a 10 ур.: на ^96f5ff30^ffcb4a сек. к урону добавляется ^96f5ff50%%^ffcb4a урона оружия@1@2
			^ffcb4aНа ^96f5ff30^ffcb4a сек. к наносимому урону добавляется ^96f5ff%d%%^ffcb4a урона оружия.
			*/
			static float aarray[10] = { 0.2, 0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.4, 0.4, 0.5 };			
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetRatio ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetGiant (1);
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
            return (float) (25);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) ((player->GetSoulpower () - player->GetLevel () * player->GetLevel () - 50 * player->GetLevel ()) / 10000);
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
            return 33;
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
            return (float) (2);
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
