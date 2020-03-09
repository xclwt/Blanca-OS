OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(main)

SECTIONS{
    . = 0xc0001500;
    
    .text : {
		*(.text .text.*)
		. = ALIGN(1024);
	}

	.rodata : {
		*(.rodata)
		. = ALIGN(1024);
	}

	.stab : {
		PROVIDE(_STAB_BEGIN_ = .);
		*(.stab);
		PROVIDE(_STAB_END_ = .);
		. = ALIGN(1024);

	}

	.stabstr : {
		PROVIDE(_STABSTR_BEGIN_ = .);
		*(.stabstr);
		PROVIDE(_STABSTR_END_ = .);
		. = ALIGN(1024);

    }
    
	.data : {
		*(.data)
		. = ALIGN(1024);
	}

	.bss : {
		*(.bss)
		. = ALIGN(1024);
	}
	
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}
