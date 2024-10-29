#ifndef __CPPGEN_GNET_SKILL5430
#define __CPPGEN_GNET_SKILL5430
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill5430:public Skill
    {
    public:
        enum { SKILL_ID = 5430 };
        Skill5430 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill5430Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp (20);
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
                skill->GetPlayer ()->SetDecmp (121);
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
    Skill5430Stub ():SkillStub (5430)
    {
        cls = 0;
        name = L"����";
        nativename = "����";
        icon = "����.dds";
        max_level = 1;
        type = 8;
        apcost = 50;
        arrowcost = 0;
        apgain = 0;
        attr = 7;
        rank = 31;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 2901;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
            restrict_weapons.push_back (0);
            restrict_weapons.push_back (1);
            restrict_weapons.push_back (5);
            restrict_weapons.push_back (9);
            restrict_weapons.push_back (182);
            restrict_weapons.push_back (292);
        }
        effect = "����.sgc";
        range.type = 0;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(1815, 1));
        pre_skills.push_back (std::pair < ID, int >(391, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill5430Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 141,141,141,141,141,141,141,141,141,141 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 600,600,600,600,600,600,600,600,600,600 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 90000,90000,90000,90000,90000,90000,90000,90000,90000,90000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 100 };
            return array[skill->GetLevel () - 1];
        }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 };
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
            return (float) (15);
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
            return 100;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (4600);
            skill->GetVictim ()->SetFix (1);
            skill->GetVictim ()->SetValue (skill->GetT0 () *
                                           (1 +
                                            0.01 * (skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () >
                                                    0 ? skill->GetT1 () -
                                                    skill->GetPlayer ()->GetDefenddegree () : 0)) * (skill->GetPlayer ()->GetHp () <
                                                                                                     0.5 * skill->GetPlayer ()->GetMaxhp ()? 2 : 1));
            skill->GetVictim ()->SetPhysichurt (1);
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
            return 0;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (2 * player->GetPureattack () * (player->GetRand () < player->GetCrit () * 2 ? 2 : 1));
        }
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetAttackdegree ());
        }
#endif
    };
}
#endif
