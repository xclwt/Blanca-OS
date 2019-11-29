%include "./include/boot.inc"
SECTION loader vstart=loader_base_addr
        jmp start
    
        gdt_ptr dw GDT_LIMIT
                dd 0x7e00
                
        CODE_SELECTOR equ (0x01 << 3) + TI_GDT + RPL_0
        DATA_SELECTOR equ (0x02 << 3) + TI_GDT + RPL_0
        VIDEO_SELECTOR equ (0x03 << 3) + TI_GDT + RPL_0
            
start:
        mov eax,[cs:gdt_ptr + 0x02]
        xor edx,edx
        mov ebx,16
        div ebx
        
        mov ds,ax
        mov ebx,edx
        
        mov dword [ebx + 0x00], 0x00000000
        mov dword [ebx + 0x04], 0x00000000
        
        mov dword [ebx + 0x08], 0x0000FFFF
        mov dword [ebx + 0x0c], CODE_DESC_HIGH
        
        mov dword [ebx + 0x10], 0x0000FFFF
        mov dword [ebx + 0x14], DATA_DESC_HIGH
        
        mov dword [ebx + 0x18], 0x80000007
        mov dword [ebx + 0x1c], VIDEO_DESC_HIGH
        
        in al,0x93
        or al,0010b
        out 0x92,al
        
        lgdt [gdt_ptr]
        
        mov eax,cr0
        or eax,0x01
        mov cr0,eax
        
        jmp dword CODE_SELECTOR:p_mode
        
        
[bits 32]
p_mode:
        
