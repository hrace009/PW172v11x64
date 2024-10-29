//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
66350  "Великое сотрясение небес"66351  "^ff5c00Великое сотрясение небес^ffcb4aПерсонаж должен быть в образе белой обезьяны^ffcb4aДальность: ^96f5ff%d^ffffff^ffcb4a м^ffcb4aМаг. энергия: ^96f5ff%d^ffffff^ffcb4aПодготовка: ^ffffffмгновенно^ffcb4aПрименение: ^ffffff1,0 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff60^ffcb4a сек.^ffcb4aОграничение по оружию: ^ffffffбоевой шест, без оружия^ffcb4aСтатус: ^ffffffМудрецСтранник прыжком настигает цель, нанося ей и всем противникам в радиусе ^96f5ff10^ffffff м^96f5ff200%%^ffffff базового физического урона плюс ^96f5ff%d^ffffff ед. физического урона и обездвиживая ихна ^96f5ff1^ffffff сек. Если странник находится под действием знаков 'Инь' и 'Ян', они активируются,оглушая противников на ^96f5ff5^ffffff сек.Умение не может нанести критический урон, но с вероятностью, в 2 разапревышающей шанс критического удара, наносит ^96f5ffполуторакратный^ffffff урон.^ffa4a9Во время применения персонаж невосприимчив к наложению негативных эффектов.Умение нельзя отменить.^a6caf0Не промахивается.Дополнительная стоимость: ^ffffff2^a6caf0 ци.^ffcb4aЭффект золотой руны:@1^ffcb4a1-4 ур.: добавляется ^96f5ff15%%^ffcb4a базового физического урона^ffcb4a5-7 ур.: добавляется ^96f5ff20%%^ffcb4a базового физического урона^ffcb4a8-9 ур.: добавляется ^96f5ff25%%^ffcb4a базового физического урона^ffcb4a 10 ур.: добавляется ^96f5ff30%%^ffcb4a базового физического урона@1@2К наносимому урону добавляется ^96f5ff%d%%^ffcb4a базового физического урона.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL6635 
#define __CPPGEN_GNET_SKILL6635 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill6635:public Skill 
    { 
    public: 
        enum { SKILL_ID = 6635 }; 
        Skill6635 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill6635Stub:public SkillStub 
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
                skill->GetPlayer()->SetDecmp(0.2 * (345));
                skill->GetPlayer ()->SetInvincibleMonkey (1550);
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
                return 1500;
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
                skill->GetPlayer()->SetDecmp(0.8 * (345));
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
    Skill6635Stub ():SkillStub (6635) 
    { 
        cls                 = 14; 
#ifdef _SKILL_CLIENT 
        name                = L"��������ǵ"; 
        nativename          = "��������ǵ"; 
        icon                = "��������ǵ��.dds"; 
#endif 
        max_level           = 1; 
        type                = 8; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1501; 
        allow_forms         = 2; 
        apcost              = 200; 
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
        combosk_nobreak     = 0; 
#ifdef _SKILL_CLIENT 
        effect              = ""; 
        aerial_effect       = ""; 
#endif 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 1401; 
        extra_effect        = 0; 
        immune_casting      = 1; 
        pre_skills.push_back (std::pair < ID, int >(6502, 1)); 
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
        static int array[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
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
        return (float)(20);
    }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 345,345,345,345,345,345,345,345,345,345 }; 
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
            skill->GetVictim ()->SetValue ((skill->GetPlayer ()->GetPureattack () + 1.8 * skill->GetPlayer ()->GetWeapondamage () + 12745) * skill->GetT2 () * 0.1 *
                                           (1 +
                                            0.01 * (skill->GetPlayer ()->GetAttackdegree () - skill->GetPlayer ()->GetDefenddegree () >
                                                    0 ? skill->GetPlayer ()->GetAttackdegree () - skill->GetPlayer ()->GetDefenddegree () : 0)));
            skill->GetVictim ()->SetPhysichurt (1);

            skill->GetVictim ()->SetProbability (1.0 * (skill->GetT0 () && skill->GetT1 () ? 100 : 0));
            skill->GetVictim ()->SetTime (5050);
            skill->GetVictim ()->SetValue (2);
            skill->GetVictim ()->SetPalsy (1);
            return true;
    }
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const
    {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetRemoveFilterMonkey (1);
            return true;
    }   
#endif 
#ifdef _SKILL_SERVER 
    float GetEffectdistance(Skill *skill) const
    {
        return (float)(25);
    }
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent0 (PlayerWrapper * player) const
    {
        return (float) (player->GetFilterID (4485));
    }
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent1 (PlayerWrapper * player) const
    {
        return (float) (player->GetFilterID (4486));
    }
#endif 
#ifdef _SKILL_SERVER 
    float GetTalent2 (PlayerWrapper * player) const
    {
            return (float) (player->GetRand () < player->GetCrit () * 2 ? 15 : 10);
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
