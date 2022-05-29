all: main.o util.o crc.o
	gcc -o main main.o util.o crc.o

main.o: main.c
	gcc -c main.c

test: test.o util.o crc.o
	gcc -o test test.o util.o crc.o

test.o: test.c util.h crc.h
	gcc -c test.c

util.o: util.c util.h
	gcc -c util.c

crc.o: crc.c crc.h
	gcc -c crc.c

clean:
	rm *.o test
