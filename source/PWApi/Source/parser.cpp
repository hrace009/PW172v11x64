
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <tchar.h>

#include "../Header/utf.h"
#include "../Header/asm.h"
#include "../Header/config.h"
#include "../Header/parser.h"

namespace GPARSER
{

#ifdef _WIN64

#else //WIN32

    __declspec(naked) CSKILL* __cdecl
        ElementSkill__Create(unsigned int, int)
    {
        _asm
        {
            mov     eax, 0x0111D084
            mov     eax, [eax]
            jmp     eax
        }
    }
    //---------------------------------------------------------------------------
    __declspec(naked) void __stdcall
        ElementSkill__Destroy(void*)
    {
        _asm
        {
            push    ebp
            mov     ebp, esp
            push    ecx
            mov     ecx, [ebp + 8]
            test    ecx, ecx
            jz      locret_101A471E
            mov     eax, [ecx]
            push    1
            call    dword ptr[eax + 100h]
            locret_101A471E:
            pop     ecx
                pop     ebp
                ret     4
        }
    }
    //---------------------------------------------------------------------------
    __declspec(naked) int __stdcall
        ElementSkill__GetInt(void*, int)
    {
        _asm
        {
            push    ebp
            mov     ebp, esp
            push    ecx
            mov     ecx, [ebp + 8]
            mov     eax, [ecx]
            add     eax, [ebp + 12]
            call    dword ptr[eax]
            pop     ecx
            pop     ebp
            ret     8
        }
    }
    //---------------------------------------------------------------------------
    __declspec(naked) float __stdcall
        ElementSkill__GetFloat(void*, int)
    {
        _asm
        {
            push    ebp
            mov     ebp, esp
            push    ecx
            mov     ecx, [ebp + 8]
            mov     eax, [ecx]
            add     eax, [ebp + 12]
            call    dword ptr[eax]
            pop     ecx
            pop     ebp
            ret     8
        }
    }

    int CSKILL::GetMpCost()
    {
        return ElementSkill__GetInt(this, 0x80);
    }

    int CSKILL::GetRequiredBook()
    {
        return ElementSkill__GetInt(this, 0x34);
    }

    int CSKILL::GetRequiredLevel()
    {
        return ElementSkill__GetInt(this, 0x2C);
    }

    int CSKILL::GetRequiredMoney()
    {
        return ElementSkill__GetInt(this, 0x38);
    }

    int CSKILL::GetRequiredSp()
    {
        return ElementSkill__GetInt(this, 0x30);
    }

    int CSKILL::GetRequiredRealmLevel()
    {
        return ElementSkill__GetInt(this, 0x3C);
    }

    int CSKILL::GetExecuteTime()
    {
        return ElementSkill__GetInt(this, 0x1C);
    }

    int CSKILL::GetCoolingtime()
    {
        return ElementSkill__GetInt(this, 0x18);
    }

    void CSKILL::Destroy()
    {
        ElementSkill__Destroy(this);
    }


    CSKILL* __cdecl lib_ElementSkill__Create(unsigned int skillID, int skillLevel)
    {
        return ElementSkill__Create(skillID, skillLevel);
    }
    //---------------------------------------------------------------------------
    void SET_SKILL_INFO(FILE* fp, const char* Src, const char* name)
    {
        static char RES[2048];
        sprintf_s(RES, "%s\n", Src);
        size_t iSize = strlen(RES);
        fwrite(RES, 1, iSize, fp);
    }
    //---------------------------------------------------------------------------
    void SET_SKILL_WINFO(FILE* fp, const char16_t* Src, const char* name)
    {
        static wchar_t RES[256];
        swprintf_s(RES, L"%s", Src);
        size_t iSize = lstrlenW(RES);
        fwrite(RES, 1, iSize, fp);
    }

    //---------------------------------------------------------------------------
    int GetMpCost(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetMpCost();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetRequiredBook(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetRequiredBook();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetRequiredLevel(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetRequiredLevel();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetRequiredMoney(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetRequiredMoney();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetRequiredSp(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetRequiredSp();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetRequiredRealmLevel(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetRequiredRealmLevel();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetExecuteTime(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetExecuteTime();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------
    int GetCoolingtime(CSKILL::ID id, int level)
    {
        int res = 0;
        CSKILL* s = lib_ElementSkill__Create(id, level);
        if (s)
        {
            res = s->GetCoolingtime();
            s->Destroy();
        }
        return res;
    }
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    void CSKILL_PARSER(int skill)
    {
        CSKILL* s = lib_ElementSkill__Create(skill, 1); if (!s) return;
        size_t i = 0;
        static FILE* fp;
        static char name[32];
        //static char skill_name[20];
        //sprintf_s(skill_name, "SKILL%d", skill);
        sprintf_s(name, "./cskill/skill%d.h", skill);
        fopen_s(&fp, (const char*)name, "a+");

        static char Src[1024];
        sprintf_s(Src, "#ifndef __CPPGEN_GNET_SKILL%d", skill); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "#define __CPPGEN_GNET_SKILL%d", skill); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "namespace GNET", name);
        SET_SKILL_INFO(fp, "{", name);
        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);
        sprintf_s(Src, "    class Skill%d:public Skill", skill); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "    {", name);
        SET_SKILL_INFO(fp, "    public:", name);
        sprintf_s(Src, "        enum { SKILL_ID = %d };", skill); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        Skill%d ():Skill (SKILL_ID){ }", skill); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "    };", name);
        SET_SKILL_INFO(fp, "#endif", name);

        sprintf_s(Src, "    class Skill%dStub:public SkillStub", skill); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "    {", name);
        SET_SKILL_INFO(fp, "    public:", name);
        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);

        SET_SKILL_INFO(fp, "    class State1:public SkillStub::State", name);
        SET_SKILL_INFO(fp, "    {", name);
        SET_SKILL_INFO(fp, "    public:", name);
        SET_SKILL_INFO(fp, "        int GetTime (Skill * skill) const { return 1000; }", name);
        SET_SKILL_INFO(fp, "        bool Quit (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Loop (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Bypass (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        void Calculate (Skill * skill) const { }", name);
        SET_SKILL_INFO(fp, "        bool Interrupt (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Cancel (Skill * skill) const { return 1; }", name);
        SET_SKILL_INFO(fp, "        bool Skip (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "    };", name);
        SET_SKILL_INFO(fp, "#endif", name);

        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);
        SET_SKILL_INFO(fp, "    class State2:public SkillStub::State", name);
        SET_SKILL_INFO(fp, "    {", name);
        SET_SKILL_INFO(fp, "    public:", name);
        SET_SKILL_INFO(fp, "        int GetTime (Skill * skill) const { return 1000; }", name);
        SET_SKILL_INFO(fp, "        bool Quit (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Loop (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Bypass (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        void Calculate (Skill * skill) const { }", name);
        SET_SKILL_INFO(fp, "        bool Interrupt (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Cancel (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "        bool Skip (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "    };", name);
        SET_SKILL_INFO(fp, "#endif", name);

        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);
        SET_SKILL_INFO(fp, "    class State3:public SkillStub::State", name);
        SET_SKILL_INFO(fp, "    {", name);
        SET_SKILL_INFO(fp, "    public:", name);
        SET_SKILL_INFO(fp, "        int GetTime (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "        bool Quit (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Loop (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Bypass (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        void Calculate (Skill * skill) const { }", name);
        SET_SKILL_INFO(fp, "        bool Interrupt (Skill * skill) const { return false; }", name);
        SET_SKILL_INFO(fp, "        bool Cancel (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "        bool Skip (Skill * skill) const { return 0; }", name);
        SET_SKILL_INFO(fp, "    };", name);
        SET_SKILL_INFO(fp, "#endif", name);

        sprintf_s(Src, "    Skill%dStub ():SkillStub (%d)", skill, skill); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        cls = %d;", s->skill->cls); SET_SKILL_INFO(fp, Src, name);

        //name
        static char skill_name[256];
        memset(skill_name, 0x00, sizeof(skill_name));
        size_t name_len = lstrlenW(s->skill->name);
        if (name_len > 0 && name_len < sizeof(skill_name))
        {
            
            WideCharToMultiByte(936, 0, s->skill->name, -1, (char*)&skill_name, 256, NULL, NULL);
            //utf16_to_utf8(s->skill->name, skill_name, 256);
        }
        else
        {
            sprintf_s(skill_name, "SKILL%d", skill);
        }
        //--
        sprintf_s(Src, "        name = L\"%s\";", skill_name); SET_SKILL_INFO(fp, Src, name);

        //sprintf_s(Src, "        name = L\"%s\";", skill_name); SET_SKILL_INFO(fp, Src, name);


        sprintf_s(Src, "        nativename = \"%s\";", s->skill->nativename); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        icon = \"%s\";", s->skill->icon); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        max_level = %d;", s->skill->max_level); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        type = %d;", s->skill->type); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        apcost = %d;", s->skill->apcost); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        arrowcost = %d;", s->skill->arrowcost); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        apgain = %d;", s->skill->apgain); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        attr = %d;", s->skill->attr); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        rank = %d;", s->skill->rank); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        eventflag = %d;", s->skill->eventflag); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        is_senior = %d;", s->skill->is_senior); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        clslimit = %d;", s->skill->clslimit); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        time_type = %d;", s->skill->time_type); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        showorder = %d;", s->skill->showorder); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        allow_land = %d;", s->skill->allow_land); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        allow_air = %d;", s->skill->allow_air); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        allow_water = %d;", s->skill->allow_water); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        allow_ride = %d;", s->skill->allow_ride); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        auto_attack = %d;", s->skill->auto_attack); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        long_range = %d;", s->skill->long_range); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        restrict_corpse = %d;", s->skill->restrict_corpse); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        allow_forms = %d;", s->skill->allow_forms); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        {", name);
        for (i = 0; i < s->skill->restrict_weapons.size(); i++)
        {
            sprintf_s(Src, "            restrict_weapons.push_back (%d);", s->skill->restrict_weapons[i]); SET_SKILL_INFO(fp, Src, name);
        }
        SET_SKILL_INFO(fp, "        }", name);
        sprintf_s(Src, "        effect = \"%s\";", s->skill->effect); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        range.type = %d;", s->skill->range.type); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        doenchant = %d;", s->skill->doenchant); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        dobless = %d;", s->skill->dobless); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        commoncooldown = %d;", s->skill->commoncooldown); SET_SKILL_INFO(fp, Src, name);
        sprintf_s(Src, "        commoncooldowntime = %d;", s->skill->commoncooldowntime); SET_SKILL_INFO(fp, Src, name);

        for (i = 0; i < s->skill->pre_skills.size(); i++)
        {
            sprintf_s(Src, "        pre_skills.push_back (std::pair < ID, int >(%d, %d));",
                s->skill->pre_skills.at(i).first, s->skill->pre_skills.at(i).second); SET_SKILL_INFO(fp, Src, name);
        }

        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);
        SET_SKILL_INFO(fp, "        statestub.push_back (new State1 ());", name);
        SET_SKILL_INFO(fp, "        statestub.push_back (new State2 ());", name);
        SET_SKILL_INFO(fp, "        statestub.push_back (new State3 ());", name);
        SET_SKILL_INFO(fp, "#endif", name);
        SET_SKILL_INFO(fp, "    }", name);
        sprintf_s(Src, "    virtual ~ Skill%dStub () {}", skill); SET_SKILL_INFO(fp, Src, name);

        SET_SKILL_INFO(fp, "    float GetMpcost (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static float array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetMpCost(skill, 1),
            GetMpCost(skill, 2),
            GetMpCost(skill, 3),
            GetMpCost(skill, 4),
            GetMpCost(skill, 5),
            GetMpCost(skill, 6),
            GetMpCost(skill, 7),
            GetMpCost(skill, 8),
            GetMpCost(skill, 9),
            GetMpCost(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetExecutetime (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetExecuteTime(skill, 1),
            GetExecuteTime(skill, 2),
            GetExecuteTime(skill, 3),
            GetExecuteTime(skill, 4),
            GetExecuteTime(skill, 5),
            GetExecuteTime(skill, 6),
            GetExecuteTime(skill, 7),
            GetExecuteTime(skill, 8),
            GetExecuteTime(skill, 9),
            GetExecuteTime(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetCoolingtime (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetCoolingtime(skill, 1),
            GetCoolingtime(skill, 2),
            GetCoolingtime(skill, 3),
            GetCoolingtime(skill, 4),
            GetCoolingtime(skill, 5),
            GetCoolingtime(skill, 6),
            GetCoolingtime(skill, 7),
            GetCoolingtime(skill, 8),
            GetCoolingtime(skill, 9),
            GetCoolingtime(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetRequiredLevel (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetRequiredLevel(skill, 1),
            GetRequiredLevel(skill, 2),
            GetRequiredLevel(skill, 3),
            GetRequiredLevel(skill, 4),
            GetRequiredLevel(skill, 5),
            GetRequiredLevel(skill, 6),
            GetRequiredLevel(skill, 7),
            GetRequiredLevel(skill, 8),
            GetRequiredLevel(skill, 9),
            GetRequiredLevel(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetRequiredSp (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetRequiredSp(skill, 1),
            GetRequiredSp(skill, 2),
            GetRequiredSp(skill, 3),
            GetRequiredSp(skill, 4),
            GetRequiredSp(skill, 5),
            GetRequiredSp(skill, 6),
            GetRequiredSp(skill, 7),
            GetRequiredSp(skill, 8),
            GetRequiredSp(skill, 9),
            GetRequiredSp(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetRequiredItem (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetRequiredBook(skill, 1),
            GetRequiredBook(skill, 2),
            GetRequiredBook(skill, 3),
            GetRequiredBook(skill, 4),
            GetRequiredBook(skill, 5),
            GetRequiredBook(skill, 6),
            GetRequiredBook(skill, 7),
            GetRequiredBook(skill, 8),
            GetRequiredBook(skill, 9),
            GetRequiredBook(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    int GetRequiredMoney (Skill * skill) const ", name);
        SET_SKILL_INFO(fp, "    {", name);
        sprintf_s(Src, "        static int array[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d };",
            GetRequiredMoney(skill, 1),
            GetRequiredMoney(skill, 2),
            GetRequiredMoney(skill, 3),
            GetRequiredMoney(skill, 4),
            GetRequiredMoney(skill, 5),
            GetRequiredMoney(skill, 6),
            GetRequiredMoney(skill, 7),
            GetRequiredMoney(skill, 8),
            GetRequiredMoney(skill, 9),
            GetRequiredMoney(skill, 10)
        ); SET_SKILL_INFO(fp, Src, name);
        SET_SKILL_INFO(fp, "        return array[skill->GetLevel () - 1];", name);
        SET_SKILL_INFO(fp, "    }", name);

        SET_SKILL_INFO(fp, "    float GetRadius (Skill * skill) const { return 5; } ", name);
        SET_SKILL_INFO(fp, "    float GetAttackdistance (Skill * skill) const { return 4; } ", name);
        SET_SKILL_INFO(fp, "    float GetAngle (Skill * skill) const {  return (float) (1 - 0.0111111 * (0)); } ", name);
        SET_SKILL_INFO(fp, "    float GetPraydistance (Skill * skill) const { return (float) 10; } ", name);

        SET_SKILL_INFO(fp, "#ifdef _SKILL_CLIENT", name);
        SET_SKILL_INFO(fp, "    int GetIntroduction (Skill * skill, wchar_t * buffer, int length, wchar_t * format) const { return 0; }", name);
        SET_SKILL_INFO(fp, "#endif", name);

        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);
        SET_SKILL_INFO(fp, "    int GetEnmity (Skill * skill) const { return 10000; } ", name);
        SET_SKILL_INFO(fp, "    bool StateAttack (Skill * skill) const { return true; } ", name);
        SET_SKILL_INFO(fp, "    bool BlessMe (Skill * skill) const { return true; } ", name);
        SET_SKILL_INFO(fp, "    bool TakeEffect (Skill * skill) const { return true; } ", name);
        SET_SKILL_INFO(fp, "    float GetEffectdistance (Skill * skill) const { return 5; } ", name);
        SET_SKILL_INFO(fp, "    int GetAttackspeed (Skill * skill) const { return 16; } ", name);
        SET_SKILL_INFO(fp, "    float GetHitrate (Skill * skill) const { return 3; } ", name);
        SET_SKILL_INFO(fp, "#endif", name);
        SET_SKILL_INFO(fp, "    };", name);
        SET_SKILL_INFO(fp, "}", name);
        SET_SKILL_INFO(fp, "#endif", name);

        s->Destroy();
        fclose(fp);
        return;
    }

    void STUB_PARSER(size_t num, size_t count, size_t max_count)
    {
        size_t i = 0;
        static FILE* fp;
        static char name[32];
        sprintf_s(name, "./cskill/stubs%d.cpp", (num / count + 1));
        fopen_s(&fp, (const char*)name, "a+");
        static char Src[1024];

        SET_SKILL_INFO(fp, "#include \"skill.h\"", name);

        for (i = 0; i < count && (i + num) < max_count; ++i)
        {
            int skill = (1 + i + num);
            CSKILL* s = lib_ElementSkill__Create(skill, 1);
            if (s)
            {
                sprintf_s(Src, "#include \"skill%d.h\"", skill);
                SET_SKILL_INFO(fp, Src, name);
                s->Destroy();
            }
        }

        SET_SKILL_INFO(fp, "namespace GNET", name);
        SET_SKILL_INFO(fp, "{", name);

        for (i = 0; i < count && (i + num) < max_count; ++i)
        {
            int skill = (1 + i + num);
            CSKILL* s = lib_ElementSkill__Create(skill, 1);
            if (s)
            {
                sprintf_s(Src, "Skill%dStub   __stub_Skill%dStub;", skill, skill);
                SET_SKILL_INFO(fp, Src, name);
                s->Destroy();
            }
        }

        SET_SKILL_INFO(fp, "#ifdef _SKILL_SERVER", name);

        for (i = 0; i < count && (i + num) < max_count; ++i)
        {
            int skill = (1 + i + num);
            CSKILL* s = lib_ElementSkill__Create(skill, 1);
            if (s)
            {
                sprintf_s(Src, "Skill%d		__stub_Skill%d;", skill, skill);
                SET_SKILL_INFO(fp, Src, name);
                s->Destroy();
            }
        }

        SET_SKILL_INFO(fp, "#endif", name);
        SET_SKILL_INFO(fp, "}", name);

        fclose(fp);
        return;
    }
#endif

    void SKILL_STUBS_PARSER(size_t count, size_t stubs_size)
    {
#ifdef _WIN64

#else //WIN32
        
        for (size_t i = 1; i < count; i++)
            CSKILL_PARSER(i);

        size_t num = count / stubs_size;

        for (size_t i = 0; i < num; i++)
        {
            STUB_PARSER((i * stubs_size), stubs_size, count);
        }
#endif
    }

}


