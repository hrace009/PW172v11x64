//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL2921 
#define __CPPGEN_GNET_SKILL2921 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill2921:public Skill 
    { 
    public: 
        enum { SKILL_ID = 2921 }; 
        Skill2921 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill2921Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
    class State1:public SkillStub::State 
    { 
    public: 
        int GetTime (Skill * skill) const { return 0; } 
        bool Quit (Skill * skill) const { return false; } 
        bool Loop (Skill * skill) const { return false; } 
        bool Bypass (Skill * skill) const { return false; } 
        void Calculate (Skill * skill) const { } 
        bool Interrupt (Skill * skill) const { return false; } 
        bool Cancel (Skill * skill) const { return 1; } 
        bool Skip (Skill * skill) const { return 0; } 
    }; 
#endif 
#ifdef _SKILL_SERVER 
    class State2:public SkillStub::State 
    { 
    public: 
        int GetTime (Skill * skill) const { return 0; } 
        bool Quit (Skill * skill) const { return false; } 
        bool Loop (Skill * skill) const { return false; } 
        bool Bypass (Skill * skill) const { return false; } 
        void Calculate (Skill * skill) const { } 
        bool Interrupt (Skill * skill) const { return false; } 
        bool Cancel (Skill * skill) const { return 1; } 
        bool Skip (Skill * skill) const { return 0; } 
    }; 
#endif 
#ifdef _SKILL_SERVER 
    class State3:public SkillStub::State 
    { 
    public: 
        int GetTime (Skill * skill) const { return 0; } 
        bool Quit (Skill * skill) const { return false; } 
        bool Loop (Skill * skill) const { return false; } 
        bool Bypass (Skill * skill) const { return false; } 
        void Calculate (Skill * skill) const { } 
        bool Interrupt (Skill * skill) const { return false; } 
        bool Cancel (Skill * skill) const { return 1; } 
        bool Skip (Skill * skill) const { return 0; } 
    }; 
#endif 
    Skill2921Stub ():SkillStub (2921) 
    { 
        cls                 = 255; 
#ifdef _SKILL_CLIENT 
        name                = L"三清化形"; 
        nativename          = "三清化形"; 
        icon                = "三清化形.dds"; 
#endif 
        max_level           = 10; 
        type                = 5; 
        allow_ride          = 0; 
        attr                = 0; 
        rank                = 8; 
        eventflag           = 1; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2004; 
        allow_forms         = 0; 
        apcost              = 0; 
        apgain              = 0; 
        doenchant           = 0; 
        dobless             = 0; 
        arrowcost           = 0; 
        allow_land          = 1; 
        allow_air           = 1; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 0; 
        time_type           = 0; 
        long_range          = 0; 
        posdouble           = 0; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        itemcostcount       = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
#ifdef _SKILL_CLIENT 
        effect              = ""; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 0; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 47448,47448,47448,47448,47448,62147,62147,62147,62147,62147 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 32,34,36,38,40,52,54,56,58,60 }; 
        return aarray[skill->GetLevel () - 1]; 
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
        static float aarray[10] = { 0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCoolDownLimit (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCostShieldEnergy (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
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
#endif 
#ifdef _SKILL_SERVER 
    int GetMaxAbility (Skill * skill) const 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    bool StateAttack (Skill * skill) const 
    { 
        return 1; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const 
    { 
        return 1; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (0);
        }
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent0 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent1 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent2 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent3 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent4 (PlayerWrapper * player) 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    int GetAttackspeed (Skill * skill) const 
    { 
        return 0; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        bool TakeEffect (Skill * skill) const
        {
			// максимальное здоровье
            float health = 0.0f;
			if(skill->GetPlayer ()->GetCls () == 0) health = 0.3f; // воин
			if(skill->GetPlayer ()->GetCls () == 1) health = 0.3f; // маг
			if(skill->GetPlayer ()->GetCls () == 2) health = 0.3f; // шаман
			if(skill->GetPlayer ()->GetCls () == 3) health = 0.3f; // друид	
			if(skill->GetPlayer ()->GetCls () == 4) health = 0.3f; // танк	
			if(skill->GetPlayer ()->GetCls () == 5) health = 0.3f; // син			
			if(skill->GetPlayer ()->GetCls () == 6) health = 0.3f; // лук			
			if(skill->GetPlayer ()->GetCls () == 7) health = 0.3f; // жрец			
			if(skill->GetPlayer ()->GetCls () == 8) health = 0.3f; // страж				
			if(skill->GetPlayer ()->GetCls () == 9) health = 0.3f; // мистик	
			if(skill->GetPlayer ()->GetCls () == 10) health = 0.3f; // призрак
			if(skill->GetPlayer ()->GetCls () == 11) health = 0.3f; // жнец	
			if(skill->GetPlayer ()->GetCls () == 12) health = 0.3f; // стрелок
			if(skill->GetPlayer ()->GetCls () == 13) health = 0.3f; // палалин ??		
            skill->GetPlayer ()->SetAddmaxhp (health);
			
			// физичиская защита
            float pdef = 0.0f;
			if(skill->GetPlayer ()->GetCls () == 0) pdef = 0.4f; // воин
			if(skill->GetPlayer ()->GetCls () == 1) pdef = 0.4f; // маг
			if(skill->GetPlayer ()->GetCls () == 2) pdef = 0.5f; // шаман
			if(skill->GetPlayer ()->GetCls () == 3) pdef = 0.4f; // друид	
			if(skill->GetPlayer ()->GetCls () == 4) pdef = 0.4f; // танк	
			if(skill->GetPlayer ()->GetCls () == 5) pdef = 0.4f; // син			
			if(skill->GetPlayer ()->GetCls () == 6) pdef = 0.4f; // лук			
			if(skill->GetPlayer ()->GetCls () == 7) pdef = 0.4f; // жрец			
			if(skill->GetPlayer ()->GetCls () == 8) pdef = 0.4f; // страж				
			if(skill->GetPlayer ()->GetCls () == 9) pdef = 0.4f; // мистик	
			if(skill->GetPlayer ()->GetCls () == 10) pdef = 0.4f; // призрак
			if(skill->GetPlayer ()->GetCls () == 11) pdef = 0.4f; // жнец
			if(skill->GetPlayer ()->GetCls () == 12) pdef = 0.4f; // стрелок
			if(skill->GetPlayer ()->GetCls () == 13) pdef = 0.4f; // палалин ??	
            skill->GetPlayer ()->SetAdddefence (pdef);
			
			// магическая защита
            float mdef = 0.0f;
			if(skill->GetPlayer ()->GetCls () == 0) mdef = 0.4f; // воин
			if(skill->GetPlayer ()->GetCls () == 1) mdef = 0.4f; // маг
			if(skill->GetPlayer ()->GetCls () == 2) mdef = 0.4f; // шаман
			if(skill->GetPlayer ()->GetCls () == 3) mdef = 0.4f; // друид	
			if(skill->GetPlayer ()->GetCls () == 4) mdef = 0.4f; // танк	
			if(skill->GetPlayer ()->GetCls () == 5) mdef = 0.4f; // син			
			if(skill->GetPlayer ()->GetCls () == 6) mdef = 0.4f; // лук			
			if(skill->GetPlayer ()->GetCls () == 7) mdef = 0.4f; // жрец			
			if(skill->GetPlayer ()->GetCls () == 8) mdef = 0.4f; // страж				
			if(skill->GetPlayer ()->GetCls () == 9) mdef = 0.4f; // мистик	
			if(skill->GetPlayer ()->GetCls () == 10) mdef = 0.4f; // призрак
			if(skill->GetPlayer ()->GetCls () == 11) mdef = 0.4f; // жнец
			if(skill->GetPlayer ()->GetCls () == 12) mdef = 0.4f; // стрелок
			if(skill->GetPlayer ()->GetCls () == 13) mdef = 0.4f; // палалин ??
            skill->GetPlayer ()->SetAddresistance (mdef);
			
			// урон от умений
            float skilldmg = 0.0f;
			if(skill->GetPlayer ()->GetCls () == 0) skilldmg = 0.3f; // воин
			if(skill->GetPlayer ()->GetCls () == 1) skilldmg = 0.0f; // маг
			if(skill->GetPlayer ()->GetCls () == 2) skilldmg = 0.0f; // шаман
			if(skill->GetPlayer ()->GetCls () == 3) skilldmg = 0.0f; // друид	
			if(skill->GetPlayer ()->GetCls () == 4) skilldmg = 0.3f; // танк	
			if(skill->GetPlayer ()->GetCls () == 5) skilldmg = 0.3f; // син			
			if(skill->GetPlayer ()->GetCls () == 6) skilldmg = 0.0f; // лук			
			if(skill->GetPlayer ()->GetCls () == 7) skilldmg = 0.0f; // жрец			
			if(skill->GetPlayer ()->GetCls () == 8) skilldmg = 0.0f; // страж				
			if(skill->GetPlayer ()->GetCls () == 9) skilldmg = 0.0f; // мистик
			if(skill->GetPlayer ()->GetCls () == 10) skilldmg = 0.0f; // призрак
			if(skill->GetPlayer ()->GetCls () == 11) skilldmg = 0.0f; // жнец
			if(skill->GetPlayer ()->GetCls () == 12) skilldmg = 0.0f; // стрелок
			if(skill->GetPlayer ()->GetCls () == 13) skilldmg = 0.0f; // палалин ??
            skill->GetPlayer ()->SetAddskilldamage (skilldmg);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetHitrate (Skill * skill) const
        {
            return (float) (1.0);
        }
#endif 
#ifdef _SKILL_SERVER 
    void ComboSkEndAction (Skill * skill) const 
    { 
        return; 
    } 
#endif 
    }; 
} 
#endif 
