#ifndef __CPPGEN_GNET_SKILL4124
#define __CPPGEN_GNET_SKILL4124
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill4124:public Skill
    {
    public:
        enum { SKILL_ID = 4124 };
        Skill4124 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill4124Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 67;
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
                skill->GetPlayer ()->SetDecmp (0.2 * 152);
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
                return 1101;
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
                skill->GetPlayer ()->SetDecmp (0.8 * 152);
                skill->SetRatio (2);
				skill->SetPlus (10428);
                skill->SetDamage (skill->GetAttack ());
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
    Skill4124Stub ():SkillStub (4124)
    {
        cls = 10;
        name = L"����";
        nativename = "����";
        icon = "����.dds";
        max_level = 1;
        type = 1;
        apcost = 30;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 41;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 1018;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 1;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 3;
        {
            restrict_weapons.push_back (44878);
        }
        effect = "����.sgc";
        range.type = 0;
        doenchant = 1;
        dobless = 0;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(2899, 1));
        pre_skills.push_back (std::pair < ID, int >(2900, 1));
        combosk_preskill = 2564;
        combosk_interval = 6000;
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill4124Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 152,152,152,152,152,152,152,152,152,152 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1101,1101,1101,1101,1101,1101,1101,1101,1101,1101 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 6000,6000,6000,6000,6000,6000,6000,6000,6000,6000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000 };
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
            return (float) (skill->GetPlayer ()->GetRange ());
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
            skill->GetVictim ()->SetTime (8101);
            skill->GetVictim ()->SetRatio (skill->GetPlayer ()->GetCls () == 127 ? 0.6 : 0.8);
            skill->GetVictim ()->SetDecdefence (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 1.35 * 5.5);
        }		
        float GetHitrate (Skill * skill) const
        {
            return (float) (3);
        }
#endif
    };
}
#endif
