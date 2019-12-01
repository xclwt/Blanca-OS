%include "./include/boot.inc"


SECTION loader vstart=loader_base_addr
        loader_length: dd loader_end
        
        jmp start
        
        CODE_SELECTOR equ (0x01 << 3) + TI_GDT + RPL_0
        DATA_SELECTOR equ (0x02 << 3) + TI_GDT + RPL_0
        VIDEO_SELECTOR equ (0x03 << 3) + TI_GDT + RPL_0
    
        gdt_ptr dw 0
                dd 0x7e00
                
        ards_buf times 20 db 0
        
        total_memory dd 0
        
        msg_boot:
            db "MBR loaded...", 13, 10, 0
        
        msg_err:
            db "Fail to load ...", 13, 10, 0
        
        msg_load_succ:
            db "Succeed to load loader...", 13, 10, 0
        
        msg_gdt:
            db "GDT loader...", 13, 10, 0
        
        msg_a20:
            db "A20 line on...", 13, 10, 0
        
        msg_get_mem_fail:
            db "Fail to get memory...", 13, 10, 0
            
        msg_p_mode_on:
            db "Protected mode on...", 13, 10, 0
            
print_msg:
loop:
        lodsb
        or al,al
        jz done
        mov ah,0x0e
        mov bx,15
        int 0x10
        jmp loop
done:
        ret
            
start:
        mov si,msg_load_succ
        call print_msg

        ;计算段地址：偏移地址
        mov eax,[cs:gdt_ptr + 0x02]
        xor edx,edx
        mov ebx,16
        div ebx
        
        mov ds,ax
        mov ebx,edx
        
        ;生成gdt
        mov dword [ebx + 0x00], 0x00000000
        mov dword [ebx + 0x04], 0x00000000
        
        mov dword [ebx + 0x08], 0x0000ffff
        mov dword [ebx + 0x0c], CODE_DESC_HIGH
        
        mov dword [ebx + 0x10], 0x0000ffff
        mov dword [ebx + 0x14], DATA_DESC_HIGH
        
        mov dword [ebx + 0x18], 0x80000007
        mov dword [ebx + 0x1c], VIDEO_DESC_HIGH
        
        mov ax,0
        mov ds,ax
        mov word [gdt_ptr],31
        
        xor ebx,ebx
        mov edx,0x534d4150
        mov di,ards_buf
        mov ax,0
        mov es,ax
        
@0xe820:
        mov eax,0xe820
        mov ecx,20
        int 0x15
        jc @0xe801
        mov eax,[es:ards_buf]
        add eax,[es:ards_buf + 8]
        mov ecx,[total_memory]
        cmp eax,ecx
        cmova ecx,eax
        mov [total_memory],ecx
        cmp ebx,0
        jnz @0xe820
        
        jmp memory_ready
        
@0xe801:
        mov ax,0xe801
        int 0x15
        jc @0x88
        mov cx,0x400
        mul cx
        shl edx,16
        and eax,0x0000ffff
        or edx,eax
        add edx,0x100000
        
        xor eax,eax
        mov ax,bx
        mov ecx,0x10000
        mul ecx
        add edx,eax
        mov [total_memory],edx
        jmp memory_ready

@0x88:
        mov ah,0x88
        int 0x15
        jc error
        mov cx,0x400
        mul cx
        shl edx,16
        and eax,0x0000ffff
        or edx,eax
        add edx,0x100000
        mov [total_memory],edx
        
memory_ready:
        ;加载gdt
        lgdt [gdt_ptr]
        mov si,msg_gdt
        call print_msg
        
        cli
        
        ;打开A20
        in al,0x92
        or al,0010b
        out 0x92,al
        mov si,msg_a20
        call print_msg
        
        
        
        ;进入保护模式
        mov eax,cr0
        or eax,0x01
        mov cr0,eax
        
        jmp dword CODE_SELECTOR:p_mode
        
error:
        mov si,msg_get_mem_fail
        call print_msg
        hlt
        
[bits 32]
p_mode:
        mov eax,0x0008
        
loader_end:
