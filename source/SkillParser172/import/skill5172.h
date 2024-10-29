#ifndef __CPPGEN_GNET_SKILL5172
#define __CPPGEN_GNET_SKILL5172
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5172:public Skill
    {
      public:
        enum
        { SKILL_ID = 5172 };
          Skill5172 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill5172Stub:public SkillStub
    {
      public:
		Skill5172Stub ():SkillStub (5172)
        {
            cls = 13;
            name = L"????";
            nativename = "????";
            icon = "??????.dds";
            max_level = 1;
            type = 5;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 0;
            rank = 32;
            eventflag = 1;
			is_senior = 1;
            posdouble = 0;
            clslimit = 0;
            time_type = 0;
            showorder = 1203;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 1;
            {
            restrict_weapons.push_back (59830);
			}
            effect = "";
            range.type = 0;
            doenchant = false;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;			
			
			pre_skills.push_back (std::pair < ID, int >(5090, 5));
#ifdef _SKILL_SERVER
#endif
        }
        virtual ~ Skill5172Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (0);
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
            static int array[10] = { 100 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 1000000 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredItem (Skill * skill) const
        {
            static int array[10] = { 60732 };
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
            skill->GetPlayer ()->SetNewSheildMax ( 30.0f );
			skill->GetPlayer ()->SetNewSheildGen ( 2.0f );
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
