/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
35120  "§£§Ö§Ý§Ú§Ü§Ú§Û §á§Ñ§â§ñ§ë§Ú§Û §à§â§Ö§Ý"
35121  "^ff5c00§£§Ö§Ý§Ú§Ü§Ú§Û §á§Ñ§â§ñ§ë§Ú§Û §à§â§Ö§Ý

^ffcb4a§®§Ñ§Ô. §ï§ß§Ö§â§Ô§Ú§ñ: ^96f5ff100
^ffcb4a§±§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ: ^ffffff1,0 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§±§â§Ú§Þ§Ö§ß§Ö§ß§Ú§Ö: ^ffffff2,5 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§±§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ: ^ffffff30,0 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§°§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §á§à §à§â§å§Ø§Ú§ð: ^ffffff§ß§Ö§ä
^ffcb4a§·§Ñ§â§Ñ§Ü§ä§Ö§â§Ú§ã§ä§Ú§Ü§Ñ: ^ff5c00§®§å§Õ§â§à§ã§ä§î

^ffcb4a§³§ä§Ñ§ä§å§ã: ^ffffff§¡§ã§å§â§Ñ
§­§å§é§ß§Ú§Ü §Ü§à§ß§è§Ö§ß§ä§â§Ú§â§å§Ö§ä §ã§Ó§à§Ú §ã§Ú§Ý§í, §ã§ä§Ñ§ß§à§Ó§ñ§ã§î §ß§Ñ ^96f5ff15^ffffff §ã§Ö§Ü. §ß§Ö§Ó§à§ã§á§â§Ú§Ú§Þ§é§Ú§Ó§í§Þ §Ü §ï§æ§æ§Ö§Ü§ä§Ñ§Þ, §à§Ô§â§Ñ§ß§Ú§é§Ú§Ó§Ñ§ð§ë§Ú§Þ §ã§Ü§à§â§à§ã§ä§î §á§Ö§â§Ö§Õ§Ó§Ú§Ø§Ö§ß§Ú§ñ,
§Ú §á§à§Ý§å§é§Ñ§Ö§ä §ß§Ñ ^96f5ff30%%^ffffff §Þ§Ö§ß§î§ê§Ö §å§â§à§ß§Ñ.
§¦§Ô§à §ã§Ü§à§â§à§ã§ä§î §á§Ö§â§Ö§Õ§Ó§Ú§Ø§Ö§ß§Ú§ñ §å§Ó§Ö§Ý§Ú§é§Ú§Ó§Ñ§Ö§ä§ã§ñ §ß§Ñ ^96f5ff30%%^ffffff.
§£§à §Ó§â§Ö§Þ§ñ §á§â§Ú§Þ§Ö§ß§Ö§ß§Ú§ñ §Õ§Ñ§ß§ß§à§Ô§à §ß§Ñ§Ó§í§Ü§Ñ §Ý§å§é§ß§Ú§Ü §ß§Ö §á§à§Ý§å§é§Ñ§Ö§ä §å§â§à§ß§Ñ.

^a6caf0§¥§à§á§à§Ý§ß§Ú§ä§Ö§Ý§î§ß§Ñ§ñ §ã§ä§à§Ú§Þ§à§ã§ä§î: ^ffffff1^a6caf0 §è§Ú.

^00ff00§¿§æ§æ§Ö§Ü§ä §Ú§Ù§å§Þ§â§å§Õ§ß§à§Û §â§å§ß§í:@1
^00ff001-4 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,7^00ff00 §ã§Ö§Ü.
^00ff005-7 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,5^00ff00 §ã§Ö§Ü.
^00ff008-9 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,3^00ff00 §ã§Ö§Ü.
^00ff00 10 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,1^00ff00 §ã§Ö§Ü.@1@2
§±§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff%.1f^00ff00 §ã§Ö§Ü.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3512 
#define __CPPGEN_GNET_SKILL3512 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3512:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3512 }; 
        Skill3512 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3512Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
			static int aarray[10] = { 700,700,700,700,500,500,500,300,300,100 }; 
			return aarray[skill->GetLevel () - 1]; 
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
                return 3000;
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
                skill->GetPlayer ()->SetDecmp (100);
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
    Skill3512Stub ():SkillStub (3512) 
    { 
        cls                 = 6; 
        name                = L"Éñ¡¤ÉñÓ¥ÒíÑï"; 
        nativename          = "Éñ¡¤ÉñÓ¥ÒíÑï"; 
        icon                = "Éñ¡¤ÉñÓ¥ÒíÑïÂÌ.dds"; 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1320; 
        allow_forms         = 1; 
        apcost              = 100; 
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
        effect              = "ÉñÓ¥Ö®Òí.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = "Ò÷³ªÊ±¼äËõ¶Ì.gfx"; 
        gfxhangpoint        = "HH_bind"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (13); 
        restrict_weapons.push_back (1); 
        restrict_weapons.push_back (5); 
        restrict_weapons.push_back (9); 
        restrict_weapons.push_back (182); 
        restrict_weapons.push_back (291); 
        restrict_weapons.push_back (292); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
	/*
	^00ff001-4 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,7^00ff00 §ã§Ö§Ü.
	^00ff005-7 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,5^00ff00 §ã§Ö§Ü.
	^00ff008-9 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,3^00ff00 §ã§Ö§Ü.
	^00ff00 10 §å§â.: §á§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ §ã§à§Ü§â§Ñ§ë§Ñ§Ö§ä§ã§ñ §Õ§à ^96f5ff0,1^00ff00 §ã§Ö§Ü
	*/
        static int aarray[10] = { 700,700,700,700,500,500,500,300,300,100 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 69600,69600,69600,69600,69600,69600,69600,69600,69600,69600 }; 
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
        static float aarray[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
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
            skill->GetVictim ()->SetTime (15000);
            skill->GetVictim ()->SetFreemove (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (15000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetDechurt (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (15000);
            skill->GetVictim ()->SetRatio (0.3);
            skill->GetVictim ()->SetSpeedup (1);
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (3000);
            skill->GetVictim ()->SetShowicon (1);
            skill->GetVictim ()->SetInvincible (1);
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
            return (float) (1 + 0.05 * skill->GetLevel ());
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
