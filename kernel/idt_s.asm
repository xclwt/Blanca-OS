[bits 32]

[GLOBAL load_idt]
load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret

%macro isr 1
[GLOBAL isr%1]
isr%1:
	%if %1 < 8 || %1 = 9 || (%1 > 14 && %1 != 17)
		push 0
	%endif
	push %1
	jmp asm_isr_stub
%endmacro

%assign i 0
%rep 32
	isr i
%assign i i+1
%endrep

isr 128
isr 255

%macro irq 1
[GLOBAL irq%1]
irq%1:
	push 0
	push %1 + 32
	jmp asm_isr_stub
%endmacro

%assign i 0
%rep 16
	irq i
%assign i i+1
%endrep

[extern c_isr_stub]
asm_isr_stub:
	pusha
	push ds
	push es
	push gs
	push fs

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov gs,ax
	mov fs,ax

	push esp
	call c_isr_stub
	
[GLOBAL intr_exit]
intr_exit:
	add esp,4

	pop fs
	pop gs
	pop es
	pop ds
	popa
	
	add esp,8
	iret

