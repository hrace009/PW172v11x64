#ifndef __CPPGEN_GNET_SKILL3148
#define __CPPGEN_GNET_SKILL3148
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3148:public Skill
    {
      public:
        enum
        { SKILL_ID = 3148 };
          Skill3148 ():Skill (SKILL_ID)
        {
        }
    };
#endif
    class Skill3148Stub:public SkillStub
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
                return 900;
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
            	skill->GetPlayer ()->SetDisappear (1);
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
      Skill3148Stub ():SkillStub (3148)
        {
            cls = 127;
            name = L"Ů���������";//TODO:parse it
            nativename = "Ů���������";//TODO:parse it
            icon = "";//TODO:parse it
            max_level = 10;
            type = 3;
            apcost = 0;
            arrowcost = 0;
            apgain = 0;
            attr = 1;
            rank = 0;
            eventflag = 0;
            posdouble = 0;
            clslimit = 0;
            time_type = 0;
            showorder = 1425;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 0;
            effect = "";//TODO:parse it
            range.type = 0;
            doenchant = true;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
#ifdef _SKILL_SERVER
            statestub.push_back (new State1 ());
            statestub.push_back (new State2 ());
            statestub.push_back (new State3 ());
#endif
        }
        virtual ~ Skill3148Stub ()
        {
        }
        float GetMpcost (Skill * skill) const
        {
            return (float) (0);
        }
        int GetExecutetime (Skill * skill) const
        {
            return 900;
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
            return (float) (60.0);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (0);
        }
        float GetAngle (Skill * skill) const
        {
        	return (float) (1 - 0.0111111 * (60 + 2.5 * skill->GetLevel ()));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (145.0);
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
        	/* from other skill
        	
            skill->GetVictim ()->SetProbability (1.0 * 140);
            skill->GetVictim ()->SetTime (300);
            skill->GetVictim ()->SetRatio (skill->GetLevel () > 1 ? (skill->GetLevel () == 3 ? 59 : 99) : 41);
            skill->GetVictim ()->SetAmount (34);
            skill->GetVictim ()->SetValue (skill->GetLevel () > 2 ? -135 : -54);
            skill->GetVictim ()->SetDelaytransmit (1);
            
            */
            
            //TODO: pizdec...
            
            skill->GetVictim ()->SetProbability(177.0);
            skill->GetVictim ()->SetTime(50.0);
            
            //TODO:begin===================================================
            float pos1;
            if ( skill->GetLevel () <= 5 )
              pos1 = (float)(204 * skill->GetLevel () - 613);
            else
              pos1 = (float)(204 * skill->GetLevel () - 1633);
            skill->GetVictim ()->SetRatio(pos1);
            //TODO:end=====================================================
            
            skill->GetVictim ()->SetAmount(276.0);
            
            //TODO:begin===================================================
            float pos2;
            if ( skill->GetLevel () <= 5 )
              pos2 = 512.0;
            else
              pos2 = 307.0;
            skill->GetVictim ()->SetValue(pos2);
            //TODO:end=====================================================
            
            skill->GetVictim ()->SetDelaytransmit(1);
            skill->GetVictim ()->SetProbability(100.0);
            skill->GetVictim ()->SetTime(20000.0);
            skill->GetVictim ()->SetSealed2(1);
            skill->GetVictim ()->SetProbability(100.0);
            skill->GetVictim ()->SetTime(2000.0);
            skill->GetVictim ()->SetRatio(0.0);
            skill->GetVictim ()->SetAmount(0.0);
            skill->GetVictim ()->SetValue(200.0);
            skill->GetVictim ()->SetInvisible2(1);
            
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (145.0);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 8;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
