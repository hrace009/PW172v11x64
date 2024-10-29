//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------

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

#include "config.h"
#include "asm.h"
#include "gobject.h"
#include "regid.h"
#include "informer.h"
#include "packet.h"
#include "interfaces.h"
#include "colorname.h"
#include "autoswap.h"
#include "luaman.h"
#include "main.h"

//Perfect World GS 
#include "../Header/common/types.h"
#include "../Header/common/protocol.h"
#include "../Header/cnet/rpcdata.h"

//Perfect World sckill 
#include "../cskill/skill.h"
#include "../cskill/ElementSkill.h"
#include "parser.h"

extern "C"
{
    size_t BASE_ADDRES = CONFIG::BASE_ADDRES;
    int TransportTag[] = TRANSPORT_TAGS; //локации для телепорта
    size_t TransportTagSize = ((sizeof(TransportTag) / sizeof(TransportTag[0])) - 1); //количество 
    int free_items[] = FREE_ITEMS; // выключаем требования по некоторым итемам
}

MainApi* MainApi::instance = 0;
size_t MainApi::logs = CONFIG::ENABLE_LOG;
MainApi::IDATA_FUNCTIONS MainApi::Skill;
static CRITICAL_SECTION cs_file;

#ifdef _WIN64
    static const char LogFileName[] = "./elementclient_64.log";
    static const char DumpFileName[] = "./dump_64/%s";
#else
    static const char LogFileName[] = "./elementclient.log";
    static const char DumpFileName[] = "./dump/%s";
#endif

void MainApi::IDATA_FUNCTIONS::init(size_t address, size_t & old_address, size_t lib_address)
{
    old_address = get_size_t(address, 0x00);
    setup_size_t(address, lib_address);
}

const char* MainApi::GetTimeStr()
{
    static char tm_s[64];
    time_t ticks = time(NULL);
    ctime_s(tm_s, sizeof(tm_s), &ticks);
    return (const char* )tm_s;
}

void MainApi::Log(const char* Src)
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
    catch ( ... )
    {
        //ERROR...
    }
    LeaveCriticalSection(&cs_file);
}

void MainApi::Dump(void* Src, size_t len, const char* name)
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


void MainApi::Init()
{
    srand(time(NULL));
    fashion_weapon_enable = true;
    InitializeCriticalSection(&cs_file);
    GNET::ElementSkill::InitStaticData();
    Packet::GetInstance()->Init();
    ClassInformer::GetInstance()->Init();
    Regid::GetInstance()->Init();
    Interfaces::GetInstance()->Init();
    NpcRemote::GetInstance()->Init();
    AutoSwap::GetInstance()->Init();
    Gobject::GetInstance()->Init();
    //LuaManager::GetInstance()->Init();
}

void MainApi::HeartBeat(size_t tick)
{
    Interfaces::GetInstance()->HeartBeat(tick);
    //LuaManager::GetInstance()->HeartBeat(tick);
}

void MainApi::EnterWorld()
{
    GPlayer* pImp = GetPlayer();
    Regid* Key = Regid::GetInstance();
    if (pImp)
    {
        Gobject::GetInstance()->Create(Gobject::PLAYER_POOL, pImp->GetId(), pImp);
        Packet::GetInstance()->GetMainInfo(pImp->GetId());
    }
    Packet::GetInstance()->GameDataSend(Key->Get(), Key->Size());
    Interfaces::GetInstance()->Enable();
    AutoSwap::GetInstance()->Init();
}

void MainApi::LeaveWorld()
{
    Gobject::GetInstance()->Init();
    Interfaces::GetInstance()->Distable();
}

#ifdef _WIN64
//--------------------------------------------------------------------------
//----------------MAIN API WIN 64
//--------------------------------------------------------------------------

int __fastcall MainApi::GetRequiredBook(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredBook();
        s->Destroy();
    }
    else
    {
        res = ((int(__fastcall*)(unsigned int, int))Skill.GetRequiredBook)(id, level);
    }
    return res;
}

int __fastcall MainApi::GetRequiredMoney(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredMoney();
        s->Destroy();
    }
    else
    {
        res = ((int(__fastcall*)(unsigned int, int))Skill.GetRequiredMoney)(id, level);
    }
    return res;
}

int __fastcall MainApi::GetRequiredSp(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredSp();
        s->Destroy();
    }
    else
    {
        res = ((int(__fastcall*)(unsigned int, int))Skill.GetRequiredSp)(id, level);
    }
    return res;
}

int __fastcall MainApi::SkillCondition(unsigned int id, void* info, int ilevel)
{
    int res = 1;
    GNET::Skill* s = GNET::Skill::Create(id, ilevel);
    if (s)
    {
        res = s->Condition(id, (GNET::UseRequirement & )info, ilevel);
        s->Destroy();
    }
    else
    {
        res = ((int(__fastcall*)(unsigned int, void*, int))Skill.Condition)(id, info, ilevel);
    }
    return res;
}

void* __fastcall MainApi::SkillCreate(unsigned int id, int level)
{
    GPARSER::CSKILL* res = ((GPARSER::CSKILL * (__fastcall*)(unsigned int, int))Skill.Create)(id, level);
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s && res)
    {
        const GNET::SkillStub* stub = s->GetStub();
        res->skill->cls = stub->cls;
        res->skill->max_level = stub->max_level;
        res->skill->type = stub->type;
        res->skill->apcost = stub->apcost;
        res->skill->arrowcost = stub->arrowcost;
        res->skill->apgain = stub->apgain;
        res->skill->attr = stub->attr;
        res->skill->rank = stub->rank;
        res->skill->eventflag = stub->eventflag;
        res->skill->is_senior = stub->is_senior;
        res->skill->clslimit = stub->clslimit;
        res->skill->time_type = stub->time_type;
        res->skill->showorder = stub->showorder;
        res->skill->allow_land = stub->allow_land;
        res->skill->allow_air = stub->allow_air;
        res->skill->allow_water = stub->allow_water;
        res->skill->allow_ride = stub->allow_ride;
        res->skill->auto_attack = stub->auto_attack;
        res->skill->long_range = stub->long_range;
        res->skill->restrict_corpse = stub->restrict_corpse;
        res->skill->allow_forms = stub->allow_forms;
        res->skill->effect = stub->effect;
        res->skill->range.type = stub->range.type;
        res->skill->doenchant = stub->doenchant;
        res->skill->dobless = stub->dobless;
        res->skill->commoncooldown = stub->commoncooldown;
        res->skill->commoncooldowntime = stub->commoncooldowntime;

        res->skill->restrict_weapons.clear();
        for (size_t i = 0; i < stub->restrict_weapons.size(); i++)
        {
            res->skill->restrict_weapons.push_back(stub->restrict_weapons[i]);
        }

        res->skill->pre_skills.clear();
        for (size_t i = 0; i < stub->pre_skills.size(); i++)
        {
            res->skill->pre_skills.push_back(stub->pre_skills[i]);
        }

        s->Destroy();
    }
    return res;
}



char __fastcall MainApi::CgameSendPacket(void* base, void* it, unsigned int size)
{
    return ASM::CgameSendPacket(base, it, size);
}

long long __fastcall MainApi::CgameRecvPacket(void* base, int type, void* it, unsigned int size)
{
    long long res = ASM::CgameRecvPacket(base, type, it, size);
    res = Packet::GetInstance()->OnGameDataRecv(type, it, size, res);
    return res;
}

char __fastcall MainApi::CnetSendPacket(void* base, void* it, char c)
{
    if (((Packet*)it)->OnSend()) return 0;
    return ASM::CnetSendPacket(base, it, c);
}

char __fastcall MainApi::CnetRecvPacket(void* base, void* it)
{
    if (((Packet*)it)->OnRecv()) return 0;
    return ASM::CnetRecvPacket(base, it);
}

char __fastcall MainApi::ClickButton(void* base, const char* str)
{
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] BUTTON: cmd = %s \n", GetTimeStr(), str);
        GetInstance()->Log(Src);
    }

    if (*(int*)str == 1601008481/*asm_*/)
    {
        Interfaces::GetInstance()->OnClick(str);
    }
    
    return ASM::ClickButton(base, str);
}

int __fastcall MainApi::PvPPause(void* RCX, int iSevTime, int iTimeZoneBias, int pvp)
{
    return ASM::PvPPause(RCX, iSevTime, iTimeZoneBias, 0);
}

void* __fastcall MainApi::GetNPC(void* RCX, int nid, int born)
{
    void* res = ASM::GetNPC(RCX, nid, born);
    if (!res)
    {
        res = NpcRemote::GetInstance()->GetNPCbyID(nid);
    }
    return res;
}

int __fastcall MainApi::GetItemCount(void* inv, int item_id)
{
    int res = ASM::GetItemCount(inv, item_id);

    if (res < 1)
    {
        for (size_t i = 0; free_items[i] && i < 128; i++)
        {
            if (item_id == free_items[i])
            {
                res++;
                break;
            }
        }
    }
    return res;
}

void* __fastcall MainApi::ElsePlayerEnter(void* RCX, int* Info, int iCmd)
{
    void* res = ASM::ElsePlayerEnter(RCX, Info, iCmd);
    S2C::INFO::player_info_1* pInfo = (S2C::INFO::player_info_1*)Info;
    Gobject::GetInstance()->Create(Gobject::PLAYER_POOL, pInfo->cid, res);
    Packet::GetInstance()->GetMainInfo(pInfo->cid);
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] ElsePlayerEnter: roleid = %d \n", GetTimeStr(), pInfo->cid);
        GetInstance()->Log(Src);
    }
    return res;
}

void __fastcall MainApi::ElsePlayerLeave(void* RCX, int cid, bool bExit, bool bUpdateMMArray)
{
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] ElsePlayerLeave: roleid = %d \n", GetTimeStr(), cid);
        GetInstance()->Log(Src);
    }
    Gobject::GetInstance()->Destroy(Gobject::PLAYER_POOL, cid);
    ASM::ElsePlayerLeave(RCX, cid, bExit, bUpdateMMArray);
}

int __fastcall MainApi::GetColorName(void* RCX)
{
    int res = ASM::GetColorName(RCX);
    GameColorName* name = GameColorName::GetInstance();

    if (name->GetEnable() && (*(size_t*)RCX == CONFIG::EC_HOSTPLAYER || *(size_t*)RCX == CONFIG::EC_ELSEPLAYER))
    {
        GPlayer* pImp = (GPlayer*)RCX;
        int ColorName = Gobject::GetInstance()->GetPlayerInfo(pImp->GetId())->colot_name;
        if (ColorName)
        {
            res = name->GetColorName(ColorName);
        }
    }

    return res;
}

bool __fastcall MainApi::IsFashionWeaponTypeFit(int weapon_type, int fashion_weapon_type)
{
    return GetInstance()->fashion_weapon_enable ? ASM::IsFashionWeaponTypeFit(weapon_type, fashion_weapon_type) : false;
}

void* __fastcall MainApi::ResponseMarshal(void* RCX, void* Buf, void* v1, void* v2, char v3)
{
    GNET::Response* response = (GNET::Response*)RCX;
    Regid* Key = Regid::GetInstance();
    Key->Init();

    unsigned long long* aresp = (unsigned long long*)response->response.begin;
    unsigned long long* ahwid = (unsigned long long*)Key->WhGet();
    aresp[0] ^= ahwid[0];
    aresp[1] ^= ahwid[0];

    void* res = ASM::ResponseMarshal(RCX, Buf, v1, v2, v3);
    ASM_PaketPushCuint(Buf, Key->WhSize());
    ASM_PaketPushMem(Buf, Key->WhGet(), Key->WhSize());

    return res;
}

//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
//----------------MAIN API WIN 32
//--------------------------------------------------------------------------

int __cdecl MainApi::GetRequiredBook(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredBook();
        s->Destroy();
    }
    else
    {
      res = ((int(__cdecl*)(unsigned int, int))Skill.GetRequiredBook)(id, level);
    }
    return res;
}

int __cdecl MainApi::GetRequiredMoney(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredMoney();
        s->Destroy();
    }
    else
    {
        res = ((int(__cdecl*)(unsigned int, int))Skill.GetRequiredMoney)(id, level);
    }
    return res;
}

int __cdecl MainApi::GetRequiredSp(unsigned int id, int level)
{
    int res = 0;
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s)
    {
        res = s->GetRequiredSp();
        s->Destroy();
    }
    else
    {
        res = ((int(__cdecl*)(unsigned int, int))Skill.GetRequiredSp)(id, level);
    }
    return res;
}

int __cdecl MainApi::SkillCondition(unsigned int id, GNET::UseRequirement& info, int ilevel)
{
    int res = ((int(__cdecl*)(unsigned int, struct GNET::UseRequirement&, int))Skill.Condition)(id, info, ilevel);
    GNET::Skill* s = GNET::Skill::Create(id, ilevel);
    if (s)
    {
        res = s->Condition(id, info, ilevel);
        s->Destroy();
    }
    return res;
}

void* __cdecl MainApi::SkillCreate(unsigned int id, int level)
{
    GPARSER::CSKILL* res = ((GPARSER::CSKILL * (__cdecl*)(unsigned int, int))Skill.Create)(id, level);
    GNET::Skill* s = GNET::Skill::Create(id, level);
    if (s && res)
    {
        const GNET::SkillStub* stub = s->GetStub();
        res->skill->cls = stub->cls;
        res->skill->max_level = stub->max_level;
        res->skill->type = stub->type;
        res->skill->apcost = stub->apcost;
        res->skill->arrowcost = stub->arrowcost;
        res->skill->apgain = stub->apgain;
        res->skill->attr = stub->attr;
        res->skill->rank = stub->rank;
        res->skill->eventflag = stub->eventflag;
        res->skill->is_senior = stub->is_senior;
        res->skill->clslimit = stub->clslimit;
        res->skill->time_type = stub->time_type;
        res->skill->showorder = stub->showorder;
        res->skill->allow_land = stub->allow_land;
        res->skill->allow_air = stub->allow_air;
        res->skill->allow_water = stub->allow_water;
        res->skill->allow_ride = stub->allow_ride;
        res->skill->auto_attack = stub->auto_attack;
        res->skill->long_range = stub->long_range;
        res->skill->restrict_corpse = stub->restrict_corpse;
        res->skill->allow_forms = stub->allow_forms;
        res->skill->effect = stub->effect;
        res->skill->range.type = stub->range.type;
        res->skill->doenchant = stub->doenchant;
        res->skill->dobless = stub->dobless;
        res->skill->commoncooldown = stub->commoncooldown;
        res->skill->commoncooldowntime = stub->commoncooldowntime;

        res->skill->restrict_weapons.clear();
        for (size_t i = 0; i < stub->restrict_weapons.size(); i++)
        {
            res->skill->restrict_weapons.push_back(stub->restrict_weapons[i]);
        }

        res->skill->pre_skills.clear();
        for (size_t i = 0; i < stub->pre_skills.size(); i++)
        {
            res->skill->pre_skills.push_back(stub->pre_skills[i]);
        }

        s->Destroy();
    }
    return res;
}


int __fastcall MainApi::CgameSendPacket(void* ECX, void* EDX, void * it, size_t size)
{
    return ASM::CgameSendPacket(ECX, EDX, it, size); //ASM_SendPacket(it, size);
}

int _stdcall MainApi::CgameRecvPacket(int type, void * it, int size)
{
    int res = ASM::CgameRecvPacket(type, it, size);
    res = Packet::GetInstance()->OnGameDataRecv(type, it, size, res);
    return res;
}

int __fastcall MainApi::CnetSendPacket(void* ECX, void* EDX, void* it, int size)
{
    if (((Packet*)it)->OnSend()) return 0;
    return ASM::CnetSendPacket(ECX, EDX, it, size);
}

int __fastcall MainApi::CnetRecvPacket(void* ECX, void* EDX, void* it)
{
    if ( ((Packet*)it)->OnRecv() ) return 0;
    return ASM::CnetRecvPacket(ECX, EDX, it);
}


int __fastcall MainApi::ClickButton(void* ECX, void* EDX, char* str)
{
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] BUTTON: cmd = %s \n", GetTimeStr(), str);
        GetInstance()->Log(Src);
    }

    if (*(int*)str == 1601008481/*asm_*/)
    {
        Interfaces::GetInstance()->OnClick(str);
    }

    return ASM_ClickButton(ECX, EDX, str);
}

int __fastcall MainApi::PvPPause(void * ECX, void* EDX, int iSevTime, int iTimeZoneBias, int pvp)
{
    return ((int(__fastcall*)(void*, void*, int, int, int))0x009E26C0)(ECX, EDX, iSevTime, iTimeZoneBias, 0 );
}

void* __fastcall MainApi::GetNPC(void* ECX, void* EDX, int nid, int born)
{
    void* res = ASM::GetNPC(ECX, EDX, nid, born);
    if (!res)
    {
        res = NpcRemote::GetInstance()->GetNPCbyID(nid);
    }
    return res;
}

int __fastcall MainApi::GetItemCount(void* inv, void* EDX, int item_id)
{
    int res = ASM::GetItemCount(inv, EDX, item_id);
    
    if (res < 1)
    {
        for (size_t i = 0; free_items[i] && i < 128; i++)
        {
            if (item_id == free_items[i])
            {
                res++;
                break;
            }
        }
    }
    return res;
}

void * __fastcall MainApi::ElsePlayerEnter(void* ECX, void* EDX, int* Info, int iCmd)
{
    void * res = ASM::ElsePlayerEnter(ECX, EDX, Info, iCmd);
    S2C::INFO::player_info_1* pInfo = (S2C::INFO::player_info_1*)Info;
    Gobject::GetInstance()->Create(Gobject::PLAYER_POOL, pInfo->cid , res);
    Packet::GetInstance()->GetMainInfo(pInfo->cid);
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] ElsePlayerEnter: roleid = %d \n", GetTimeStr(), pInfo->cid);
        GetInstance()->Log(Src);
    }
    return res;
}

void __fastcall MainApi::ElsePlayerLeave(void* ECX, void* EDX, int cid, bool bExit, bool bUpdateMMArray)
{
    if (logs)
    {
        char Src[256];
        sprintf_s(Src, "[%.24s] ElsePlayerLeave: roleid = %d \n", GetTimeStr(), cid);
        GetInstance()->Log(Src);
    }
    Gobject::GetInstance()->Destroy(Gobject::PLAYER_POOL, cid);
    ASM::ElsePlayerLeave(ECX,EDX,cid,bExit,bUpdateMMArray);
}

int __fastcall MainApi::GetColorName(void* ECX, void* EDX)
{
    int res = ASM::GetColorName(ECX, EDX);
    GameColorName* name = GameColorName::GetInstance();

    if (name->GetEnable() && (*(size_t*)ECX == CONFIG::EC_HOSTPLAYER || *(size_t*)ECX == CONFIG::EC_ELSEPLAYER))
    {
        GPlayer* pImp = (GPlayer*)ECX;
        int ColorName = Gobject::GetInstance()->GetPlayerInfo(pImp->GetId())->colot_name;
        if (ColorName)
        {
            res = name->GetColorName(ColorName);
        }
    }

    return res;
}

bool __cdecl MainApi::IsFashionWeaponTypeFit(int weapon_type, int fashion_weapon_type)
{
    return GetInstance()->fashion_weapon_enable ? ASM::IsFashionWeaponTypeFit(weapon_type, fashion_weapon_type) : false;
}

void* __fastcall MainApi::ResponseMarshal(void* ECX, void* EDX, void* Buf)
{
    GNET::Response* response = (GNET::Response*)ECX;
    Regid* Key = Regid::GetInstance();
    Key->Init();

    unsigned long long* aresp = (unsigned long long*)response->response.begin;
    unsigned long long* ahwid = (unsigned long long*)Key->WhGet();
    aresp[0] ^= ahwid[0];
    aresp[1] ^= ahwid[0];

    void* res = ASM::ResponseMarshal(ECX, EDX, Buf);
    ASM_PaketPushCuint(Buf, Key->WhSize());
    ASM_PaketPushMem(Buf, Key->WhGet(), Key->WhSize());

    return res;
}


//--------------------------------------------------------------------------
#endif

//--------------------------------------------------------------------------
//--patch functions
//--------------------------------------------------------------------------

void MainApi::Patch(size_t type)
{
#ifdef _WIN64
    switch (type)
    {
        case TEXT:
        {
            setup_uchar(0x0000000140B176AB, 0xEB); //принудительный запуск
            setup_farjmp(0x0000000140B4A587, 0x0000000140B4A82B); //вырезаем старую версию
            setup_uchar(0x0000000140794600, 0xC3); //вырезаем пвп паузу
            
            setup_farjmp64(0x0000000140B56C90, CgameSendPacket); //игрок отправляет пакет на gs
            setup_farjmp64(0x0000000140B31F50, CgameRecvPacket); //игрок получает пакет от gs
            setup_farjmp64(0x0000000140B56DF0, CnetSendPacket); //игрок отправляет пакет на сервер
            setup_farjmp64(0x0000000140B3F2C0, CnetRecvPacket); //игрок получает пакет с сервера
            setup_farjmp64(0x0000000140B5DAD0, ResponseMarshal); //Запаковка пакета с авторизацией

            setup_farjmp64(0x0000000140E3D580, ClickButton); //игрок нажал кнопку
            setup_farjmp64(0x0000000140794600, PvPPause); //фикс пвп паузы + фикс таймера квестов

            setup_farjmp64(0x000000014098B650, ElsePlayerEnter); //персонаж появился в поле зрения игрока
            setup_farjmp64(0x000000014098B790, ElsePlayerLeave); //персонаж пропал с поля зрения игрока

            setup_farjmp64(0x00000001409F3AC0, GetColorName); //определить цвет ника

            //макс колличество квестов
            setup_uchar(0x00000001406273A3, CONFIG::QUEST_DEF);
            setup_uchar(0x00000001406273A8, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);

            setup_uchar(0x0000000140C59A85, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
            setup_uchar(0x0000000140C59A90, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF + CONFIG::QUEST_NEW);
            setup_uchar(0x0000000140C59ACF, CONFIG::QUEST_DEF);
            setup_uchar(0x0000000140C59ADB, CONFIG::QUEST_DEF);
            setup_uchar(0x0000000140C59AE5, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);

            setup_uchar(0x0000000140C5FCE0, CONFIG::QUEST_DEF);
            setup_uchar(0x0000000140C5FCBB, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
            setup_uchar(0x0000000140C5FCF6, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF + CONFIG::QUEST_NEW);

            setup_uchar(0x000000014062DB91, CONFIG::QUEST_DEF);
            setup_uchar(0x000000014062DB9D, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);

            //телепортация через новую руну телепорта
            setup_farjmp64(0x0000000140A6F3B1, ASM::TransportLocations);

            //фикс наценки
            setup_farjmp64(0x000000014097F5F0, GetNPC);

            //фикс дистанционного магазина
            setup_fillmem(0x00000001408D6541, 0x90, 6);

            //фикс вылета при заточке
            setup_farjmp64(0x00000001403B79D6, ASM::FixNpcRefine);
 
            //делаем бесконечный зум
            setup_uchar(0x00000001406EA23F, 0xEB);

            //делаем спидстарт
            setup_ushort(0x00000001408A744E, 0x9090);

            //разрешаем пользоваться любыми горнами
            setup_farjmp64(0x0000000140904440, GetItemCount);

            break;
        }
        case RDATA:
        {
            break;
        }
        case IDATA:
        {
            //Skill.init(0x000000014108E088, Skill.GetRequiredBook, (size_t)GetRequiredBook);
            //Skill.init(0x000000014108E1D8, Skill.GetRequiredMoney, (size_t)GetRequiredMoney);
            //Skill.init(0x000000014108E1E0, Skill.GetRequiredSp, (size_t)GetRequiredSp);
            //Skill.init(0x000000014108E0A8, Skill.Condition, (size_t)SkillCondition);
            //Skill.init(0x000000014108E108, Skill.Create, (size_t)SkillCreate);
            break;
        }
        default: break;
    }
#else //_WIN32
    switch (type)
    {
    case TEXT:
    {
        setup_uchar(0x00C98F9D, 0xEB); //принудительный запуск
        setup_farjmp(0x00CC315B, 0x00CC338E); //вырезаем старую версию

        setup_farjmp(0x00CD1910, ResponseMarshal); //Запаковка пакета с авторизацией  

        setup_farjmp(0x00CCDB30, CgameSendPacket); //игрок отправляет пакет на gs
        setup_farjmp(0x00CAD8B0, CgameRecvPacket); //игрок получает пакет от gs
        setup_farjmp(0x00CCDC60, CnetSendPacket); //игрок отправляет пакет на сервер
        setup_farjmp(0x00CBAB60, CnetRecvPacket); //игрок получает пакет с сервера

        setup_farjmp(0x00B73390, ElsePlayerEnter); //персонаж появился в поле зрения игрока
        setup_farjmp(0x00B73500, ElsePlayerLeave); //персонаж пропал с поля зрения игрока

        setup_farjmp(0x00BC20F0, GetColorName); //определить цвет ника

        setup_call(0x00660011, ClickButton); //игрок нажал кнопку
        setup_call(0x00F3906E, ClickButton); //игрок нажал кнопку


        setup_call(0x0095A0F6, PvPPause); //фикс пвп паузы + фикс таймера квестов
        setup_call(0x009EA69E, PvPPause); //фикс пвп паузы + фикс таймера квестов
        setup_call(0x00CC2540, PvPPause); //фикс пвп паузы + фикс таймера квестов
        setup_call(0x00CCA332, PvPPause); //фикс пвп паузы + фикс таймера квестов

        //макс колличество квестов
        setup_uchar(0x008C7948, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x008C7951, CONFIG::QUEST_DEF);

        setup_uchar(0x00D90BF9, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x00D90BFE, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF + CONFIG::QUEST_NEW);
        setup_uchar(0x00D90C41, CONFIG::QUEST_DEF);
        setup_uchar(0x00D90C54, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x00D90C59, CONFIG::QUEST_DEF);

        setup_uchar(0x00D9631A, CONFIG::QUEST_DEF);
        setup_uchar(0x00D96325, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x00D96333, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x00D9634A, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF + CONFIG::QUEST_NEW);

        setup_uchar(0x008CC8FA, CONFIG::QUEST_ADD + CONFIG::QUEST_DEF);
        setup_uchar(0x008CC903, CONFIG::QUEST_DEF);

        //телепортация через новую руну телепорта
        setup_void(0x00C23E4F, TransportTag);
        setup_void(0x00C23E9B, (TransportTag + TransportTagSize));

        //фикс дистанционного магазина
        setup_fillmem(0x00AE746A, 0x90, 6);

        //фикс вылета при заточке
        setup_farjmp(0x006D590A, ASM::FixNpcRefine);

        //делаем бесконечный зум
        setup_uchar(0x0095F5E3, 0xEB);

        //делаем спидстарт
        setup_ushort(0x00ABFB6B, 0x9090);

        //фикс наценки
        setup_farjmp(0x00B6A630, GetNPC);

        //разрешаем пользоваться любыми горнами
        setup_farjmp(0x00B0C160, GetItemCount);

        //проверка на использование стиль пухи
        setup_farjmp(0x00BC38C0, IsFashionWeaponTypeFit);

        //версия и билд 
        //setup_int(0x0133DCCC, 4999);
        //setup_int(0x0133DCC8, 132866);


        break;
    }
    case RDATA:
    {
        setup_void(0x011F45E0, ClickButton); //игрок нажал кнопку
        setup_void(0x011FFE48, ClickButton); //игрок нажал кнопку
        break;
    }
    case IDATA:
    {
        //Skill.init(0x0111D044, Skill.GetRequiredBook, (size_t)GetRequiredBook);
        //Skill.init(0x0111D0EC, Skill.GetRequiredMoney, (size_t)GetRequiredMoney);
        //Skill.init(0x0111D0F0, Skill.GetRequiredSp, (size_t)GetRequiredSp);
        //Skill.init(0x0111D06C, Skill.Condition, (size_t)SkillCondition);
        //Skill.init(0x0111D084, Skill.Create, (size_t)SkillCreate);

        break;
    }
    default: break;
    }
#endif
}

