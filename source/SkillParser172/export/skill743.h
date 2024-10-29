//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
37430  "Великое нашествие саранчи"37431  "^ff5c00Великое нашествие саранчи^ffcb4aДальность: ^96f5ff%d^ffcb4a мМаг. энергия: ^96f5ff%d^ffcb4aПодготовка: ^ffffff3,0^ffcb4a сек.Применение: ^ffffff1,2^ffcb4a сек.Перезарядка: ^ffffff30,0^ffcb4a сек.Ограничение по оружию: ^ffffffмагическое оружие, без оружия^ffcb4aХарактеристика: ^ff5c00Храбрость^ffcb4aСтатус: ^ffffffМудрецПризывает рой насекомых, которые наносят цели и всем врагам в радиусе 12 мбазовый маг. урон, плюс 300%% урона оружия, плюс 8606 ед. урона стихией дерева.Укусы саранчи наклад. на врагов печать, и они не могут атак. и двиг. в течение 8 сек.Цель, на которую наложена печать, получит доп. 20%% урона.^a6caf0Доп. стоимость: ^ffffff2^a6caf0 ци.После применения восст. ^96f5ff0,5^a6caf0 ци.^ffeaabЭффект серебряной руны:@1^ffeaabНаносит доп. урон, если у цели присутствуют эффекты серебр. руны умений^96f5ff [Великий жалящий рой]^ffeaab, ^96f5ff[Великое каменное проклятие]^ffeaab, ^96f5ff[Великий муравьиный рой]^ffeaab и ^96f5ff[Великий рой камней]^ffeaab, затем эффект пропадает.^ffeaab1-4 ур.: наносит дополнительный урон ядом в размере ^96f5ff50%%^ffeaab урона от стихий^ffeaab5-7 ур.: наносит дополнительный урон ядом в размере ^96f5ff60%%^ffeaab урона от стихий^ffeaab8-9 ур.: наносит дополнительный урон ядом в размере ^96f5ff70%%^ffeaab урона от стихий^ffeaab 10 ур.: наносит дополнительный урон ядом в размере ^96f5ff80%%^ffeaab урона от стихий@1@2^ffeaabНаносит доп. урон, равный ^96f5ff%d%%^ffeaab от урона стихий, если у цели присутств. эффекты серебр. руны умений^96f5ff [Великий жалящий рой]^ffeaab,^96f5ff[Великое каменное проклятие]^ffeaab, ^96f5ff[Великий муравьиный рой]^ffeaab или ^96f5ff[Великий рой камней]^ffeaab, затем эффект пропадает.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL743 
#define __CPPGEN_GNET_SKILL743 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill743:public Skill 
    { 
    public: 
        enum { SKILL_ID = 743 }; 
        Skill743 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill743Stub:public SkillStub 
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
    Skill743Stub ():SkillStub (743) 
    { 
        cls                 = 127; 
#ifdef _SKILL_CLIENT 
        name                = L"��Ʒ����-����ܰ����"; 
        nativename          = "��Ʒ����-����ܰ����"; 
        icon                = ""; 
#endif 
        max_level           = 10; 
        type                = 4; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 0; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 0; 
        allow_forms         = 0; 
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
        effect              = ""; 
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
        pre_skills.push_back (std::pair < ID, int >(0, 1)); 
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 1,2,3,4,5,0,0,0,0,0 }; 
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
            skill->GetVictim ()->SetTime (300000);
            skill->GetVictim ()->SetFlower1 (1);
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
            return (float) (250);
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
            return (float) (0);
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
