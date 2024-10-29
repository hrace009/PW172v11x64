/*Skill Parser (c)Deadraky 2022 
rune effect by serega62rus
35210  "Великая кровавая стрела"
35211  "^ff5c00Великая кровавая стрела

^ffcb4aДальность: ^ffffffдальняя атака
^ffcb4aПодготовка: концентрация силы
^ffcb4aПрименение: ^ffffff0,6 ^ffcb4aсек.
^ffcb4aПерезарядка: ^ffffff2 ^ffcb4aмин.
^ffcb4aОграничение по оружию: ^ffffffоружие дальнего боя
^ffcb4aХарактеристика: ^ff5c00Храбрость

^ffcb4aСтатус: ^ffffffМудрец
Наносит противнику базовый физ. урон, плюс ^96f5ff150%%^ffffff урона оружия, плюс ^96f5ff4444^ffffff ед.
На ^96f5ff30^ffffff сек. снижает макс. запас здоровья противника на ^96f5ff18%%^ffffff и увеличивает получаемый им урон на ^96f5ff25%%^ffffff.
Кроме того, в течение ^96f5ff9^ffffff сек. наносит противнику урон стихией металла, равный ^96f5ff150%%^ffffff базового урона плюс ^96f5ff4444^ffffff ед.
Не промахивается.

^a6caf0^a6caf0Дополнительная стоимость: ^ffffff1^a6caf0 ци.

^ffeaabЭффект серебряной руны:@1
Концентрирует силу в течение ^96f5ff2,0^ffeaab сек.
^ffeaab1-4 ур.: макс. урон, наносимый цели, повышается на ^96f5ff20%%^ffeaab, 
на ^96f5ff20%%^ffeaab уменьшается максимум ЖС.
^ffeaab5-7 ур.: макс. урон, наносимый цели, повышается на ^96f5ff24%%^ffeaab, 
на ^96f5ff24%%^ffeaab уменьшается максимум ЖС.
^ffeaab8-9 ур.: макс. урон, наносимый цели, повышается на ^96f5ff28%%^ffeaab, 
на ^96f5ff28%%^ffeaab уменьшается максимум ЖС.
^ffeaab 10 ур.: макс. урон, наносимый цели, повышается на ^96f5ff32%%^ffeaab, 
на ^96f5ff32%%^ffeaab уменьшается максимум ЖС.@1@2
Концентрирует силу в течение ^96f5ff2,0^ffeaab сек., макс. урон, наносимый цели, повышается на ^96f5ff%d%%^ffeaab, 
на ^96f5ff%d%%^ffeaab уменьшается максимум ЖС.@2"
*/
#ifndef __CPPGEN_GNET_SKILL3521 
#define __CPPGEN_GNET_SKILL3521 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3521:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3521 }; 
        Skill3521 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3521Stub:public SkillStub 
    { 
    public: 
#ifdef _SKILL_SERVER 
        class State1:public SkillStub::State
        {
          public:
            int GetTime (Skill * skill) const
            {
                return 2000;
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
                skill->SetRatio (2.5 * skill->GetCharging () / 2000);
                skill->SetPlus (4444);
                skill->SetDamage (skill->GetAttack ());
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
    Skill3521Stub ():SkillStub (3521) 
    { 
        cls                 = 6; 
        name                = L"神·血矢"; 
        nativename          = "神·血矢"; 
        icon                = "神·血矢白.dds"; 
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
        showorder           = 2556; 
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
        effect              = "血咒.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 3; 
        gfxfilename         = "负面状态效果增强2.gfx"; 
        gfxhangpoint        = "HH_spine"; 
        gfxtarget           = 1; 
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
        static int aarray[10] = { 1000,1000,1000,1000,1000,1000,1000,1000,1000,1000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 120000,120000,120000,120000,120000,120000,120000,120000,120000,120000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000,4000000 }; 
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
        static int aarray[10] = { 3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000,3000000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    float GetRadius (Skill * skill) const
    {
            return (float) (8 + 0.4 * skill->GetLevel ());
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
        static float aarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
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
			Концентрирует силу в течение ^96f5ff2,0^ffeaab сек.
			^ffeaab1-4 ур.: макс. урон, наносимый цели, повышается на ^96f5ff20%%^ffeaab, 
			на ^96f5ff20%%^ffeaab уменьшается максимум ЖС.
			^ffeaab5-7 ур.: макс. урон, наносимый цели, повышается на ^96f5ff24%%^ffeaab, 
			на ^96f5ff24%%^ffeaab уменьшается максимум ЖС.
			^ffeaab8-9 ур.: макс. урон, наносимый цели, повышается на ^96f5ff28%%^ffeaab, 
			на ^96f5ff28%%^ffeaab уменьшается максимум ЖС.
			^ffeaab 10 ур.: макс. урон, наносимый цели, повышается на ^96f5ff32%%^ffeaab, 
			на ^96f5ff32%%^ffeaab уменьшается максимум ЖС.
			*/
			static float aarrayDecHp[10] = { 0.02, 0.02, 0.02, 0.02, 0.06, 0.06, 0.06, 0.1, 0.1, 0.12 };
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetRatio (0.18 +  ( aarrayDecHp[skill->GetLevel () - 1] ) * skill->GetT0 () / 2000); 
            skill->GetVictim ()->SetDechp (1);
			
			
			static float aarrayInchurt[10] = { 0.02, 0.02, 0.02, 0.02, 0.06, 0.06, 0.06, 0.1, 0.1, 0.12 };			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (30000);
            skill->GetVictim ()->SetRatio (0.18 + ( aarrayInchurt[skill->GetLevel () - 1] ) * skill->GetT0 () / 2000);
            skill->GetVictim ()->SetInchurt (1);
			
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (9000);
            skill->GetVictim ()->SetAmount (skill->GetT0 () *
                                            (1 +
                                             0.01 * (skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () >
                                                     0 ? skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () : 0)));
            skill->GetVictim ()->SetThunder (1);
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
            return (float) (skill->GetPlayer ()->GetRange () + 10);
        }		
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (1.5 * player->GetAttack () + 4444);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetAttackdegree ());
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
            return (float) (3);
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
