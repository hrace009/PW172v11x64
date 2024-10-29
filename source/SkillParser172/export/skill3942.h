//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
39420  "Великое морозное сияние"39421  "^ff5c00Великое морозное сияние^ffcb4aДальность: ^96f5ff20^ffffff ^ffcb4aм^ffcb4aМаг. энергия: ^96f5ff%d^ffcb4aПодготовка: ^ffffff0,3 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,2 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff30 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffкопье^ffcb4aХарактеристика: ^ff5c00Храбрость^ffcb4aСтатус: ^ffffffМудрецВоин ударяет по земле, поражая всех противников в радиусе ^96f5ff12^ffffff м от цели. Наноситбазовый физический урон, плюс ^96f5ff100%%^ffffff урона оружия, плюс ^96f5ff8504^ffffff ед. физ. урона.Если расстояние до противников меньше ^96f5ff10^ffffff м, снижает их физическую и магическую защиту.Снижает защиту монстров на ^96f5ff%d%%^ffffff. Снижает физическую защиту игроков на ^96f5ff90%%^ffffff, а магическую - на ^96f5ff60%%^ffffff.Если расстояние до противников больше ^96f5ff10^ffffff м, замораживает их на ^96f5ff5^ffffff сек.После применения восстанавливается ^96f5ff0,5^ffffff ци.^a6caf0Дополнительная стоимость: ^ffffff2^a6caf0 ци.^ffeaabЭффект серебряной руны:@1^ffeaab1-4 ур.: добавляется ^96f5ff60%%^ffeaab урона оружия и ^96f5ff1592^ffeaab ед. физ. урона^ffeaab5-7 ур.: добавляется ^96f5ff90%%^ffeaab урона оружия и ^96f5ff2388^ffeaab ед. физ. урона^ffeaab8-9 ур.: добавляется ^96f5ff120%%^ffeaab урона оружия и ^96f5ff3184^ffeaab ед. физ. урона^ffeaab 10 ур.: добавляется ^96f5ff150%%^ffeaab урона оружия и ^96f5ff3980^ffeaab ед. физ. урона@1@2^ffeaabДобавляется ^96f5ff%d%%^ffeaab урона оружия и ^96f5ff%d^ffeaab ед. физ. урона.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3942 
#define __CPPGEN_GNET_SKILL3942 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3942:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3942 }; 
        Skill3942 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3942Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

#ifdef _SKILL_SERVER 
    class State1:public SkillStub::State
    {
     public:
            int GetTime (Skill * skill) const{return 300;}
            bool Quit (Skill * skill) const{return false;}
            bool Loop (Skill * skill) const{return false;}
            bool Bypass (Skill * skill) const{return false;}
            void Calculate (Skill * skill) const{skill->GetPlayer ()->SetDecmp (61);skill->GetPlayer ()->SetPray (1);}
            bool Interrupt (Skill * skill) const{return false;}bool Cancel (Skill * skill) const{return 1;}
            bool Skip (Skill * skill) const{return 0;}
    };
#endif 
#ifdef _SKILL_SERVER 
    class State2:public SkillStub::State
    {
    public:
            int GetTime (Skill * skill) const{return 1800;}
            bool Quit (Skill * skill) const{return false;}
            bool Loop (Skill * skill) const{return false;}
            bool Bypass (Skill * skill) const{return false;}
            void Calculate (Skill * skill) const{
                skill->GetPlayer ()->SetDecmp (244);
                skill->SetPlus (9504);
                skill->SetRatio (2);
                skill->SetDamage (skill->GetAttack ());
                skill->GetPlayer ()->SetPerform (1);
            }
            bool Interrupt (Skill * skill) const{return false;}
            bool Cancel (Skill * skill) const{return 0;}
            bool Skip (Skill * skill) const{return 0;}
    };
#endif 
#ifdef _SKILL_SERVER 
    class State3:public SkillStub::State
    {
          public:
            int GetTime (Skill * skill) const{return 0;}
            bool Quit (Skill * skill) const{return false;}
            bool Loop (Skill * skill) const{return false;}
            bool Bypass (Skill * skill) const{return false;}
            void Calculate (Skill * skill) const{}
            bool Interrupt (Skill * skill) const{return false;}
            bool Cancel (Skill * skill) const{return 0;}
            bool Skip (Skill * skill) const{return 0;}
    };
#endif 
    Skill3942Stub ():SkillStub (3942) 
    { 
        cls                 = 0; 
#ifdef _SKILL_CLIENT 
        name                = L"�񡤺�������"; 
        nativename          = "�񡤺�������"; 
        icon                = "�񡤺��������.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1116; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 50; 
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
        effect              = "��_��������_����.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "ֱ���˺�����1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
#endif 
        gfxtarget           = 0; 
        feature             = 3; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (5); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1800,1800,1800,1800,1800,1800,1800,1800,1800,1800 };
        return array[skill->GetLevel () - 1];
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
            return (float) (12);
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
        static float aarray[10] = { 305,305,305,305,305,305,305,305,305,305 }; 
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
            return _snwprintf (buffer, length, format, 305, 50);

        }
#endif 
#ifdef _SKILL_SERVER 
        int GetEnmity (Skill * skill) const
        {
            return 10000;
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
            skill->GetVictim ()->SetRatio (0.9);
            skill->GetVictim ()->SetDecdefence (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetDecresist (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 50);
            skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetValue (99);
            skill->GetVictim ()->SetIncsmite (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (8);
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
            return 16;
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
            return (float) (3);
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
