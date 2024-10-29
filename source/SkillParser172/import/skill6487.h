#ifndef __CPPGEN_GNET_SKILL6487
#define __CPPGEN_GNET_SKILL6487
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6487:public Skill
    {
    public:
        enum { SKILL_ID = 6487 };
        Skill6487 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6487Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 100;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.2 * ((9 * skill->GetLevel()) + 97.2));
                skill->GetPlayer()->SetPray(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 1;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State2 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 1500;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.8 * ((9 * skill->GetLevel()) + 97.2));
                skill->SetPlus(skill->GetLevel() == 1 ? 3911.4 : skill->GetLevel() == 2 ? 4196.7
                                                            : skill->GetLevel() == 3   ? 4490.6
                                                            : skill->GetLevel() == 4   ? 4793.1
                                                            : skill->GetLevel() == 5   ? 5104.2
                                                            : skill->GetLevel() == 6   ? 5423.9
                                                            : skill->GetLevel() == 7   ? 5752.2
                                                            : skill->GetLevel() == 8   ? 6089.1
                                                            : skill->GetLevel() == 9   ? 6434.6
                                                            : skill->GetLevel() == 10  ? 6788.7
                                                                                       : 0);
                skill->SetRatio(1.2);
                skill->SetDamage(skill->GetAttack());
                skill->GetPlayer()->SetPerform(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State3 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 0;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
    Skill6487Stub ():SkillStub (6487)
    {
        cls = 14;
        name = L"a�[";
        nativename = "�ⶨ";
        icon = "�ⶨ.dds";
        max_level = 10;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 6;
        eventflag = 0;
        is_senior = 0;
        clslimit = 0;
        time_type = 0;
        showorder = 1501;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
            restrict_weapons.push_back (69843);
        }
        effect = "������_����_����.att";
        range.type = 1;
        doenchant = true;
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
    virtual ~ Skill6487Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 108,113,118,124,129,135,140,145,151,156 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1500,1500,1500,1500,1500,1500,1500,1500,1500,1500 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 120000,120000,120000,120000,120000,120000,120000,120000,120000,120000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 60,63,66,69,72,75,78,81,84,87 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 33200,42600,56000,73000,94800,140700,204400,292000,411200,572500 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    float GetRadius(Skill *skill) const
    {
        return (float)(skill->GetPlayer ()->GetRange () + 20);
    }
    float GetAttackdistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer ()->GetRange () + 20);
    }
    float GetAngle(Skill *skill) const
    {
        return (float)(1 - 0.0111111 * (15));
    }
    float GetPraydistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer ()->GetRange () + 20);
    }
#ifdef _SKILL_CLIENT
    int GetIntroduction(Skill *skill, wchar_t *buffer, int length, wchar_t *format) const
    {
            return _snwprintf(buffer, length, format);
    }
#endif
#ifdef _SKILL_SERVER
    int GetEnmity(Skill *skill) const
    {
            return 0;
    }

    bool StateAttack (Skill * skill) const
    {
            skill->GetVictim ()->SetProbability (1.0 * skill->GetPlayer ()->GetCls () == -1 ? 0 : 100);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetNofly (1);            
            return true;
    }
    bool TakeEffect(Skill *skill) const
    {;
        return true;
    }
    float GetEffectdistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer ()->GetRange () + 30);
    }
    int GetAttackspeed(Skill *skill) const
    {
        return 0;
    }
    float GetHitrate(Skill *skill) const
    {
        return (float)(1.0);
    }
#endif
    };
}
#endif
