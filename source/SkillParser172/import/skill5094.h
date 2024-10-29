#ifndef __CPPGEN_GNET_SKILL5094
#define __CPPGEN_GNET_SKILL5094
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5094:public Skill
    {
      public:
        enum
        { SKILL_ID = 5094 };
          Skill5094 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill5094Stub:public SkillStub
    {
      public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
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
                skill->GetPlayer ()->SetDecmp (30.6 + (9 * skill->GetLevel ()));
                skill->SetPlus ((610.4 + (176 * skill->GetLevel () - 176) + (14 * skill->GetLevel () - 14)) + (skill->GetLevel () > 8 ? 37.76 * skill->GetLevel () : 0));
                skill->SetRatio (0.418 + (0.038 * skill->GetLevel () - 0.038));
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
      Skill5094Stub ():SkillStub (5094)
        {
            cls = 13;
            name = L"����";
            nativename = "����";
            icon = "����.dds";
            max_level = 10;
            type = 1;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 7;
            rank = 2;
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
            allow_forms = 15;
			{
            restrict_weapons.push_back (59830);
			}	
			{
            restrict_weapons.push_back (0);
			}	
            effect = "����.sgc";
            range.type = 0;
            doenchant = true;
            dobless = false;

            is_movingcast = true;
			
            commoncooldown = 0;
            commoncooldowntime = 0;                      
			sheild_energy = 100;
			
			pre_skills.push_back (std::pair < ID, int >(5092, 1));
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
#endif
        }
        virtual ~ Skill5094Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (30.6 + (9 * skill->GetLevel ()));
        }
        int GetExecutetime (Skill * skill) const
        {
            return -1;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 90000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 22, 27, 32, 37, 42, 47, 52, 57, 62, 67 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 6272, 9300, 13112, 17845, 23400, 30222, 38488, 48447, 60320, 75260 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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
            return (float) (20);
        }
#ifdef _SKILL_CLIENT
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format, skill->GetLevel (), 30.6 + (9 * skill->GetLevel ()));

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
            skill->GetVictim ()->SetTime (3200);
            skill->GetVictim ()->SetDizzy (1);
			        
            return true;
        }
				
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (20);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 0;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
