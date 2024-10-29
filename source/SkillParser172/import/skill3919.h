#ifndef __CPPGEN_GNET_SKILL3919
#define __CPPGEN_GNET_SKILL3919
// OldSchool
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill3919:public Skill
    {
    public:
        enum { SKILL_ID = 3919 };
        Skill3919 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill3919Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 400;
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
                skill->GetPlayer ()->SetDecmp (30);
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
                return 1800;
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
                skill->GetPlayer ()->SetDecmp (170);
                skill->SetPlus (4664);
                skill->SetRatio (1.2);
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
    Skill3919Stub ():SkillStub (3919)
    {
        cls = 0;
        name = L"SKILL3921";
        nativename = "神·断水凌风";
        icon = "神·断水凌风绿.dds";
        max_level = 1;
        type = 1;
        apcost = 0;
        arrowcost = 0;
        apgain = 10;
        attr = 1;
        rank = 40;
        eventflag = 0;
        is_senior = 1;
        clslimit = 0;
        time_type = 0;
        showorder = 1104;
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
            restrict_weapons.push_back (5);
            restrict_weapons.push_back (9);
            restrict_weapons.push_back (182);
            restrict_weapons.push_back (292);
            restrict_weapons.push_back (0);
        }
        effect = "神_断水凌风_击中.sgc";
        range.type = 0;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
		
		glyphType = 0;
        gfx_filename = "";
        gfx_bind_target = "HH_chibang";
        gfx_target = 0;
        feature = 0;

        pre_skills.push_back (std::pair < ID, int >(2210, 1));
        pre_skills.push_back (std::pair < ID, int >(2211, 1));

#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
        statestub.push_back (new State3 ());
#endif
    }
    virtual ~ Skill3919Stub () {}
    float GetMpcost (Skill * skill) const 
    {
            return (float) (150);
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1200 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 5000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const
        {
            static int array[10] = { 100 };
            return array[skill->GetLevel () - 1];
        }
    int GetRequiredSp (Skill * skill) const
        {
            static int array[10] = { 50000000 };
            return array[skill->GetLevel () - 1];
        }
        int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 53890 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const
        {
            static int array[10] = { 10000000 };
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
            return _snwprintf (buffer, length, format, 150);
        }
#endif
#ifdef _SKILL_SERVER
    int GetEnmity (Skill * skill) const
        {
            return skill->GetT0 () + 22500;
        }    
		bool StateAttack (Skill * skill) const
        {            
            skill->GetVictim ()->SetProbability (1.1 * 55);
            skill->GetVictim ()->SetTime (4000);
            skill->GetVictim ()->SetDizzy (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetValue (8000);
            skill->GetVictim ()->SetAssault (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (22.1);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 16;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (3);
        }
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetMaxhp ());
        }
#endif
    };
}
#endif
