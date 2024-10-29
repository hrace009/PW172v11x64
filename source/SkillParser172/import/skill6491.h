#ifndef __CPPGEN_GNET_SKILL6491
#define __CPPGEN_GNET_SKILL6491
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6491:public Skill
    {
    public:
        enum { SKILL_ID = 6491 };
        Skill6491 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6491Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1 : public SkillStub::State
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
                skill->GetPlayer()->SetDecmp(226);
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
    Skill6491Stub ():SkillStub (6491)
    {
        cls = 14;
        name = L"q0�";
        nativename = "��ɽ����";
        icon = "��ɽ����.dds";
        max_level = 1;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 0;
        eventflag = 0;
        is_senior = 0;
        clslimit = 0;
        time_type = 4; 
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
        range.type = 5;
        doenchant = true;
        dobless = true;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));

        combosk_preskill = 6490;
        combosk_interval = 8100;

#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
#endif
    }
    virtual ~ Skill6491Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 226,226,226,226,226,226,226,226,226,226 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 };
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
            return (float) (skill->GetPlayer ()->GetRange () + 10);
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
            skill->GetVictim ()->SetProbability (1.0 * (skill->GetPlayer ()->GetForm () == 1 ? 100 : 1));
            skill->GetVictim ()->SetTime (skill->GetPlayer ()->GetForm () == 1 ? 2000 : 1);
            skill->GetVictim ()->SetRatio (8);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (6492);
            skill->GetVictim ()->SetAuracurseMonkey (1);
            return true;
        }
        bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetRemoveFilterMonkey2 (1);
            return true;
        }  
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 30);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 1;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        } 
        
#endif
    };
}
#endif
