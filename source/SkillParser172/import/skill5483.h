/*Skill Parser (c)Deadraky 2022 
54830  "���֧ݧڧܧڧ� �ܧ�ԧ�� �ߧ֧ҧ֧�"
54831  "^ff5c00���֧ݧڧܧڧ� �ܧ�ԧ�� �ߧ֧ҧ֧�

^ffcb4a���ѧݧ�ߧ����: ^ffffff�էѧݧ�ߧ�� �ѧ�ѧܧ�
^ffcb4a���ѧ�. ��ߧ֧�ԧڧ�: ^96f5ff%d^ffffff
^ffcb4a����էԧ���ӧܧ�: ^ffffff1,0 ^ffcb4a��֧�.
^ffcb4a����ڧާ֧ߧ֧ߧڧ�: ^ffffff0,8 ^ffcb4a��֧�.
^ffcb4a���֧�֧٧ѧ��էܧ�: ^ffffff30 ^ffcb4a��֧�.
^ffcb4a���ԧ�ѧߧڧ�֧ߧڧ� ��� ����اڧ�: ^ffffff����اڧ� �էѧݧ�ߧ֧ԧ� �ҧ��
^ffcb4a���ѧ�ѧܧ�֧�ڧ��ڧܧ�: ^ff5c00������

^ffcb4a����ѧ���: ^ffffff����է�֧�
�����ߧڧ� ���ڧ٧��ӧѧ֧� �ӧ�ݧ�֧ҧߧ�� ���ڧ��, �ܧ����ѧ� �ҧ���ѧ֧��� �ߧ� �����ڧӧߧڧܧ� �� �ߧѧߧ��ڧ� �֧ާ�
�ҧѧ٧�ӧ��� ��ڧ٧ڧ�֧�ܧڧ� �����, ��ݧ�� ^96f5ff100%%^ffffff ����ߧ� ����اڧ�, ��ݧ�� ^96f5ff8343^ffffff �֧�. ����ߧ� ���ڧ�ڧ֧� �ާ֧�ѧݧݧ�.
�� ��֧�֧ߧڧ� ^96f5ff15^ffffff ��֧�. ��ڧ٧ڧ�֧�ܧѧ� �� �ާѧԧڧ�֧�ܧѧ� �٧ѧ�ڧ�� �����ڧӧߧڧܧ� ��ߧڧاѧ���� �ߧ� ^96f5ff50%%^ffffff,
�� ��ܧ������ �֧ԧ� ��֧�֧էӧڧا֧ߧڧ� - �ߧ� ^96f5ff80%%^ffffff.

^a6caf0����֧ҧ�֧���: ^ffffff1^a6caf0 ����֧ݧ� �ڧݧ� ��ߧѧ���.
^a6caf0������ݧߧڧ�֧ݧ�ߧѧ� ����ڧާ����: ^ffffff2^a6caf0 ���."
*/
#ifndef __CPPGEN_GNET_SKILL5483 
#define __CPPGEN_GNET_SKILL5483 
namespace GNET 
{ 
#ifdef _SKILL_SERVER 
    class Skill5483:public Skill 
    { 
    public: 
        enum { SKILL_ID = 5483 }; 
        Skill5483 ():Skill (SKILL_ID){ } 
    }; 
#endif 
    class Skill5483Stub:public SkillStub 
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
                skill->GetPlayer ()->SetDecmp (110);
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
                return 800;
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
                skill->GetPlayer ()->SetDecmp (440);
                skill->SetPlus (8343);
                skill->SetRatio (1.0);
                skill->SetGolddamage (skill->GetAttack ());
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
    Skill5483Stub ():SkillStub (5483) 
    { 
        cls                 = 6; 
        name                = L"�񡤿�����ӥ"; 
        nativename          = "�񡤿�����ӥ"; 
        icon                = "�������ӥ.dds"; 
        max_level           = 1; 
        type                = 1; 
        allow_ride          = 0; 
        attr                = 2; 
        rank                = 41; 
        eventflag           = 0; 
        is_senior           = 1; 
        is_inherent         = 0; 
        is_movingcast       = 0; 
        npcdelay            = 0; 
        showorder           = 1311; 
        allow_forms         = 1; 
        apcost              = 200; 
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
        effect              = "1������ӥ.sgc"; 
        aerial_effect       = ""; 
        range.type          = 0; 
        has_stateattack     = 0; 
        runes_attr          = 1; 
        gfxfilename         = ""; 
        gfxhangpoint        = "0"; 
        gfxtarget           = 0; 
        feature             = 0; 
        extra_effect        = 0; 
        immune_casting      = 0; 
        pre_skills.push_back (std::pair < ID, int >(610, 1)); 
        pre_skills.push_back (std::pair < ID, int >(611, 1)); 
        restrict_weapons.push_back (13); 
#ifdef _SKILL_SERVER 
        statestub.push_back (new State1 ()); 
        statestub.push_back (new State2 ()); 
        statestub.push_back (new State3 ()); 
#endif 
    } 
    int GetExecutetime (Skill * skill) const 
    { 
        static int aarray[10] = { 800,800,800,800,800,800,800,800,800,800 }; 
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
        static int aarray[10] = { 61679,61679,61679,61679,61679,61679,61679,61679,61679,61679 }; 
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
            return (float) (skill->GetPlayer ()->GetRange ());
        }
    float GetMpcost (Skill * skill) const 
    { 
        static float aarray[10] = { 550,550,550,550,550,550,550,550,550,550 }; 
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
            return _snwprintf (buffer, length, format, 550);

        }
#endif 
#ifdef _SKILL_SERVER 
        int GetEnmity (Skill * skill) const
        {
            return 8000;
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
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio (0.3);
				skill->GetVictim ()->SetAmount (skill->GetT0 () *
												(1 +
												 0.01 * (skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () >
														 0 ? skill->GetT1 () - skill->GetPlayer ()->GetDefenddegree () : 0)));
				skill->GetVictim ()->SetEaglecurse (1);
				skill->GetVictim ()->SetProbability (1.0 * 100);
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio (0.5);
				skill->GetVictim ()->SetDecdefence (1);
				skill->GetVictim ()->SetProbability (1.0 * 100);
				skill->GetVictim ()->SetTime (15000);
				skill->GetVictim ()->SetRatio (0.5);
				skill->GetVictim ()->SetDecresist (1);

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
            return (float) (skill->GetPlayer ()->GetRange () + 5);
        }
#endif 
#ifdef _SKILL_SERVER 
        float GetTalent0 (PlayerWrapper * player) const
        {
            return (float) (6 * player->GetWeapondamage () + 12000);
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
            return 21;
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
