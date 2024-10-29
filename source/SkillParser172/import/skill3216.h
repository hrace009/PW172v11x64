#ifndef __CPPGEN_GNET_SKILL3216
#define __CPPGEN_GNET_SKILL3216
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3216:public Skill
    {
      public:
        enum
        { SKILL_ID = 3216 };
          Skill3216 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3216Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp (218);
                skill->GetPlayer ()->SetPerform (1);
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
      Skill3216Stub ():SkillStub (3216)
        {
            cls = 3;
            name = L"����";
            nativename = "����";
            icon = "���֮��.dds";
            max_level = 1;
            type = 10;
            apcost = 30;
            arrowcost = 0;
            apgain = 0;
            attr = 0;
            rank = 8;
            eventflag = 1;
			is_senior = 1;
            posdouble = 0;
            clslimit = 0;
            time_type = 1;
            showorder = 2903;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 3;
            {
                restrict_weapons.push_back (292);
            }
            {
                restrict_weapons.push_back (0);
            }
            effect = "����_����_��������.sgc";
            range.type = 0;
            doenchant = true;
            dobless = true;
            commoncooldown = 0;
            commoncooldowntime = 0;
            pre_skills.push_back (std::pair < ID, int >(1828, 1));
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
#endif
        }
        virtual ~ Skill3216Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (218);
        }
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 120000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 100 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 4000000 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredItem (Skill * skill) const
        {
            static int array[10] = { 49921 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = { 4000000 };
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
            return (float) (35);
        }
#ifdef _SKILL_CLIENT
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format, 218);

        }
#endif
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 100;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetFreemove (1);
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (1.5);
            skill->GetVictim ()->SetGiant (1);
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (1.5);
            skill->GetVictim ()->SetIncaccuracy (1);
			
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetRatio (227);
            skill->GetVictim ()->SetAmount (112);
            skill->GetVictim ()->SetValue (1);
            skill->GetVictim ()->SetInsertvstate (1);
            return true;
        }
        bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetTime (16000);
            skill->GetVictim ()->SetFreemove (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {
            skill->GetPlayer ()->SetIncmpgen (2 * skill->GetLevel ());
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (45);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 0;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
#endif
    };
}
#endif
