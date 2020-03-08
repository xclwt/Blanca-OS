OUTPUT_FORMAT("elf32-i386")
ENTRY(main)
paddr = 0xc0001500;

SECTIONS{
    .text paddr ALIGN(4) : AT(paddr) {
		*(.text)
	}

	.rodata ALIGN(4) : {
		*(.rodata)
	}

	.stab ALIGN(4) : {
		PROVIDE(_STAB_BEGIN_ = .);
		*(.stab);
		PROVIDE(_STAB_END_ = .);
	}

	.stabstr ALIGN(4) : {
		PROVIDE(_STABSTR_BEGIN_ = .);
		*(.stabstr);
		PROVIDE(_STABSTR_END_ = .);

	.data ALIGN(4) : {
		*(.data)
	}

	.bss ALIGN(4) : {
		*(.bss)
	}
}
