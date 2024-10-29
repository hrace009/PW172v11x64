#ifndef __CPPGEN_GNET_SKILL3249
#define __CPPGEN_GNET_SKILL3249
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3249:public Skill
    {
      public:
        enum
        { SKILL_ID = 3249 };
          Skill3249 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3249Stub:public SkillStub
    {
      public:
      Skill3249Stub ():SkillStub (3249)
        {
            cls = 5;
            name = L"虎击";
            nativename = "虎击";
            icon = "虎击.dds";
            max_level = 10;
            type = 2;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 1;
            rank = 0;
            eventflag = 0;
            posdouble = 0;
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
            allow_forms = 0;
            range.type = 0;
            doenchant = true;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
#ifdef _SKILL_SERVER

#endif
        }
        virtual ~ Skill3249Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return 0;
        }
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 0;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 0};
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
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
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime(3000);
            skill->GetVictim ()->SetRatio(2);
            skill->GetVictim ()->SetSlowattack(1);
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime(3000);
            skill->GetVictim ()->SetRatio(0);
            skill->GetVictim ()->SetAmount(10);
            skill->GetVictim ()->SetValue(12);
            skill->GetVictim ()->SetInvisible2(1);
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
