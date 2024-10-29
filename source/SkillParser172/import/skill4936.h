#ifndef __CPPGEN_GNET_SKILL4936
#define __CPPGEN_GNET_SKILL4936
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill4936:public Skill
    {
      public:
        enum
        { SKILL_ID = 4936 };
          Skill4936 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill4936Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp (0.2 * (8.2 * skill->GetLevel () + 6.7));
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
                skill->GetPlayer ()->SetDecmp (0.8 * (8.2 * skill->GetLevel () + 6.7));
                skill->SetPlus (skill->GetLevel () < 3 ? 101.2 * skill->GetLevel () + 102 : 0 
							  || skill->GetLevel () < 4 ? 101.2 * skill->GetLevel () + 111.2 : 0
							  || skill->GetLevel () < 5 ? 101.2 * skill->GetLevel () + 132.6 : 0
							  || skill->GetLevel () < 6 ? 101.2 * skill->GetLevel () + 305.6 : 0
							  || skill->GetLevel () < 8 ? 101.2 * skill->GetLevel () + 356.2 : 0
							  || skill->GetLevel () > 7 ? 101.2 * skill->GetLevel () + 469.2 : 0);
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
      Skill4936Stub ():SkillStub (4936)
        {
            cls = 12;
        name = L"00q0@g";
        nativename = "¡ºÑæ¡»ÖðÉ±";
        icon = "ÑæÖðÉ±.dds";
        max_level = 10;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 15;
        attr = 1;
        rank = 1;
        eventflag = 0;
        is_senior = 0;
        clslimit = 0;
        time_type = 0;
        showorder = 1003;
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
        effect = "Éñ»ú_É¢µ¯_»÷ÖÐ.sgc";
        range.type = 4;
        doenchant = 1;
        dobless = 0;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(4934, 1));
			
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
            statestub.push_back (new State2 ());
            statestub.push_back (new State3 ());
#endif
        }
        virtual ~ Skill4936Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (8.2 * skill->GetLevel () + 6.7);
        }
        int GetExecutetime (Skill * skill) const
        {
            return 1100;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 6000;
        }
         int GetRequiredLevel (Skill * skill) const 
        {
        static int array[10] = { 9,14,19,24,29,34,39,44,49,54 };
        return array[skill->GetLevel () - 1];
        }
         int GetRequiredSp (Skill * skill) const 
         {
        static int array[10] = { 1000,2400,4600,7392,10738,14878,19926,25992,33370,42240 };
          return array[skill->GetLevel () - 1];
         }
         int GetRequiredMoney (Skill * skill) const 
         {
         static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
         return array[skill->GetLevel () - 1];
         }
        float GetRadius (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange ());
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () - 1);
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1 - 0.0111111 * (15));
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
            skill->GetVictim ()->SetTime (5000);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetDecdefence (1);
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
        int GetAttackspeed (Skill * skill) const
        {
            return 20;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
