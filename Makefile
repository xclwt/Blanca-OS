.PHONY : clean

objects := $(wildcard bin/*.o)

CC = gcc
CFLAGS = -c -O0 -m32
LD = ld

bin/%.o : */%.c
	$(CC) $(CFLAGS) $^ -o $@


clean :
	-rm $(objects)