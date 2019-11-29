%include "./include/boot.inc"

SECTION mbr vstart=0x7c00
        mov ax,cs
        mov ds,ax
        mov ss,ax
        mov sp,0x7c00

        mov eax,loader_start_sector
        mov ebx,loader_base_addr
        call read_hard_disk

        mov eax,[loader_base_addr]
        xor edx,edx
        mov ecx,512
        div ecx
        
        or edx,edx
        jnz @1
        dec eax

    @1:
        or eax,eax
        jz loader_base_addr + 0x04
        
        mov ecx,eax
        mov eax,loader_start_sector
        
    @2: 
        inc eax
        call read_hard_disk
        loop @2
        
        jz loader_base_addr + 0x04

read_hard_disk:	
        push eax
        push ecx
        push edx
        
        push eax
        
        mov dx,0x1f2
        mov al,1
        out dx,al
        
        inc dx
        pop eax
        out dx,al
        
        mov cl,8
        shr eax,cl
        inc dx
        out dx,al
        
        shr eax,cl
        inc dx
        out dx,al
        
        shr eax,cl
        or al,0xe0
        inc dx
        out dx,al
        
        inc dx
        mov al,0x20
        out dx,al
        
    .not_ready:
        in al,dx
        and al,0x88
        cmp al,0x08
        jnz .not_ready
        
        mov ecx,256
        mov dx,0x1f0
    .read:
        in ax,dx
        mov [ebx],ax
        add ebx,2
        loop .read
        
        pop edx
        pop ecx
        pop eax
        
        ret
        
        
times 510 - ($ - $$) db 0
db 0x55, 0xaa
