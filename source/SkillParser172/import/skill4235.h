#ifndef __CPPGEN_GNET_SKILL4235
#define __CPPGEN_GNET_SKILL4235
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill4235:public Skill
    {
    public:
        enum { SKILL_ID = 4235 };
        Skill4235 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill4235Stub:public SkillStub
    {
    public:

    Skill4235Stub ():SkillStub (4235)
    {
        cls = 11;
        name = L"SKILL4235";
        nativename = "���µӻ꼼��Ч��";
        icon = "˷��ӽ.dds";
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
        time_type = 0;
        showorder = 0;
        allow_land = 1;
        allow_air = 1;
        allow_water = 1;
        allow_ride = 0;
        auto_attack = 0;
        long_range = 0;
        restrict_corpse = 0;
        allow_forms = 1;
        {
        }
        effect = "";
        range.type = 5;
        doenchant = 1;
        dobless = 0;
        commoncooldown = 0;
        commoncooldowntime = 0;
#ifdef _SKILL_SERVER
#endif
    }
    virtual ~ Skill4235Stub () {}
    float GetMpcost (Skill * skill) const 
    {
        static float array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 802,802,802,802,802,802,802,802,802,802 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    {
        static int array[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredLevel (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
        return array[skill->GetLevel () - 1];
    }
    int GetRequiredSp (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
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
    float GetRadius (Skill * skill) const { return 5; } 
    float GetAttackdistance (Skill * skill) const { return 4; } 
    float GetAngle (Skill * skill) const {  return (float) (1 - 0.0111111 * (0)); } 
    float GetPraydistance (Skill * skill) const { return (float) (skill->GetPlayer ()->GetRange ()); } 
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
            skill->GetVictim ()->SetProbability (1.0 * skill->GetLevel () == 2 ? 100 : 0);
            skill->GetVictim ()->SetTime (7401);
            skill->GetVictim ()->SetRatio (0.4);
            skill->GetVictim ()->SetDechurt (1);
            skill->GetVictim ()->SetProbability (1.0 * skill->GetLevel () == 2 ? 100 : 0);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetScaleinchp (1);
            skill->GetVictim ()->SetProbability (1.0 * skill->GetLevel () == 1 ? 100 : 0);
            skill->GetVictim ()->SetTime (21401);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetEnhanceskilldamage3 (1);
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
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
