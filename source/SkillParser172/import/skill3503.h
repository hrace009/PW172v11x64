/*Skill Parser (c)Deadraky 2022 
35030  "§£§Ö§Ý§Ú§Ü§Ñ§ñ §ã§Ó§ñ§Ù§í§Ó§Ñ§ð§ë§Ñ§ñ §ã§ä§â§Ö§Ý§Ñ"
35031  "^ff5c00§£§Ö§Ý§Ú§Ü§Ñ§ñ §ã§Ó§ñ§Ù§í§Ó§Ñ§ð§ë§Ñ§ñ §ã§ä§â§Ö§Ý§Ñ 

^ffcb4a§¥§Ñ§Ý§î§ß§à§ã§ä§î: ^ffffff§Õ§Ñ§Ý§î§ß§ñ§ñ §Ñ§ä§Ñ§Ü§Ñ
^ffcb4a§®§Ñ§Ô. §ï§ß§Ö§â§Ô§Ú§ñ: ^96f5ff%d^ffffff
^ffcb4a§±§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ: §Ü§à§ß§è§Ö§ß§ä§â§Ñ§è§Ú§ñ §ã§Ú§Ý§í
^ffcb4a§±§â§Ú§Þ§Ö§ß§Ö§ß§Ú§Ö: ^ffffff0,6 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§±§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ: ^ffffff15,0 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§°§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §á§à §à§â§å§Ø§Ú§ð: ^ffffff§à§â§å§Ø§Ú§Ö §Õ§Ñ§Ý§î§ß§Ö§Ô§à §Ò§à§ñ
^ffcb4a§·§Ñ§â§Ñ§Ü§ä§Ö§â§Ú§ã§ä§Ú§Ü§Ñ: ^ff5c00§·§â§Ñ§Ò§â§à§ã§ä§î

^ffcb4a§³§ä§Ñ§ä§å§ã: ^ffffff§¡§ã§å§â§Ñ
§¬§à§Ó§Ñ§â§ß§í§Û §Ó§í§ã§ä§â§Ö§Ý, §ß§Ñ§ß§à§ã§ñ§ë§Ú§Û §Ò§Ñ§Ù§à§Ó§í§Û §æ§Ú§Ù§Ú§é§Ö§ã§Ü§Ú§Û §å§â§à§ß §á§Ý§ð§ã ^96f5ff9631^ffffff §Ö§Õ.
§°§Ò§Ö§Ù§Õ§Ó§Ú§Ø§Ú§Ó§Ñ§Ö§ä §á§â§à§ä§Ú§Ó§ß§Ú§Ü§Ñ §ß§Ñ ^96f5ff%d^ffffff §ã§Ö§Ü. §Ú §ß§Ñ§Ü§Ý§Ñ§Õ§í§Ó§Ñ§Ö§ä §ï§æ§æ§Ö§Ü§ä §Þ§à§Ý§é§Ñ§ß§Ú§ñ §ß§Ñ ^96f5ff%d^ffffff §ã§Ö§Ü.

^a6caf0§´§â§Ö§Ò§å§Ö§ä§ã§ñ: ^ffffff1^a6caf0 §ã§ä§â§Ö§Ý§Ñ §Ú§Ý§Ú §ã§ß§Ñ§â§ñ§Õ.
^a6caf0§¥§à§á§à§Ý§ß§Ú§ä§Ö§Ý§î§ß§Ñ§ñ §ã§ä§à§Ú§Þ§à§ã§ä§î: ^ffffff1^a6caf0 §è§Ú.

^ffeaab§¿§æ§æ§Ö§Ü§ä §ã§Ö§â§Ö§Ò§â§ñ§ß§à§Û §â§å§ß§í:@1
§¬§à§ß§è§Ö§ß§ä§â§Ú§â§å§Ö§ä §ã§Ú§Ý§å §Ó §ä§Ö§é§Ö§ß§Ú§Ö ^96f5ff1,5^ffeaab §ã§Ö§Ü.
^ffeaab1-4 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff2,5^ffeaab §ã§Ö§Ü.
^ffeaab5-7 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff3,3^ffeaab §ã§Ö§Ü.
^ffeaab8-9 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff4,0^ffeaab §ã§Ö§Ü.
^ffeaab 10 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff4,8^ffeaab §ã§Ö§Ü.@1@2
§¬§à§ß§è§Ö§ß§ä§â§Ú§â§å§Ö§ä §ã§Ú§Ý§å §Ó §ä§Ö§é§Ö§ß§Ú§Ö ^96f5ff1,5^ffeaab §ã§Ö§Ü., §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff%.1f^ffeaab §ã§Ö§Ü.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3503 
#define __CPPGEN_GNET_SKILL3503 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3503:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3503 }; 
        Skill3503 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3503Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 1000;
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
                skill->GetPlayer ()->SetDecmp (45);
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
                return 600;
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
                skill->GetPlayer ()->SetDecmp (180);
                skill->SetPlus (43);
                skill->SetRatio (0);
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
    Skill3503Stub ():SkillStub (3503) 
    { 
        cls                 = 6; 
        name                = L"Éñ¡¤À§¸¿Ê¸"; 
        nativename          = "Éñ¡¤À§¸¿Ê¸"; 
        icon                = "Éñ¡¤À§¸¿Ê¸°×.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1304; 
        allow_forms         = 1; 
        apcost              = 100; 
        apgain              = 0; 
        doenchant           = 1; 
        dobless             = 0; 
        arrowcost           = 1; 
        allow_land          = 1; 
        allow_air           = 1; 
        allow_water         = 1; 
        notuse_in_combat    = 0; 
        restrict_corpse     = 0; 
        restrict_change     = 0; 
        restrict_attach     = 0; 
        auto_attack         = 1; 
        time_type           = 3; 
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
        effect              = "2ÐéÈõÊ¸.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "¸ºÃæ×´Ì¬Ð§¹ûÔöÇ¿2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (13); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 600,600,600,600,600,600,600,600,600,600 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 15000,15000,15000,15000,15000,15000,15000,15000,15000,15000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 92,92,92,92,92,92,92,92,92,92 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int aarray[10] = { 1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000,1500000 }; 
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
        static float aarray[10] = { 225,225,225,225,225,225,225,225,225,225 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (8500);
            skill->GetVictim ()->SetFix (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
			
			/*
			^ffeaab1-4 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff2,5^ffeaab §ã§Ö§Ü.
			^ffeaab5-7 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff3,3^ffeaab §ã§Ö§Ü.
			^ffeaab8-9 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff4,0^ffeaab §ã§Ö§Ü.
			^ffeaab 10 §å§â.: §Þ§Ñ§Ü§ã. §Õ§Ý§Ú§ä§Ö§Ý§î§ß§à§ã§ä§î §ï§æ§æ§Ö§Ü§ä§Ñ §Þ§à§Ý§é§Ñ§ß§Ú§ñ - ^96f5ff4,8^ffeaab §ã§Ö§Ü.
			*/
			static int aarray[10] = { 1800, 1800, 1800, 1800, 2600, 2600, 2600, 3300, 3300, 4100 };				
            skill->GetVictim ()->SetTime (1000 + ( aarray[skill->GetLevel () - 1] ) * skill->GetT0 () / 1500); 
            skill->GetVictim ()->SetSealed (1);
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
            return (float) (skill->GetPlayer ()->GetRange () + 5);
        }		
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetCharging ());
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
            return (float) (1.5);
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
