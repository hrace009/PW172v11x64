/*Skill Parser (c)Deadraky 2022 
44400  "Великий зов ветра"
44401  "^ff5c00Великий зов ветра

^ffcb4aМаг. энергия: ^96f5ff237^ffffff
^ffcb4aПодготовка: ^ffffffмгновенно
^ffcb4aПерезарядка: ^ffffff90,0 ^ffcb4aсек.
^ffcb4aОграничение по оружию: ^ffffffмагическая сфера, без оружия
^ffcb4aХарактеристика: ^ff5c00Храбрость

^ffcb4aСтатус: ^ffffffМудрец
Увеличивает скорость перемещения ^ff5c00шамана^ffffff до ^96f5ffмаксимальной^ffffff на ^96f5ff3^ffffff сек.
Кроме того, на ^96f5ff5^ffffff сек. шаман получает иммунитет к эффектам, ограничивающим передвижение.

^ff0000Эффект рубиновой руны:@1
^ff00001-4 ур.: скорость перемещения возрастает до максимума на ^96f5ff4^ff0000 сек.
^ff00005-7 ур.: скорость перемещения возрастает до максимума на ^96f5ff6^ff0000 сек.
^ff00008-9 ур.: скорость перемещения возрастает до максимума на ^96f5ff8^ff0000 сек.
 ^ff000010 ур.: скорость перемещения возрастает до максимума на ^96f5ff10^ff0000 сек.@1@2
^ff0000Скорость перемещения возрастает до максимума на ^96f5ff%d^ff0000 сек.@2"
*/
#ifndef __CPPGEN_GNET_SKILL4440 
#define __CPPGEN_GNET_SKILL4440 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4440:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4440 }; 
        Skill4440 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4440Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 500;
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
                skill->GetPlayer ()->SetDecmp (47);
                skill->GetPlayer ()->SetPerform (1);
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
    Skill4440Stub ():SkillStub (4440) 
    { 
        cls                 = 2; 
        name                = L"神·海风召唤"; 
        nativename          = "神·海风召唤"; 
        icon                = "神海风召唤红.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 0; 
        rank                = 41; 
        eventflag           = 1; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2451; 
        allow_forms         = 1; 
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
        effect              = "空.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "正面状态效果增强2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (25333); 
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
        static int aarray[10] = { 90000,90000,90000,90000,90000,90000,90000,90000,90000,90000 }; 
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
            return (float) (28.5);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 237,237,237,237,237,237,237,237,237,237 }; 
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
			^ff00001-4 ур.: скорость перемещения возрастает до максимума на ^96f5ff4^ff0000 сек.
			^ff00005-7 ур.: скорость перемещения возрастает до максимума на ^96f5ff6^ff0000 сек.
			^ff00008-9 ур.: скорость перемещения возрастает до максимума на ^96f5ff8^ff0000 сек.
			^ff000010 ур.: скорость перемещения возрастает до максимума на ^96f5ff10^ff0000 сек.
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 1000;
			static const int LEVEL_5_7 = 3000;
			static const int LEVEL_8_9 = 5000;
			static const int LEVEL_10_10 = 7000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };					
            skill->GetVictim ()->SetTime (4000 + ( aarray[skill->GetLevel () - 1] ));
            skill->GetVictim ()->SetRatio (9.9);
            skill->GetVictim ()->SetSpeedup (1);
			// шаман получает иммунитет к эффектам, ограничивающим передвижение
            skill->GetVictim ()->SetProbability (1.0 * 100);
			skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetFreemove (1);		

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
            return (float) (45);
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
            skill->GetPlayer ()->SetIncmpgen (2 * skill->GetLevel ());
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetHitrate (Skill * skill) const
        {
            return (float) (1);
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
