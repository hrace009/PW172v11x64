#ifndef __CPPGEN_GNET_SKILL1370
#define __CPPGEN_GNET_SKILL1370
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill1370:public Skill
    {
      public:
        enum
        { SKILL_ID = 1370 };
          Skill1370 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill1370Stub:public SkillStub
    {
      public:
        Skill1370Stub ():SkillStub (1370)
        {
            cls = 8;
            name = L"�������ۼ���";
            nativename = "�������ۼ���";
            icon = "";
            max_level = MAX_LEVEL;
            type = 3;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 0;
            rank = 0;
            eventflag = 0;
            posdouble = 0;
            clslimit = 0;
            time_type = 0;
            showorder = 0;
            allow_land = 1;
            allow_air = 0;
            allow_water = 0;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 1;
            restrict_corpse = 0;
            allow_forms = 0;
            effect = "�������ۼ���.sgc";
            range.type = 0;
            doenchant = true;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
            pre_skills.push_back (std::pair < ID, int >(0, 0));
#ifdef _SKILL_SERVER
#endif
        }
        virtual ~ Skill1370Stub ()
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
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (180000);
            skill->GetVictim ()->SetValue (skill->GetLevel ());
            skill->GetVictim ()->SetSubattackdegree (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (180000);
            skill->GetVictim ()->SetValue (skill->GetLevel ());
            skill->GetVictim ()->SetSubdefencedegree (1);
            skill->GetVictim ()->SetValue (1.5 * 5.7 * skill->GetLevel () * skill->GetLevel () + 1.5 * 238.5 * skill->GetLevel () + 1.5 * 1960);
            skill->GetVictim ()->SetGoldhurt (1);
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
            return (float) (1.0);
        }
#endif
    };
}
#endif
