#ifndef __CPPGEN_GNET_SKILL3263
#define __CPPGEN_GNET_SKILL3263
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3263:public Skill
    {
      public:
        enum
        { SKILL_ID = 3263 };
          Skill3263 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3263Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp(225);
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
#ifdef _SKILL_SERVER
        class State2:public SkillStub::State
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
      Skill3263Stub ():SkillStub (3263)
        {
            cls = 8;
            name = L"����";
            nativename = "����";
            icon = "����.dds";
            max_level = 2;
            type = 2;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 1;
            rank = 8;
            eventflag = 0;
            posdouble = 0;
            clslimit = 0;
            time_type = 1;
            showorder = 1125;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 1;
            {
                restrict_weapons.push_back (1);
            }
            effect = "����.sgc";
            range.type = 5;
            doenchant = true;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
            itemcost = 49982;
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
            statestub.push_back (new State2 ());
#endif
        }
        virtual ~ Skill3263Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return 225;
        }
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 300000;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 100};
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 1000000};
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredItem (Skill * skill) const
        {
            static int array[10] = {49959, 49960};//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = {0};//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return array[skill->GetLevel () - 1];
        }
        float GetRadius (Skill * skill) const
        {
            return (float) (16);
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
            skill->GetVictim ()->SetTime(10000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(2);
            skill->GetVictim ()->SetAmount(1);
            skill->GetVictim ()->SetValue(0.5);
            skill->GetVictim ()->SetGiantform(1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (5.0);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 9;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
