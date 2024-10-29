#ifndef __CPPGEN_GNET_SKILL6504
#define __CPPGEN_GNET_SKILL6504
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6504:public Skill
    {
    public:
        enum { SKILL_ID = 6504 };
        Skill6504 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill6504Stub:public SkillStub
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
                skill->GetPlayer ()->SetDecmp(225);
                skill->GetPlayer ()->SetPerform (1);
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
    Skill6504Stub ():SkillStub (6504)
    {
        cls = 14;
        name = L"RN�";
        nativename = "������һ��˫Ϣ";
        icon = "����һ��˫Ϣ.dds";
        max_level = 2;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 8;
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
        allow_forms = 2;
        {
            restrict_weapons.push_back (69843);
            restrict_weapons.push_back (0);
        }
        effect = "";
        range.type = 5;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;

        itemcost = 49982;

        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER
        statestub.push_back (new State1 ());
        statestub.push_back (new State2 ());
#endif
    }
    virtual ~ Skill6504Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 225,225,225,225,225,225,225,225,225,225 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 900,900,900,900,900,900,900,900,900,900 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 300000,300000,300000,300000,300000,300000,300000,300000,300000,300000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 1000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredItem (Skill * skill) const 
    {
        static int array[10] = { 70226,70227,70227,70227,70227,70227,70227,70227,70227,70227 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 1000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 };
        return array[skill->GetLevel () - 1];
    }
    float GetRadius (Skill * skill) const
        {
            return (float) (16);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (0);
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1);
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange ());
        }
#ifdef _SKILL_SERVER
        int GetEnmity (Skill * skill) const
        {
            return 0;
        }
        bool StateAttack (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetCleardebuff2 (1);
            
			skill->GetVictim ()->SetTime (2000);
            skill->GetVictim ()->SetFeAtiradora (1);

            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (13000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio (20);
            skill->GetVictim ()->SetAmount (1);
            skill->GetVictim ()->SetValue (6505);
            skill->GetVictim ()->SetAurabless (1);

            // Define Icon / Gfx Buff
            skill->GetVictim ()->SetTime(13000 * skill->GetLevel()); // Tempo
            skill->GetVictim ()->SetRatio (556); // Icon Macaco
            skill->GetVictim ()->SetAmount (0); // Buff
            skill->GetVictim ()->SetValue (1); // Definir
            skill->GetVictim ()->SetInsertvstate (1);

            skill->GetVictim ()->SetTime(13000 * skill->GetLevel()); // Tempo
            skill->GetVictim ()->SetRatio (558); // Icon
            skill->GetVictim ()->SetAmount (0); // Buff
            skill->GetVictim ()->SetValue (1); // Definir
            skill->GetVictim ()->SetInsertvstate (1);
            return true;
        }
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (35);
        }
        int GetAttackspeed (Skill * skill) const
        {
            return 9;
        }
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
        }
#endif
    };
}
#endif
