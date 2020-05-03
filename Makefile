.PHONY : link clean update_image bochs gdb objdump

C_SRC = $(shell find . -name "*.c")
C_SRC := $(filter-out kernel/debug.c, $(C_SRC))
C_OBJ = $(patsubst %.c, %.o, $(C_SRC))

S_SRC = $(shell find . -name "*.asm")
S_SRC := $(filter-out kernel/idt_s.asm, $(S_SRC))
S_BIN = boot/mbr.bin\
		boot/loader.bin
#S_BIN = $(patsubst %.asm, %.bin, $(S_SRC))
S_OBJ = kernel/idt_s.o

CC = gcc
LD = ld
ASM = nasm
ASM_FLAGS = -I boot/inc
C_FLAGS = -c -Wall -O0 -m32 -nostdinc -fno-builtin -fno-stack-protector -ggdb -gstabs+ -I inc 
LD_FLAGS1 = -T tools/ld/kernel.ld
LD_FLAGS2 = -Ttext 0xc0001500 -e main -m elf_i386

all1 : $(S_OBJ) $(S_BIN) $(C_OBJ) link update_image clean objdump bochs
all2 : $(S_OBJ) $(S_BIN) $(C_OBJ) link update_image clean objdump bochs-gdb
all3 : $(S_OBJ) $(S_BIN) $(C_OBJ) link update_image clean objdump

%.o:%.c
	$(CC) $(C_FLAGS) $< -o $@
	
%.o:%.asm
	$(ASM) $(ASM_FLAGS) -f elf32 $< -o $@
	
%.bin:%.asm
	$(ASM) $(ASM_FLAGS) $< -o $@ 

link : 
	ld $(C_OBJ) $(S_OBJ) $(LD_FLAGS2) -o kernel.bin
	
update_image:
	dd if=boot/mbr.bin of=tools/bochs/hd60M.img bs=512 seek=0 conv=notrunc
	dd if=boot/loader.bin of=tools/bochs/hd60M.img bs=512 seek=1 conv=notrunc
	dd if=kernel.bin of=tools/bochs/hd60M.img bs=512 count=200 seek=9 conv=notrunc

bochs:
	bochs -f tools/bochs/bochsrc.disk -q
	
bochs-gdb:
	bochs-gdb -f tools/bochs/bochgdb.disk -q
	
gdb:
	gdb kernel.bin -x tools/gdb/cmd.txt
	
objdump:
	objdump -d kernel.bin > kernel.s
	
clean :
	-rm $(C_OBJ) $(S_OBJ)
