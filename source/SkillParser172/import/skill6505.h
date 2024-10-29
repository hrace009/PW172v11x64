#ifndef __CPPGEN_GNET_SKILL6505
#define __CPPGEN_GNET_SKILL6505
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6505:public Skill
    {
    public:
        enum { SKILL_ID = 6505 };
        Skill6505 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6505Stub:public SkillStub
    {
    public:
    Skill6505Stub ():SkillStub (6505)
    {
        cls = 14;
        name = L"RN�b��He�g";
        nativename = "��������Ч��";
        icon = "������.dds";
        max_level = 10;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 0;
        eventflag = 0;
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
        allow_forms = 0; //2
        {
            restrict_weapons.push_back (69843);
            restrict_weapons.push_back (0);
        }
        effect = "0";
        range.type = 2;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill6505Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 2,7,12,17,22,27,32,37,42,47 };
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
        static int array[10] = { 0,5,10,15,20,25,30,35,40,45 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 0,300,1200,2800,5200,8400,12800,18600,26300,36500 };
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
            return (float) (1);
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (0);
        }
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool StateAttack (Skill * skill) const
        {   
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime(3000); // Tempo
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetAmount (0.5);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetMonkeyformUltimate (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        } 
#endif
    };
}
#endif
