/*Skill Parser (c)Deadraky 2022 
38450  "§£§Ö§Ý§Ú§Ü§Ú§Û §ä§í§ã§ñ§é§Ö§ä§à§ß§ß§í§Û §Þ§à§Ý§à§ä"
38451  "^ff5c00§£§Ö§Ý§Ú§Ü§Ú§Û §ä§í§ã§ñ§é§Ö§ä§à§ß§ß§í§Û §Þ§à§Ý§à§ä

^ffcb4a§¥§Ñ§Ý§î§ß§à§ã§ä§î: ^ffffff§Ò§Ý§Ú§Ø§ß§Ú§Û §Ò§à§Û
^ffcb4a§®§Ñ§Ô. §ï§ß§Ö§â§Ô§Ú§ñ: ^96f5ff%d^ffffff
^ffcb4a§±§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ: ^ffffff0,2^ffcb4a §ã§Ö§Ü.
^ffcb4a§±§â§Ú§Þ§Ö§ß§Ö§ß§Ú§Ö: ^ffffff0,9^ffcb4a §ã§Ö§Ü.
^ffcb4a§±§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ: ^ffffff6,0^ffcb4a §ã§Ö§Ü.
^ffcb4a§±§à§Ý§å§é§Ö§ß§Ú§Ö §è§Ú: ^ffffff0,15
^ffcb4a§°§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §á§à §à§â§å§Ø§Ú§ð: ^ffffff§ä§à§á§à§â§í §Ú §Þ§à§Ý§à§ä§í
^ffcb4a§·§Ñ§â§Ñ§Ü§ä§Ö§â§Ú§ã§ä§Ú§Ü§Ñ: ^ff5c00§®§å§Õ§â§à§ã§ä§î

^ffcb4a§³§ä§Ñ§ä§å§ã: ^ffffff§®§å§Õ§â§Ö§è
§²§Ñ§Ù§Þ§Ñ§ê§Ú§ã§ä§í§Û §å§Õ§Ñ§â, §ã§à§Ü§â§å§ê§Ñ§ð§ë§Ú§Û §á§â§à§ä§Ú§Ó§ß§Ú§Ü§Ñ.
§¯§Ñ§ß§à§ã§Ú§ä §Ò§Ñ§Ù§à§Ó§í§Û §æ§Ú§Ù§Ú§é§Ö§ã§Ü§Ú§Û §å§â§à§ß §á§Ý§ð§ã ^96f5ff3836^ffffff §Ö§Õ. §æ§Ú§Ù§Ú§é§Ö§ã§Ü§à§Ô§à §å§â§à§ß§Ñ.
§³ §Ó§Ö§â§à§ñ§ä§ß§à§ã§ä§î§ð ^96f5ff100%%^ffffff §á§Ñ§â§Ñ§Ý§Ú§Ù§å§Ö§ä §á§â§à§ä§Ú§Ó§ß§Ú§Ü§Ñ §ß§Ñ ^96f5ff4^ffffff §ã§Ö§Ü.

§¯§Ö §á§â§à§Þ§Ñ§ç§Ú§Ó§Ñ§Ö§ä§ã§ñ.

^ff0000§¿§æ§æ§Ö§Ü§ä §â§å§Ò§Ú§ß§à§Ó§à§Û §â§å§ß§í:@1
^ff00001-4 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff18^ff0000 §ã§Ö§Ü.
^ff00005-7 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff16^ff0000 §ã§Ö§Ü.
^ff00008-9 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff14^ff0000 §ã§Ö§Ü.
^ff0000 10 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff12^ff0000 §ã§Ö§Ü.@1@2
^ff0000§±§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff%d^ff0000 §ã§Ö§Ü.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3845 
#define __CPPGEN_GNET_SKILL3845 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3845:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3845 }; 
        Skill3845 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3845Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 200;
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
                skill->GetPlayer ()->SetDecmp (27);
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
                return 900;
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
                skill->GetPlayer ()->SetDecmp (108);
                skill->SetPlus (3836);
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
    Skill3845Stub ():SkillStub (3845) 
    { 
        cls                 = 4; 
        name                = L"Éñ¡¤Ç§½ï´¸"; 
        nativename          = "Éñ¡¤Ç§½ï´¸"; 
        icon                = "Éñ¡¤Ç§½ï´¸ºì.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 7; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1504; 
        allow_forms         = 1; 
        apcost              = 0; 
        apgain              = 15; 
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
        effect              = "ÑýÊÞ_ÐÂÇ§½ï´¸_»÷ÖÐ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "¸ºÃæ×´Ì¬Ð§¹ûÔöÇ¿1.gfx"; 
        gfxhangpoint        = "HH_spine"; 
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
        static int aarray[10] = { 900,900,900,900,900,900,900,900,900,900 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
		/*
		^ff00001-4 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff18^ff0000 §ã§Ö§Ü.
		^ff00005-7 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff16^ff0000 §ã§Ö§Ü.
		^ff00008-9 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff14^ff0000 §ã§Ö§Ü.
		^ff0000 10 §å§â.: §á§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff12^ff0000 §ã§Ö§Ü
		*/
		static const int LEVEL_1_4 = 18000;
		static const int LEVEL_5_7 = 16000;
		static const int LEVEL_8_9 = 14000;
		static const int LEVEL_10_10 = 12000;
		static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };
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
            return (float) (1 - 0.0111111 * (20 + 2.5 * skill->GetLevel ()));
        }
    float GetPraydistance (Skill * skill) const
    {
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 135,135,135,135,135,135,135,135,135,135 }; 
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
            skill->GetVictim ()->SetProbability (100);
            skill->GetVictim ()->SetTime (5000);
            skill->GetVictim ()->SetValue (2);
            skill->GetVictim ()->SetPalsy (1);
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
            return (float) (13);
        }		
#endif 
#ifdef _SKILL_SERVER 
                float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetRand ());
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
            return (float) (1.7);
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
