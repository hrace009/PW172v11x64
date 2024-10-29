//-------------------------------------------------------------------------------------------------------------------------
//--ASM DATA (c) DEADRAKY 2022
//-------------------------------------------------------------------------------------------------------------------------

#include "asm.h"

#ifdef _WIN64
#else //WIN32

__declspec(naked) void* __fastcall ASM::GetNPC(void*, void*, int, int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        sub     esp, 8
        mov		eax, 00B6A636h
        jmp		eax
    }
}

__declspec(naked) int __fastcall ASM::GetItemCount(void*, void*, int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    esi
        mov     esi, [ecx + 10h]
        mov		eax, 00B0C167h
        jmp		eax
    }
}

__declspec(naked) int __fastcall ASM::CgameSendPacket(void*, void*, void*, unsigned int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    0FFFFFFFFh
        mov		eax, 00CCDB35h
        jmp		eax
    }
}

__declspec(naked) int __stdcall ASM::CgameRecvPacket(int, void*, unsigned int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    0FFFFFFFFh
        mov     eax, 00CAD8B5h
        jmp     eax
    }
}


__declspec(naked) int __fastcall ASM::CnetSendPacket(void*, void*, void*, int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    0FFFFFFFFh
        mov     eax, 00CCDC65h
        jmp     eax
    }
}

__declspec(naked) int __fastcall ASM::CnetRecvPacket(void*, void*, void*)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    ebx
        push    esi
        mov     eax, 00CBAB65h
        jmp     eax
    }
}

__declspec(naked) void ASM::FixNpcRefine()
{
    _asm
    {
        mov     eax, [eax + 0A74h]
        test	eax, eax
        jz		loc_def
        mov		eax, [eax]
    loc_def:
        push eax
        mov     eax, 006D5912h
        jmp     eax
    }
}

__declspec(naked) void * __fastcall ASM::ElsePlayerEnter(void*, void*, int*, int)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    0FFFFFFFFh
        mov     eax, 00B73395h
        jmp     eax
    }
}

__declspec(naked) void __fastcall ASM::ElsePlayerLeave(void*, void*, int, char, char)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    0FFFFFFFFh
        mov     eax, 00B73505h
        jmp     eax
    }
}

__declspec(naked) int __fastcall ASM::GetColorName(void*, void*)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    ecx
        push    esi
        mov     eax, 00BC20F5h
        jmp     eax
    }
}

__declspec(naked) bool __cdecl ASM::IsFashionWeaponTypeFit(int , int )
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    esi
        mov     esi, [ebp + 12]
        mov     eax, 00BC38C7h
        jmp     eax
    }
}

__declspec(naked) void* __fastcall ASM::ResponseMarshal(void*, void*, void*)
{
    _asm
    {
        push    ebp
        mov     ebp, esp
        push    esi
        mov     esi, [ebp + 8]
        push    00CD1917h
        ret
    }
}



#endif