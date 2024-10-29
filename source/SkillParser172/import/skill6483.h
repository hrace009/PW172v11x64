#ifndef __CPPGEN_GNET_SKILL6483
#define __CPPGEN_GNET_SKILL6483
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6483:public Skill
    {
    public:
        enum { SKILL_ID = 6483 };
        Skill6483 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6483Stub:public SkillStub
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
                skill->GetPlayer()->SetDecmp(0.2 * ((9 * skill->GetLevel()) + 70.2));
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
        class State2:public SkillStub::State
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
                skill->GetPlayer ()->SetPerform (2);
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
        class State3 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 200;
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
                skill->SetSection (1);
                skill->GetPlayer()->SetDecmp(0.4 * ((9 * skill->GetLevel()) + 70.2));
                skill->SetPlus(0.4 * (skill->GetLevel() == 1 ? 2446.9 : skill->GetLevel() == 2 ? 2757.1
                                                            : skill->GetLevel() == 3   ? 3081.9
                                                            : skill->GetLevel() == 4   ? 3421.3
                                                            : skill->GetLevel() == 5   ? 3775.3
                                                            : skill->GetLevel() == 6   ? 4143.9
                                                            : skill->GetLevel() == 7   ? 4527.1
                                                            : skill->GetLevel() == 8   ? 4924.9
                                                            : skill->GetLevel() == 9   ? 5337.3
                                                            : skill->GetLevel() == 10  ? 5764.3
                                                                                       : 0));
                skill->SetRatio(0);
                skill->SetDamage(skill->GetAttack());
                skill->GetPlayer()->SetPerform(0);
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
        class State4 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 850;
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
                skill->SetSection (2);
                skill->GetPlayer()->SetDecmp(0.4 * ((9 * skill->GetLevel()) + 70.2));
                skill->SetPlus(0.6 * (skill->GetLevel() == 1 ? 2446.9 : skill->GetLevel() == 2 ? 2757.1
                                                            : skill->GetLevel() == 3   ? 3081.9
                                                            : skill->GetLevel() == 4   ? 3421.3
                                                            : skill->GetLevel() == 5   ? 3775.3
                                                            : skill->GetLevel() == 6   ? 4143.9
                                                            : skill->GetLevel() == 7   ? 4527.1
                                                            : skill->GetLevel() == 8   ? 4924.9
                                                            : skill->GetLevel() == 9   ? 5337.3
                                                            : skill->GetLevel() == 10  ? 5764.3
                                                                                       : 0));
                skill->SetRatio(0);
                skill->SetDamage(skill->GetAttack());
                skill->GetPlayer ()->SetPerform (0);
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
        class State5 : public SkillStub::State
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
    Skill6483Stub ():SkillStub (6483)
    {
        cls = 14;
        name = L"a��pkp";
        nativename = "�����";
        icon = "�����.dds";
        max_level = 10;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 5;
        attr = 1;
        rank = 4;
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
        effect = "������_С����3_ʩ����_����_01.att";
        range.type = 0;
        doenchant = false;
        dobless = true;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
        statestub.push_back (new State4 ());
        statestub.push_back (new State5 ());
#endif
    }
    virtual ~ Skill6483Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 79,86,93,100,108,115,122,129,136,144 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 45000,45000,45000,45000,45000,45000,45000,45000,45000,45000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 39,43,47,51,55,59,63,67,71,75 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 8600,11300,14700,18900,24300,31200,42600,61200,86900,140700 };
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
        return (float)(0);
    }
    float GetAttackdistance(Skill *skill) const
    {
        return (float)(0);
    }
    float GetAngle(Skill *skill) const
    {
        return (float)(1 - 0.0111111 * (0));
    }
    float GetPraydistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer()->GetRange());
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
            return 100;
    }

    bool BlessMe (Skill * skill) const
    {
            //skill->GetVictim ()->SetProbability (1.0 * 100);
            //skill->GetVictim ()->SetTime (16000);
            //skill->GetVictim ()->SetShowicon (0);
            //skill->GetVictim ()->SetMarcaYin (1); 

            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetFeMonkey (1);

        return true;
    }   

    bool TakeEffect(Skill *skill) const
    {;
        return true;
    }
    float GetEffectdistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer()->GetRange() + 10);
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
