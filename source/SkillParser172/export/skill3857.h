//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
38570  "Великий сбитый дракон"38571  "^ff5c00Великий сбитый дракон ^ffcb4aДальность: ^96f5ff35^ffffff ^ffcb4aм^ffcb4aМаг. энергия: ^96f5ff303^ffffff^ffcb4aПодготовка: ^ffffff0,6^ffcb4a сек.^ffcb4aПрименение: ^ffffff1,5^ffcb4a сек.^ffcb4aПерезарядка: ^ffffff60,0^ffcb4a сек.^ffcb4aОграничение по оружию: ^ffffffтопоры и молоты^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffАсураНаносит всем противникам в радиусе ^96f5ff20^ffffff м ^96f5ff120%%^ffffff базового физического урона.Летающим противникам наносит ^96f5ffтройной^ffffff урон и с вероятностью ^96f5ff100%%^ffffffсбивает их на землю, после чего они не могут взлететь в течение ^96f5ff30^ffffff сек.Не промахивается.^a6caf0Навык нельзя применить в полете.Дополнительная стоимость: ^ffffff2^a6caf0 ци.^ff0000Эффект рубиновой руны:@1^ff00001-4 ур.: после применения возвращается ^96f5ff0,4^ff0000 ци^ff00005-7 ур.: после применения возвращается ^96f5ff0,6^ff0000 ци^ff00008-9 ур.: после применения возвращается ^96f5ff0,8^ff0000 ци^ff0000 10 ур.: после применения возвращается ^96f5ff1^ff0000 ци@1@2^ff0000После применения возвращается ^96f5ff%d сотых ед. ци.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL3857 
#define __CPPGEN_GNET_SKILL3857 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3857:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3857 }; 
        Skill3857 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3857Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 650;
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
                skill->GetPlayer ()->SetDecmp (61);
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
                return 1450;
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
                skill->GetPlayer ()->SetDecmp (242);
                skill->SetPlus (0);
                skill->SetRatio (0);
                skill->SetDamage (1.2 * skill->GetAttack ());
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
    Skill3857Stub ():SkillStub (3857) 
    { 
        cls                 = 4; 
#ifdef _SKILL_CLIENT 
        name                = L"�����ɾ�"; 
        nativename          = "�����ɾ�"; 
        icon                = "�����ɾ���.dds"; 
#endif 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2905; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 0; 
        doenchant           = 1; 
        dobless             = 0; 
        arrowcost           = 0; 
        allow_land          = 1; 
        allow_air           = 0; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 1; 
        time_type           = 0; 
        long_range          = 0; 
        posdouble           = 2; 
        clslimit            = 0; 
        commoncooldown      = 0; 
        commoncooldowntime  = 0; 
        itemcost            = 0; 
        itemcostcount       = 0; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
#ifdef _SKILL_CLIENT 
        effect              = "����_����֮��.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 3; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "����Ԫ������.gfx"; 
        gfxhangpoint        = "HH_bind"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (9); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    {
        static int array[10] = { 1450,1450,1450,1450,1450,1450,1450,1450,1450,1450 };
        return array[skill->GetLevel () - 1];
    }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 60000,60000,60000,60000,60000,60000,60000,60000,60000,60000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 500000,500000,500000,500000,500000,500000,500000,500000,500000,500000 }; 
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
            return (float) (20);
        }
    float GetAttackdistance (Skill * skill) const
    {
            return (float) (0);
        }
    float GetAngle (Skill * skill) const
    {
            return (float) (1 - 0.0111111 * (180));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (35);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 240,240,240,240,240,240,240,240,240,240 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 80 + (skill->GetT0 () - skill->GetPlayer ()->GetSoulpower ()) / 2000);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetNofly (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
bool BlessMe (Skill * skill) const
        {            
			static const float LEVEL_1_4 = 40;
			static const float LEVEL_5_7 = 60;
			static const float LEVEL_8_9 = 80;
			static const float LEVEL_10_10 = 100;
			static float aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };
			
			
            skill->GetVictim ()->SetProbability (1.0 * 100); 
            skill->GetVictim ()->SetValue ( aarray[skill->GetLevel () - 1] ); 
            skill->GetVictim ()->SetAp (1); 

			return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (50);
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
            return (float) (4);
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
