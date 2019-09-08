CC       = gcc
CFLAGS   = -O2 -g -Wno-unused-result -Wunused

.PHONY: all clean

all:    28874Decoder

clean: 
	rm *.o
	rm 28874Decoder

28874Decoder: 28874Decoder.o
	gcc $^ -o $@
