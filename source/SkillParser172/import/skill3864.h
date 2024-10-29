/*Skill Parser (c)Deadraky 2022 
38640  "Великое неистовство зверя"
38641  "^ff5c00Великое неистовство зверя

^ffcb4aМаг. энергия: ^96f5ff50
^ffcb4aПодготовка: ^ffffffмгновенно
^ffcb4aПерезарядка: ^ffffff30,0 ^ffcb4aсек.
^ffcb4aОграничение по оружию: ^ffffffтопоры и молоты, без оружия
^ffcb4aХарактеристика: ^ff5c00Мощь

^ffcb4aСтатус: ^ffffffАсура
Моментально затрачивается ^96f5ff5%%^ffffff текущего количества ЖС.
Если на момент активации умения у оборотня осталось менее ^96f5ff50%%^ffffff ЖС, появится щит,
способный поглотить урон, равный ^96f5ff50%%^ffffff базовой физ. атаки оборотня.
Щит действует не дольше ^96f5ff10^ffffff сек.
Если количество ЖС персонажа ниже ^96f5ff5%%^ffffff, умение использовать нельзя.

^ffeaabЭффект серебряной руны:@1
^ffeaab1-4 ур.: с каждых потраченных ^96f5ff16^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
^ffeaab5-7 ур.: с каждых потраченных ^96f5ff14^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
^ffeaab8-9 ур.: с каждых потраченных ^96f5ff12^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
^ffeaab 10 ур.: с каждых потраченных ^96f5ff10^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.@1@2
^ffeaabС каждых потраченных ^96f5ff%d^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3864 
#define __CPPGEN_GNET_SKILL3864 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3864:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3864 }; 
        Skill3864 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3864Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (50);
                skill->GetPlayer ()->SetPerform (1);
                skill->GetPlayer ()->SetHp (skill->GetPlayer ()->GetHp () * 0.05); // забирает 5% хп
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
    Skill3864Stub ():SkillStub (3864) 
    { 
        cls                 = 4; 
        name                = L"神·兽王之怒"; 
        nativename          = "神·兽王之怒"; 
        icon                = "神·兽王之怒白.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 1; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1526; 
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
        effect              = "怪物治疗术.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = "获得元气增加.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (9); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
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
        static int aarray[10] = { 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 }; 
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
        static float aarray[10] = { 50,50,50,50,50,50,50,50,50,50 }; 
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
			/*
			^ffeaab1-4 ур.: с каждых потраченных ^96f5ff16^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
			^ffeaab5-7 ур.: с каждых потраченных ^96f5ff14^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
			^ffeaab8-9 ур.: с каждых потраченных ^96f5ff12^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
			^ffeaab 10 ур.: с каждых потраченных ^96f5ff10^ffeaab ед. ЖС, возвращается ^96f5ff0,01^ffeaab ци.
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 10;
			static const int LEVEL_5_7 = 14;
			static const int LEVEL_8_9 = 12;
			static const int LEVEL_10_10 = 16;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };
            skill->GetVictim ()->SetValue ((skill->GetPlayer ()->GetHp () * 0.05) / ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetAp (1);
			
			
            skill->GetVictim ()->SetProbability (1.0 * skill->GetPlayer ()->GetHp () > skill->GetPlayer ()->GetMaxhp () * 0.5 ? 0 : 100);
            skill->GetVictim ()->SetTime (10000);
            skill->GetVictim ()->SetShowicon (1);
            skill->GetVictim ()->SetAmount (skill->GetT0 () * 0.5);
            skill->GetVictim ()->SetValue (0);
            skill->GetVictim ()->SetAbsorbmagicdamage (1);
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
            return (float) (8.5);
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
