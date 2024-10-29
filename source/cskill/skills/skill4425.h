//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
44250  "Ð’ÐµÐ»Ð¸ÐºÐ¾Ðµ Ð½ÐµÐ²Ð¸Ð´Ð¸Ð¼Ð¾Ðµ Ð»ÐµÐ·Ð²Ð¸Ðµ"44251  "^ff5c00Ð’ÐµÐ»Ð¸ÐºÐ¾Ðµ Ð½ÐµÐ²Ð¸Ð´Ð¸Ð¼Ð¾Ðµ Ð»ÐµÐ·Ð²Ð¸Ðµ^ffcb4aÐœÐ°Ð³. ÑÐ½ÐµÑ€Ð³Ð¸Ñ: ^96f5ff200^ffffff^ffcb4aÐŸÐ¾Ð´Ð³Ð¾Ñ‚Ð¾Ð²ÐºÐ°: ^ffffffÐ¼Ð³Ð½Ð¾Ð²ÐµÐ½Ð½Ð¾^ffcb4a^ffcb4aÐŸÐµÑ€ÐµÐ·Ð°Ñ€ÑÐ´ÐºÐ°: ^ffffff3,0^ffcb4a Ð¼Ð¸Ð½^ffcb4aÐžÐ³Ñ€Ð°Ð½Ð¸Ñ‡ÐµÐ½Ð¸Ðµ Ð¿Ð¾ Ð¾Ñ€ÑƒÐ¶Ð¸ÑŽ: ^ffffffÐ¼ÐµÑ‡^ffcb4aÐ¥Ð°Ñ€Ð°ÐºÑ‚ÐµÑ€Ð¸ÑÑ‚Ð¸ÐºÐ°: ^ff5c00ÐœÐ¾Ñ‰ÑŒ^ffcb4aÐ¡Ñ‚Ð°Ñ‚ÑƒÑ: ^ffffffÐÑÑƒÑ€Ð°ÐŸÐ¾Ð²Ñ‹ÑˆÐ°ÐµÑ‚ ÑˆÐ°Ð½Ñ Ð½Ð°Ð½ÐµÑÐµÐ½Ð¸Ñ ÐºÑ€Ð¸Ñ‚Ð¸Ñ‡ÐµÑÐºÐ¾Ð³Ð¾ ÑƒÐ´Ð°Ñ€Ð° Ð´Ð¾ ^96f5ff100%%^ffffff Ð½Ð° Ð²Ñ€ÐµÐ¼Ñ, Ð·Ð°Ð²Ð¸ÑÑÑ‰ÐµÐµ Ð¾Ñ‚ ÑƒÑ€Ð¾Ð²Ð½Ñ Ñ€ÑƒÐ½Ñ‹.^ffcb4aÐ­Ñ„Ñ„ÐµÐºÑ‚ Ð·Ð¾Ð»Ð¾Ñ‚Ð¾Ð¹ Ñ€ÑƒÐ½Ñ‹:@1^ffcb4a1-4 ÑƒÑ€.: ÑÑ„Ñ„ÐµÐºÑ‚ Ð´Ð»Ð¸Ñ‚ÑÑ ^96f5ff6^ffcb4a ÑÐµÐº.^ffcb4a5-7 ÑƒÑ€.: ÑÑ„Ñ„ÐµÐºÑ‚ Ð´Ð»Ð¸Ñ‚ÑÑ ^96f5ff8^ffcb4a ÑÐµÐº.^ffcb4a8-9 ÑƒÑ€.: ÑÑ„Ñ„ÐµÐºÑ‚ Ð´Ð»Ð¸Ñ‚ÑÑ ^96f5ff10^ffcb4a ÑÐµÐº. ^ffcb4a10 ÑƒÑ€.: ÑÑ„Ñ„ÐµÐºÑ‚ Ð´Ð»Ð¸Ñ‚ÑÑ ^96f5ff12^ffcb4a ÑÐµÐº.@1@2^ffcb4aÐ­Ñ„Ñ„ÐµÐºÑ‚ Ð´Ð»Ð¸Ñ‚ÑÑ ^96f5ff%d^ffcb4a ÑÐµÐº.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL4425 
#define __CPPGEN_GNET_SKILL4425 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill4425:public Skill 
    { 
    public: 
        enum { SKILL_ID = 4425 }; 
        Skill4425 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill4425Stub:public SkillStub 
    { 
    public: 
#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; 

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
                skill->GetPlayer ()->SetDecmp (200);
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
        class State2:public SkillStub::State
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
    Skill4425Stub ():SkillStub (4425) 
    { 
        cls                 = 8; 
#ifdef _SKILL_CLIENT 
        name                = L"Éñ¡¤¹éÈÐ¾÷"; 
        nativename          = "Éñ¡¤¹éÈÐ¾÷"; 
        icon                = "Éñ¹éÈÐ¾÷»Æ.dds"; 
#endif 
        max_level           = 1; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 0; 
        rank                = 40; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1133; 
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
#ifdef _SKILL_CLIENT 
        effect              = "½£Áé_¹éÈÐ¾÷.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = "Ö±½ÓÉËº¦Ôö¼Ó1.gfx"; 
        gfxhangpoint        = "HH_bind"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        restrict_weapons.push_back (1); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 180000,180000,180000,180000,180000,180000,180000,180000,180000,180000 }; 
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
        static int aarray[10] = { 11208,11208,11208,11208,11208,11208,11208,11208,11208,11208 }; 
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
            return (float) (0);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 200,200,200,200,200,200,200,200,200,200 }; 
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
			/**
			Ïîâûøàåò øàíñ íàíåñåíèÿ êðèòè÷åñêîãî óäàðà äî ^96f5ff100%%^ffffff íà âðåìÿ, çàâèñÿùåå îò óð

			^ffcb4a1-4 óð.: ýôôåêò äëèòñÿ ^96f5ff6^ffcb4a ñåê.
			^ffcb4a5-7 óð.: ýôôåêò äëèòñÿ ^96f5ff8^ffcb4a ñåê.
			^ffcb4a8-9 óð.: ýôôåêò äëèòñÿ ^96f5ff10^ffcb4a ñåê.
			^ffcb4a10 óð.: ýôôåêò äëèòñÿ ^96f5ff12^ffcb4a ñåê.
			*/
            skill->GetVictim ()->SetProbability (1.0 * 100);
			static const int LEVEL_1_4 = 6000;
			static const int LEVEL_5_7 = 8000;
			static const int LEVEL_8_9 = 10000;
			static const int LEVEL_10_10 = 12000;
			static int aarray[10] = { LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_1_4, LEVEL_5_7, LEVEL_5_7, LEVEL_5_7, LEVEL_8_9, LEVEL_8_9, LEVEL_10_10 };				
            skill->GetVictim ()->SetTime ( aarray[skill->GetLevel () - 1] );
            skill->GetVictim ()->SetValue (99);
            skill->GetVictim ()->SetIncsmite (1);	
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
            return (float) (0);
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
