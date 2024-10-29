#ifndef __CPPGEN_GNET_SKILL3901
#define __CPPGEN_GNET_SKILL3901
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3901:public Skill
    {
    public:
        enum { SKILL_ID = 3901 };
        Skill3901 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill3901Stub:public SkillStub
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
            skill->SetPlus (2800);
            skill->SetRatio (0);
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
    Skill3901Stub ():SkillStub (3901)
    {
        cls = 0;
        name = L"SKILL3901";
        nativename = "�񡤶���ն";
        icon = "�񡤶���ն.dds";
        max_level = 1;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 5;
        attr = 1;
        rank = 40;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 1106;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 1;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
            restrict_weapons.push_back (0);
            restrict_weapons.push_back (1);
            restrict_weapons.push_back (182);
            restrict_weapons.push_back (5);
            restrict_weapons.push_back (292);
            restrict_weapons.push_back (9);
        }
        effect = "1����ն.sgc";
        range.type = 0;
        doenchant = 1;
        dobless = 0;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(384, 1));
        pre_skills.push_back (std::pair < ID, int >(385, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill3901Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 140,140,140,140,140,140,140,140,140,140 };
        return array[skill->GetLevel () - 1];
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
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 53887,53887,53887,53887,53887,53887,53887,53887,53887,53887 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000 };
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
#ifdef _SKILL_CLIENT
    int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const { return 0; }
#endif
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (0.6);
            skill->GetVictim ()->SetSlow (1);
            skill->GetVictim ()->SetProbability (1.0 * 20);
            skill->GetVictim ()->SetTime (3500);
            skill->GetVictim ()->SetFix (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (14.9);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 6;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (2.5);
        }
#endif
    };
}
#endif
