#ifndef __CPPGEN_GNET_SKILL3251
#define __CPPGEN_GNET_SKILL3251
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3251:public Skill
    {
      public:
        enum
        { SKILL_ID = 3251 };
          Skill3251 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3251Stub:public SkillStub
    {
      public:
      Skill3251Stub ():SkillStub (3251)
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
            allow_forms = 1;
            range.type = 0;
            doenchant = true;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
#ifdef _SKILL_SERVER

#endif
        }
        virtual ~ Skill3251Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return 0;
        }
        int GetExecutetime (Skill * skill) const
        {
            return 1001;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 1000;
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
            return (float) (skill->GetPlayer ()->GetRange ());
        }
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime(8000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(20);
            skill->GetVictim ()->SetAmount(2);
            skill->GetVictim ()->SetValue(1119);
            skill->GetVictim ()->SetCooldownaward(1);
            skill->GetVictim ()->SetProbability (100);

            skill->GetVictim ()->SetTime(8000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(20);
            skill->GetVictim ()->SetAmount(2);
            skill->GetVictim ()->SetValue(1300);
            skill->GetVictim ()->SetCooldownaward(1);

            skill->GetVictim ()->SetProbability (100);            
            skill->GetVictim ()->SetTime(8000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(20);
            skill->GetVictim ()->SetAmount(2);
            skill->GetVictim ()->SetValue(1301);
            skill->GetVictim ()->SetCooldownaward(1);

            skill->GetVictim ()->SetProbability (100);            
            skill->GetVictim ()->SetTime(8000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(20);
            skill->GetVictim ()->SetAmount(2);
            skill->GetVictim ()->SetValue(3799);
            skill->GetVictim ()->SetCooldownaward(1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 5);
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
#endif
    };
}
#endif
