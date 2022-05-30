all: main.o util.o crc.o hamming.o
	gcc -o main main.o util.o crc.o hamming.o

main.o: main.c
	gcc -c main.c

test: test.o util.o crc.o hamming.o
	gcc -o test test.o util.o crc.o hamming.o

test.o: test.c util.h crc.h
	gcc -c test.c

util.o: util.c util.h
	gcc -c util.c

crc.o: crc.c crc.h
	gcc -c crc.c

hamming.o: hamming.c hamming.h
	gcc -c hamming.c

clean:
	rm *.o test main
