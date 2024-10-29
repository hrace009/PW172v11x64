#ifndef __CPPGEN_GNET_SKILL6279
#define __CPPGEN_GNET_SKILL6279
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6279:public Skill
    {
    public:
        enum { SKILL_ID = 6279 };
        Skill6279 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6279Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp (35);
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
                return 1667;
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
                skill->GetPlayer ()->SetDecmp (140);
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
    Skill6279Stub ():SkillStub (6279)
    {
        cls = 5;
        name = L"R��";
        nativename = "�ġ�������ӡ��";
        icon = "������ӡ��ħ.dds";
        max_level = 1;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 32;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 1616;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
            restrict_weapons.push_back (23749);
        }
        effect = "��.sgc";
        range.type = 5;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(1285, 1));
        pre_skills.push_back (std::pair < ID, int >(1287, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill6279Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 175,175,175,175,175,175,175,175,175,175 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1667,1667,1667,1667,1667,1667,1667,1667,1667,1667 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 120000,120000,120000,120000,120000,120000,120000,120000,120000,120000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 92,92,92,92,92,92,92,92,92,92 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 };
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
            skill->GetVictim ()->SetTime (60000);
            skill->GetVictim ()->SetRatio (0.60);
            skill->GetVictim ()->SetIncdebuffdodge (1);

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (60000);
            skill->GetVictim ()->SetRatio (0.40);
            skill->GetVictim ()->SetIncdamagedodge (1);

            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
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
