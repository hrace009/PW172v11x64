//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
37010  "Великий огненный ливень"37011  "^ff5c00Великий огненный ливень^ffcb4aДальность: ^96f5ff%d^ffffff ^ffcb4aм^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffff4 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,5 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff30 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffмагическое оружие, без оружия^ffcb4aХарактеристика: ^ff5c00Мощь^ffcb4aСтатус: ^ffffffМудрецМаг призывает множество пламенных клинков, которые обрушиваются на врагов смертоносным ливнем.Наносит всем противникам в радиусе ^96f5ff12^ffffff м базовый магический урон, плюс ^96f5ff200%%^ffffff урона оружия,плюс ^96f5ff6200^ffffff ед. огненного и физ. урона.После применения восстанавливается ^96f5ff0,4^ffffff ци, а также есть ^96f5ff50%%^ffffff шанспрервать подготовку заклинаний противников.^a6caf0Дополнительная стоимость: ^ffffff2^a6caf0 ци.^ffeaabЭффект серебряной руны:@1^ffeaab1-4 ур.: в течение ^96f5ff10^ffeaab сек. расход ци на ^96f5ffВеликую силу гор^ffeaab уменьшается до ^96f5ff1,6^ffeaab5-7 ур.: в течение ^96f5ff10^ffeaab сек. расход ци на ^96f5ffВеликую силу гор^ffeaab уменьшается до ^96f5ff1,4^ffeaab8-9 ур.: в течение ^96f5ff10^ffeaab сек. расход ци на ^96f5ffВеликую силу гор^ffeaab уменьшается до ^96f5ff1,2^ffeaab 10 ур.: в течение ^96f5ff10^ffeaab сек. расход ци на ^96f5ffВеликую силу гор^ffeaab уменьшается до ^96f5ff1@1@2^ffeaabВ течение ^96f5ff10^ffeaab сек. расход ци на ^96f5ffВеликую силу гор^ffeaab уменьшается до ^96f5ff%d^ffeaab сотых ци.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3701 
#define __CPPGEN_GNET_SKILL3701 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3701:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3701 }; 
        Skill3701 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3701Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

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
            skill->GetPlayer ()->SetDecmp (655);
            skill->SetPlus (6200);
            skill->SetRatio (2);
            skill->SetFiredamage (skill->GetMagicattack ());
            skill->SetPlus (6200);
            skill->SetRatio (2);
            skill->SetDamage (skill->GetMagicattack ());
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
    Skill3701Stub ():SkillStub (3701) 
    { 
        cls                 = 1; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤻𺣵�ɽ"; 
        nativename          = "�񡤻𺣵�ɽ"; 
        icon                = "�񡤻𺣵�ɽ��.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 5; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1208; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 40; 
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
        combosk_nobreak     = 0; 
#ifdef _SKILL_CLIENT 
        effect              = "��ʦ_��_�𺣵�ɽ_����.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "����״̬Ч����ǿ2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
#endif 
        gfxtarget           = 0; 
        feature             = 107; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
        int GetExecutetime (Skill * skill) const
        {
            return 1000;
        }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
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
            return (float) (1 - 0.0111111 * (0));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (0);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 655,655,655,655,655,655,655,655,655,655 }; 
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
            return _snwprintf (buffer, length, format, 23 * skill->GetLevel () - 22);

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
            skill->GetVictim ()->SetClearbuff (1);
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
            return (float) (5);
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
        {;
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
