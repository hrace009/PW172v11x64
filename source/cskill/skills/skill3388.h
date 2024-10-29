//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
33880  "Ножницы"33881  "^ffffffНожницы Ур. 1^ffcb4aДальность: ^ffffff20^ffcb4a м.^ffcb4aПодготовка: ^ffffff1,0^ffcb4a сек.^ffcb4aПрименение: ^ffffff2,0^ffcb4a сек.^ffcb4aПерезарядка: ^ffffff1,5^ffcb4a сек.^ffffffНаносит урон врагу в статусе 'Бумага'."*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3388 
#define __CPPGEN_GNET_SKILL3388 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3388:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3388 }; 
        Skill3388 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3388Stub:public SkillStub 
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
    Skill3388Stub ():SkillStub (3388) 
    { 
        cls                 = 255; 
#ifdef _SKILL_CLIENT 
        name                = L"����"; 
        nativename          = "����"; 
        icon                = "����.dds"; 
#endif 
        max_level           = 10; 
        type                = 3; 
        allow_ride          = 0; 
        attr                = 2; 
        rank                = 0; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 0; 
        allow_forms         = 4; 
        apcost              = 0; 
        apgain              = 0; 
        doenchant           = 1; 
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
        effect              = "����ս���߼�_����.sgc"; 
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
        pre_skills.push_back (std::pair < ID, int >(0, 1)); 
        restrict_weapons.push_back (1); 
        restrict_weapons.push_back (5); 
        restrict_weapons.push_back (9); 
        restrict_weapons.push_back (13); 
        restrict_weapons.push_back (182); 
        restrict_weapons.push_back (291); 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (23749); 
        restrict_weapons.push_back (25333); 
        restrict_weapons.push_back (44878); 
        restrict_weapons.push_back (44879); 
        restrict_weapons.push_back (59830); 
        restrict_weapons.push_back (59831); 
        restrict_weapons.push_back (69843); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 2000,2000,2000,2000,2000,2000,2000,2000,2000,2000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 1500,1500,1500,1500,1500,1500,1500,1500,1500,1500 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
        return (float) (0); 
    } 
    float GetPraydistance (Skill * skill) const 
    { 
        static float aarray[10] = { 20.00,20.00,20.00,20.00,20.00,20.00,20.00,20.00,20.00,20.00 }; 
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
    int GetIntroduction (Skill * skill, const wchar_t * buffer, int length, const wchar_t * format) const 
    { 
        return 0; 
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
        return 5; 
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
        return 1; 
    } 
#endif 
#ifdef _SKILL_SERVER 
    float GetHitrate (Skill * skill) const 
    { 
        return 1; 
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
