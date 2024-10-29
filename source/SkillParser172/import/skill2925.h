#ifndef __CPPGEN_GNET_SKILL2925
#define __CPPGEN_GNET_SKILL2925
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill2925:public Skill
    {
    public:
        enum { SKILL_ID = 2925 };
        Skill2925 ():Skill (SKILL_ID){ }
    };
#endif
    class Skill2925Stub:public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
#endif
    Skill2925Stub ():SkillStub (2925)
    {
        cls = 10;
        name = L"虎击";
        nativename = "虎击";
        icon = "虎击.dds";
        max_level = 10;
        type = 2;
        apcost = 0;
        arrowcost = 0;
        apgain = 0;
        attr = 1;
        rank = 0;
        eventflag = 0;
        posdouble = 0;
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
        allow_forms = 0;
        {
        }
        effect = "虎击.sgc";
        range.type = 0;
        doenchant = true;
        dobless = false;
        commoncooldown = 0;
        commoncooldowntime = 0;
        pre_skills.push_back (std::pair < ID, int >(0, 1));
#ifdef _SKILL_SERVER

#endif
    }
    virtual ~ Skill2925Stub () {}
    float GetMpcost (Skill * skill) const
        {
            return (float) (0);
        }
    int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
    int GetCoolingtime (Skill * skill) const
        {
            return 0;
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
    int GetRequiredMoney (Skill * skill) const 
    {
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 };
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
        return (float) (0);
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
        skill->GetVictim()->SetProbability(1 * 100.0);
        skill->GetVictim()->SetTime(7001);
        skill->GetVictim()->SetRatio(100);
        skill->GetVictim()->SetAmount(1);
        skill->GetVictim()->SetValue(2547);
        skill->GetVictim()->SetIncspecskillcrit(1);
        skill->GetVictim()->SetProbability(1 * 100.0);
        skill->GetVictim()->SetTime(7001);
        skill->GetVictim()->SetRatio(0.5);
        skill->GetVictim()->SetAmount(1);
        skill->GetVictim()->SetValue(2728);
        skill->GetVictim()->SetIncspecskilldamage(1);
        skill->GetVictim()->SetProbability(1 * 100.0);
        skill->GetVictim()->SetTime(7001);
        skill->GetVictim()->SetRatio(0.5);
        skill->GetVictim()->SetAmount(1);
        skill->GetVictim()->SetValue(2547);
        skill->GetVictim()->SetIncspecskilldamage(1);
        skill->GetVictim()->SetProbability(1 * 100.0);
        skill->GetVictim()->SetTime(7001);
        skill->GetVictim()->SetRatio(100);
        skill->GetVictim()->SetAmount(1);
        skill->GetVictim()->SetValue(2728);
        skill->GetVictim()->SetIncspecskillcrit(1);
        return true; 
    }  
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
        }		
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif
    };
}
#endif
