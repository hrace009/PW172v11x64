#ifndef __CPPGEN_GNET_SKILL6533
#define __CPPGEN_GNET_SKILL6533
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6533:public Skill
    {
    public:
        enum { SKILL_ID = 6533 };
        Skill6533 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6533Stub:public SkillStub
    {
    public:
    Skill6533Stub ():SkillStub (6533)
    {
        cls = 14;
        name = L"w�";
        nativename = "�桤����ǿ��";
        icon = "�ɱ���ǿ������.dds";
        max_level = 1;
        type = 5;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 20;
        eventflag = 4;
        is_senior = 1;
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
        pre_skills.push_back (std::pair < ID, int >(6472, 10));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill6533Stub () {}
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
        static int array[10] = { 89,89,89,89,89,89,89,89,89,89 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 };
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
            skill->GetPlayer ()->SetIncsformmonkey (0.8);
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
