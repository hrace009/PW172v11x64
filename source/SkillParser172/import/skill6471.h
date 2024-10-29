#ifndef __CPPGEN_GNET_SKILL6471
#define __CPPGEN_GNET_SKILL6471
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6471:public Skill
    {
    public:
        enum { SKILL_ID = 6471 };
        Skill6471 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6471Stub:public SkillStub
    {
    public:
    Skill6471Stub ():SkillStub (6471)
    {
        cls = 14;
        name = L"lxSO";
        nativename = "Ӳ��";
        icon = "Ӳ��.dds";
        max_level = 10;
        type = 5;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 1;
        eventflag = 4;
        is_senior = 0;
        clslimit = 0;
        time_type = 0;
        showorder = 0;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
            restrict_weapons.push_back (69843);
            restrict_weapons.push_back (0);
        }
        effect = "";
        range.type = 0;
        doenchant = false;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(6469, 1));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill6471Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 2,7,12,17,22,27,32,37,42,47 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 15,20,25,30,35,40,45,50,55,60 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 1600,3000,3800,5900,6500,9200,12900,17800,24300,33200 };
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
        bool TakeEffect (Skill * skill) const
        {            
           // skill->GetPlayer ()->SetIncsformmonkeyDefense (skill->GetPlayer ()->GetMaxhp () < 3000 ? 100 + (skill->GetPlayer ()->GetMaxhp () * (0.02 + 0.002 * skill->GetLevel ())) : 3000);
            skill->GetPlayer ()->SetIncsformmonkeyDefense (skill->GetPlayer ()->GetMaxhp () < 100 ? 50 + (skill->GetPlayer ()->GetMaxhp () * (0.01 + 0.002 * skill->GetLevel ())) : 100);
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
