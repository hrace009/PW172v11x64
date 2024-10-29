#ifndef __CPPGEN_GNET_SKILL6462
#define __CPPGEN_GNET_SKILL6462
namespace GNET
{
#ifdef _SKILL_SERVER
    class Skill6462 : public Skill
    {
    public:
        enum
        {
            SKILL_ID = 6462
        };
        Skill6462() : Skill(SKILL_ID)
        {
        }
    };
#endif
    class Skill6462Stub : public SkillStub
    {
    public:
#ifdef _SKILL_SERVER
        class State1 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 100;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.2 * ((9 * skill->GetLevel()) - 5.4));
                skill->GetPlayer()->SetPray(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 1;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State2 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 900;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
                skill->GetPlayer()->SetDecmp(0.8 * ((9 * skill->GetLevel()) - 5.4));
                skill->SetPlus(skill->GetLevel() == 1 ? 163.5 : skill->GetLevel() == 2 ? 337.6
                                                            : skill->GetLevel() == 3   ? 532.9
                                                            : skill->GetLevel() == 4   ? 749.4
                                                            : skill->GetLevel() == 5   ? 987.1
                                                            : skill->GetLevel() == 6   ? 1246.0
                                                            : skill->GetLevel() == 7   ? 1426.1
                                                            : skill->GetLevel() == 8   ? 1827.4
                                                            : skill->GetLevel() == 9   ? 2149.9
                                                            : skill->GetLevel() == 10  ? 2493.6
                                                                                       : 0);
                skill->SetRatio(0);
                skill->SetDamage(skill->GetAttack());
                skill->GetPlayer()->SetPerform(1);
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
#ifdef _SKILL_SERVER
        class State3 : public SkillStub::State
        {
        public:
            int GetTime(Skill *skill) const
            {
                return 0;
            }
            bool Quit(Skill *skill) const
            {
                return false;
            }
            bool Loop(Skill *skill) const
            {
                return false;
            }
            bool Bypass(Skill *skill) const
            {
                return false;
            }
            void Calculate(Skill *skill) const
            {
            }
            bool Interrupt(Skill *skill) const
            {
                return false;
            }
            bool Cancel(Skill *skill) const
            {
                return 0;
            }
            bool Skip(Skill *skill) const
            {
                return 0;
            }
        };
#endif
        Skill6462Stub() : SkillStub(6462)
        {
            cls = 14;
            name = L"ðl—e";
            nativename = "Ì©¶·";
            icon = "Ì©¶·.dds";
            max_level = 10;
            type = 1;
            apcost = 0;
            arrowcost = 0;
            apgain = 5;
            attr = 1;
            rank = 0;
            eventflag = 0;
            is_senior = 0;
            clslimit = 0;
            time_type = 0;
            showorder = 1501;
            allow_land = 1;
            allow_air = 1;
            allow_water = 1;
            allow_ride = 0;
            auto_attack = 0;
            long_range = 0;
            restrict_corpse = 0;
            allow_forms = 17;
            {
                restrict_weapons.push_back(69843);
            }
            effect = "ÑýºïÄÐ_»ù´¡¹÷·¨_»÷ÖÐ.att";
            range.type = 0;
            doenchant = false;
            dobless = false;
            commoncooldown = 0;
            commoncooldowntime = 0;
            pre_skills.push_back(std::pair<ID, int>(0, 1));
#ifdef _SKILL_SERVER
            statestub.push_back(new State1());
            statestub.push_back(new State2());
            statestub.push_back(new State3());
#endif
        }
        virtual ~Skill6462Stub()
        {
        }
        float GetMpcost(Skill *skill) const
        {
            static float array[10] = {3, 12, 21, 30, 39, 48, 57, 66, 75, 84};
            return array[skill->GetLevel() - 1];
        }
        int GetExecutetime(Skill *skill) const
        {
            static int array[10] = {900, 900, 900, 900, 900, 900, 900, 900, 900, 900};
            return array[skill->GetLevel() - 1];
        }
        int GetCoolingtime(Skill *skill) const
        {
            static int array[10] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
            return array[skill->GetLevel() - 1];
        }
        int GetRequiredLevel(Skill *skill) const
        {
            static int array[10] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45};
            return array[skill->GetLevel() - 1];
        }
        int GetRequiredSp(Skill *skill) const
        {
            static int array[10] = {0, 200, 700, 1600, 3000, 3800, 5900, 6500, 9200, 12900};
            return array[skill->GetLevel() - 1];
        }
        float GetRadius(Skill *skill) const
        {
            return (float)(0);
        }
        float GetAttackdistance(Skill *skill) const
        {
            return (float)(0);
        }
        float GetAngle(Skill *skill) const
        {
            return (float)(1 - 0.0111111 * (0));
        }
        float GetPraydistance(Skill *skill) const
        {
            return (float)(skill->GetPlayer()->GetRange());
        }
#ifdef _SKILL_CLIENT
        int GetIntroduction(Skill *skill, wchar_t *buffer, int length, wchar_t *format) const
        {
            return _snwprintf(buffer, length, format);
        }
#endif
#ifdef _SKILL_SERVER
        int GetEnmity(Skill *skill) const
        {
            return 0;
        }
        bool TakeEffect(Skill *skill) const
        {
            ;
            return true;
        }
        float GetEffectdistance(Skill *skill) const
        {
            return (float)(skill->GetPlayer()->GetRange() + 10);
        }
        int GetAttackspeed(Skill *skill) const
        {
            return 3;
        }
        float GetHitrate(Skill *skill) const
        {
            return (float)(1.2 + 0.05 * skill->GetLevel());
        }
#endif
    };
}
#endif
