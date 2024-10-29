#ifndef __CPPGEN_GNET_SKILL6473
#define __CPPGEN_GNET_SKILL6473
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6473:public Skill
    {
    public:
        enum { SKILL_ID = 6473 };
        Skill6473 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6473Stub:public SkillStub
    {
    public:
    Skill6473Stub ():SkillStub (6473)
    {
        cls = 14;
        name = L"4l'`�|�";
        nativename = "ˮ�Ծ�ͨ";
        icon = "ˮ�Ծ�ͨ.dds";
        max_level = 1;
        type = 5;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 1;
        eventflag = 1;
        is_senior = 0;
        clslimit = 0;
        time_type = 0;
        showorder = 1501;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 3;
        {
            restrict_weapons.push_back (69843);
        }
        effect = "������.sgc";
        range.type = 0;
        doenchant = false;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill6473Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 2,2,2,2,2,2,2,2,2,2 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1500,1500,1500,1500,1500,1500,1500,1500,1500,1500 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 9,9,9,9,9,9,9,9,9,9 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 500,500,500,500,500,500,500,500,500,500 };
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
            skill->GetPlayer ()->SetIncswim (0.5); 
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
