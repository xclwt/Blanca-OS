.PHONY : link clean update_image bochs

C_SRC = $(shell find . -name "*.c")
C_OBJ = $(patsubst %.c, %.o, $(C_SRC))
S_SRC = $(shell find . -name "*.asm")
S_OBJ = $(patsubst %.asm, %.bin, $(S_SRC))

CC = gcc
LD = ld
ASM = nasm
C_FLAGS = -c -m32 -I inc 
LD_FLAGS = -Ttext 0xc0001500 -e main -m elf_i386

all : $(S_OBJ) $(C_OBJ) link update_image clean bochs

%.o:%.c
	$(CC) $(C_FLAGS) $< -o $@
	
%.bin:%.asm
	$(ASM) -o $@ $< 

link : 
	ld $(C_OBJ) -o kernel.bin
	
update_image:
	dd if=boot/boot.bin of=./hd60M.img bs=512 count=0 conv=notrunc
	dd if=boot/loader.bin of=./hd60M.img bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=/./hd60M.img bs=512 count=200 seek=9 conv=notrunc

bochs:
	bochs -f ./bochsrc.disk
	
clean :
	-rm $(C_OBJ) $(S_OBJ)
