
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

#include "../Header/common/A3DMacros.h"
#include "../Header/asm.h"
#include "../Header/autoswap.h"
#include "../Header/gobject.h"
#include "../Header/player.h"
#include "../Header/packet.h"
#include "../Header/colorname.h"
#include "../Header/main.h"
#include "../Header/interfaces.h"



Interfaces* Interfaces::instance = 0;

void Interfaces::Init()
{
    chFile = L"./userdata/ColorName.ini";
    instance_timer = 0;
    timer_enable = false;
    cur_hp = 0;
    max_hp = 0;
    cur_level = 0;
}

void Interfaces::HeartBeat(size_t tick)
{
    if (timer_enable)
    {
        if (!(tick % 20))
        {
            InsRefreshOnTick();
        }

        if (!(tick % 2))
        {
            HpMpOtherBOnTick();
        }
    }
}

void Interfaces::InsRefreshOnTick()
{
    if (instance_timer)
    {
        if (instance_timer > CONFIG::REFRESH_INS_TIMER)
            instance_timer = CONFIG::REFRESH_INS_TIMER;
        if (instance_timer < 0)
            instance_timer = 0;

        if (instance_timer > 0)
            instance_timer--;
        SetInsTimer(instance_timer);
    }
}

void Interfaces::HpMpOtherBOnTick()
{
    GPlayer* pElse = GetElsePlayer(0);
    if (pElse && pElse->GetId() >= 1024)
    {
        if (cur_level != pElse->GetLevel())
        {
            cur_level = pElse->GetLevel();
            SetTargetLevel(cur_level);
        }
        
        if (cur_hp != pElse->GetHp() || max_hp != pElse->GetMaxHp())
        {
            cur_hp = pElse->GetHp();
            max_hp = pElse->GetMaxHp();
            SetTargetHP(cur_hp, max_hp);
        }
    }
}

int Interfaces::Btn_c2scmd(const char* str)
{
    char Src[12];
    setup_fillmem(Src, 0x00, 12);
    setup_copymem(Src, str, 10);
    if (!strcmp(Src, "asm_c2scmd"))
    {
        short cmd = atoi(str + 11);
        Packet::GetInstance()->GameDataSend(cmd);
        return 1;
    }
    return 0;
}

void* Interfaces::GetInGameUIMan()
{
    if ((size_t)GetCECBase() > CONFIG::VAL_ADDRESS &&
        (size_t)GetCECBase()->g_pGame > CONFIG::VAL_ADDRESS &&
        (size_t)GetCECBase()->g_pGame->m_pGameRun > CONFIG::VAL_ADDRESS &&
        (size_t)GetCECBase()->g_pGame->m_pGameRun->m_pUIManager > CONFIG::VAL_ADDRESS
        )
    {
        CECUIManager* AUI = GetCECBase()->g_pGame->m_pGameRun->m_pUIManager;
        return !AUI->m_pCurUIMan || AUI->m_iCurUIMan != 1 ? NULL : AUI->m_pCurUIMan;
    }
    return NULL;
}

void* Interfaces::GetDialog(const char * str)
{
    void* UI = GetInGameUIMan();
    if (UI)
    {
        return ASM_GetDialog(UI, str);
    }
    return NULL;
}

bool Interfaces::ShowDialog(const char* str)
{
    bool res = false;
    void * AUI = GetInGameUIMan();
    if (AUI)
    {
        void* DIALOG = ASM_GetDialog( AUI, str);
        if (DIALOG)
        {
            ASM_ShowDialog(DIALOG);
            res = true;
        }
    }
    return res;
}

void* Interfaces::GetDlgItem(void* DIALOG, const char * label)
{
    if (DIALOG)
    {
        void* LABEL = ASM_SearchLabel(DIALOG, LABEL, label);
        return LABEL;
    }
    return NULL;
}

void Interfaces::SetSelfProperty(int * property)
{
    char dest[0x40];
    wchar_t Str[40];

    void* DIALOG = GetDialog("Win_Character");
    if (  DIALOG )
    {
        for (size_t i = 0; i < CONFIG::NEW_PROPERTY_COUNT; i++)
        {
            sprintf_s(dest, "Lab_Value%d", i);
            AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, dest);
            if (Label)
            {
                _itow_s(property[i], Str, 10);
                Label->SetText(Str);
            }
        }
    }
}

bool Interfaces::InsRefreshCmd()
{
    if (instance_timer) return false;
    instance_timer = CONFIG::REFRESH_INS_TIMER;
    Packet::GetInstance()->GameDataSend(Packet::CMD_INSTANCE_REFRESH);
    return true;
}

void Interfaces::DistanceNpcShop(int it)
{
    NpcRemote * nr = NpcRemote::GetInstance();
    void* Win_Shop = GetDialog("Win_Shop");
    if (Win_Shop)
    {
        nr->Create(CONFIG::ID_NPC_REMOTE, 0);
        GPlayer* pImp = GetPlayer();
        pImp->PrepareNPCService(it);
        pImp->SetTargetNPCId(nr->GetNPCid(0));
        ASM_NpcListUpdate(Win_Shop);
        ASM_ShowDialog(Win_Shop);
    }

    void* Win_Inventory = GetDialog("Win_Inventory");
    if (Win_Inventory)
    {
        ASM_ShowDialog(Win_Inventory);
    }

}

void Interfaces::ArenaSetInfo(const char * lab, int value)
{
    void* DIALOG = GetDialog("Win_ArenaTeam");
    if (DIALOG)
    {
        AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, lab);
        if (Label)
        {
            wchar_t Str[40];
            _itow_s(value, Str, 10);
            Label->SetText(Str);
        }
    }
}

void Interfaces::SetInsTimer(int ins_timer)
{
    void* DIALOG = GetDialog("Win_Map");
    if (DIALOG)
    {
        AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, "asm_instimer");
        if (Label)
        {
            wchar_t Str[40];
            _itow_s(ins_timer, Str, 10);
            Label->SetText(Str);
        }
    }
}

void Interfaces::SetTargetLevel(int level)
{
    void* DIALOG = GetDialog("Win_HpmpOtherB");
    if (DIALOG)
    {
        AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, "Txt_Level");
        if (Label)
        {
            wchar_t Str[40];
            _itow_s(level, Str, 10);
            Label->SetText(Str);
        }
    }
}

void Interfaces::SetTargetHP(int hp, int max_hp)
{
    void* DIALOG = GetDialog("Win_HpmpOtherB");
    if (DIALOG)
    {
        AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, "Txt_HP");
        if (Label)
        {
            wchar_t Str[40];
            swprintf_s(Str, L"%d/%d", hp, max_hp);
            Label->SetText(Str);
        }
    }
}

void Interfaces::SetStging(const char * win_dlg, const char * label, const wchar_t * value)
{
    void* DIALOG = GetDialog(win_dlg);
    if (DIALOG)
    {
        AUILabel* Label = (AUILabel*)GetDlgItem(DIALOG, label);
        if (Label)
        {
            Label->SetText(value);
        }
    }
}



void Interfaces::OnClick(const char * str)
{
    if (Btn_c2scmd(str)) return;
    Packet* RPC = Packet::GetInstance();

    //other
    if (!strcmp(str, "asm_roleoff")) { RPC->GameDataSend(Packet::CMD_OFFLINE_ROLE); return; } //перс офлайн
    if (!strcmp(str, "asm_catoff")) { RPC->GameDataSend(Packet::CMD_OFFLINE_CAT); return; } //кот офлайн
    if (!strcmp(str, "asm_npcshop")) { DistanceNpcShop(CONFIG::ID_NPCSHOP); return; } //карманный магазин за юани
    if (!strcmp(str, "asm_instrefresh")) { InsRefreshCmd(); return; } //обновить локации 
    if (!strcmp(str, "asm_bank")) { ASM_SendBank(); return; } //банк
    //if (!strcmp(str, "asm_radius")) { RadiusFixed(); return; } //увеличить радиус обзора
    //inventory
    if (!strcmp(str, "asm_mail")) { ShowDialog("Win_MailList"); return; } //почта
    if (!strcmp(str, "asm_refine")) { ShowDialog("Win_EquipRefine");  return; } //заточка
    if (!strcmp(str, "asm_addenchase")) { ShowDialog("Win_EquipSlot");  return; } //сделать дырку 
    if (!strcmp(str, "asm_enchase")) { ShowDialog("Win_Enchase");  return; } //вплавить камень
    if (!strcmp(str, "asm_disenchase")) { ShowDialog("Win_Disenchase"); return; } //очистить камни
    if (!strcmp(str, "asm_money")) { RPC->GameDataSend(Packet::CMD_MONEY); return; } //сконвертить юаньки в чек
    if (!strcmp(str, "asm_moneys")) { RPC->GameDataSend(Packet::CMD_MONEYS); return; } //сконвертить все юани в чеки
    //pet_cell
    if (!strcmp(str, "asm_pethatch")) { ShowDialog("Win_PetHatch"); return; } //приручить пета
    if (!strcmp(str, "asm_petrec")) { ShowDialog("Win_PetRec"); return; } //восстановить пета
    if (!strcmp(str, "asm_petrename")) { ShowDialog("Win_PetRename"); return; } //сменить имя пету
    //skillsender
    //if (!strcmp(str, "asm_skillset")) { skill.set(); return; } //записать скиллы которые кинул
    //if (!strcmp(str, "asm_skillsender")) { skill.server_start(); return; } //запустить скрипт
    //if (!strcmp(str, "asm_skillfilter")) { skill.change_filter(); return; } //кидать бафы на себя/на других
    //if (!strcmp(str, "asm_skillmod")) { skill.change_script(); return; } //включить пакетный режим кидания скиллов
    //configs
    //if (!strcmp(str, "asm_autoattack")) { off_autoatack ^= 1; return; } //вкл/выкл автоатаку
    //if (!strcmp(str, "asm_offfreez")) { off_freez ^= 1; return; } //выключить фриз неактивного окна
    if (!strcmp(str, "asm_offweapon")) { MainApi::GetInstance()->ChkFashionWeapon(); return; } //выключить стиль пухи
    
    //if (!strcmp(str, "asm_offface")) { off_face ^= 1; return; } //выключить причёски
    //autoswap
    if (!strcmp(str, "asm_swapsend")) { AutoSwap::GetInstance()->Change(); return; }

    //Color Name
    if (!strcmp(str, "asm_offname")) { GameColorName::GetInstance()->ChkEnable(); return; } //выключить цв ники

    //ArenaManager
    if (!strcmp(str, "asm_arena_quit")) { RPC->GameDataSend(Packet::ARENA_CMD_QUIT); return; } //выйти с арены
    if (!strcmp(str, "asm_arena_join_1x1")) { Packet::GetInstance()->ArenaJoin(Packet::ARENA_MODE_1X1); return; } //бои 1х1
    if (!strcmp(str, "asm_arena_join_3x3")) { Packet::GetInstance()->ArenaJoin(Packet::ARENA_MODE_3X3); return; } //бои 3х3
    if (!strcmp(str, "asm_arena_join_6x6")) { Packet::GetInstance()->ArenaJoin(Packet::ARENA_MODE_6X6); return; } //бои 6х6
    if (!strcmp(str, "asm_arena_query")) { RPC->GameDataSend(Packet::ARENA_CMD_QUERY); return; } // получить параметры арены

    if (ShowDialog(str+4)) { return; }
}

void Interfaces::AUILabel::SetText(const wchar_t* pszText)
{
    ASM_SetText(this, pszText);
}

const wchar_t* Interfaces::AUILabel::GetText()
{
    return ASM_GetText(this);
}

void Interfaces::LoadName()
{
    /*
    wchar_t chBuff[256];
    wchar_t szText[40];
    int r, g, b, a;

    memset(chBuff, 0x00, sizeof(chBuff));
    memset(szText, 0x00, sizeof(szText));
    DDX_Control("List_ColorName", m_pLstColors);
    m_pLstColors->ResetContent();

    size_t count = GetPrivateProfileInt(L"configs", L"count", 0, chFile);

    for (size_t i = 0; i < count; i++)
    {
        swprintf(szText, L"name_%d", i);
        GetPrivateProfileString(szText, L"name", L"", chBuff, sizeof(chBuff), chFile);

        m_pLstColors->AddString(chBuff);

        r = GetPrivateProfileInt(szText, L"color_r", 0, chFile);
        g = GetPrivateProfileInt(szText, L"color_g", 0, chFile);
        b = GetPrivateProfileInt(szText, L"color_b", 0, chFile);
        a = GetPrivateProfileInt(szText, L"color_a", 0, chFile);
        if (r || g || b)
        {
            unsigned int cl = A3DCOLORRGB(r, g, b);
            m_pLstColors->SetItemTextColor(m_pLstColors->GetCount() - 1, cl);
        }
        m_pLstColors->SetItemData(m_pLstColors->GetCount() - 1, SET_RGBA(r, g, b, a));
    }

    m_pLstColors->SetCurSel(-1);
    */
}