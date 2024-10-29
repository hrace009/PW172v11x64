/*Skill Parser (c)Deadraky 2022 
39490  "ß£ß÷ß›ß⁄ß‹ß⁄ß€ ßÂß’ß—ß‚ ß’ß‚ß—ß‹ß‡ßﬂß—"
39491  "^ff5c00ß£ß÷ß›ß⁄ß‹ß⁄ß€ ßÂß’ß—ß‚ ß’ß‚ß—ß‹ß‡ßﬂß—

^ffcb4aß•ß—ß›ßÓßﬂß‡ß„ß‰ßÓ: ^ffffffß“ß›ß⁄ßÿßﬂß⁄ß€ ß“ß‡ß€
^ffcb4aßÆß—ß‘. ßÔßﬂß÷ß‚ß‘ß⁄ßÒ: ^96f5ff%d^ffffff
^ffcb4aß±ß‡ß’ß‘ß‡ß‰ß‡ß”ß‹ß—: ^ffffff0,6 ^ffcb4aß„ß÷ß‹.
^ffcb4aß±ß‚ß⁄ßﬁß÷ßﬂß÷ßﬂß⁄ß÷: ^ffffff1,0 ^ffcb4aß„ß÷ß‹.
^ffcb4aß±ß÷ß‚ß÷ßŸß—ß‚ßÒß’ß‹ß—: ^ffffff30 ^ffcb4aß„ß÷ß‹.
^ffcb4aß∞ß‘ß‚ß—ßﬂß⁄ßÈß÷ßﬂß⁄ß÷ ß·ß‡ ß‡ß‚ßÂßÿß⁄ß: ^ffffffß“ß÷ßŸ ß‡ß‚ßÂßÿß⁄ßÒ, ß‹ß—ß„ß‰ß÷ß‰ßÌ
^ffcb4aß∑ß—ß‚ß—ß‹ß‰ß÷ß‚ß⁄ß„ß‰ß⁄ß‹ß—: ^ff5c00ß∑ß‚ß—ß“ß‚ß‡ß„ß‰ßÓ

^ffcb4aß≥ß‰ß—ß‰ßÂß„: ^ffffffßÆßÂß’ß‚ß÷ßË
ß≥ß‡ß“ß‚ß—ß” ßÔßﬂß÷ß‚ß‘ß⁄ß ß” ß›ß—ß’ß‡ßﬂßÒßÁ, ß·ß÷ß‚ß„ß‡ßﬂß—ßÿ ßﬂß—ßﬂß‡ß„ß⁄ß‰ ß·ß‚ßÒßﬁß‡ß€ ßÂß’ß—ß‚ ß·ß‡ ß·ß‚ß‡ß‰ß⁄ß”ßﬂß⁄ß‹ß—ßﬁ, ß„ß‰ß‡ßÒßÎß⁄ßﬁ ßﬂß— ß‚ß—ß„ß„ß‰ß‡ßÒßﬂß⁄ß⁄
ß’ß‡ ^96f5ff15^ffffff ßﬁ., ß·ß‚ß⁄ßÈß⁄ßﬂßÒßÒ ß⁄ßﬁ ß“ß—ßŸß‡ß”ßÌß€ ßÊß⁄ßŸß⁄ßÈß÷ß„ß‹ß⁄ß€ ßÂß‚ß‡ßﬂ, ß·ß›ßß„ ^96f5ff100%%^ffffff ßÂß‚ß‡ßﬂß— ß‡ß‚ßÂßÿß⁄ßÒ, ß·ß›ßß„ ^96f5ff11504^ffffff ß÷ß’. ßÊß⁄ßŸ. ßÂß‚ß‡ßﬂß—.
ßØß— ß“ß›ß⁄ßÿß—ß€ßÍß⁄ß÷ ^96f5ff15^ffffff ß„ß÷ß‹. ß’ß‡ß“ß—ß”ß›ßÒß÷ß‰ ß‹ ßÊß⁄ßŸß⁄ßÈß÷ß„ß‹ß‡ß€ ß—ß‰ß—ß‹ß÷ ^96f5ff120%%^ffffff ßÂß‚ß‡ßﬂß— ß„ß‰ß⁄ßÁß⁄ß÷ß€ ß‡ß‘ßﬂßÒ. 

^a6caf0ß•ß‡ß·ß‡ß›ßﬂß⁄ß‰ß÷ß›ßÓßﬂß—ßÒ ß„ß‰ß‡ß⁄ßﬁß‡ß„ß‰ßÓ: ^ffffff2^a6caf0 ßËß⁄."
*/
#ifndef __CPPGEN_GNET_SKILL3949 
#define __CPPGEN_GNET_SKILL3949 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3949:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3949 }; 
        Skill3949 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3949Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
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
                skill->GetPlayer ()->SetDecmp (244);
                skill->SetPlus (11504);
                skill->SetRatio (1);
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
    Skill3949Stub ():SkillStub (3949) 
    { 
        cls                 = 0; 
        name                = L"…Ò°§‘∆¡˙æ≈œ÷"; 
        nativename          = "…Ò°§‘∆¡˙æ≈œ÷"; 
        icon                = "…Ò°§‘∆¡˙æ≈œ÷.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1112; 
        allow_forms         = 1; 
        apcost              = 200; 
        apgain              = 0; 
        doenchant           = 0; 
        dobless             = 1; 
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
        effect              = "1‘∆¡˙æ≈œ÷.sgc"; 
        aerial_effect       = ""; 
        range.type          = 1; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 5; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(396, 1)); 
        pre_skills.push_back (std::pair < ID, int >(397, 1)); 
        restrict_weapons.push_back (182); 
        restrict_weapons.push_back (0); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 30000,30000,30000,30000,30000,30000,30000,30000,30000,30000 }; 
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
        static int aarray[10] = { 53892,53892,53892,53892,53892,53892,53892,53892,53892,53892 }; 
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
            return (float) (4);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (12);
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
        static float aarray[10] = { 305,305,305,305,305,305,305,305,305,305 }; 
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
            return 10000;
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
        return 1; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        bool BlessMe (Skill * skill) const
        {
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (15000);
            skill->GetVictim ()->SetRatio (1.2);
            skill->GetVictim ()->SetFireblade (1);
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (20);
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
            return 11;
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
            return (float) (5);
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
