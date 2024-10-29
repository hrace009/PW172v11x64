//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
60700  "Покров света"60701  "|if&skilllv()>0&^00FF00&^ffffff||if&skilllv()>1&^00FFFF&||if&skilllv()>2&^d618e7&||if&skilllv()>3&^FF6600&|Покров света　　　　　　　　　　  ^ffffffУровень: %d^ffcb4aДальность: ^ffffff30 ^ffcb4a м^ffcb4aПодготовка: ^ffffff0,1 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff3,7: ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff30,0 ^ffcb4aсек.   ^ffffffВыпускает множество стрел, которые наносят врагам ^96f5ff350%%^ffffff базового физического урона.Кроме этого, накладывает на врага эффект 'кровожадность': в течение ^96f5ff15^ffffff сек. враг получает ^96f5ff40%%^ffffff базового физ. урона,а при накоплении ^96f5ff5^ffffff слоев статуса дополнительно наносится урон в размере остаточного физического урона,который должен нанести эффект 'кровожадности'.Во время применения умения Шогри неуязвима.|if&skilllv()>1&Ур. 2: ^ffffffнаносит ^96f5ff400%%^ffffff базового физ. урона&^808080Ур. 2: наносит 400%% базового физ. урона||if&skilllv()>2&Ур. 3: ^ffffffнаносит ^96f5ff450%%^ffffff базового физ. урона&^808080Ур. 3: наносит 450%% базового физ. урона||if&skilllv()>3&Ур. 4: ^ffffffнаносит ^96f5ff500%%^ffffff базового физ. урона&^808080Ур. 4: наносит 500%% базового физ. урона|^ffcb4aНа уровнях ^ffffff40/80/90/105^ffcb4a божества открываются ^ffffff1/2/3/4^ffcb4a уровни умения."*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL6070 
#define __CPPGEN_GNET_SKILL6070 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6070:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6070 }; 
        Skill6070 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6070Stub:public SkillStub 
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
    Skill6070Stub ():SkillStub (6070) 
    { 
        cls                 = 262; 
#ifdef _SKILL_CLIENT 
        name                = L"�չ�����"; 
        nativename          = "�չ�����"; 
        icon                = "��ͯ�չ�����.dds"; 
#endif 
        max_level           = 4; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 0; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 0; 
        allow_forms         = 8; 
        apcost              = 0; 
        apgain              = 0; 
        doenchant           = 1; 
        dobless             = 1; 
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
        combosk_nobreak     = 1; 
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
        feature             = 262002; 
        extra_effect        = 0; 
        immune_casting      = 0; 
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
        static int aarray[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
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
        static float aarray[10] = { 30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00 }; 
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
