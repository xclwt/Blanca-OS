.PHONY : link clean update_image bochs gdb objdump

C_SRC = $(shell find . -name "*.c")
C_OBJ = $(patsubst %.c, %.o, $(C_SRC))
S_SRC = $(shell find . -name "*.asm")
S_OBJ = $(patsubst %.asm, %.bin, $(S_SRC))

CC = gcc
LD = ld
ASM = nasm
ASM_FLAGS = -I boot/inc
C_FLAGS = -c  -O0 -m32 -g -nostdinc -fno-builtin -fno-stack-protector -I inc 
LD_FLAGS =  -Ttext 0xc0001500 -e main -m elf_i386

all : $(S_OBJ) $(C_OBJ) link update_image clean objdump bochs gdb

%.o:%.c
	$(CC) $(C_FLAGS) $< -o $@
	
%.bin:%.asm
	$(ASM) $(ASM_FLAGS) $< -o $@ 

link : 
	ld $(C_OBJ) $(LD_FLAGS) -o kernel.bin
	
update_image:
	dd if=boot/mbr.bin of=tools/bochs/hd60M.img bs=512 seek=0 conv=notrunc
	dd if=boot/loader.bin of=tools/bochs/hd60M.img bs=512 seek=1 conv=notrunc
	dd if=kernel.bin of=tools/bochs/hd60M.img bs=512 count=200 seek=9 conv=notrunc

bochs:
	bochs -f tools/bochs/bochsrc.disk -q
	
gdb:
	gdb kernel.bin -x tools/gdb/cmd.txt
	
objdump:
	objdump -d kernel.bin > kernel.s
	
clean :
	-rm $(C_OBJ) $(S_OBJ)
