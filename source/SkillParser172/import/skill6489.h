#ifndef __CPPGEN_GNET_SKILL6489
#define __CPPGEN_GNET_SKILL6489
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6489:public Skill
    {
    public:
        enum { SKILL_ID = 6489 };
        Skill6489 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6489Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 300;
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
                skill->GetPlayer()->SetDecmp(0.2 * ((9 * skill->GetLevel()) + 191.3));
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
                return 1300;
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
                skill->GetPlayer()->SetDecmp(0.8 * ((9 * skill->GetLevel()) + 191.3));
                skill->SetPlus(7399);
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
    Skill6489Stub ():SkillStub (6489)
    {
        cls = 14;
        name = L"`WfS�[";
        nativename = "׹�ǻ���";
        icon = "׹�ǻ���.dds";
        max_level = 1;
        type = 1;
        apcost = 100;
        arrowcost = 0;
        apgain = 0;
        attr = 7;
        rank = 8;
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
        effect = "";
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
    virtual ~ Skill6489Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 200,200,200,200,200,200,200,200,200,200 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1300,1300,1300,1300,1300,1300,1300,1300,1300,1300 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 89,89,89,89,89,89,89,89,89,89 };
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
        static int array[10] = { 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000 };
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
            skill->GetVictim ()->SetProbability (1.0 * skill->GetPlayer ()->GetCls () == -1 ? 0 : skill->GetT0 () && skill->GetT1 () ? 100 : 0);
            skill->GetVictim ()->SetTime (11000);
            skill->GetVictim ()->SetShowicon (0);
            skill->GetVictim ()->SetComboYinYang2 (1);

        return true;
    }  


    bool BlessMe (Skill * skill) const
    {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetRemoveFilterMonkey (1);
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

    float GetTalent0 (PlayerWrapper * player) const
    {
        return (float) (player->GetFilterID (4485));
    }
    float GetTalent1 (PlayerWrapper * player) const
    {
        return (float) (player->GetFilterID (4486));
    }

#endif
    };
}
#endif
