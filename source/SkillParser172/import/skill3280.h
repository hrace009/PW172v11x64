#ifndef __CPPGEN_GNET_SKILL3280 
#define __CPPGEN_GNET_SKILL3280 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill3280:public Skill 
    { 
    public: 
        enum { SKILL_ID = 3280 }; 
        Skill3280 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill3280Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp(225);
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
        class State2:public SkillStub::State
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
    Skill3280Stub ():SkillStub (3280) 
    { 
        cls                 = 10; 
        name                = L"创世·暗夜之王"; 
        nativename          = "创世·暗夜之王"; 
        icon                = "创世暗夜之王.dds"; 
        max_level           = 2; 
        type                = 2; 
        allow_ride          = 0; 
        attr                = 1; 
        rank                = 8; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1125; 
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
        itemcost            = 49982; 
        itemcostcount       = 1; 
        combosk_preskill    = 0; 
        combosk_interval    = 0; 
        combosk_nobreak     = 0; 
        effect              = "夜影_暗黑之王_击中.sgc"; 
        aerial_effect       = ""; 
        range.type          = 5; 
        has_stateattack     = 0; 
        runes_attr          = 0; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        stubs_num           = 1; 
        reserve1            = 0; 
        pre_skills.push_back (std::pair < ID, int >(0, 1)); 
        restrict_weapons.push_back (44878); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
#endif 
    } 
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
        int GetCoolingtime (Skill * skill) const
        {
            return 300000;
        }
    int GetRequiredSp (Skill * skill) const 
    { 
        static int array[10] = { 1000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int array[10] = { 100,100,100,100,100,100,100,100,100,100 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredItem (Skill * skill) const 
    { 
        static int array[10] = { 49972,49973,49973,49973,49973,49973,49973,49973,49973,49973 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredMoney (Skill * skill) const 
    { 
        static int array[10] = { 1000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000,2000000 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    int GetRequiredRealmLevel (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
    } 
        float GetRadius (Skill * skill) const
        {
            return (float) (16);
        }
        float GetAttackdistance (Skill * skill) const
        {
            return (float) (0);
        }
        float GetAngle (Skill * skill) const
        {
            return (float) (1.0);
        }
        float GetPraydistance (Skill * skill) const
        {
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float array[10] = { 225,225,225,225,225,225,225,225,225,225 }; 
        return array[skill->GetLevel () - 1]; 
    } 
    bool CheckComboSkExtraCondition (Skill * skill) const 
    { 
        return 1; 
    } 
    int GetCostShieldEnergy (Skill * skill) const 
    { 
        static int array[10] = { 0,0,0,0,0,0,0,0,0,0 }; 
        return array[skill->GetLevel () - 1]; 
    } 
#ifdef _SKILL_CLIENT 
    int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const 
    { 
        return 0; 
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
            skill->GetVictim ()->SetProbability(100);
            skill->GetVictim ()->SetTime(15000 * skill->GetLevel());
            skill->GetVictim ()->SetRatio(0.99000001);
            skill->GetVictim ()->SetAmount(2.0);
            skill->GetVictim ()->SetValue(0.99000001);
            skill->GetVictim ()->SetDecfardmg(1);
            skill->GetVictim ()->SetProbability(skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetTime(100);
            skill->GetVictim ()->SetSkillcooldown2(1);
			
// перезарядка рунных

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4094);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4095);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4096);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4097);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4098);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4099);
            skill->GetVictim ()->SetSkillcooldown (1);		

//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4100);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4101);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4102);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4103);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4104);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4105);
            skill->GetVictim ()->SetSkillcooldown (1);		
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4106);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4107);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4108);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4109);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4110);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4111);
            skill->GetVictim ()->SetSkillcooldown (1);		
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4112);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4113);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4114);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4115);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4116);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4117);
            skill->GetVictim ()->SetSkillcooldown (1);			

//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4118);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4119);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4120);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4121);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4122);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4123);
            skill->GetVictim ()->SetSkillcooldown (1);		

//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4124);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4125);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4126);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4127);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4128);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4129);
            skill->GetVictim ()->SetSkillcooldown (1);		

//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4130);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4131);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4132);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4133);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4134);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4135);
            skill->GetVictim ()->SetSkillcooldown (1);			
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4136);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4137);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4138);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4139);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4140);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4141);
            skill->GetVictim ()->SetSkillcooldown (1);	
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4142);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4143);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4144);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4145);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4146);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4147);
            skill->GetVictim ()->SetSkillcooldown (1);			
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4148);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4149);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4150);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4151);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4152);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4153);
            skill->GetVictim ()->SetSkillcooldown (1);		
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4464);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4465);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4466);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4467);
            skill->GetVictim ()->SetSkillcooldown (1);	
	
//----------------------------------------------------------------------

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4469);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4470);
            skill->GetVictim ()->SetSkillcooldown (1);		

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4471);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4472);
            skill->GetVictim ()->SetSkillcooldown (1);	

            skill->GetVictim ()->SetProbability (skill->GetLevel() == 2.0 ? 100 : 0);
            skill->GetVictim ()->SetRatio (4473);
            skill->GetVictim ()->SetAmount (500);
            skill->GetVictim ()->SetValue (4474);
            skill->GetVictim ()->SetSkillcooldown (1);				
            return true;
        }
#endif 
#ifdef _SKILL_SERVER 
    bool BlessMe (Skill * skill) const 
    { 
        return 1; 
    } 
#endif 
#ifdef _SKILL_SERVER 
        float GetEffectdistance (Skill * skill) const
        {
            return (float) (35);
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
            return 9;
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
