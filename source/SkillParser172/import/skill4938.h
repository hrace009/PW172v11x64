#ifndef __CPPGEN_GNET_SKILL4938
#define __CPPGEN_GNET_SKILL4938
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill4938:public Skill
    {
      public:
        enum
        { SKILL_ID = 4938 };
          Skill4938 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill4938Stub:public SkillStub
    {
      public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 200;
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
                skill->GetPlayer ()->SetDecmp (0.2 * (9.7 * skill->GetLevel () + 25.4));
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
                return 1100;
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
                skill->GetPlayer ()->SetDecmp (0.8 * (9.7 * skill->GetLevel () + 25.4));
                skill->SetPlus (skill->GetLevel () < 3 ? 120 * skill->GetLevel () + 225.9 : 0 
							  || skill->GetLevel () < 4 ? 120 * skill->GetLevel () + 235.1 : 0
							  || skill->GetLevel () < 6 ? 120 * skill->GetLevel () + 255 : 0
							  || skill->GetLevel () < 8 ? 120 * skill->GetLevel () + 325.4 : 0
							  || skill->GetLevel () > 7 ? 120 * skill->GetLevel () + 588.6 : 0);
                skill->SetRatio (0);
                skill->SetDamage (skill->GetAttack ());
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
      Skill4938Stub ():SkillStub (4938)
        {
            cls = 12;
            name = L"����";
            nativename = "����";
            icon = "����.dds";
            max_level = 10;
            type = 1;
            apcost = 0;
            arrowcost = 0;
            apgain = 15;
            attr = 1;
            rank = 2;
            eventflag = 0;
            posdouble = 0;
            clslimit = 0;
            time_type = 0;
            showorder = 1005;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 1;
			{
                restrict_weapons.push_back (59831);
            }  
            effect = "����.sgc";
            range.type = 3;
            doenchant = false;
            dobless = true;
            commoncooldown = 0;
            commoncooldowntime = 0;
			
			pre_skills.push_back (std::pair < ID, int >(4936, 1));
			
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
            statestub.push_back (new State2 ());
            statestub.push_back (new State3 ());
#endif
        }
        virtual ~ Skill4938Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (9.7 * skill->GetLevel () + 25.4);
        }
        int GetExecutetime (Skill * skill) const
        {
            return 1100;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 8000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 18, 23, 28, 33, 38, 43, 48, 53, 58, 63 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 2100, 4100, 7000, 10900, 16100, 23000, 32000, 44100, 60200, 81800 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = {0,0,0,0,0,0,0,0,0,0};//{ 220, 400, 630, 1000, 1450, 1900, 2380, 2880, 3380, 3880 };
            return array[skill->GetLevel () - 1];
        }
        float GetRadius (Skill * skill) const
        {
            return (float) (4.4 + 0.4 * skill->GetLevel ());
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
            return (float) (skill->GetPlayer ()->GetRange ());
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
            skill->GetVictim ()->SetValue (1 * skill->GetTarget ()->GetValid ());
            skill->GetVictim ()->SetAp (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 4.4 + 0.4 * skill->GetLevel ());
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 3;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
#endif
    };
}
#endif
