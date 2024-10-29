//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
50850  "Таинственный огневой рубеж"50851  "^ffff00Таинственный огневой рубеж^ffcb4aМаг. энергия: ^96f5ff300^ffffff^ffcb4aПодготовка: ^ffffffмгновенно^ffcb4aПерезарядка: ^ffffff60 ^ffcb4aсек.^ffcb4aОграничение по оружию: ^ffffffручная пушка^ffcb4aСтатус: ^ffffffБессмертныйСтрелок призывает под свое управление огневую платформу.В этом состоянии дальность атаки увеличивается на ^96f5ff10^ffffff м, урон увеличивается на ^96f5ff100%%^ffffff.После выхода из огневого режима эти эффекты исчезают.^808080В состоянии трансформации нельзя перемещаться, применять обычные умения и умения джинна.^a6caf0В этом состоянии можно использовать только особое умение 'Сияющий звездопад'.Огневая платформа существует ^96f5ff10^a6caf0 сек."*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL5085 
#define __CPPGEN_GNET_SKILL5085 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5085:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5085 }; 
        Skill5085 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5085Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
    class State1:public SkillStub::State
    {
    public:
        int GetTime (Skill * skill) const { return 1000; }
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
        int GetTime (Skill * skill) const { return 1000; }
        bool Quit (Skill * skill) const { return false; }
        bool Loop (Skill * skill) const { return false; }
        bool Bypass (Skill * skill) const { return false; }
        void Calculate (Skill * skill) const { }
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
    Skill5085Stub ():SkillStub (5085) 
    { 
        cls                 = 12; 
#ifdef _SKILL_CLIENT 
        name                = L"�����ױ�ɺ�"; 
        nativename          = "�����ױ�ɺ�"; 
        icon                = "�ױ�ɺ�.dds"; 
#endif 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 22; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1021; 
        allow_forms         = 3; 
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
        time_type           = 1; 
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
        pre_skills.push_back (std::pair < ID, int >(4955, 1)); 
        restrict_weapons.push_back (59831); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 500,500,500,500,500,500,500,500,500,500 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 }; 
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
        static int aarray[10] = { 5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000,5000000 }; 
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
        static float aarray[10] = { 0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 300,300,300,300,300,300,300,300,300,300 }; 
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
            skill->GetVictim ()->SetRatio (0);
            skill->GetVictim ()->SetAmount (0*skill->GetPlayer ()->GetAttack ());
            skill->GetVictim ()->SetValue (1.1);
			skill->GetVictim ()->SetTime (60000);
            skill->GetVictim ()->SetCannonform (1);
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
            return (float) (skill->GetPlayer ()->GetRange ());
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
