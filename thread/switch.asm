[bits 32]

[GLOBAL switch_to]
switch_to:
	mov eax,[esp + 4]
	mov [eax],esp

	mov eax,[esp + 8]

	push esi
	push edi
	push ebx
	push ebp

	mov esp,[eax]

	pop ebp
	pop ebx
	pop edi
	pop esi

	ret


