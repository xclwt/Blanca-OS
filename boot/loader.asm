%include "./include/boot.inc"


SECTION loader vstart=loader_base_addr
        loader_length: dd loader_end - loader_base_addr
        
        jmp start
        
        CODE_SELECTOR equ (0x01 << 3) + TI_GDT + RPL_0
        DATA_SELECTOR equ (0x02 << 3) + TI_GDT + RPL_0
        VIDEO_SELECTOR equ (0x03 << 3) + TI_GDT + RPL_0
    
        gdt_ptr dw 0
                dd 0x1100
                
        ards_buf times 20 db 0
        
        total_memory dd 0
        
        msg_load_succ:
            db "Succeed to load loader...", 13, 10, 0
        
        msg_gdt:
            db "GDT loaded...", 13, 10, 0
        
        msg_a20:
            db "A20 line on...", 13, 10, 0
        
        msg_get_mem_fail:
            db "Fail to get memory...", 13, 10, 0
            
print_msg_16:
    .loop:
        lodsb
        or al,al
        jz .done
        mov ah,0x0e
        mov bx,15
        int 0x10
        jmp .loop
    .done:
        ret
            
start:
        mov si,msg_load_succ
        call print_msg_16

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
     
    ;int0x15子功能0xe820 
    .0xe820:
        mov eax,0xe820
        mov ecx,20
        int 0x15
        jc .0xe801
        mov eax,[es:ards_buf]
        add eax,[es:ards_buf + 8]
        mov ecx,[total_memory]
        cmp eax,ecx
        cmova ecx,eax
        mov [total_memory],ecx
        cmp ebx,0
        jnz .0xe820
        
        jmp .memory_ready
    
    ;int0x15子功能0xe801     
    .0xe801:
        mov ax,0xe801
        int 0x15
        jc .0x88
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
        jmp .memory_ready

    ;int0x15子功能0x88
    .0x88:
        mov ah,0x88
        int 0x15
        jc .error
        mov cx,0x400
        mul cx
        shl edx,16
        and eax,0x0000ffff
        or edx,eax
        add edx,0x100000
        mov [total_memory],edx
        
    .memory_ready:
        ;加载gdt
        lgdt [gdt_ptr]
        mov si,msg_gdt
        call print_msg_16
        
        cli
        
        ;打开A20
        in al,0x92
        or al,0010b
        out 0x92,al
        mov si,msg_a20
        call print_msg_16
        
        ;进入保护模式
        mov eax,cr0
        or eax,0x01
        mov cr0,eax
        
        jmp dword CODE_SELECTOR:p_mode
        
    .error:
        mov si,msg_get_mem_fail
        call print_msg_16
        hlt
        
[bits 32]
p_mode:
        mov ax,DATA_SELECTOR
        mov ds,ax
        mov es,ax
        mov ss,ax
        mov ax,VIDEO_SELECTOR
        mov gs,ax
        
        ;读取elf文件的前512字节
        mov eax,kernel_start_sector
        mov ebx,kernel_elf_addr
        call read_hard_disk_m32
        
        ;利用elf头信息计算elf文件大小
        ;利用长度计算总共需要读取的扇区数
        xor eax,eax
        mov ax,[kernel_elf_addr + 0x2e]
        mov cx,[kernel_elf_addr + 0x30]
        mul cx
        shl edx,16
        or eax,edx
        add eax,[kernel_elf_addr + 0x20]
        xor edx,edx
        mov ecx,512
        div ecx
        
        or edx,edx
        jnz .1
        dec eax
    
    .1:
        or eax,eax
        jz .continue
        
        mov ecx,eax
        mov eax,kernel_start_sector
        
    .2: 
        inc eax
        call read_hard_disk_m32
        loop .2
        
    .continue:
        call create_page
        
        sgdt [gdt_ptr]
        mov ebx,[gdt_ptr + 2]
        add dword [gdt_ptr + 2],0xc0000000
        add dword [ebx + 0x1c],0xc0000000
        add esp,0xc0000000
        
        mov eax,PAGE_DIR_POS
        mov cr3,eax
        
        mov eax,cr0
        or eax,0x80000000
        mov cr0,eax
        
        lgdt [gdt_ptr]
        
        call init_kernel
        mov esp,0x1100
        
        jmp kernel_image_addr
  
  
;ebx = 程序头表地址
;cx = 程序头表中程序头的数量
;dx = 程序头的尺寸
init_kernel:
        xor eax,eax
        xor ebx,ebx
        xor ecx,ecx
        xor edx,edx
        
        mov ebx,[kernel_elf_addr + 0x1c] ;获取程序头表在程序中的偏移量
        add ebx,kernel_elf_addr ;计算程序头表在内存中的地址
        
        mov cx,[kernel_elf_addr + 0x2c] ;获取程序头表中程序头的数量
        
        mov dx,[kernel_elf_addr + 0x2a] ;获取程序头尺寸
    
    .each_segment:
        cmp dword[ebx + 0],0 ;若p_type为0,则当前程序头未使用
        je .PTNULL
        
        push dword [ebx + 0x10] ;mem_cpy的参数三：size
        
        mov eax,[ebx + 0x4]
        add eax,kernel_elf_addr
        push eax ;mem_cpy的参数二：源地址
        
        push dword [ebx + 0x8] ;mem_cpy的参数一：目的地址
        
        call mem_cpy
        add esp,0xc
        
    .PTNULL:
        add ebx,edx
        
        loop .each_segment
        
        ret
  
;[ebp + 0x8] = 目的地址
;[ebp + 0xc] = 源地址
;[ebp + 0x10] = size
mem_cpy:
        cld
        push ebp
        mov ebp,esp
        push ecx
        
        mov edi,[ebp + 0x8]
        mov esi,[ebp + 0xc]
        mov ecx,[ebp + 0x10]
        
        rep movsb
        
        pop ecx
        pop ebp
        
        ret
  
print_msg_32:
        add edi,160
        push edi
        cld
        
    .loop:
        lodsb
        cmp al,0
        je .out
        mov [gs:edi],ax
        add edi,2
        jmp .loop
        
    .out:
        pop edi
        ret

create_page:
        mov ecx,4096
        mov esi,0
        
    .clear_pde:
        mov byte [PAGE_DIR_POS + esi],0
        inc esi
        loop .clear_pde
        
    .create_pde:
        mov eax,PAGE_DIR_POS
        add eax,0x1000
        mov ebx,eax
        
        or eax,PAGE_P | PAGE_RW_W | PAGE_US_U
        mov [PAGE_DIR_POS + 0x0],eax
        mov [PAGE_DIR_POS + 0xc00],eax
        
        sub eax,0x1000
        mov [PAGE_DIR_POS + 4092],eax
        
        mov ecx,1024
        mov esi,0
        mov edx,PAGE_P | PAGE_RW_W | PAGE_US_U
        
    .create_pte:
        mov [ebx + 4 * esi],edx
        add edx,4096
        inc esi
        loop .create_pte
        
        add eax,0x2000
        mov ebx,PAGE_DIR_POS
        mov ecx,254
        mov esi,769
        
    .create_rest_kernel_pde:
        mov [ebx + 4 * esi],eax
        add eax,0x1000
        inc esi
        loop .create_rest_kernel_pde
        
        ret

;读取磁盘的一个扇区
;eax = 扇区号
;ds:ecx = 加载的内存地址
;返回ebx = ebx + 512 
read_hard_disk_m32:	
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
        
msg_p_mode_on:
    db "Protect mode on...", 0

msg_page_on:
    db "Pages on...", 0

        
loader_end:
