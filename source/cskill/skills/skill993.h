//Skill Parser (c)Deadraky 2023 

/* SKILL DESCRIPTION BEGIN */ 
/* 
39930  "Великая мощь яростного медведя"39931  "^ff5c00Великая мощь яростного медведя^ffcb4aДальность: ^96f5ffближний бой^ffcb4aМаг. энергия: ^96f5ff115^ffffff^ffcb4aПодготовка: ^ffffff0,3 ^ffcb4aсек.^ffcb4aПрименение: ^ffffff0,7 ^ffcb4aсек.^ffcb4aПерезарядка: ^ffffff6,0 ^ffcb4aсек.^ffcb4aПолучение ци: ^ffffff0,1^ffcb4aОграничение по оружию: ^ffffffмеч^ffcb4aХарактеристика: ^ff5c00Мудрость^ffcb4aСтатус: ^ffffffАсураС силой разгневанного зверя страж атакует окружающих врагов.Всем противникам в радиусе ^96f5ff12^ffffff м наносится ^96f5ff110%%^ffffff базового физ. урона, ^96f5ff100%%^ffffff урона оружия и ^96f5ff2700^ffffff ед. физ. урона.С вероятностью ^96f5ff50%%^ffffff прерывает подготовку заклинаний.При активации Великого Ока черного воина может нанести противнику дополнительный урон,обездвижить и снизить его показатель защиты.^ffcb4aЭффект золотой руны:@1^ffcb4a1-4 ур.: добавляется ^96f5ff40%%^ffcb4a урона оружия^ffcb4a5-7 ур.: добавляется ^96f5ff60%%^ffcb4a урона оружия^ffcb4a8-9 ур.: добавляется ^96f5ff80%%^ffcb4a урона оружия^ffcb4a 10 ур.: добавляется ^96f5ff100%%^ffcb4a урона оружия@1@2^ffcb4aДобавляется ^96f5ff%d%%^ffcb4a урона оружия.@2"*/ 
/* SKILL DESCRIPTION END */ 

#ifndef __CPPGEN_GNET_SKILL993 
#define __CPPGEN_GNET_SKILL993 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill993:public Skill 
    { 
    public: 
        enum { SKILL_ID = 993 }; 
        Skill993 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill993Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecelfmp (35 + (skill->GetLevel () - 1) * 3);
                skill->GetPlayer ()->SetDecelfap (53 + 40 * (skill->GetLevel () - 1));
                skill->SetFiredamage ((7 + (skill->GetLevel () - 1) * 14 + skill->GetT1 ()) * 6.7);
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
    Skill993Stub ():SkillStub (993) 
    { 
        cls                 = 258; 
#ifdef _SKILL_CLIENT 
        name                = L"��ĸ�׻���"; 
        nativename          = "��ĸ�׻���"; 
        icon                = "��ĸ�׻���.dds"; 
#endif 
        max_level           = 10; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 5; 
        rank                = 0; 
        eventflag           = 0; 
        is_senior           = 0; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 0; 
        allow_forms         = 1; 
        apcost              = 53040; 
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
        effect              = "��ĸ������.sgc"; 
        aerial_effect       = ""; 
#endif 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 0; 
#ifdef _SKILL_CLIENT 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
#endif 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(0, 0)); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
#endif 
    } 
        int GetExecutetime (Skill * skill) const
        {
            return 0;
        }
    int GetCoolingtime (Skill * skill) const 
    { 
        static int aarray[10] = { 40000,40000,40000,40000,40000,40000,40000,40000,40000,40000 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredSp (Skill * skill) const 
    { 
        static int aarray[10] = { 160,420,820,1400,2180,3220,4600,6400,8820,12040 }; 
        return aarray[skill->GetLevel () - 1]; 
    } 
    int GetRequiredLevel (Skill * skill) const 
    { 
        static int aarray[10] = { 2008,2013,2018,2023,2028,2033,2038,2043,2048,2053 }; 
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
            return (float) (20);
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 35,38,41,44,47,50,53,56,59,62 }; 
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
            return _snwprintf (buffer, length, format,
                               skill->GetLevel (),
                               35 + (skill->GetLevel () - 1) * 3,
                               53 + 40 * (skill->GetLevel () - 1), (7 + 14 * (skill->GetLevel () - 1)) * 6.7, skill->GetLevel () * 3);

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
            float percent = 0.03f;
			if(skill->GetPlayer ()->GetCls () == 0) percent = 0.03f; // ����
			if(skill->GetPlayer ()->GetCls () == 1) percent = 0.03f; // ���
			if(skill->GetPlayer ()->GetCls () == 2) percent = 0.02f; // �����
			if(skill->GetPlayer ()->GetCls () == 3) percent = 0.03f; // �����	
			if(skill->GetPlayer ()->GetCls () == 4) percent = 0.02f; // ����	
			if(skill->GetPlayer ()->GetCls () == 5) percent = 0.01f; // ���			
			if(skill->GetPlayer ()->GetCls () == 6) percent = 0.01f; // ���			
			if(skill->GetPlayer ()->GetCls () == 7) percent = 0.03f; // ����			
			if(skill->GetPlayer ()->GetCls () == 8) percent = 0.03f; // �����				
			if(skill->GetPlayer ()->GetCls () == 9) percent = 0.03f; // ������		
			if(skill->GetPlayer ()->GetCls () == 10) percent = 0.03f; // �������
			if(skill->GetPlayer ()->GetCls () == 11) percent = 0.01f; // ����				  
			
            skill->GetVictim ()->SetProbability (1.0 * 100);
            skill->GetVictim ()->SetTime (6000);
            skill->GetVictim ()->SetRatio (skill->GetLevel () * percent + skill->GetT1 () * 0.006);
            skill->GetVictim ()->SetReducefire2 (1);
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
            return (float) (20);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (player->GetElfstr ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent1 (PlayerWrapper * player) const
        {
            return (float) (player->GetElfagi ());
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent2 (PlayerWrapper * player) const
        {
            return (float) (player->GetLevel ());
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
            return 20;
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
