#ifndef __CPPGEN_GNET_SKILL5520
#define __CPPGEN_GNET_SKILL5520
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5520:public Skill
    {
    public:
        enum { SKILL_ID = 5520 };
        Skill5520 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill5520Stub:public SkillStub
    {
    public:
        Skill5520Stub ():SkillStub (5520)
    {
        cls = 255;
        name = L"CQKNR";
        nativename = "��֮��";
        icon = "��֮������.dds";
        max_level = 10;
        type = 5;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 0;
        rank = 41;
        eventflag = 1;
        is_senior = 0;
        clslimit = 0;
        time_type = 0;
        showorder = 2001;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 0;
        {
        }
        effect = "";
        range.type = 0;
        doenchant = 0;
        dobless = 0;
        commoncooldown = 0;
        commoncooldowntime = 0;

        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill5520Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 105,105,105,105,105,105,105,105,105,105 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 62139,62139,62139,62139,62139,62140,62140,62140,62140,62140 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredRealmLevel (Skill * skill) const 
    {
        static int array[10] = { 60,60,60,60,60,60,60,60,60,60 };
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
            return _snwprintf (buffer, length, format, 1);
        }
#endif
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool TakeEffect (Skill * skill) const
        {			
			skill->GetPlayer ()->SetAddskilldamage2 (0.02 * skill->GetLevel ());
            skill->GetPlayer ()->SetAttackMPasive (10 * skill->GetLevel ());
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
