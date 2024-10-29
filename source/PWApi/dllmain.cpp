// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <stdio.h>
#include "Header/config.h"
#include "Header/main.h"




DWORD __stdcall ThreadRelease(LPVOID thparam)
{
    static size_t tick = 0;
    MainApi* main = MainApi::GetInstance();
    while (true)
    {
        main->HeartBeat(tick);
        Sleep(50);
        tick++;
    }
}

void RebuildRelease(size_t type)
{
    MainApi* main = MainApi::GetInstance();
    DWORD dwOldProtect;
    size_t SECTION_BEGIN = 0;
    size_t SECTION_SIZE = 0;
    char Src[256];

    switch (type)
    {
    case MainApi::TEXT:  { SECTION_BEGIN = CONFIG::SECTION_TEXT_BEGIN; SECTION_SIZE  = CONFIG::SECTION_TEXT_SIZE;  break; }
    case MainApi::RDATA: { SECTION_BEGIN = CONFIG::SECTION_RDATA_BEGIN; SECTION_SIZE = CONFIG::SECTION_RDATA_SIZE; break; }
    case MainApi::IDATA: { SECTION_BEGIN = CONFIG::SECTION_IDATA_BEGIN; SECTION_SIZE = CONFIG::SECTION_IDATA_SIZE; break; }
    default: break;
    }

    if (SECTION_BEGIN && SECTION_SIZE)
    {
        if (!VirtualProtect((LPVOID)SECTION_BEGIN, SECTION_SIZE, PAGE_EXECUTE_READWRITE, &dwOldProtect) && main->GetLog())
        {
            sprintf_s(Src, "VirtualProtect - Error Code: %d \n", GetLastError());
            main->Log(Src);
        }
        main->Patch(type);
        if (!VirtualProtect((LPVOID)SECTION_BEGIN, SECTION_SIZE, dwOldProtect, NULL) && main->GetLog())
        {
            sprintf_s(Src, "VirtualProtect - Error Code: %d \n", GetLastError());
            main->Log(Src);
        }
    }

}

void InjectRelease()
{
    MainApi* main = MainApi::GetInstance();
    LPVOID lpParameter = NULL;
    DWORD ThreadId = 0;

    //инициализация классов
    main->Init();

    //создание потока
    CreateThread(0, 0, ThreadRelease, lpParameter, 0, &ThreadId);

    //патчинг функций
    RebuildRelease(MainApi::TEXT);
    RebuildRelease(MainApi::RDATA);
    RebuildRelease(MainApi::IDATA);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        InjectRelease();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

__declspec(dllexport) void PWApi()
{
#ifdef _WIN64
    LoadLibrary(L"PWApi_64.dll");
#else
    LoadLibrary(L"PWApi.dll");
#endif
}
