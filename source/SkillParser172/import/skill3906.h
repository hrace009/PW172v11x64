#ifndef __CPPGEN_GNET_SKILL3906 
#define __CPPGEN_GNET_SKILL3906 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3906:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3906 }; 
        Skill3906 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3906Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
    class State1:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 300; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const
        {
            skill->GetPlayer ()->SetDecmp (28);
            skill->GetPlayer ()->SetPray (1);
        }
        bool Interrupt (Skill * skill) const { return false; }
        bool Cancel (Skill * skill) const { return 1; }
        bool Skip (Skill * skill) const { return 0; }
    };
#endif 
#ifdef _SKILL_SERVER 
    class State2:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 300; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const
        {
            skill->GetPlayer ()->SetDecmp (112);
            skill->SetPlus (7800);
            skill->SetRatio (1.7);
            skill->SetDamage (skill->GetAttack ());
            skill->GetPlayer ()->SetPerform (1);
        }
        bool Interrupt (Skill * skill) const { return false; }
        bool Cancel (Skill * skill) const { return 0; }
        bool Skip (Skill * skill) const { return 0; }
    };
#endif 
#ifdef _SKILL_SERVER 
    class State3:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 0; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const { }
        bool Interrupt (Skill * skill) const { return false; }
        bool Cancel (Skill * skill) const { return 0; }
        bool Skip (Skill * skill) const { return 0; }
    };
#endif 
    Skill3906Stub ():SkillStub (3906) 
    { 
        cls                 = 0; 
        name                = L"Éñ¡¤¶ÏÑÒÕ¶"; 
        nativename          = "Éñ¡¤¶ÏÑÒÕ¶"; 
        icon                = "Éñ¡¤¶ÏÑÒÕ¶ºì°×.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1106; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 5; 
        doenchant           = 0; 
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
        effect              = "1¶ÏÑÒÕ¶.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "Ö±½ÓÉËº¦Ôö¼Ó2.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 1; 
        extra_effect        = 0; 
        stubs_num           = 6; 
        reserve1            = 0; 
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (1); 
        restrict_weapons.push_back (182); 
        restrict_weapons.push_back (5); 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    { 
        static int array[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int array[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int array[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
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
        return (float) (skill->GetPlayer ()->GetRange () + 3 + 0.3 * skill->GetLevel ());
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
        static float array[10] = { 140,140,140,140,140,140,140,140,140,140 }; 
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
            return (float) (14.9);
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
            return 6;
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
            return (float) (2.5);
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
