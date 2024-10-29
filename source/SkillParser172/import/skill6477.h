#ifndef __CPPGEN_GNET_SKILL6477
#define __CPPGEN_GNET_SKILL6477
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6477:public Skill
    {
    public:
        enum { SKILL_ID = 6477 };
        Skill6477 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6477Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1 : public SkillStub::State
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
                skill->GetPlayer()->SetDecmp(0.2 * ((9 * skill->GetLevel()) + 43.2));
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
                return 1400;
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
                skill->GetPlayer()->SetDecmp(0.8 * ((9 * skill->GetLevel()) + 43.2));
                skill->SetPlus(skill->GetLevel() == 1 ? 884.8 : skill->GetLevel() == 2 ? 1130.2
                                                            : skill->GetLevel() == 3   ? 1394.8
                                                            : skill->GetLevel() == 4   ? 1678.6
                                                            : skill->GetLevel() == 5   ? 1981.6
                                                            : skill->GetLevel() == 6   ? 2303.8
                                                            : skill->GetLevel() == 7   ? 2645.2
                                                            : skill->GetLevel() == 8   ? 3005.8
                                                            : skill->GetLevel() == 9   ? 3385.6
                                                            : skill->GetLevel() == 10  ? 3784.6
                                                                                       : 0);
                skill->SetRatio(1.3);
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
    Skill6477Stub ():SkillStub (6477)
    {
        cls = 14;
        name = L"�e�[�b";
        nativename = "����ȭ";
        icon = "����ȭ.dds";
        max_level = 10;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 30;
        attr = 1;
        rank = 2;
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
        allow_forms = 2;
        {
            restrict_weapons.push_back (69843);
            restrict_weapons.push_back (0);
        }
        effect = "";
        range.type = 2;
        doenchant = true;
        dobless = true;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(6468, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill6477Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 45,54,63,72,81,90,99,108,117,126 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1400,1400,1400,1400,1400,1400,1400,1400,1400,1400 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 5000,5000,5000,5000,5000,5000,5000,5000,5000,5000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 25,30,35,40,45,50,55,60,65,70 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 3800,5900,6500,9200,12900,17800,24300,33200,51100,79700 };
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
        return (float)(8);
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
        return (float)(skill->GetPlayer()->GetRange() + 8);
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetSlowattack (1);

        return true;
    }
    bool BlessMe (Skill * skill) const
    {
            //skill->GetVictim ()->SetProbability (1.0 * 100);
            //skill->GetVictim ()->SetTime (16000);
            //skill->GetVictim ()->SetShowicon (0);
            //skill->GetVictim ()->SetMarcaYang (1); 

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
