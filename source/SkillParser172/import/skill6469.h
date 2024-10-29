#ifndef __CPPGEN_GNET_SKILL6469
#define __CPPGEN_GNET_SKILL6469
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6469:public Skill
    {
      public:
        enum
        { SKILL_ID = 6469 };
          Skill6469 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill6469Stub:public SkillStub
    {
      public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 50;
            }
            bool Quit (Skill * skill) const
            {
                return false;
            }
            bool Loop (Skill * skill) const
            {
                return false;
            }
            bool Bypass (Skill * skill) const
            {
                return false;
            }
            void Calculate (Skill * skill) const
            {
                skill->GetPlayer ()->SetDecmp (0.2 * (20 * skill->GetLevel () ));
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return false;
            }
            bool Cancel (Skill * skill) const
            {
                return 1;
            }
            bool Skip (Skill * skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State2:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1000;
            }
            bool Quit (Skill * skill) const
            {
                return false;
            }
            bool Loop (Skill * skill) const
            {
                return false;
            }
            bool Bypass (Skill * skill) const
            {
                return false;
            }
            void Calculate (Skill * skill) const
            {
                skill->GetPlayer ()->SetDecmp (0.8 * (20 * skill->GetLevel ()));
                skill->GetPlayer ()->SetPerform (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return false;
            }
            bool Cancel (Skill * skill) const
            {
                return 0;
            }
            bool Skip (Skill * skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State3:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 0;
            }
            bool Quit (Skill * skill) const
            {
                return false;
            }
            bool Loop (Skill * skill) const
            {
                return false;
            }
            bool Bypass (Skill * skill) const
            {
                return false;
            }
            void Calculate (Skill * skill) const
            {
            }
            bool Interrupt (Skill * skill) const
            {
                return false;
            }
            bool Cancel (Skill * skill) const
            {
                return 0;
            }
            bool Skip (Skill * skill) const
            {
                return 0;
            }
        };
#endif
      Skill6469Stub ():SkillStub (6469)
        {
        cls = 14;
        name = L"}v?s�S";
        nativename = "��Գ��";
        icon = "��Գ��.dds";
        max_level = 3;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 1;
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
        allow_forms = 3;
        {
            restrict_weapons.push_back (69843);
            restrict_weapons.push_back (0);
        }
        effect = "��.sgc";
        range.type = 5;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
			statestub.push_back (new State2 ());
			statestub.push_back (new State3 ());
#endif
        }
        virtual ~ Skill6469Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (20 * skill->GetLevel ());
        }
        int GetExecutetime (Skill * skill) const
        {
            return 1000;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 3000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 9, 29, 59 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 500, 5400, 31200 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = {0,0,0,0,0,0,0,0,0,0};//{ 110, 1090, 3980 };
            return array[skill->GetLevel () - 1];
        }
        float GetRadius (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 12);
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
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetAmount (skill->GetLevel () == 1 ? 0.2 : skill->GetLevel () == 2 ? 0.35 : skill->GetLevel () == 3 ? 0.5 : 0);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetMonkeyform (1);

            skill->GetVictim ()->SetTime (skill->GetPlayer ()->GetForm () == 1 ? 2600 : 1);
            skill->GetVictim ()->SetFreemoveMonkey (skill->GetPlayer ()->GetForm () == 1 ? 1 : 0);

           //skill->GetVictim ()->SetProbability (1.0 * (skill->GetPlayer ()->GetForm () == 1 ? 100 : 1));
           // skill->GetVictim ()->SetTime (skill->GetPlayer ()->GetForm () == 1 ? 2000 : 1);
           // skill->GetVictim ()->SetRatio (12);
           // skill->GetVictim ()->SetAmount (1);
           //  skill->GetVictim ()->SetValue (6470);
           //  skill->GetVictim ()->SetAuracurseMonkey (1);
                   
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
