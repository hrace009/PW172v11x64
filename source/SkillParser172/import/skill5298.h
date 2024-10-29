#ifndef __CPPGEN_GNET_SKILL5298
#define __CPPGEN_GNET_SKILL5298
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5298:public Skill
    {
    public:
        enum { SKILL_ID = 5298 };
        Skill5298 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill5298Stub:public SkillStub
    {
    public:
        Skill5298Stub ():SkillStub (5298)
        {
        cls = 255;
        name = L"SKILL5298";
        nativename = "��������";
        icon = "��������.dds";
        max_level = 6;
        type = 5;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 0;
        rank = 0;
        eventflag = 1;
        is_senior = 1;
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
            effect = "";
            range.type = 0;
            doenchant = false;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;

        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill5298Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 0 };
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
            skill->GetPlayer ()->SetIncdefencePatente (0.05 * skill->GetLevel ());
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
