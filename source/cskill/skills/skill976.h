//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
39760  "Великая сила тысячи зверей"39761  "^ff5c00Великая сила тысячи зверей^ffcb4aДальность: ^96f5ff28^ffffff ^ffcb4aм^ffcb4aМаг. энергия: ^96f5ff150^ffcb4aПодготовка: ^ffffff3,3 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,0 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff15,0 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffмеч^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffАсураНаносит цели и всем противникам в радиусе ^96f5ff12^ffffff м базовый физический урон,плюс ^96f5ff500%%^ffffff урона оружия, плюс ^96f5ff8250^ffffff ед.Если противник находится под действием эффекта 'Великое Око каменного змея',удар наносит дополнительный урон и снижает его показатель атаки и защиты. С вероятностью ^96f5ff100%%^ffffff скорость перемещения противников снизится на значение,^96f5ff зависящее от уровня руны^ffffff на ^96f5ff8^ffffff сек.^00ff00Эффект изумрудной руны:@1^00ff001-4 ур.: гарантированно замедляет противников на ^96f5ff40%%^00ff00 в течение ^96f5ff8^00ff00 сек.^00ff005-7 ур.: гарантированно замедляет противников на ^96f5ff50%%^00ff00 в течение ^96f5ff8^00ff00 сек.^00ff008-9 ур.: гарантированно замедляет противников на ^96f5ff60%%^00ff00 в течение ^96f5ff8^00ff00 сек.^00ff00 10 ур.: гарантированно замедляет противников на ^96f5ff70%%^00ff00 в течение ^96f5ff8^00ff00 сек.@1@2^00ff00Гарантированно замедляет противников на ^96f5ff%d%%^00ff00 в течение ^96f5ff8^00ff00 сек.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL976 
#define __CPPGEN_GNET_SKILL976 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill976:public Skill 
    { 
    public: 
        enum { SKILL_ID = 976 }; 
        Skill976 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill976Stub:public SkillStub 
    { 
    public: 
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
                skill->GetPlayer ()->SetDecelfmp (55 + (skill->GetLevel () - 1) * 3);
                skill->GetPlayer ()->SetDecelfap (600);
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
    Skill976Stub ():SkillStub (976) 
    { 
        cls                 = 258; 
#ifdef _SKILL_CLIENT 
        name                = L"������"; 
        nativename          = "������"; 
        icon                = "������.dds"; 
#endif 
        max_level           = 10; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 5; 
        rank                = 0; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 0; 
        allow_forms         = 1; 
        apcost              = 600000; 
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
        auto_attack         = 1; 
        time_type           = 1; 
        long_range          = 0; 
        posdouble           = 1; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        itemcostcount       = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
#ifdef _SKILL_CLIENT 
        effect              = "������.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 5; 
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
        pre_skills.push_back (std::pair < ID, int >(0, 0)); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1160,1840,2780,4000,5620,7780,10640,14480,19660,26600 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 500021,500026,500031,500036,500041,500046,500051,500056,500061,500066 }; 
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
            return (float) (1 - 0.0111111 * (0));
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (0);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 55,58,61,64,67,70,73,76,79,82 }; 
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
            return _snwprintf (buffer, length, format, skill->GetLevel (), 55 + (skill->GetLevel () - 1) * 3, 100 - skill->GetLevel () * 5);

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
            skill->GetVictim ()->SetTime (3000 + skill->GetT1 () * 34);
            skill->GetVictim ()->SetImmuneslowdizzy (1);
            skill->GetVictim ()->SetProbability (1.0 * 100 - skill->GetLevel () * 5);
            skill->GetVictim ()->SetTime (8000);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetDecresist (1);
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
            return (float) (40);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetElfstr ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetElfagi ());
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
            return 20;
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
