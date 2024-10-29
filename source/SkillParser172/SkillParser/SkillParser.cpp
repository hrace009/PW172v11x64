// SkillParser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
#include <string>
#include <codecvt>

#include "config.h"
#include "ElementSkill.h"
#include "SkillParser.h"

bool SkillImport::is_logs = false;
SkillImport* SkillImport::instance = NULL;
const char SkillImport::LogFileName[] = "./elementskill.log";
const char SkillImport::DumpFileName[] = "./dump/%s";

void SkillImport::Init()
{
    GNET::ElementSkill::InitStaticData();
    InitializeCriticalSection(&cs_file);
}

void SkillImport::Print(const char* src)
{
    std::cout << src;
}

void SkillImport::Log(const char* Src)
{
    EnterCriticalSection(&cs_file);
    try
    {
        size_t len = strlen(Src);
        if (len && len < 2048)
        {
	        FILE* fp;
	        errno_t err = fopen_s(&fp, LogFileName, "a+");
	        if (!err)
	        {
		        fwrite(Src, 1, len, fp);
		        fclose(fp);
	        }
        }
    }
    catch (...)
    {
        //ERROR...
    }
    LeaveCriticalSection(&cs_file);
}

void SkillImport::Dump(void* Src, size_t len, const char* name)
{
    EnterCriticalSection(&cs_file);
    try
    {
        static char fname[1024];
        sprintf_s(fname, DumpFileName, name);
        FILE* fp;
        errno_t err = fopen_s(&fp, fname, "wb");
        if (!err)
        {
            fwrite(Src, 1, len, fp);
            fclose(fp);
        }
    }
    catch (...)
    {
        //ERROR...
    }
    LeaveCriticalSection(&cs_file);
}

void SkillImport::Restore(void* Src, size_t len, const char* name)
{
    EnterCriticalSection(&cs_file);
    try
    {
        static char fname[1024];
        sprintf_s(fname, DumpFileName, name);
        FILE* fp;
        errno_t err = fopen_s(&fp, fname, "r");
        if (!err)
        {
            fread(Src, 1, len, fp);
            fclose(fp);
        }
    }
    catch (...)
    {
        //ERROR...
    }
    LeaveCriticalSection(&cs_file);
}

bool SkillImport::Load()
{
    EnterCriticalSection(&cs_file);
    FILE* fp;
    char fname[MAX_NAME_LEN];
    char src[MAX_STRING];
    
    for (size_t i = 0; i < MAX_SKILL; i++)
    {
        ids[i].clear();
        ids[i].reserve(MAX_STRING);

        sprintf_s(fname, "../import/skill%d.h", i);
        errno_t err = fopen_s(&fp, (const char*)fname, "r");
        if (!err)
        {
            for (size_t j = 0; !feof(fp) && j < MAX_STRING; j++)
            {
                fgets(src, MAX_STRING, fp);
                ids[i].push_back(src);
            }
            fclose(fp);
        }
        else
        {
            printf("LOAD: file = %s, err = %d \n", fname, err);
        }
    }

    LeaveCriticalSection(&cs_file);
    return true;
}


bool SkillImport::LoadScript()
{
    bool res = false;
    if (LoadStrScript())
    {
        for (size_t j = 0; j < MAX_SKILL; j++)
        {
            LoadSkillScript(j);
        }
        res = true;
    }
    return res;
}

bool SkillImport::LoadStrScript()
{
    bool res = false;
    EnterCriticalSection(&cs_file);

    std::wifstream file(L"../import/skillstr.txt", std::ios::binary);
    if (file.is_open())
    {
        file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
        std::wstring line;
        while (std::getline(file, line)) { // чтение файла построчно
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::string utf8_line = converter.to_bytes(line); // конвертация строки в utf8
            skillstr_all.push_back(utf8_line); // добавление строки в вектор
        }

        file.close(); // закрытие файла
        res = true;
    }
    printf("SkillImport::LoadScript: skillstr_all.size=%d \n", skillstr_all.size());

    LeaveCriticalSection(&cs_file);
    return res;
}

bool SkillImport::LoadSkillScript(int skill)
{
    bool res = false;
    EnterCriticalSection(&cs_file);

    if (skill && skill < MAX_SKILL)
    {
        skillstr[skill].clear();
        skillstr[skill].reserve(MAX_STRING);

        std::string begin_str = std::to_string(skill) + "0  ";
        std::string end_str = std::to_string(skill + 1) + "0  ";

        size_t begin = 0;
        for (size_t j = 0; j < skillstr_all.size() && j < MAX_STRLEN; j++)
        {
            if (skillstr_all[j].find(begin_str) != std::string::npos)
            {
                begin = j;
                break;
            }
        }

        size_t end = 0;
        for (size_t j = begin; j < skillstr_all.size() && j < MAX_STRLEN; j++)
        {
            if (skillstr_all[j].find(end_str) != std::string::npos)
            {
                end = j;
                break;
            }
        }

        if (begin > 0 && begin < skillstr_all.size() && end > 0 && end < skillstr_all.size() && end > begin && (end - begin) < MAX_STRING)
        {
            for (size_t j = begin; j < end; j++)
            {
                skillstr[skill].push_back(skillstr_all[j]);
            }
            res = true;
        }
    }

    LeaveCriticalSection(&cs_file);
    return res;
}


const char* SkillImport::WtoGB2312(const wchar_t* wstr)
{
    if (wstr && wstr[0])
    {
        size_t len = lstrlenW(wstr);
        static char gb2312[256];
        memset(gb2312, 0x00, sizeof(gb2312));
        if (len > 0 && len < sizeof(gb2312))
        {
            WideCharToMultiByte(936, 0, wstr, -1, (char*)&gb2312, 256, NULL, NULL);
            return gb2312;
        }
    }
    return "";
}

const char* SkillImport::CheckNullStr(const char* str)
{
    return str ? str : "";
}

size_t SkillImport::Search(int skill, const char * src, size_t n)
{
    size_t res = 0;
    if (skill < MAX_SKILL)
    {
        for (size_t i = n; i < ids[skill].size() && i < MAX_STRING; i++)
        {
            if (ids[skill][i].find(src) != std::string::npos)
            {
                res = i;
                break;
            }
        }
    }
    return res;
}

size_t SkillImport::CountItem(int skill, const char* src)
{
    size_t res = 0;
    if (skill < MAX_SKILL)
    {
        for (size_t i = 0; i < ids[skill].size() && i < MAX_STRING; i++)
        {
            if (ids[skill][i].find(src) != std::string::npos)
            {
                res++;
            }
        }
    }
    return res;
}

bool SkillImport::PrintItem(int skill, size_t num)
{
    bool res = false;
    if (skill < MAX_SKILL)
    {
        if (num < ids[skill].size() && num < MAX_STRING)
        {
            GenSkillAdd(ids[skill][num].c_str());
            res = true;
        }
        else
        {
            if (is_logs) printf("SkillImport::GetItem: num = %d BAD!!! \n", num);
        }
    }
    return res;
}

bool SkillImport::PrintItem(int skill, size_t begin, size_t end, int section)
{
    bool res = false;
    if (skill < MAX_SKILL)
    {
        const char* SECTION_BEGIN = NULL;
        const char* SECTION_END = NULL;

        switch (section)
        {
        case SECTION_CLT:
        {
            SECTION_BEGIN = "#ifdef _SKILL_CLIENT \n";
            SECTION_END = "#endif \n";
            break;
        }
        case SECTION_SEV:
        {
            SECTION_BEGIN = "#ifdef _SKILL_SERVER \n";
            SECTION_END = "#endif \n";
            break;
        }
        default:
            break;
        }

        if (begin && begin < end)
        {
            if (SECTION_BEGIN) GenSkillAdd(SECTION_BEGIN);
            for (size_t i = begin; i <= end && i < MAX_STRING; i++)
            {
                PrintItem(skill, i);
            }
            if (SECTION_END) GenSkillAdd(SECTION_END);
            res = true;
        }
        else
        {
            if (is_logs) printf("SkillImport::PrintItem: begin = %d , end = %d  BAD!!! \n", begin, end);
        }
    }
    return res;
}


bool SkillImport::PrintStub(int skill, size_t stub)
{
    bool res = false;
    if (skill < MAX_SKILL && stub <= MAX_STUBS)
    {
        size_t begin = 0;
        size_t end = 0;

        char Str[128];
        sprintf_s(Str, "State%d", stub);

        begin = Search(skill, Str);
        end = Search(skill, "bool Skip", begin);
        end = Search(skill, "};", end);

        res = PrintItem(skill, begin, end, SECTION_SEV);
    }
    return res;
}

bool SkillImport::PrintFunc( int skill, const char* src, int section)
{
    bool res = false;
    if (skill > 0 && skill < MAX_SKILL)
    {
        if (ids[skill].size() > 0)
        {

            size_t begin = 0;
            size_t end = 0;

            begin = Search(skill, src);
            end = Search(skill, "return", begin);
            end = Search(skill, "}", end);

            res = PrintItem(skill, begin, end, section);
        }
        else
        {
            GNET::ElementSkill * s = GNET::ElementSkill::Create(skill, 1);
            if (s)
            {
                for (size_t i = 0; i < s->skill->pre_skills.size() && i < 8; i++)
                {
                    if (PrintFunc(s->skill->pre_skills.at(i).first, src, section))
                    {
                        res = true;
                        break;
                    }
                }

                if (!res && s->skill->runes_attr)
                {
                    int glyph_base_sk = GetBaseSkillGlyph(skill);
                    if (glyph_base_sk)
                    {
                        if (PrintFunc(glyph_base_sk, src, section))
                        {
                            res = true;
                        }
                    }
                }
                s->Destroy();
            }
        }
    }
    return res;
}

bool SkillImport::PrintStubDef(int skill, size_t stub, size_t count)
{
    printf("SkillImport::PrintStubDef : skill=%d, stub=%d, count=%d \n", skill, stub, count);
    
    
    static char Src[MAX_STRING];
    static char state_name[256];
    GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
    if (s)
    {
        sprintf_s(state_name, "    class State%d:public SkillStub::State \n", stub);
        GenSkillAdd("#ifdef _SKILL_SERVER \n");

        GenSkillAdd(state_name);
        GenSkillAdd("    { \n");
        GenSkillAdd("    public: \n");
        
        if (count == 3 && stub == 1 && s->GetCls() < USER_CLASS_COUNT)
        {
            sprintf_s(Src , "        int GetTime (Skill * skill) const { return %d; } \n", (int)(s->GetExecuteTime() * 0.2)); GenSkillAdd(Src);
            GenSkillAdd(    "        bool Quit (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Loop (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Bypass (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        void Calculate (Skill * skill) const \n");
            GenSkillAdd(    "        { \n");
            sprintf_s(Src,  "            static int aarray[10] = { %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f }; \n",
                (GNET::ElementSkill::GetMpcost(skill, 1)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 2)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 3)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 4)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 5)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 6)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 7)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 8)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 9)   * 0.2),
                (GNET::ElementSkill::GetMpcost(skill, 10)  * 0.2)
            ); GenSkillAdd(Src);
            GenSkillAdd(    "            skill->GetPlayer ()->SetDecmp (aarray[skill->GetLevel () - 1]); \n");
            GenSkillAdd(    "            skill->GetPlayer ()->SetPray (1); \n");
            GenSkillAdd(    "            return; \n");
            GenSkillAdd(    "        } \n");
            GenSkillAdd(    "        bool Interrupt (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Cancel (Skill * skill) const { return 1; } \n");
            GenSkillAdd(    "        bool Skip (Skill * skill) const { return 0; } \n");
        }
        else if (count == 3 && stub == 2 && s->GetCls() < USER_CLASS_COUNT)
        {
            sprintf_s(Src , "        int GetTime (Skill * skill) const { return %d; } \n", (int)(s->GetExecuteTime() * 0.8)); GenSkillAdd(Src);
            GenSkillAdd(    "        bool Quit (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Loop (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Bypass (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        void Calculate (Skill * skill) const \n");
            GenSkillAdd(    "        { \n");
            sprintf_s(Src, "            static int aarray[10] = { %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f }; \n",
                (GNET::ElementSkill::GetMpcost(skill, 1) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 2) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 3) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 4) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 5) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 6) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 7) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 8) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 9) * 0.8 ),
                (GNET::ElementSkill::GetMpcost(skill, 10) * 0.8)
            ); GenSkillAdd(Src);
            GenSkillAdd(    "            skill->GetPlayer ()->SetDecmp (aarray[skill->GetLevel () - 1]); \n");
            sprintf_s(Src,  "            skill->SetDamage (%s); \n", s->skill->attr == 1 ? "skill->GetAttack ()" : "skill->GetMagicattack ()"); GenSkillAdd(Src);
            GenSkillAdd(    "            skill->GetPlayer ()->SetPerform (1); \n");
            GenSkillAdd(    "            return; \n");
            GenSkillAdd(    "        } \n");
            GenSkillAdd(    "        bool Interrupt (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Cancel (Skill * skill) const { return 1; } \n");
            GenSkillAdd(    "        bool Skip (Skill * skill) const { return 0; } \n");
        }
        else if (count == 1 && stub == 1 && s->GetCls() < USER_CLASS_COUNT)
        {
            GenSkillAdd(    "        int GetTime (Skill * skill) const { return 0; } \n");
            GenSkillAdd(    "        bool Quit (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Loop (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Bypass (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        void Calculate (Skill * skill) const \n");
            GenSkillAdd(    "        { \n");
            sprintf_s(Src,  "            static int aarray[10] = { %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f }; \n",
                GNET::ElementSkill::GetMpcost(skill, 1)  ,
                GNET::ElementSkill::GetMpcost(skill, 2)  ,
                GNET::ElementSkill::GetMpcost(skill, 3)  ,
                GNET::ElementSkill::GetMpcost(skill, 4)  ,
                GNET::ElementSkill::GetMpcost(skill, 5)  ,
                GNET::ElementSkill::GetMpcost(skill, 6)  ,
                GNET::ElementSkill::GetMpcost(skill, 7)  ,
                GNET::ElementSkill::GetMpcost(skill, 8)  ,
                GNET::ElementSkill::GetMpcost(skill, 9)  ,
                GNET::ElementSkill::GetMpcost(skill, 10) 
            ); GenSkillAdd(Src);
            GenSkillAdd(    "            skill->GetPlayer ()->SetDecmp (aarray[skill->GetLevel () - 1]); \n");
            GenSkillAdd(    "            skill->GetPlayer ()->SetPerform (1); \n");
            GenSkillAdd(    "            return; \n");
            GenSkillAdd(    "        } \n");
            GenSkillAdd(    "        bool Interrupt (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Cancel (Skill * skill) const { return 1; } \n");
            GenSkillAdd(    "        bool Skip (Skill * skill) const { return 0; } \n");
        }
        else
        {
            GenSkillAdd(    "        int GetTime (Skill * skill) const { return 0; } \n");
            GenSkillAdd(    "        bool Quit (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Loop (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Bypass (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        void Calculate (Skill * skill) const { } \n");
            GenSkillAdd(    "        bool Interrupt (Skill * skill) const { return false; } \n");
            GenSkillAdd(    "        bool Cancel (Skill * skill) const { return 1; } \n");
            GenSkillAdd(    "        bool Skip (Skill * skill) const { return 0; } \n");
        }
        GenSkillAdd("    }; \n");
        GenSkillAdd("#endif \n");
        s->Destroy();
		return true;
    }
    return false;
}

void SkillImport::GenCreateScript(int skillid)
{
    GenSkillAdd("/* SKILL DESCRIPTION BEGIN */ \n");
    GenSkillAdd("/* \n");

    for (size_t i = 0; i < skillstr[skillid].size(); i++)
    {
        GenSkillAdd(skillstr[skillid][i].c_str());
    }

    GenSkillAdd("*/ \n");
    GenSkillAdd("/* SKILL DESCRIPTION END */ \n");
    GenSkillAdd("\n");
}

void SkillImport::GenCreateMacro(int skillid)
{
    for (size_t i = 0; CONFIG::GlyphSkill[i] && i < 1000; i++)
    {
        if (skillid == CONFIG::GlyphSkill[i])
        {
            GenSkillAdd("#define get_glyph(level, l1_4, l5_7, l8_9, lmax) level >= 1 && level <= 4 ? l1_4 : level >= 5 && level <= 7 ? l5_7 : level >= 8 && level <= 9 ? l8_9 : lmax; \n");
            GenSkillAdd("\n");
        }
    }
}

void SkillImport::GenSkillCreate(int skill, size_t count)
{
    static char Src[MAX_STRING];

    sprintf_s(Src, "#ifndef __CPPGEN_GNET_SKILL%d \n", skill); GenSkillAdd(Src);
    sprintf_s(Src, "#define __CPPGEN_GNET_SKILL%d \n", skill); GenSkillAdd(Src);
    GenSkillAdd("namespace GNET \n");
    GenSkillAdd("{ \n");
    GenSkillAdd("#ifdef _SKILL_SERVER \n");
    sprintf_s(Src, "    class Skill%d:public Skill \n", skill); GenSkillAdd(Src);
    GenSkillAdd("    { \n");
    GenSkillAdd("    public: \n");
    sprintf_s(Src, "        enum { SKILL_ID = %d }; \n", skill); GenSkillAdd(Src);
    sprintf_s(Src, "        Skill%d ():Skill (SKILL_ID){ } \n", skill); GenSkillAdd(Src);
    GenSkillAdd("    }; \n");
    GenSkillAdd("#endif \n");

    sprintf_s(Src, "    class Skill%dStub:public SkillStub \n", skill); GenSkillAdd(Src);
    GenSkillAdd("    { \n");
    GenSkillAdd("    public: \n");

}

void SkillImport::GenSkillRelease(int skill)
{
    GenSkillAdd( "    }; \n");
    GenSkillAdd( "} \n");
    GenSkillAdd( "#endif \n");
    
    EnterCriticalSection(&cs_file);

    FILE* fp;
    static char fname[MAX_NAME_LEN];

    sprintf_s(fname, "../export/skill%d.h", skill);
    errno_t err = fopen_s(&fp, (const char*)fname, "w+");
    if (!err)
    {
        for (size_t i = 0; i < SkillRes.size(); i++)
        {
            if (SkillRes[i].size())
            {
                fwrite(SkillRes[i].c_str(), 1, SkillRes[i].size(), fp);
            }
        }

        SkillRes.clear();
        SkillRes.reserve(MAX_STRING);
        fclose(fp);
    }
    LeaveCriticalSection(&cs_file);
}

void SkillImport::GenSkillAdd(const char* str)
{
    SkillRes.push_back(str);
}

void SkillImport::GenSkillBase(int skill, size_t count_stubs)
{
    GNET::ElementSkill * s = GNET::ElementSkill::Create(skill, 1);
    if (s)
    {
        char Src[MAX_STRING];

        sprintf_s(Src, "    Skill%dStub ():SkillStub (%d) \n", skill, skill); GenSkillAdd(Src);
        GenSkillAdd("    { \n");

        sprintf_s(Src, "        cls                 = %d; \n"      ,  s->skill->cls                               ); GenSkillAdd(Src);
        GenSkillAdd("#ifdef _SKILL_CLIENT \n");
        sprintf_s(Src, "        name                = L\"%s\"; \n" ,  WtoGB2312(s->skill->name)                   ); GenSkillAdd(Src);
        sprintf_s(Src, "        nativename          = \"%s\"; \n"  ,  CheckNullStr(s->skill->nativename)          ); GenSkillAdd(Src);
        sprintf_s(Src, "        icon                = \"%s\"; \n"  ,  CheckNullStr(s->skill->icon)                ); GenSkillAdd(Src);
        GenSkillAdd("#endif \n");
        sprintf_s(Src, "        max_level           = %d; \n"      ,  s->skill->max_level                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        type                = %d; \n"      ,  s->skill->type                              ); GenSkillAdd(Src);
        sprintf_s(Src, "        allow_ride          = %d; \n"      ,  s->skill->allow_ride                        ); GenSkillAdd(Src);
        sprintf_s(Src, "        attr                = %d; \n"      ,  s->skill->attr                              ); GenSkillAdd(Src);
        sprintf_s(Src, "        rank                = %d; \n"      ,  s->skill->rank                              ); GenSkillAdd(Src);
        sprintf_s(Src, "        eventflag           = %d; \n"      ,  s->skill->eventflag                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        is_senior           = %d; \n"      ,  s->skill->is_senior                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        is_inherent         = %d; \n"      ,  s->skill->is_inherent                       ); GenSkillAdd(Src);
        sprintf_s(Src, "        is_movingcast       = %d; \n"      ,  s->skill->is_movingcast                     ); GenSkillAdd(Src);
        sprintf_s(Src, "        npcdelay            = %d; \n"      ,  s->skill->npcdelay                          ); GenSkillAdd(Src);
        sprintf_s(Src, "        showorder           = %d; \n"      ,  s->skill->showorder                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        allow_forms         = %d; \n"      ,  s->skill->allow_forms                       ); GenSkillAdd(Src);
        sprintf_s(Src, "        apcost              = %d; \n"      ,  s->skill->apcost                            ); GenSkillAdd(Src);
        sprintf_s(Src, "        apgain              = %d; \n"      ,  s->skill->apgain                            ); GenSkillAdd(Src);

        size_t doenchant = Search(skill, "doenchant           = 1;");
        if (doenchant)
        {
            sprintf_s(Src, "        doenchant           = %d; \n", 1); GenSkillAdd(Src);
        }
        else
        {
            sprintf_s(Src, "        doenchant           = %d; \n", s->skill->doenchant); GenSkillAdd(Src);
        }

        size_t dobless = Search(skill, "dobless             = 1;");
        if (dobless)
        {
            sprintf_s(Src, "        dobless             = %d; \n", 1); GenSkillAdd(Src);
        }
        else
        {
            sprintf_s(Src, "        dobless             = %d; \n", s->skill->dobless); GenSkillAdd(Src);
        }

        sprintf_s(Src, "        arrowcost           = %d; \n"      ,  s->skill->arrowcost                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        allow_land          = %d; \n"      ,  s->skill->allow_land                        ); GenSkillAdd(Src);
        sprintf_s(Src, "        allow_air           = %d; \n"      ,  s->skill->allow_air                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        allow_water         = %d; \n"      ,  s->skill->allow_water                       ); GenSkillAdd(Src);
        sprintf_s(Src, "        notuse_in_combat    = %d; \n"      ,  s->skill->notuse_in_combat                  ); GenSkillAdd(Src);
        sprintf_s(Src, "        restrict_corpse     = %d; \n"      ,  s->skill->restrict_corpse                   ); GenSkillAdd(Src);
        sprintf_s(Src, "        restrict_change     = %d; \n"      ,  s->skill->restrict_change                   ); GenSkillAdd(Src);
        sprintf_s(Src, "        restrict_attach     = %d; \n"      ,  s->skill->restrict_attach                   ); GenSkillAdd(Src);
        sprintf_s(Src, "        auto_attack         = %d; \n"      ,  s->skill->auto_attack                       ); GenSkillAdd(Src);
        sprintf_s(Src, "        time_type           = %d; \n"      ,  s->skill->time_type                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        long_range          = %d; \n"      ,  s->skill->long_range                        ); GenSkillAdd(Src);
        sprintf_s(Src, "        posdouble           = %d; \n"      ,  s->skill->posdouble                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        clslimit            = %d; \n"      ,  s->skill->clslimit                          ); GenSkillAdd(Src);
        sprintf_s(Src, "        commoncooldown      = %d; \n"      ,  s->skill->commoncooldown                    ); GenSkillAdd(Src);
        sprintf_s(Src, "        commoncooldowntime  = %d; \n"      ,  s->skill->commoncooldowntime                ); GenSkillAdd(Src);
        sprintf_s(Src, "        itemcost            = %d; \n"      ,  s->skill->itemcost                          ); GenSkillAdd(Src);
        sprintf_s(Src, "        itemcostcount       = %d; \n"      ,  s->skill->itemcostcount                     ); GenSkillAdd(Src);
        sprintf_s(Src, "        combosk_preskill    = %d; \n"      ,  s->skill->combosk_preskill                  ); GenSkillAdd(Src);
        sprintf_s(Src, "        combosk_interval    = %d; \n"      ,  s->skill->combosk_interval                  ); GenSkillAdd(Src);
        sprintf_s(Src, "        combosk_nobreak     = %d; \n"      ,  s->skill->combosk_nobreak                   ); GenSkillAdd(Src);
        GenSkillAdd("#ifdef _SKILL_CLIENT \n");
        sprintf_s(Src, "        effect              = \"%s\"; \n"  ,  CheckNullStr(s->skill->effect)              ); GenSkillAdd(Src);
        sprintf_s(Src, "        aerial_effect       = \"%s\"; \n"  ,  CheckNullStr(s->skill->aerial_effect)       ); GenSkillAdd(Src);
        GenSkillAdd("#endif \n");
        sprintf_s(Src, "        range.type          = %d; \n"      ,  s->skill->range.type                        ); GenSkillAdd(Src);
        sprintf_s(Src, "        has_stateattack     = %d; \n"      ,  s->skill->has_stateattack                   ); GenSkillAdd(Src);
        sprintf_s(Src, "        runes_attr          = %d; \n"      ,  s->skill->runes_attr                        ); GenSkillAdd(Src);
        GenSkillAdd("#ifdef _SKILL_CLIENT \n");
        sprintf_s(Src, "        gfxfilename         = \"%s\"; \n"  ,  CheckNullStr(s->skill->gfxfilename)         ); GenSkillAdd(Src);
        sprintf_s(Src, "        gfxhangpoint        = \"%s\"; \n"  ,  CheckNullStr(s->skill->gfxhangpoint)        ); GenSkillAdd(Src);
        GenSkillAdd("#endif \n");
        sprintf_s(Src, "        gfxtarget           = %d; \n"      ,  s->skill->gfxtarget                         ); GenSkillAdd(Src);
        sprintf_s(Src, "        feature             = %d; \n"      ,  s->skill->feature                           ); GenSkillAdd(Src);
        sprintf_s(Src, "        extra_effect        = %d; \n"      ,  s->skill->extra_effect                      ); GenSkillAdd(Src);
        sprintf_s(Src, "        immune_casting      = %d; \n"      ,  s->skill->immune_casting                    ); GenSkillAdd(Src);

        for (size_t i = 0; i < s->skill->pre_skills.size(); i++)
        {
            sprintf_s(Src, "        pre_skills.push_back (std::pair < ID, int >(%d, %d)); \n",
                s->skill->pre_skills.at(i).first, s->skill->pre_skills.at(i).second); GenSkillAdd(Src);
        }

        for (size_t i = 0; i < s->skill->restrict_weapons.size(); i++)
        {
            sprintf_s(Src, "        restrict_weapons.push_back (%d); \n", 
                s->skill->restrict_weapons[i]); GenSkillAdd(Src);
        }

        if (skill > MAX_DEF_SKILL || s->skill->eventflag != 2)

        {
            GenSkillAdd("#ifdef _SKILL_SERVER \n");
            for (size_t i = 0; i < count_stubs; i++)
            {
                sprintf_s(Src, "        statestub.push_back (new State%d ()); \n",
                    (i + 1)); GenSkillAdd(Src);
            }
            GenSkillAdd("#endif \n");
        }

        GenSkillAdd("    } \n");
        s->Destroy();
    }
}

bool SkillImport::GenSkillStubs(int skillid, size_t count)
{
    if (CountItem(skillid, "statestub"))
    {
        for (size_t i = 1; i <= count && i <= MAX_STUBS; i++)
        {
            PrintStub(skillid, i);
        }
        return true;
    }
    else
    {
        GNET::ElementSkill* s = GNET::ElementSkill::Create(skillid, 1);
        if (s)
        {
            for (size_t i = 0; i < s->skill->pre_skills.size() && i < 8; i++)
            {
                if (GenSkillStubs(s->skill->pre_skills.at(i).first, count))
                {
                    s->Destroy();
                    return true;
                }
            }
            
            if (s->skill->runes_attr)
            {
                int glyph_base_sk = GetBaseSkillGlyph(skillid);
                if (glyph_base_sk)
                {
                    if (GenSkillStubs(glyph_base_sk, count))
                    {
                        s->Destroy();
                        return true;
                    }
                }
            }
            
            for (size_t i = 1; i <= count && i <= MAX_STUBS; i++)
            {
                PrintStubDef(skillid, i, count);
            }
            s->Destroy();
            return true;
        }
    }
    return false;
}

void SkillImport::GenSkillGetExecutetime(int skill)
{
    static char Src[MAX_STRING];
    GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
    if (s)
    {
        if ((skill > MAX_DEF_SKILL && (s->skill->cls >= USER_CLASS_COUNT) ) || !PrintFunc(skill, "GetExecutetime"))
        {
            GenSkillAdd("    int GetExecutetime (Skill * skill) const \n");
            GenSkillAdd("    { \n");
            sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
                GNET::ElementSkill::GetExecuteTime(skill, 1),
                GNET::ElementSkill::GetExecuteTime(skill, 2),
                GNET::ElementSkill::GetExecuteTime(skill, 3),
                GNET::ElementSkill::GetExecuteTime(skill, 4),
                GNET::ElementSkill::GetExecuteTime(skill, 5),
                GNET::ElementSkill::GetExecuteTime(skill, 6),
                GNET::ElementSkill::GetExecuteTime(skill, 7),
                GNET::ElementSkill::GetExecuteTime(skill, 8),
                GNET::ElementSkill::GetExecuteTime(skill, 9),
                GNET::ElementSkill::GetExecuteTime(skill, 10)
            ); GenSkillAdd(Src);
            GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
            GenSkillAdd("    } \n");
        }
        s->Destroy();
    }
}

void SkillImport::GenSkillGetCoolingtime(int skill)
{
    static char Src[MAX_STRING];
    GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
    if (s)
    {
        GenSkillAdd("    int GetCoolingtime (Skill * skill) const \n");
        GenSkillAdd("    { \n");

        if (GNET::ElementSkill::GetCoolingTime(skill, 1, 0) == GNET::ElementSkill::GetCoolingTime(skill, 1, 1))
        {
            sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
                GNET::ElementSkill::GetCoolingTime(skill, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 2),
                GNET::ElementSkill::GetCoolingTime(skill, 3),
                GNET::ElementSkill::GetCoolingTime(skill, 4),
                GNET::ElementSkill::GetCoolingTime(skill, 5),
                GNET::ElementSkill::GetCoolingTime(skill, 6),
                GNET::ElementSkill::GetCoolingTime(skill, 7),
                GNET::ElementSkill::GetCoolingTime(skill, 8),
                GNET::ElementSkill::GetCoolingTime(skill, 9),
                GNET::ElementSkill::GetCoolingTime(skill, 10)
            ); GenSkillAdd(Src);
            GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
        }
        else
        {
            sprintf_s(Src, "        static int aarray[2][10] = { {%d,%d,%d,%d,%d,%d,%d,%d,%d,%d} , {%d,%d,%d,%d,%d,%d,%d,%d,%d,%d} }; \n",

                GNET::ElementSkill::GetCoolingTime(skill, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 2),
                GNET::ElementSkill::GetCoolingTime(skill, 3),
                GNET::ElementSkill::GetCoolingTime(skill, 4),
                GNET::ElementSkill::GetCoolingTime(skill, 5),
                GNET::ElementSkill::GetCoolingTime(skill, 6),
                GNET::ElementSkill::GetCoolingTime(skill, 7),
                GNET::ElementSkill::GetCoolingTime(skill, 8),
                GNET::ElementSkill::GetCoolingTime(skill, 9),
                GNET::ElementSkill::GetCoolingTime(skill, 10),

                GNET::ElementSkill::GetCoolingTime(skill, 1, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 2, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 3, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 4, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 5, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 6, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 7, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 8, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 9, 1),
                GNET::ElementSkill::GetCoolingTime(skill, 10, 1)
            ); GenSkillAdd(Src);
            GenSkillAdd("        return aarray[skill->GetPlayer ()->GetForm ()][skill->GetLevel () - 1]; \n");
        }
        
        GenSkillAdd("    } \n");
        s->Destroy();
    }
}

void SkillImport::GenSkillGetRequiredSp(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetRequiredSp (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetRequiredSp(skill, 1),
        GNET::ElementSkill::GetRequiredSp(skill, 2),
        GNET::ElementSkill::GetRequiredSp(skill, 3),
        GNET::ElementSkill::GetRequiredSp(skill, 4),
        GNET::ElementSkill::GetRequiredSp(skill, 5),
        GNET::ElementSkill::GetRequiredSp(skill, 6),
        GNET::ElementSkill::GetRequiredSp(skill, 7),
        GNET::ElementSkill::GetRequiredSp(skill, 8),
        GNET::ElementSkill::GetRequiredSp(skill, 9),
        GNET::ElementSkill::GetRequiredSp(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetRequiredLevel(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetRequiredLevel (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetRequiredLevel(skill, 1),
        GNET::ElementSkill::GetRequiredLevel(skill, 2),
        GNET::ElementSkill::GetRequiredLevel(skill, 3),
        GNET::ElementSkill::GetRequiredLevel(skill, 4),
        GNET::ElementSkill::GetRequiredLevel(skill, 5),
        GNET::ElementSkill::GetRequiredLevel(skill, 6),
        GNET::ElementSkill::GetRequiredLevel(skill, 7),
        GNET::ElementSkill::GetRequiredLevel(skill, 8),
        GNET::ElementSkill::GetRequiredLevel(skill, 9),
        GNET::ElementSkill::GetRequiredLevel(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetRequiredItem(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetRequiredItem (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetRequiredBook(skill, 1),
        GNET::ElementSkill::GetRequiredBook(skill, 2),
        GNET::ElementSkill::GetRequiredBook(skill, 3),
        GNET::ElementSkill::GetRequiredBook(skill, 4),
        GNET::ElementSkill::GetRequiredBook(skill, 5),
        GNET::ElementSkill::GetRequiredBook(skill, 6),
        GNET::ElementSkill::GetRequiredBook(skill, 7),
        GNET::ElementSkill::GetRequiredBook(skill, 8),
        GNET::ElementSkill::GetRequiredBook(skill, 9),
        GNET::ElementSkill::GetRequiredBook(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetRequiredMoney(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetRequiredMoney (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetRequiredMoney(skill, 1),
        GNET::ElementSkill::GetRequiredMoney(skill, 2),
        GNET::ElementSkill::GetRequiredMoney(skill, 3),
        GNET::ElementSkill::GetRequiredMoney(skill, 4),
        GNET::ElementSkill::GetRequiredMoney(skill, 5),
        GNET::ElementSkill::GetRequiredMoney(skill, 6),
        GNET::ElementSkill::GetRequiredMoney(skill, 7),
        GNET::ElementSkill::GetRequiredMoney(skill, 8),
        GNET::ElementSkill::GetRequiredMoney(skill, 9),
        GNET::ElementSkill::GetRequiredMoney(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetRequiredRealmLevel(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetRequiredRealmLevel (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 1),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 2),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 3),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 4),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 5),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 6),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 7),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 8),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 9),
        GNET::ElementSkill::GetRequiredRealmLevel(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetRadius(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetRadius"))
    {
        GenSkillAdd("    float GetRadius (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return (float) (0); \n");
        GenSkillAdd("    } \n");
    }
}

void SkillImport::GenSkillGetAttackdistance(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetAttackdistance"))
    {
        GenSkillAdd("    float GetAttackdistance (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return (float) (0); \n");
        GenSkillAdd("    } \n");
    }
}

void SkillImport::GenSkillGetAngle(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetAngle"))
    {
        GenSkillAdd("    float GetAngle (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return (float) (0); \n");
        GenSkillAdd("    } \n");
    }
}

void SkillImport::GenSkillGetPraydistance(int skill)
{
    static char Src[MAX_STRING];
    GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
    if (s)
    {
        if ((skill > MAX_DEF_SKILL && (s->skill->cls > 14)) || !PrintFunc(skill, "GetPraydistance"))
        {
            GenSkillAdd("    float GetPraydistance (Skill * skill) const \n");
            GenSkillAdd("    { \n");
            sprintf_s(Src, "        static float aarray[10] = { %.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f }; \n",
                GNET::ElementSkill::GetPraydistance(skill, 1),
                GNET::ElementSkill::GetPraydistance(skill, 2),
                GNET::ElementSkill::GetPraydistance(skill, 3),
                GNET::ElementSkill::GetPraydistance(skill, 4),
                GNET::ElementSkill::GetPraydistance(skill, 5),
                GNET::ElementSkill::GetPraydistance(skill, 6),
                GNET::ElementSkill::GetPraydistance(skill, 7),
                GNET::ElementSkill::GetPraydistance(skill, 8),
                GNET::ElementSkill::GetPraydistance(skill, 9),
                GNET::ElementSkill::GetPraydistance(skill, 10)
            ); GenSkillAdd(Src);
            GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
            GenSkillAdd("    } \n");
        }
        s->Destroy();
    }
}

void SkillImport::GenSkillGetMpcost(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    float GetMpcost (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static float aarray[10] = { %.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f }; \n",
        GNET::ElementSkill::GetMpcost(skill, 1),
        GNET::ElementSkill::GetMpcost(skill, 2),
        GNET::ElementSkill::GetMpcost(skill, 3),
        GNET::ElementSkill::GetMpcost(skill, 4),
        GNET::ElementSkill::GetMpcost(skill, 5),
        GNET::ElementSkill::GetMpcost(skill, 6),
        GNET::ElementSkill::GetMpcost(skill, 7),
        GNET::ElementSkill::GetMpcost(skill, 8),
        GNET::ElementSkill::GetMpcost(skill, 9),
        GNET::ElementSkill::GetMpcost(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GetCoolDownLimit(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetCoolDownLimit (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetCoolDownLimit(skill, 1),
        GNET::ElementSkill::GetCoolDownLimit(skill, 2),
        GNET::ElementSkill::GetCoolDownLimit(skill, 3),
        GNET::ElementSkill::GetCoolDownLimit(skill, 4),
        GNET::ElementSkill::GetCoolDownLimit(skill, 5),
        GNET::ElementSkill::GetCoolDownLimit(skill, 6),
        GNET::ElementSkill::GetCoolDownLimit(skill, 7),
        GNET::ElementSkill::GetCoolDownLimit(skill, 8),
        GNET::ElementSkill::GetCoolDownLimit(skill, 9),
        GNET::ElementSkill::GetCoolDownLimit(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillGetCostShieldEnergy(int skill)
{
    static char Src[MAX_STRING];
    GenSkillAdd("    int GetCostShieldEnergy (Skill * skill) const \n");
    GenSkillAdd("    { \n");
    sprintf_s(Src, "        static int aarray[10] = { %d,%d,%d,%d,%d,%d,%d,%d,%d,%d }; \n",
        GNET::ElementSkill::GetCostShieldEnergy(skill, 1),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 2),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 3),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 4),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 5),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 6),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 7),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 8),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 9),
        GNET::ElementSkill::GetCostShieldEnergy(skill, 10)
    ); GenSkillAdd(Src);
    GenSkillAdd("        return aarray[skill->GetLevel () - 1]; \n");
    GenSkillAdd("    } \n");
}

void SkillImport::GenSkillCheckComboSkExtraCondition(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "CheckComboSkExtraCondition"))
    {
        GenSkillAdd("    bool CheckComboSkExtraCondition (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 1; \n");
        GenSkillAdd("    } \n");
    }
}

void SkillImport::GenSkillGetIntroduction(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetIntroduction", SECTION_CLT))
    {
        GenSkillAdd("#ifdef _SKILL_CLIENT \n");
        GenSkillAdd("    int GetIntroduction (Skill * skill, const wchar_t * buffer, int length, const wchar_t * format) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetEnmity(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetEnmity", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    int GetEnmity (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetMaxAbility(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetMaxAbility", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    int GetMaxAbility (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillStateAttack(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "StateAttack", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    bool StateAttack (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 1; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillBlessMe(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "BlessMe", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    bool BlessMe (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 1; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetEffectdistance(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetEffectdistance", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetEffectdistance (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 5; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetTalent0(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetTalent0", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetTalent0 (PlayerWrapper * player) \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetTalent1(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetTalent1", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetTalent1 (PlayerWrapper * player) \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetTalent2(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetTalent2", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetTalent2 (PlayerWrapper * player) \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetTalent3(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetTalent3", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetTalent3 (PlayerWrapper * player) \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetTalent4(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetTalent4", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetTalent4 (PlayerWrapper * player) \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetAttackspeed(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetAttackspeed", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    int GetAttackspeed (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 0; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillTakeEffect(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "TakeEffect", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    bool TakeEffect (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 1; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillGetHitrate(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "GetHitrate", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    float GetHitrate (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return 1; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenSkillComboSkEndAction(int skill)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skill, "ComboSkEndAction", SECTION_SEV))
    {
        GenSkillAdd("#ifdef _SKILL_SERVER \n");
        GenSkillAdd("    void ComboSkEndAction (Skill * skill) const \n");
        GenSkillAdd("    { \n");
        GenSkillAdd("        return; \n");
        GenSkillAdd("    } \n");
        GenSkillAdd("#endif \n");
    }
}

void SkillImport::GenGetChargeMerc(int skillid)
{
    static char Src[MAX_STRING];
    if (!PrintFunc(skillid, "int GetChargeMerc", SECTION_SEV))
    {
        for (size_t i = 0; CONFIG::GlyphSkill[i] && i < 1000; i++)
        {
            if (skillid == CONFIG::GlyphSkill[i])
            {
                GNET::ElementSkill* s = GNET::ElementSkill::Create(skillid, 1);
                if (s)
                {
                    if (s->GetCls() == USER_CLASS_ASN && s->GetRank() >= 40)
                    {
                        GenSkillAdd("#ifdef _SKILL_SERVER \n");
                        GenSkillAdd("    int GetChargeMerc  (Skill * skill) const \n");
                        GenSkillAdd("    { \n");
                        GenSkillAdd("        return 1; \n");
                        GenSkillAdd("    } \n");
                        GenSkillAdd("#endif \n");
                        break;
                    }
                    s->Destroy();
                }
            }
        }
    }
}

void SkillImport::SkillCreator(int skill)
{
    try {
        GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
        if (s)
        {
            printf("SKILL::Create: id = %d \n", skill);

            size_t count_stubs = CountItem(skill, "statestub");
            
            if (skill > MAX_DEF_SKILL && !count_stubs && s->skill->eventflag != 2)
            {
                s->skill->time_type == 1 ? count_stubs = 1 : count_stubs = 3;
            }
            

            SkillRes.clear();
            SkillRes.reserve(MAX_STRING);

            GenSkillAdd("//Skill Parser (c)Deadraky 2023 \n");
            GenSkillAdd("\n");

            GenCreateScript(skill);
            GenSkillCreate(skill, count_stubs);
            GenCreateMacro(skill);


            //sev
            if (count_stubs)
            {
                GenSkillStubs(skill, count_stubs);
            }
            //clt+sev
            GenSkillBase(skill, count_stubs);
            GenSkillGetExecutetime(skill);
            GenSkillGetCoolingtime(skill);
            GenSkillGetRequiredSp(skill);
            GenSkillGetRequiredLevel(skill);
            GenSkillGetRequiredItem(skill);
            GenSkillGetRequiredMoney(skill);
            GenSkillGetRequiredRealmLevel(skill);
            GenSkillGetRadius(skill);
            GenSkillGetAttackdistance(skill);
            GenSkillGetAngle(skill);
            GenSkillGetPraydistance(skill);
            GenSkillGetMpcost(skill);
            GenSkillCheckComboSkExtraCondition(skill);
            GetCoolDownLimit(skill);
            GenSkillGetCostShieldEnergy(skill);
            //clt
            GenSkillGetIntroduction(skill);
            //sev
            GenSkillGetEnmity(skill);
            GenSkillGetMaxAbility(skill);
            GenSkillStateAttack(skill);
            GenSkillBlessMe(skill);
            GenSkillGetEffectdistance(skill);
            GenSkillGetTalent0(skill);
            GenSkillGetTalent1(skill);
            GenSkillGetTalent2(skill);
            GenSkillGetTalent3(skill);
            GenSkillGetTalent4(skill);
            GenSkillGetAttackspeed(skill);
            GenSkillTakeEffect(skill);
            GenSkillGetHitrate(skill);
            GenSkillComboSkEndAction(skill);
            GenGetChargeMerc(skill);
            GenSkillRelease(skill);
            
            s->Destroy();
        }
    }
    catch (...)
    {
        return;
    }
}

void  SkillImport::StubsCreator(size_t num, size_t count, size_t max_count)
{
    static char Src[MAX_STRING];
    SkillRes.clear();
    SkillRes.reserve(MAX_STRING);

    GenSkillAdd("#include \"skill.h\" \n");

    for (size_t i = 0; i < count && (i + num) < max_count; ++i)
    {
        int skill = (1 + i + num);
        GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
        if (s)
        {
            sprintf_s(Src, "#include \"skill%d.h\" \n", skill);
            GenSkillAdd(Src);
            s->Destroy();
        }
    }

    GenSkillAdd("namespace GNET \n");
    GenSkillAdd("{ \n");

    for (size_t i = 0; i < count && (i + num) < max_count; ++i)
    {
        int skill = (1 + i + num);
        GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
        if (s)
        {
            sprintf_s(Src, "Skill%dStub   __stub_Skill%dStub; \n", skill, skill);
            GenSkillAdd(Src);
            s->Destroy();
        }
    }

    GenSkillAdd("#ifdef _SKILL_SERVER \n");

    for (size_t i = 0; i < count && (i + num) < max_count; ++i)
    {
        int skill = (1 + i + num);
        GNET::ElementSkill* s = GNET::ElementSkill::Create(skill, 1);
        if (s)
        {
            sprintf_s(Src, "Skill%d		__stub_Skill%d; \n", skill, skill);
            GenSkillAdd(Src);
            s->Destroy();
        }
    }

    GenSkillAdd("#endif \n");
    GenSkillAdd("} \n");

    EnterCriticalSection(&cs_file);
    FILE* fp;
    char fname[MAX_NAME_LEN];
    sprintf_s(fname, "../export/stubs%d.cpp", (num / count + 1));
    errno_t err = fopen_s(&fp, (const char*)fname, "w+");
    if (!err)
    {
        for (size_t i = 0; i < SkillRes.size(); i++)
        {
            if (SkillRes[i].size())
            {
                fwrite(SkillRes[i].c_str(), 1, SkillRes[i].size(), fp);
            }
        }

        fclose(fp);
    }
    LeaveCriticalSection(&cs_file);
    return;
}

void  SkillImport::Creator(size_t count, size_t stubs_size)
{
    for (size_t i = 1; i <= count; i++)
    {
        SkillCreator(i);
    }

    size_t num = (count / stubs_size);

    for (size_t i = 0; i <= num; i++)
    {
        StubsCreator((i * stubs_size), stubs_size, count);
    }
}

int SkillImport::GetBaseSkillGlyph(int skill)
{
    int res = 0;
    if (skill > 0 && skill < CONFIG::MAX_SKILLS)
    {
        for (size_t i = 0; CONFIG::GlyphSkill[i] && i < CONFIG::MAX_SKILLS; i++)
        {
            if (skill == CONFIG::GlyphSkill[i])
            {
                int base_skill = CONFIG::GlyphSkill[(i - (i % 6))];
                if (skill != base_skill)
                {
                    res = base_skill;
                }
            }
        }
    }
    return res;
}

int main()
{
    
    SkillImport* sImp = SkillImport::GetInstance();
    sImp->Init();
    sImp->Load();
    sImp->LoadScript();
    sImp->Creator(SkillImport::MAX_SKILL, 200);
    
    /*
    char src[1024];
    for (size_t i = 0;i < CONFIG::MAX_SKILLS; i++)
    {
        GNET::ElementSkill* s = GNET::ElementSkill::Create(i, 1);
        if (s)
        {
            if (GNET::ElementSkill::GetCoolingTime(i, 1, 0) != GNET::ElementSkill::GetCoolingTime(i, 1, 1))
            {
                sprintf(src, "SKILL::RESERVE: id = %d , cooltime0 = %d cooltime1 = %d \n", s->skill->id, GNET::ElementSkill::GetCoolingTime(i, 1, 0), GNET::ElementSkill::GetCoolingTime(i, 1, 1));
                std::cout << src;
            }
            s->Destroy();
        }
    }
    */
    system("Pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
