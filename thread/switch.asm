[bits 32]

[GLOBAL switch_to]
switch_to:
	mov eax,[esp + 4]

	push esi
	push edi
	push ebx
	push ebp

	pop ebp
	pop ebx
	pop edi
	pop esi

	ret


