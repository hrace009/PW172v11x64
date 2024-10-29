//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
44190  "Великий гнев дракона"44191  "^ff5c00Великий гнев дракона^ffcb4aДальность: ^ffffffближний бой^ffcb4aМаг. энергия: ^96f5ff140^ffcb4aПодготовка: ^ffffff0,4^ffcb4a сек. ^ffcb4aПрименение: ^ffffff1,2^ffcb4a сек.^ffcb4aПерезарядка: ^ffffff15,0^ffcb4a сек.^ffcb4aОграничение по оружию: ^ffffffтопоры и молоты, древковое оружие, мечи^ffcb4aХарактеристика: ^ff5c00Мощь^ffcb4aСтатус: ^ffffffМудрецНаносит противнику базовый физический урон, плюс ^96f5ff105%%^ffffff урона оружия, плюс ^96f5ff5834^ffffff ед. физического уронаи парализует его на ^96f5ff5^ffffff сек. Не промахивается.Дополнительные эффекты зависят от вида применяемого оружия.Топоры и молоты: время паралича увеличено до ^96f5ff7^ffffff сек.Древковое оружие: дальность увеличивается до ^96f5ff20^ffffff м.Мечи: не парализует цель. Время подготовки сокращается до ^96f5ff0,1^ffffff сек., время применения - до ^96f5ff1,0^ffffff сек.Добавляется ^96f5ff700%%^ffffff урона оружия.^a6caf0Дополнительная стоимость: ^ffffff0,8^a6caf0 ци.^ffcb4aЭффект золотой руны:@1^ffcb4a1-4 ур.: дополнительно наносит ^96f5ff40%%^ffcb4a урона оружия^ffcb4a5-7 ур.: дополнительно наносит ^96f5ff60%%^ffcb4a урона оружия^ffcb4a8-9 ур.: дополнительно наносит ^96f5ff80%%^ffcb4a урона оружия ^ffcb4a10 ур.: дополнительно наносит ^96f5ff100%%^ffcb4a урона оружия@1@2^ffcb4aДополнительно наносит ^96f5ff%d%%^ffcb4a урона оружия.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL4419 
#define __CPPGEN_GNET_SKILL4419 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4419:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4419 }; 
        Skill4419 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4419Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

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
                skill->GetPlayer ()->SetDecmp (28);
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
                return 1500;
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
                skill->GetPlayer ()->SetDecmp (112);
                skill->SetPlus (5834);
                skill->SetRatio (1.0 + (skill->GetPlayer ()->GetCurweapon () == 9 ? 0.5 : 0)); // ������ +0.5
                skill->SetDamage (skill->GetAttack ());
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
    Skill4419Stub ():SkillStub (4419) 
    { 
        cls                 = 0; 
#ifdef _SKILL_CLIENT 
        name                = L"��������"; 
        nativename          = "��������"; 
        icon                = "�������ƻ�.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1117; 
        allow_forms         = 1; 
        apcost              = 80; 
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
        effect              = "��_��������.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "ֱ���˺�����1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (9); 
        restrict_weapons.push_back (1); 
        restrict_weapons.push_back (5); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1500 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 }; 
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
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
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
        int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const
        {
            return _snwprintf (buffer, length, format);
        }
#endif 
#ifdef _SKILL_SERVER 
        int GetEnmity (Skill * skill) const
        {
            return 7000;
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
            skill->GetVictim ()->SetTime (5000 + skill->GetT0 ());
            skill->GetVictim ()->SetValue (2);
            skill->GetVictim ()->SetPalsy (1);

            skill->GetVictim ()->SetProbability (1.0 * skill->GetT2 ());
            skill->GetVictim ()->SetTime (11000);
            skill->GetVictim ()->SetRatio (skill->GetPlayer ()->GetCls () == -1 ? 0.7 : 1);
            skill->GetVictim ()->SetSlowpray (1);

            skill->GetVictim ()->SetProbability (1.0 * skill->GetT1 () > 0 ? 100 : 0);
            skill->GetVictim ()->SetTime (7000);
            skill->GetVictim ()->SetAmount (skill->GetT1 ());
            skill->GetVictim ()->SetBleeding (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        bool BlessMe (Skill * skill) const
        {
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (20.1);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetCurweapon () == 9 ? 2000 : 0);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetCurweapon () == 5 ? 7 * player->GetEquipattack () : 0);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent2 (PlayerWrapper * player) const
        {
            return (float) (player->GetCurweapon () == 1 ? 100 : 0);
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
            return 13;
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
            return (float) (1.7);
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
