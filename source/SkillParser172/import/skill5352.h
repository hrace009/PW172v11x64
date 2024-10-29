#ifndef __CPPGEN_GNET_SKILL5352
#define __CPPGEN_GNET_SKILL5352
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5352:public Skill
    {
      public:
        enum
        { SKILL_ID = 5352 };
          Skill5352 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill5352Stub:public SkillStub
    {
      public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 600;
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
                skill->GetPlayer ()->SetPray (1);
            }
            bool Interrupt (Skill * skill) const
            {
                return skill->GetRand () < 5;
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
                return 100;
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
                skill->GetPlayer ()->SetPerform (2);
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
                return 1500;
            }
            bool Quit (Skill * skill) const
            {
                return false;
            }
            bool Loop (Skill * skill) const
            {
                return skill->GetPlayer ()->GetMp () > 279 && skill->GetSection () < (skill->GetLevel () == 1 ? 8 : 16);
            }
            bool Bypass (Skill * skill) const
            {
                return false;
            }
            void Calculate (Skill * skill) const
            {
                skill->SetSection (skill->GetSection () + 1);
                skill->GetPlayer ()->SetDecmp (278);
                skill->SetPlus (6406);
                skill->SetRatio (4.3);
                skill->SetDamage (0.2 * skill->GetAttack ());
                skill->GetPlayer ()->SetCombat (1);
                skill->GetPlayer ()->SetPerform (0);
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
        class State4:public SkillStub::State
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
      Skill5352Stub ():SkillStub (5352)
        {
            cls = 13;
			name = L"����";
			nativename = "����";
			icon = "����.dds";
			max_level = 2;
			type = 1;
			apcost = 0;
			arrowcost = 0;
			apgain = 0;
			attr = 1;
			rank = 8;
			eventflag = 0;
			is_senior = 0;
			clslimit = 0;
			time_type = 2;
			showorder = 0;
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
            effect = "����.sgc";
            range.type = 2;
            doenchant = false;
            dobless = true;
            commoncooldown = 0;
            commoncooldowntime = 0;
			is_movingcast = true;
			
			itemcost = 49982;
			
			pre_skills.push_back (std::pair < ID, int >(0, 1));
			
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
			statestub.push_back (new State2 ());
			statestub.push_back (new State3 ());
			statestub.push_back (new State4 ());
#endif
        }
        virtual ~ Skill5352Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (278);
        }
        int GetExecutetime (Skill * skill) const
        {
            return -1;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 300000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 100, 100 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 1000000, 2000000 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredItem (Skill * skill) const
        {
            static int array[10] = { 60736, 60737 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = { 1000000, 2000000 };
            return array[skill->GetLevel () - 1];
        }
        float GetRadius (Skill * skill) const
        {
            return (float) (9);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (8);
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1 - 0.0111111 * (0));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 50);
        }
#ifdef _SKILL_CLIENT
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format , 278, 278, 4800);
        }
#endif
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * skill->GetSection () < 2 ? 100 : 0);
			skill->GetVictim ()->SetTime (skill->GetLevel () == 1 ? 11000 : 21000);
			skill->GetVictim ()->SetAmount (0.5); // Defesa       
            skill->GetVictim ()->SetRatio (1); // Speed	
            skill->GetVictim ()->SetUltimatePaladin (1);
            return true;
        }					
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (25);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 30;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
#endif
    };
}
#endif
