# Warning, this makefile requires that you correctly set SS_CC
SS_CC=/usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc

CC=${SS_CC}

all: conv2D.ss conv2D_int.ss conv2D_unroll.ss

conv2D_int.ss:
	$(CC) -O -o conv2D_int.ss conv2D_int.c

conv2D.ss:
	$(CC) -O -o conv2D.ss conv2D.c

conv2D_unroll.ss:
	$(CC) -O -o conv2D_unroll.ss conv2D_unroll.c

.PHONY:all clean

clean:
	rm conv2D_int.ss
	rm conv2D.ss
	rm conv2D_unroll.ss