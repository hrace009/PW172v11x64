//-------------------------------------------------------------------------------------------------------------------------
//--ASM DATA (c) DEADRAKY 2022
//-------------------------------------------------------------------------------------------------------------------------
#ifndef _ASM_H_
#define _ASM_H_

#include "config.h"
#include "gobject.h"

namespace ASM
{

#define setup_call(address,dest) ((int*)((unsigned int)address + 1))[0] = (int)((unsigned int)dest - (unsigned int)(address + 5)); \
								 ((char*)address)[0] = 0xE8;

#define setup_farjmp(address,dest) ((int*)((size_t)address + 1))[0] = (int)((size_t)dest - (size_t)(address + 5)); \
									 ((char*)address)[0] = 0xE9;

#define setup_char(address,value) *(char*)address = value;
#define setup_uchar(address,value) *(unsigned char*)address = value;
#define setup_short(address,value) *(short*)address = value;
#define setup_ushort(address,value) *(unsigned short*)address = value;
#define setup_int(address,value) *(int*)address = value;
#define setup_uint(address,value) *(unsigned int*)address = value;
#define setup_float(address,value) *(float*)address = value;
#define setup_double(address,value) *(double*)address = value;
#define setup_void(address,value) *(void**)address = (void*)value;
#define setup_long(address,value) *(long long*)address = value;
#define setup_ulong(address,value) *(unsigned long long*)address = value;
#define setup_fillmem(address,value,size) memset((void*)address,value,size);
#define setup_copymem(address,value,size) memcpy((void*)address,value,size);
#define setup_size_t(address,value) *(size_t*)address = value;
#define get_int(address,offset) ( *(int*)( &((char*)address)[offset] )  )
#define get_uint(address,offset) ( *(unsigned int*)( &((char*)address)[offset] )  )
#define get_char(address,offset) ( *(char*)( &((char*)address)[offset] )  )
#define get_uchar(address,offset) ( *(unsigned char*)( &((char*)address)[offset] )  )
#define get_short(address,offset) ( *(short*)( &((char*)address)[offset] )  )
#define get_ushort(address,offset) ( *(unsigned short*)( &((char*)address)[offset] )  )
#define get_float(address,offset) ( *(float*)( &((char*)address)[offset] )  )
#define get_double(address,offset) ( *(double*)( &((char*)address)[offset] )  )
#define get_void(address,offset) ( *(void**)( &((char*)address)[offset] )  )
#define get_long(address,offset) ( *(long long*)( &((char*)address)[offset] )  )
#define get_ulong(address,offset) ( *(unsigned long long*)( &((char*)address)[offset] )  )
#define get_size_t(address,offset) ( *(size_t*)( &((char*)address)[offset] )  )





	extern "C"
	{
#ifdef _WIN64

#define setup_farjmp64(address,dest) ((unsigned short*)address)[0] = 0x0B848; \
			((unsigned long long*)(address + 2))[0] = (unsigned long long)dest; \
			((unsigned short*)(address + 10))[0] = 0x0E0FF;

#define ASM_CMDEncore(cmd) ((short(__fastcall*)(short))0x0000000140B41C20)(cmd);
#define ASM_SendBank() ((short(__fastcall*)(size_t))0x0000000140A85B70)(0x0000000141292009);

#define ASM_GetDialog(AUI) (*(void* (__fastcall**)(void*, const char*))((*(size_t*)(AUI)) + (sizeof(size_t) * 14)))(AUI, str);
#define ASM_ShowDialog(DIALOG) (*(size_t(__fastcall**)(void*, int, int, int))((*(size_t*)(DIALOG)) + (sizeof(size_t) * 9)))(DIALOG, 1, 0, 1);
#define ASM_SearchLabel(DIALOG, LABEL, str) LABEL = ((void*(__fastcall*)(void*, const char*)) 0x0000000140E38F50) (DIALOG, str);
#define ASM_GetText(LABEL) (*(const wchar_t* (__fastcall**)(void* ))((*(size_t*)(LABEL)) + (sizeof(size_t) * 16)))(LABEL);
#define ASM_SetText(LABEL , str) (*(void* (__fastcall**)(void*, const wchar_t*))((*(size_t*)(LABEL)) + (sizeof(size_t) * 17)))(LABEL, str);
#define ASM_PrepareNPCService(pImp ,it) ((void(__fastcall*)(void*, int))0x00000001408D6510)(pImp,it);
#define ASM_NpcListUpdate(DIALOG) ((void(__fastcall*)(void*, int))0x00000001405C0F20)(DIALOG,1);

#define ASM_CreateNPC(ECX, Info) ((void*(__fastcall*)(void*, void*, bool))0x000000014097E9A0)(ECX, Info, 0);

#define ASM_GetElsePlayer(Man, id) ((void*(__fastcall*)(void*, int, int))0x000000014098B940)(Man, id, 0);

#define ASM_PaketPushCuint(buf, quint) ((void* (__fastcall*)(void*, size_t))0x00000001402E10F0)(buf, quint)
#define ASM_PaketPushMem(buf, mem, size) ((void* (__fastcall*)(void*, size_t, void*, size_t))0x00000001402E1680)(buf, get_size_t(buf,16), mem, size)

		short __fastcall CMDEncore(short);
		char __fastcall ClickButton(void *, const char *);
		int __fastcall PvPPause(void*, int iSevTime, int iTimeZoneBias, int pvp);

		void __fastcall TransportLocations();
		void __fastcall FixNpcRefine();

		void* __fastcall GetNPC(void*, int, int);
		int __fastcall GetItemCount(void*, int);

		char __fastcall CgameSendPacket(void*, void*, unsigned int);
		long long __fastcall CgameRecvPacket(void*, int, void*, unsigned int);
		char __fastcall CnetSendPacket(void*, void*, char);
		char __fastcall CnetRecvPacket(void*, void*);
		void* __fastcall ResponseMarshal(void*, void*, void*, void*, char);

		void* __fastcall ElsePlayerEnter(void*, int*, int);
		void __fastcall ElsePlayerLeave(void*, int, char, char);

		int __fastcall GetColorName(void*);

		bool __fastcall IsFashionWeaponTypeFit(int, int);


#define ASM_SendPacket(buf , size) ASM::CgameSendPacket( GetCECBase()->g_pGame->m_pGameSession, buf , size )

#else //WIN32

#define ASM_CMDEncore(cmd) ((short(__cdecl*)(short))0x00CBD1B0)(cmd);
#define ASM_ClickButton(ECX, EDX, str) ((int(__fastcall*)(void*, void*, char*))0x00F29050)(ECX, EDX, str);
#define ASM_SendBank() ((short(__cdecl*)(size_t))0x00C338D0)(0x01217C14);

#define ASM_GetDialog(AUI, str) (*(void* (__fastcall**)(void*, void*, const char*))((*(size_t*)(AUI)) + (sizeof(size_t) * 14)))(AUI, 0, str);
#define ASM_ShowDialog(DIALOG) (*(size_t(__fastcall**)(void*, void*, int, int, int))((*(size_t*)(DIALOG)) + (sizeof(size_t) * 9)))(DIALOG, 0, 1, 0, 1);
#define ASM_SearchLabel(DIALOG, LABEL, str) LABEL = ((void*(__fastcall*)(void*, void*, const char*)) 0x00F24E10) (DIALOG, 0, str);
#define ASM_GetText(LABEL) (*(const wchar_t* (__fastcall**)(void*, void* ))((*(size_t*)(LABEL)) + (sizeof(size_t) * 16)))(LABEL, 0);
#define ASM_SetText(LABEL , str) (*(void* (__fastcall**)(void*, void*, const wchar_t*))((*(size_t*)(LABEL)) + (sizeof(size_t) * 17)))(LABEL, 0, str);
#define ASM_NpcListUpdate(DIALOG) ((void(__fastcall*)(void*, void*,int))0x00873FC0)(DIALOG,0,1);

#define ASM_PrepareNPCService(pImp, it) ((void(__fastcall*)(void*, void*,int))0x00AE7440)(pImp,0,it);
#define ASM_CreateNPC(ECX, Info) ((void*(__fastcall*)(void*, void*, void*, bool))0x00B69BC0)(ECX, 0, Info, 0);
#define ASM_DeleteNPC(pNPC) ((void* (__fastcall*) (void*, void*, char)) (*(size_t*)pNPC))(pNPC,0, 1);

#define ASM_GetElsePlayer(Man, id) ((void*(__fastcall*)(void*, void*, int, int))0x00B73690)(Man, 0 , id, 0);

#define ASM_PaketPushCuint(buf, quint) ((void* (__fastcall*)(void*,void*, size_t))0x00626980)(buf,0, quint)
#define ASM_PaketPushMem(buf, mem, size) ((void* (__fastcall*)(void*,void*, size_t, void*, size_t))0x00626A40)(buf,0, get_size_t(buf,(sizeof(size_t)*2)), mem, size)

		void* __fastcall ResponseMarshal(void*, void*, void*);

		int __fastcall CgameSendPacket(void*, void*, void*, unsigned int);
		int __stdcall CgameRecvPacket( int, void*, unsigned int);
		int __fastcall CnetSendPacket(void*, void*, void*, int);
		int __fastcall CnetRecvPacket(void*, void*, void*);


		void FixNpcRefine();
		void* __fastcall GetNPC(void*, void*, int, int);
		int __fastcall GetItemCount(void*, void*, int);

		void * __fastcall ElsePlayerEnter(void*, void*, int*, int);
		void __fastcall ElsePlayerLeave(void*, void*, int, char, char);

		int __fastcall GetColorName(void*, void*);
		bool __cdecl IsFashionWeaponTypeFit(int, int);

#define ASM_SendPacket(buf , size) ASM::CgameSendPacket(GetCECBase()->g_pGame->m_pGameSession, 0, buf , size )
#endif
	}

};



#endif


