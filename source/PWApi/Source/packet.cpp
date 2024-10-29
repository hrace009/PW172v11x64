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

#include "../Header/config.h"
#include "../Header/asm.h"
#include "../Header/gobject.h"
#include "../Header/main.h"
#include "../Header/parser.h"
#include "../Header/informer.h"
#include "../Header/interfaces.h"
#include "../Header/autoswap.h"
#include "../Header/player.h"
#include "../Header/packet.h"

//Perfect World GS 
#include "../Header/common/types.h"
#include "../Header/common/protocol.h"

//Perfect World CNET
#include "../Header/cnet/callid.hxx"
#include "../Header/cnet/rpcdata.h"



Packet* Packet::instance = 0;

void Packet::Init()
{

}

void Packet::Log(const char* s)
{
    MainApi* main = MainApi::GetInstance();
    char Src[1600];

    sprintf_s(Src, "[%.24s] %s: type = %d, class = %s \n", main->GetTimeStr(), s, GetProtocol(), ClassInformer::GetInstance()->GetCnet(offt).str);
    main->Log(Src);
}

void Packet::Log(int c, unsigned short cmd, size_t size)
{
    MainApi* main = MainApi::GetInstance();
    char Src[1600];

    if (c == CGAME_SEND)
    {
        sprintf_s(Src, "[%.24s] GS_SEND: type = %d:%s, size = %d \n", main->GetTimeStr(), cmd, ClassInformer::GetInstance()->GetCGameSend(cmd), size);
    }
    else//== CGAME_RECV
    {
        sprintf_s(Src, "[%.24s] GS_RECV: type = %d:%s, size = %d \n", main->GetTimeStr(), cmd, ClassInformer::GetInstance()->GetCNameRecv(cmd), size);
    }
    main->Log(Src);
}

void Packet::Dump(int c, unsigned short cmd, void * buf, size_t size)
{
    static char Src[512];
    memset(Src, 0x00, sizeof(Src));
    if (c == CGAME_SEND)
    {
        sprintf_s(Src, "[SEND]%d_%s", cmd, ClassInformer::GetInstance()->GetCGameSend(cmd));
    }
    else//== CGAME_RECV
    {
        sprintf_s(Src, "[RECV]%d_%s", cmd, ClassInformer::GetInstance()->GetCNameRecv(cmd));
    }
    MainApi::GetInstance()->Dump(buf, size, (const char*)Src);
}


size_t Packet::OnSend()
{
    size_t res = 0; // 0 продолжить ; 1 прервать
    short Protocol = GetProtocol();

    switch (Protocol)
    {
    case GNET::ProtocolType::PROTOCOL_GAMEDATASEND:
    {
        GNET::GamedataSend* gds = (GNET::GamedataSend*)this;
        unsigned short cmd = *(unsigned short*)gds->data.begin;
        cmd = ASM_CMDEncore(cmd);
        res = OnGameDataSend( CGAME_SEND, cmd, gds->data.begin, gds->data.len() );
        return res;
        break;
    }
    case GNET::ProtocolType::PROTOCOL_GETUICONFIG:
        MainApi::GetInstance()->EnterWorld();
        break;
    case GNET::ProtocolType::PROTOCOL_SETUICONFIG:
        MainApi::GetInstance()->LeaveWorld();
        break;
    case GNET::ProtocolType::PROTOCOL_RESPONSE:
        //if (!Response(it)) return 0;
        break;
    case GNET::ProtocolType::PROTOCOL_FACTIONOPREQUEST:
        res = FactionOPRequest();
        break;
    default:
        break;
    }

    if (MainApi::GetInstance()->GetLog())
    {
        Log("NET_SEND");
    }
    if (Protocol <= 0 || Protocol >= CONFIG::PROTOCOL_END)
    {
        res = 1;
    }
	return res;
}

size_t Packet::OnRecv()
{
    size_t res = 0; // 0 продолжить ; 1 прервать
    short Protocol = GetProtocol();

    switch (Protocol)
    {
    case GNET::ProtocolType::PROTOCOL_GAMEDATASEND:
    {
        GNET::GamedataSend* gds = (GNET::GamedataSend*)this;
        res = OnGameDataSend( CGAME_RECV, *(unsigned short*)gds->data.begin, gds->data.begin, gds->data.len() );
        return res;
        break;
    }

    default:
        break;
    }

    if (MainApi::GetInstance()->GetLog())
    {
        Log("NET_RECV");
    }
    return res;
}

size_t Packet::OnGameDataSend(int c, unsigned short cmd, void* buf, size_t size)
{
    size_t res = 0; // 0 продолжить ; 1 прервать

    if (MainApi::GetInstance()->GetLog())
    {
        Log(c, cmd, size);
        Dump(c, cmd, buf, size);
    }

    switch (cmd)
    {
    case C2S::EQUIP_ITEM:
        EquipItem(buf, size);
        break;

    case 977:
        GetElsePlayerInfo();
        break;
    case 966:
        MainApi::GetInstance()->ChkFashionWeapon();
        break;
    case 988:
        Interfaces::GetInstance()->ShowDialog("Win_ColorName");
        break;
    case 911:
        MainApi::GetInstance()->ChangeLog();
        break;
    case 999:
        GPARSER::SKILL_STUBS_PARSER(6800, 200);
        break;
    case 900:
        NpcRemote::GetInstance()->Create(CONFIG::ID_NPC_REMOTE, 0);
        break;
    default:
        break;
    }

    return res;
}

size_t Packet::OnGameDataRecv(int type, void* it, int size, int result)
{
    GPlayer* pElse = NULL;

    switch (type)
    {
        case S2C::SELF_GET_EXT_PROPERTY:
        {
            result = Packet::GetInstance()->SelfGetExtProperty(it, result);
        }
        break;
        case ARENAQUERYINFO_RE:
        {
            result = Packet::GetInstance()->ArenaQueryInfoRe(it, result);
        }
        break;
        case GET_MAIN_INFO_OTHER_RE:
        {
            result = Gobject::GetInstance()->SetPlayerInfo(it, result);
        }
        break;
        default:
        {
            if (MainApi::GetInstance()->GetLog() && result != -2 && result != size)
            {
                char Src[80];
                sprintf_s(Src, "RECV_GS_PACKET_BUG!!!: type = %d, size = %d , resize = %d \n", type, size, result);
                GetInstance()->Log((const char*)Src);
                //result = -2;
            }
        }
        break;
    }

    return result;
}

size_t Packet::FactionOPRequest()
{
    size_t res = 0; // 0 продолжить ; 1 прервать
    GNET::FactionOPRequest * fopr = (GNET::FactionOPRequest*)this;
    if ( (fopr->optype & 0xffff) > 24) res = 1;
    return res;
}

void Packet::GameDataSend(void* Buf, size_t size)
{
    ASM_SendPacket(Buf,size);
}

void Packet::GameDataSend(short Buf)
{
    ASM_SendPacket(&Buf,sizeof(Buf));
}

int Packet::SelfGetExtProperty(void* Buf, int size)
{
    int new_property[CONFIG::NEW_PROPERTY_COUNT];
    int* pState = (int*)Buf + (size / sizeof(int));
    for (unsigned int i = 0; i < CONFIG::NEW_PROPERTY_COUNT; ++i)
    { 
        new_property[i] = pState[i];
    }
    Interfaces::GetInstance()->SetSelfProperty(new_property);
    return -2;
}

int Packet::ArenaQueryInfoRe(void* Buf, size_t size)
{
    if (size == sizeof(arena_query_info))
    {
        arena_query_info* acq = (arena_query_info*)Buf;
        Interfaces * ui = Interfaces::GetInstance();
        ui->ArenaSetInfo("asm_search_time", acq->search_time);
        ui->ArenaSetInfo("asm_self_score", acq->self_score);
        ui->ArenaSetInfo("asm_team_score", acq->team_score);
        ui->ArenaSetInfo("asm_win_count", acq->win_count);
        ui->ArenaSetInfo("asm_lose_count", acq->lose_count);
        return -2;
    }
    return -1;
}

void Packet::EquipItem(void* Buf, size_t size)
{
    if (size == sizeof(C2S::CMD::equip_item))
    {
        C2S::CMD::equip_item* ei = (C2S::CMD::equip_item*)Buf;
        AutoSwap::GetInstance()->Set(ei->idx_inv, ei->idx_eq);
    }
}

void Packet::GetMainInfo(int roleid)
{
    get_main_info gmi;
    gmi.cmd = GET_MAIN_INFO;
    gmi.roleid = roleid;
    GameDataSend(&gmi, sizeof(gmi));
}

void Packet::ArenaJoin(int mode)
{
    arena_join aj;
    aj.cmd = ARENA_CMD_JOIN;
    aj.mode = mode;
    GameDataSend(&aj, sizeof(aj));
}
