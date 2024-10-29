//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
45110  "Великое заклятие оцепенения"45111  "^ff5c00Великое заклятие оцепенения^ffcb4aПерсонаж должен быть в образе лисицы^ffcb4aДальность: ^96f5ff%d^ffcb4a м^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffff1 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,3 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff2 ^ffcb4aмин.^ffcb4aОграничение по оружию: ^ffffffмагическое оружие, без оружия^ffcb4aХарактеристика: ^ff5c00Мощь^ffcb4aСтатус: ^ffffffМудрецУникальный навык, призванный помочь друиду справиться с противником в ближнем бою.Наносит базовый магический урон, плюс ^96f5ff100%%^ffffff урона оружия,плюс урон стихией дерева, равный ^96f5ff150%%^ffffff максимума ЖС друида,плюс ^96f5ff20%%^ffffff базового магического урона.Снимает с цели эффект 'Опека духов'.На ^96f5ff15^ffffff сек. снижает скорость атаки цели на ^96f5ff100%%^ffffff, а меткость - на все ^96f5ff300%%^ffffff.Не промахивается.^a6caf0Дополнительная стоимость: ^ffffff1^a6caf0 ци.^00ffffЭффект сапфировой руны:@1^00ffffНе снижает скорость атаки и точность цели.^00ffffНе снимает с цели эффект 'Опека духов'.^00ffff1-4 ур.: физическая атака цели снижается на ^ffffff200%%^00ffff на ^ffffff10^00ffff сек.^00ffff5-7 ур.: физическая атака цели снижается на ^ffffff250%%^00ffff на ^ffffff10^00ffff сек.^00ffff8-9 ур.: физическая атака цели снижается на ^ffffff300%%^00ffff на ^ffffff10^00ffff сек. ^00ffff10 ур.: физическая атака цели снижается на ^ffffff350%%^00ffff на ^ffffff10^00ffff сек.@1@2^00ffffНе снижает скорость атаки и точность цели.^00ffffНе снимает с цели эффект 'Опека духов'.Физическая атака цели снижается на ^ffffff%d%%^00ffff на ^ffffff10^00ffff сек.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL511 
#define __CPPGEN_GNET_SKILL511 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill511:public Skill 
    { 
    public: 
        enum { SKILL_ID = 511 }; 
        Skill511 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill511Stub:public SkillStub 
    { 
    public: 
    Skill511Stub ():SkillStub (511) 
    { 
        cls                 = 4; 
#ifdef _SKILL_CLIENT 
        name                = L"��Ұ�Իظ�"; 
        nativename          = "��Ұ�Իظ�"; 
        icon                = "Ұ�Իظ�2.dds"; 
#endif 
        max_level           = 1; 
        type                = 5; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 30; 
        eventflag           = 1; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1510; 
        allow_forms         = 1; 
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
        pre_skills.push_back (std::pair < ID, int >(109, 10)); 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
#endif 
    } 
        int GetExecutetime (Skill * skill) const
        {
            return 1500;
        }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 4000,4000,4000,4000,4000,4000,4000,4000,4000,4000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 89,89,89,89,89,89,89,89,89,89 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 }; 
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
            return (float) (1 - 0.0111111 * (20 + 2.5 * skill->GetLevel ()));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange () + 3 + 0.2 * skill->GetLevel ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 19,19,19,19,19,19,19,19,19,19 }; 
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
            return _snwprintf (buffer, length, format, 25);

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
            return (float) (25);
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
            skill->GetPlayer ()->SetInchpgen (70);
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
