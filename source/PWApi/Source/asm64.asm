;------------------------------------------------------------------------------------------------------
;--ASM DATA
;------------------------------------------------------------------------------------------------------
IFDEF RAX
	;------------------------------------------------------------------------------------------------------
	;ECHO "WIN64"
	;------------------------------------------------------------------------------------------------------
	.const
	;------------------------------------------------------------------------------------------------------
	.data
	extern BASE_ADDRES:dq
	extern TransportTag:dq
	extern TransportTagSize:dq

	;------------------------------------------------------------------------------------------------------
	.data?
	;------------------------------------------------------------------------------------------------------
	.code
	;------------------------------------------------------------------------------------------------------
	GetBaseAddress proc
	mov     rcx, offset BASE_ADDRES
	mov		rcx, [rcx]
	mov		rcx, [rcx]
	mov     rcx, [rcx+40h]
	mov		rax, rcx
	ret
	GetBaseAddress endp 
	;------------------------------------------------------------------------------------------------------
	CgameSendPacket proc
	mov     r11, rsp
	push    rdi
	sub     rsp, 60h
	mov     qword ptr [r11-48h], 0FFFFFFFFFFFFFFFEh
	mov		rax, 0000000140B56CA0h
	jmp		rax
	CgameSendPacket endp
	;------------------------------------------------------------------------------------------------------
	CgameRecvPacket proc
	push    rbp
	push    rsi
	push    rdi
	lea     rbp, [rsp-47h]
	sub     rsp, 0D0h
	mov     qword ptr [rbp-51h], 0FFFFFFFFFFFFFFFEh
	mov     [rsp+0F0h], rbx
	mov		rax, 0000000140B31F70h
	jmp		rax
	CgameRecvPacket endp
	;------------------------------------------------------------------------------------------------------
	CnetSendPacket proc
	push    rdi
	sub     rsp, 30h
	mov     qword ptr [rsp+28h], 0FFFFFFFFFFFFFFFEh
	mov		rax, 0000000140B56DFFh
	jmp		rax
	CnetSendPacket endp
	;------------------------------------------------------------------------------------------------------
	CnetRecvPacket proc
	mov     [rsp+8], rbx
	mov     [rsp+10h], rsi
	push    rdi
	sub     rsp, 20h
	mov		rax, 0000000140B3F2CFh
	jmp		rax
	CnetRecvPacket endp
	;------------------------------------------------------------------------------------------------------
	ClickButton proc
	mov     [rsp+8], rbx
	mov     [rsp+10h], rsi
	push    rdi
	sub     rsp, 20h
	mov     rax, [rcx]
	mov		rdi, 0000000140E3D592h
	jmp		rdi
	ClickButton endp
	;------------------------------------------------------------------------------------------------------
	PvPPause proc
	mov     [rsp+8], rbx
	mov     [rsp+16], rbp
	mov     [rsp+24], rsi
	mov		rax, 000000014079460Fh
	jmp		rax
	PvPPause endp
	;------------------------------------------------------------------------------------------------------
	TransportLocations proc
	lea     rbx, TransportTag
	mov     rdi, rbx
	mov     rsi, TransportTagSize
	mov		rax, 0000000140A6F3C0h
	jmp		rax
	TransportLocations endp
	;------------------------------------------------------------------------------------------------------
	FixNpcRefine proc
	mov     rcx, rsi
	mov		rax, 0000000140324F00h
	call	rax
	mov     rax, [rax+1460h]
	test	rax, rax
	jz		loc_def
	mov     rax, [rax]
	loc_def:
	mov     [rsp+32], eax
	mov		rax, 00000001403B79EBh
	jmp		rax
	FixNpcRefine endp
	;------------------------------------------------------------------------------------------------------
	GetNPC proc
	mov     [rsp+16], edx
	push    rbx
	sub     rsp, 30h
	mov     ebx, r8d
	mov		rax, 000000014097F5FCh
	jmp		rax
	GetNPC endp
	;------------------------------------------------------------------------------------------------------
	GetItemCount proc
    movsxd  r9, dword ptr [rcx+20h]
    xor     eax, eax
    test    r9, r9
    jle     short locret_14090446A
    mov     r8, [rcx+18h]
    nop
loc_140904450:                         
    mov     rcx, [r8]
    test    rcx, rcx
    jz      short loc_140904460
    cmp     [rcx+0Ch], edx
    jnz     short loc_140904460
    add     eax, [rcx+14h]
loc_140904460:                                                
    add     r8, 8
    sub     r9, 1
    jnz     short loc_140904450
locret_14090446A:                     
    ret
	GetItemCount endp
	;------------------------------------------------------------------------------------------------------
	ElsePlayerEnter proc
	push    rsi
	push    rdi
	push    r14
	sub     rsp, 40h
	mov     qword ptr [rsp+32], 0FFFFFFFFFFFFFFFEh
	mov		rax, 000000014098B662h
	jmp		rax
	ElsePlayerEnter endp
	;------------------------------------------------------------------------------------------------------
	ElsePlayerLeave proc
	push    rdi
	push    r14
	push    r15
	sub     rsp, 30h
	mov     qword ptr [rsp+32], 0FFFFFFFFFFFFFFFEh
	mov		rax, 000000014098B7A3h
	jmp		rax
	ElsePlayerLeave endp
	;------------------------------------------------------------------------------------------------------
	GetColorName proc
	push    rbx
	sub     rsp, 20h
	mov     rbx, rcx
	mov     ecx, 0FF96C8FFh
	mov		rax, 00000001409F3ACEh
	jmp		rax
	GetColorName endp
	;------------------------------------------------------------------------------------------------------
	IsFashionWeaponTypeFit proc
	mov     [rsp+8], rbx
	push    rdi
	sub     rsp, 20h
	movsxd  rdi, edx
	mov     ebx, ecx
	mov		rax, 00000001409F55CFh
	jmp		rax
	IsFashionWeaponTypeFit endp
	;------------------------------------------------------------------------------------------------------
	ResponseMarshal proc
	mov     [rsp+10h], rbx
	push    rdi
	sub     rsp, 20h
	mov     rdi, rdx
	mov     rbx, rcx
	mov		rax, 0000000140B5DAE0h
	jmp		rax
	ResponseMarshal endp
	;------------------------------------------------------------------------------------------------------
ELSE
	;------------------------------------------------------------------------------------------------------
	;ECHO "WIN32"
	;------------------------------------------------------------------------------------------------------
	.386
	.model flat, stdcall
	;------------------------------------------------------------------------------------------------------
	.const
	;------------------------------------------------------------------------------------------------------
	.data
	extern BASE_ADDRES:dword
	extern TransportTag:dword
	extern TransportTagSize:dword
	;------------------------------------------------------------------------------------------------------
	.data?
	;------------------------------------------------------------------------------------------------------
	.code
ENDIF
end

