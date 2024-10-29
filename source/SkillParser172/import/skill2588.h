#ifndef __CPPGEN_GNET_SKILL2588 
#define __CPPGEN_GNET_SKILL2588 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill2588:public Skill 
    { 
    public: 
        enum { SKILL_ID = 2588 }; 
        Skill2588 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill2588Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 950;
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
                skill->GetPlayer ()->SetDecmp (0.2 * (108 + 9.6 * skill->GetLevel ()));
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
                return 735;
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
                skill->GetPlayer ()->SetDecmp (0.8 * (108 + 9.6 * skill->GetLevel ()));
                skill->SetPlus (2.9 * skill->GetLevel () * skill->GetLevel () + 122.4 * skill->GetLevel () + 1006.1);
                skill->SetRatio (0.45 + 0.045 * skill->GetLevel ());
                skill->SetGolddamage ((skill->GetPlayer ()->GetForm () == 1 ? 1.06 : 0.8) * skill->GetMagicattack ());
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
    Skill2588Stub ():SkillStub (2588) 
    { 
        cls                 = 11; 
        name                = L"ËªÀ×Êõ"; 
        nativename          = "ËªÀ×Êõ"; 
        icon                = "ËªÀ×Êõ.dds"; 
        max_level           = 10; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 2; 
        rank                = 5; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 1; 
        npcdelay            = 0; 
        showorder           = 1012; 
        allow_forms         = 3; 
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
        time_type           = 0; 
        long_range          = 0; 
        posdouble           = 0; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        feature             = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
        effect              = "ÔÂÏÉ_ËªÀ×Êõ_»÷ÖÐ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        skillruneattr       = 0; 
        gfx_patch           = ""; 
        hook_name           = "0"; 
        independent         = 0; 
        unc2                = 0; 
        NOP_2               = 0; 
        new_cls             = 2; 
        new_sphera          = 0; 
        pre_skills.push_back (std::pair < ID, int >(2575, 1)); 
        restrict_weapons.push_back (44879); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int array[10] = { 735,735,735,735,735,735,735,735,735,735 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int array[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 }; 
        return skill->GetPlayer ()->GetForm () == 1 ? 1000 : array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int array[10] = { 33370,40334,48447,57997,68750,81600,113950,186390,295240,458250 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int array[10] = { 49,53,57,61,65,69,73,77,81,85 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
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
            return (float) (16.5 + 0.9 * skill->GetLevel () + skill->GetPlayer ()->GetPrayrangeplus ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float array[10] = { 117,127,136,146,156,165,175,184,194,204 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCostShieldEnergy (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
    } 
#ifdef _SKILL_CLIENT 
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format,
                               skill->GetLevel (),
                               16.5 + 0.9 * skill->GetLevel (),
                               108 + 9.6 * skill->GetLevel (),
                               0.8 * 45 + 0.8 * 4.5 * skill->GetLevel (),
                               0.8 * 2.9 * skill->GetLevel () * skill->GetLevel () + 0.8 * 122.4 * skill->GetLevel () + 0.8 * 1006.1,
                               2.9 * skill->GetLevel () * skill->GetLevel () + 122.4 * skill->GetLevel () + 1006.1);

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
            skill->GetVictim ()->SetRatio (2);
            skill->GetVictim ()->SetAmount (0.5 * (2.9 * skill->GetLevel () * skill->GetLevel () + 122.4 * skill->GetLevel () + 1006.1) +
                                            0.1 * skill->GetT0 ());
            skill->GetVictim ()->SetValue (0.5 * (2.9 * skill->GetLevel () * skill->GetLevel () + 122.4 * skill->GetLevel () + 1006.1) +
                                           0.1 * skill->GetT0 ());
            skill->GetVictim ()->SetAddfrosteffect (1);
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
            return (float) (25 + skill->GetLevel () + skill->GetPlayer ()->GetPrayrangeplus ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetMagicattack ());
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
            return (float) (1.0);
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
