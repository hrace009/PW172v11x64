#ifndef __CPPGEN_GNET_SKILL3282
#define __CPPGEN_GNET_SKILL3282
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3282:public Skill
    {
      public:
        enum
        { SKILL_ID = 3282 };
          Skill3282 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3282Stub:public SkillStub
    {
      public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
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
                return 800;
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
      Skill3282Stub ():SkillStub (3282)
        {
            cls = 127;
            name = L"虎击";
            nativename = "虎击";
            icon = "虎击.dds";
            max_level = 1;
            type = 3;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 4;
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
            allow_forms = 0;
            range.type = 2;
            doenchant = true;
            dobless = true;
            commoncooldown = 0;
            commoncooldowntime = 0;
            pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
            statestub.push_back (new State2 ());
            statestub.push_back (new State3 ());
#endif
        }
        virtual ~ Skill3282Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return 0;
        }
        int GetExecutetime (Skill * skill) const
        {
            return 800;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 0;
        }
        int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 0 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 0 };
            return array[skill->GetLevel () - 1];
        }
        float GetRadius (Skill * skill) const
        {
            return (float) (15);
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
            return (float) (15);
        }
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 1;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime(15000);
            skill->GetVictim ()->SetRatio(2);
            skill->GetVictim ()->SetAmount(3 * skill->GetT0());
            skill->GetVictim ()->SetValue(3 * skill->GetT0());
            skill->GetVictim ()->SetAddfrosteffect (1);
            
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (GetCls() == -1 ? 0.4 : 0.8);
            skill->GetVictim ()->SetAmount (2);
            skill->GetVictim ()->SetValue (GetCls() == -1 ? 0.4 : 0.8);
            skill->GetVictim ()->SetDecphysicalmagicaldefense(1);
            
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (1);
            skill->GetVictim ()->SetSlowpray (1);
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (2);
            skill->GetVictim ()->SetSlowattack (1);
            return true;
        }
         bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime (100);
            skill->GetVictim ()->SetRatio (15);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue(3297);
            skill->GetVictim ()->SetAuracurse(1);
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
        float GetHitrate (Skill * skill) const
        {
            return (float) (3);
        }
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetMagicattack ());
        }
#endif
    };
}
#endif
