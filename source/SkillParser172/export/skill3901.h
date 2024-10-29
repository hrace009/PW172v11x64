//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
39010  "Великая расколотая гора"39011  "^ff5c00Великая расколотая гора^ffcb4aДальность: ^ffffffближний бой^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffff0,3^ffcb4a сек.^ffcb4aПрименение: ^ffffff1^ffcb4a сек.^ffcb4aПерезарядка: ^ffffff3^ffcb4a сек.^ffcb4aПолучение ци: ^ffffff0,05^ffcb4aОграничение по оружию: ^ffffffоружие ближнего боя^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffАсураВоин наполняет оружие энергией и обрушивает его на противника, наносябазовый физический урон плюс ^96f5ff2800^ffffff ед. физического урона.Эффекты зависят от применяемого оружия.Топоры и молоты: скорость противника уменьшается на ^96f5ff60%%^ffffff на ^96f5ff10^ffffff секунд. С вероятностью ^96f5ff20%%^ffffff обездвиживает противника на ^96f5ff3^ffffff сек.Древковое оружие: дальность увеличивается до ^96f5ff20^ffffff м. Добавляется ^96f5ff150%%^ffffff урона оружия.Мечи: добавляется ^96f5ff310%%^ffffff урона оружия плюс ^96f5ff1864^ffffff ед. физ. урона.Другое оружие: эффект аналогичен эффекту для топоров и молотов."*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3901 
#define __CPPGEN_GNET_SKILL3901 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3901:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3901 }; 
        Skill3901 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3901Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

#ifdef _SKILL_SERVER 
    class State1:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 300; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const
        {
            skill->GetPlayer ()->SetDecmp (28);
            skill->GetPlayer ()->SetPray (1);
        }
        bool Interrupt (Skill * skill) const { return false; }
        bool Cancel (Skill * skill) const { return 1; }
        bool Skip (Skill * skill) const { return 0; }
    };
#endif 
#ifdef _SKILL_SERVER 
    class State2:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 300; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const
        {
            skill->GetPlayer ()->SetDecmp (112);
            skill->SetPlus (2800);
            skill->SetRatio (0);
            skill->SetDamage (skill->GetAttack ());
            skill->GetPlayer ()->SetPerform (1);
        }
        bool Interrupt (Skill * skill) const { return false; }
        bool Cancel (Skill * skill) const { return 0; }
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
        bool Cancel (Skill * skill) const { return 0; }
        bool Skip (Skill * skill) const { return 0; }
    };
#endif 
    Skill3901Stub ():SkillStub (3901) 
    { 
        cls                 = 0; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤶���ն"; 
        nativename          = "�񡤶���ն"; 
        icon                = "�񡤶���ն.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1106; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 5; 
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
        effect              = "1����ն.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 1; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(384, 1)); 
        pre_skills.push_back (std::pair < ID, int >(385, 1)); 
        restrict_weapons.push_back (0); 
        restrict_weapons.push_back (1); 
        restrict_weapons.push_back (182); 
        restrict_weapons.push_back (5); 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 3000,3000,3000,3000,3000,3000,3000,3000,3000,3000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000,50000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 53887,53887,53887,53887,53887,53887,53887,53887,53887,53887 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000,10000000 }; 
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
        return (float) (skill->GetPlayer ()->GetRange () + 3 + 0.3 * skill->GetLevel ());
    }
    float GetAngle (Skill * skill) const
    {
        return (float) (1 - 0.0111111 * (0));
    }
    float GetPraydistance (Skill * skill) const
    {
        return (float) (skill->GetPlayer ()->GetRange ());
    }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 140,140,140,140,140,140,140,140,140,140 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (0.6);
            skill->GetVictim ()->SetSlow (1);
            skill->GetVictim ()->SetProbability (1.0 * 20);
            skill->GetVictim ()->SetTime (3500);
            skill->GetVictim ()->SetFix (1);
            return true;
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
            return (float) (14.9);
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
            return 6;
        }
#endif 
#ifdef _SKILL_SERVER 
        bool TakeEffect (Skill * skill) const
        {;
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetHitrate (Skill * skill) const
        {
            return (float) (2.5);
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
