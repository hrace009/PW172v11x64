#ifndef __CPPGEN_GNET_SKILL3026
#define __CPPGEN_GNET_SKILL3026
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3026:public Skill
    {
    public:
        enum { SKILL_ID = 3026 };
        Skill3026 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill3026Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 300;
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
                return 0;
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
                return 1700;
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
                skill->SetRatio ((0.1 * skill->GetLevel ()) - 0.1);
                skill->SetDamage (skill->GetMagicattack ());
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
    Skill3026Stub ():SkillStub (3026)
    {
        cls = 127;
        name = L"����";
        nativename = "����";
        icon = "����.dds";
        max_level = 10;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 0;
        eventflag = 0;
        is_senior = 0;
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
        {
        }
        effect = "����.sgc";
        range.type = 3;
        doenchant = false;
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
    virtual ~ Skill3026Stub () {}
    float GetMpcost (Skill * skill) const
        {
            return (float) (0);
        }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1700,1700,1700,1700,1700,1700,1700,1700,1700,1700 };
        return array[skill->GetLevel () - 1];
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
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    float GetRadius (Skill * skill) const
    {
        return (float) (15);
    }
    float GetAttackdistance (Skill * skill) const
    {
        return (float) (30);
    }
    float GetAngle (Skill * skill) const
    {
        return (float) (1 - 0.0111111 * (60));
    }
    float GetPraydistance (Skill * skill) const
    {
        return (float) (50);
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
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (60);
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
