#ifndef __CPPGEN_GNET_SKILL6247
#define __CPPGEN_GNET_SKILL6247
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6247:public Skill
    {
    public:
        enum { SKILL_ID = 6247 };
        Skill6247 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6247Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 2133;
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
                return skill->GetRand () < 25;
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
                return 1867;
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
                skill->GetPlayer ()->SetDecmp (100);
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
    Skill6247Stub ():SkillStub (6247)
    {
        cls = 8;
        name = L"�";
        nativename = "����ʮ������";
        icon = "����ʮ������.dds";
        max_level = 1;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 8;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 1127;
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
        effect = "����_�Ź�����.sgc";
        range.type = 2;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(1340, 10));
        pre_skills.push_back (std::pair < ID, int >(1342, 3));
        pre_skills.push_back (std::pair < ID, int >(1343, 3));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill6247Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 100,100,100,100,100,100,100,100,100,100 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 2000,2000,2000,2000,2000,2000,2000,2000,2000,2000 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 };
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
            return (float) (0);
        }
#ifdef _SKILL_CLIENT
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format, skill->GetLevel (), 10 + 5 * skill->GetLevel ());

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
            skill->GetVictim ()->SetAmount (0);
            skill->GetVictim ()->SetValue (68893); // Runa no Elements
            skill->GetVictim ()->SetActivatesharpener (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (5);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 0;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (0);
        } 
#endif
    };
}
#endif
