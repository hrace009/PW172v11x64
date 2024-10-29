//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
66110  "Великие сто вершин"66111  "^ff5c00Великие сто вершин^ffcb4aПерсонаж должен быть в образе белой обезьяны^ffcb4aДальность: ^ffffffближний бой^ffcb4aМаг. энергия: ^96f5ff%.1f^ffffff^ffcb4aПодготовка: ^ffffff0,5 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff1,7 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff5,0 ^ffcb4aсек.^ffcb4aПолучение ци: ^ffffff0,3^ffcb4aОграничение по оружию: ^ffffffбоевой шест, без оружия^ffcb4aСтатус: ^ffffffМудрецВетер дует со всех сторон, сотрясая горы.Наносит противникам в радиусе ^96f5ff10^ffffff м ^96f5ff180%%^ffffff базового физического урона плюс ^96f5ff%d^ffffff ед.физического урона. В течение ^96f5ff5^ffffff сек. скорость передвижения противников снижается на ^96f5ff50%%^ffffff.Дает страннику знак 'Ян' на ^96f5ff15^ffffff сек.^ffa4a9Во время применения персонаж невосприимчив к наложению негативных эффектов.Умение нельзя отменить.^ffcb4aЭффект золотой руны:@1^ffcb4a1-4 ур.: добавляется ^96f5ff10%%^ffcb4a базового физического урона^ffcb4a5-7 ур.: добавляется ^96f5ff15%%^ffcb4a базового физического урона^ffcb4a8-9 ур.: добавляется ^96f5ff20%%^ffcb4a базового физического урона^ffcb4a 10 ур.: добавляется ^96f5ff25%%^ffcb4a базового физического урона@1@2К наносимому урону добавляется ^96f5ff%d%%^ffcb4a базового физического урона.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL6611 
#define __CPPGEN_GNET_SKILL6611 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6611:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6611 }; 
        Skill6611 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6611Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 500;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.2 * (142.2));
                skill->GetPlayer()->SetPray(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 1;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif 
#ifdef _SKILL_SERVER 
        class State2 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 1700;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.8 * (142.2));
                skill->SetPlus(9092);
                skill->SetRatio(1.6);
                skill->SetDamage(skill->GetAttack());
                skill->GetPlayer()->SetPerform(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif 
#ifdef _SKILL_SERVER 
        class State3 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 0;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif 
    Skill6611Stub ():SkillStub (6611) 
    { 
        cls                 = 14; 
#ifdef _SKILL_CLIENT 
        name                = L"����������"; 
        nativename          = "����������"; 
        icon                = "������������.dds"; 
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
        showorder           = 1501; 
        allow_forms         = 2; 
        apcost              = 0; 
        apgain              = 30; 
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
        effect              = ""; 
        aerial_effect       = ""; 
#endif 
        range.type          = 2; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 1; 
        pre_skills.push_back (std::pair < ID, int >(6543, 1)); 
        pre_skills.push_back (std::pair < ID, int >(6544, 1)); 
        restrict_weapons.push_back (69843); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1700,1700,1700,1700,1700,1700,1700,1700,1700,1700 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 5000,5000,5000,5000,5000,5000,5000,5000,5000,5000 }; 
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
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
    float GetRadius(Skill *skill) const
    {
        return (float)(8);
    }
    float GetAttackdistance(Skill *skill) const
    {
        return (float)(0);
    }
    float GetAngle(Skill *skill) const
    {
        return (float)(1 - 0.0111111 * (0));
    }
    float GetPraydistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer()->GetRange() + 8);
    }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 142,142,142,142,142,142,142,142,142,142 }; 
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
    int GetIntroduction(Skill *skill, wchar_t *buffer, int length, wchar_t *format) const
    {
            return _snwprintf(buffer, length, format);
    }
#endif 
#ifdef _SKILL_SERVER 
    int GetEnmity(Skill *skill) const
    {
            return 100;
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
            skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetRatio (0.5);
            skill->GetVictim ()->SetSlow (1);
            return true;
    }
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const
    {
         //   skill->GetVictim ()->SetProbability (1.0 * 100);
        //    skill->GetVictim ()->SetTime (16000);
         //   skill->GetVictim ()->SetShowicon (0);
         //   skill->GetVictim ()->SetMarcaYang (1); 

        return true;
    }   
#endif 
#ifdef _SKILL_SERVER 
    float GetEffectdistance(Skill *skill) const
    {
        return (float)(skill->GetPlayer()->GetRange() + 10);
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
    int GetAttackspeed(Skill *skill) const
    {
        return 0;
    }
#endif 
#ifdef _SKILL_SERVER 
    bool TakeEffect(Skill *skill) const
    {;
        return true;
    }
#endif 
#ifdef _SKILL_SERVER 
    float GetHitrate(Skill *skill) const
    {
        return (float)(1.0);
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
