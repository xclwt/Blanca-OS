gcc -c -m32 -o main.o main.c && ld main.o-Ttext0xc0001500 -e main -m elf_i386 -o kernel.bin && dd if=kernel.bin of=/home/xclwt/bochs/hd60M.img bs=512 count=200 seek=9 conv=notrunc
