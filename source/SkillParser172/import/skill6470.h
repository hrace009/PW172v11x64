#ifndef __CPPGEN_GNET_SKILL6470
#define __CPPGEN_GNET_SKILL6470
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6470:public Skill
    {
      public:
        enum
        { SKILL_ID = 6470 };
          Skill6470 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill6470Stub:public SkillStub
    {
      public:
        Skill6470Stub ():SkillStub (6470)
        {
        cls = 14;
        name = L"}v?s?IQ?He?";
        nativename = "???????";
        icon = "???.dds";
        max_level = 10;
        type = 1;
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
        allow_forms = 1;
        {
            restrict_weapons.push_back (69843);
        }
        effect = "???.sgc";
        range.type = 0;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
#endif
        }
        virtual ~ Skill6470Stub ()
        {
        }
        float GetMpcost (Skill * skill) const 
        {
        static float array[10] = { 2,7,12,17,22,27,32,37,42,47 };
        return array[skill->GetLevel () - 1];
        }
        int GetExecutetime (Skill * skill) const 
        {
        static int array[10] = { 1900,1900,1900,1900,1900,1900,1900,1900,1900,1900 };
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
        float GetRadius (Skill * skill) const
        {
            return (float) (12);
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
            return (float) (12);
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
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (11000);
            skill->GetVictim ()->SetRatio (skill->GetLevel () == 1 ? 0.5 : 0.7);
            skill->GetVictim ()->SetDecdefence (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (12);
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
