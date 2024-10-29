/*Skill Parser (c)Deadraky 2022 
43700  "§£§Ö§Ý§Ú§Ü§Ú§Û §à§ä§á§Ö§é§Ñ§ä§à§Ü §Ø§Ú§Ù§ß§Ú"
43701  "^ff5c00§£§Ö§Ý§Ú§Ü§Ú§Û §à§ä§á§Ö§é§Ñ§ä§à§Ü §Ø§Ú§Ù§ß§Ú

^ffcb4a§¥§Ñ§Ý§î§ß§à§ã§ä§î: ^96f5ff30^ffcb4a §Þ
^ffcb4a§®§Ñ§Ô. §ï§ß§Ö§â§Ô§Ú§ñ: ^96f5ff545
^ffcb4a§±§à§Õ§Ô§à§ä§à§Ó§Ü§Ñ: ^ffffff0,2 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§±§â§Ú§Þ§Ö§ß§Ö§ß§Ú§Ö: ^ffffff0,6 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§±§Ö§â§Ö§Ù§Ñ§â§ñ§Õ§Ü§Ñ: ^ffffff60,0 ^ffcb4a§ã§Ö§Ü.
^ffcb4a§°§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §á§à §à§â§å§Ø§Ú§ð: ^ffffff§Þ§Ñ§Ô§Ú§é§Ö§ã§Ü§à§Ö §à§â§å§Ø§Ú§Ö, §Ò§Ö§Ù §à§â§å§Ø§Ú§ñ
^ffcb4a§·§Ñ§â§Ñ§Ü§ä§Ö§â§Ú§ã§ä§Ú§Ü§Ñ: ^ff5c00§®§å§Õ§â§à§ã§ä§î

^ffcb4a§³§ä§Ñ§ä§å§ã: ^ffffff§®§å§Õ§â§Ö§è
§©§Ñ§á§à§Þ§Ú§ß§Ñ§Ö§ä §ä§Ö§Ü§å§ë§Ö§Ö §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §¨§³ §á§â§à§ä§Ú§Ó§ß§Ú§Ü§Ñ §Ú §Ó§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§ä §Ö§Ô§à §Ü §ï§ä§à§Þ§å §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§å §é§Ö§â§Ö§Ù ^96f5ff6^ffffff §ã§Ö§Ü.
^a6caf0§¥§Ö§Û§ã§ä§Ó§å§Ö§ä §ä§à§Ý§î§Ü§à §ß§Ñ §Ú§Ô§â§à§Ü§à§Ó.

^a6caf0§¥§à§á§à§Ý§ß§Ú§ä§Ö§Ý§î§ß§Ñ§ñ §ã§ä§à§Ú§Þ§à§ã§ä§î: ^ffffff0,2^a6caf0 §è§Ú."
*/
#ifndef __CPPGEN_GNET_SKILL4370 
#define __CPPGEN_GNET_SKILL4370 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4370:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4370 }; 
        Skill4370 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4370Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (145);
                skill->GetPlayer ()->SetPray (1);
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
                skill->GetPlayer ()->SetDecmp (400);
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
    Skill4370Stub ():SkillStub (4370) 
    { 
        cls                 = 1; 
        name                = L"Éñ¡¤Ì«ÐéÄæÁ÷¾÷"; 
        nativename          = "Éñ¡¤Ì«ÐéÄæÁ÷¾÷"; 
        icon                = "ÉñÌ«ÐéÄæÁ÷¾÷.dds"; 
        max_level           = 1; 
        type                = 3; 
        allow_ride          = 0; 
        attr                = 5; 
        rank                = 41; 
        eventflag           = 1; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 2906; 
        allow_forms         = 1; 
        apcost              = 20; 
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
        effect              = "¾²Ú×Ö®Êõ2_»÷ÖÐ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 2; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(1865, 1)); 
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
        static int aarray[10] = { 600,600,600,600,600,600,600,600,600,600 }; 
        return aarray[skill->GetLevel () - 1]; 
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
        static int aarray[10] = { 56515,56515,56515,56515,56515,56515,56515,56515,56515,56515 }; 
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
            return (float) (30);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 545,545,545,545,545,545,545,545,545,545 }; 
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
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetHprollback (1);
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
            return (float) (38);
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
