all: main.o util.o crc.o hamming.o two_layer.o
	gcc -o main main.o util.o crc.o hamming.o two_layer.o

main.o: main.c
	gcc -c main.c

test: test.o util.o crc.o hamming.o two_layer.o
	gcc -o test test.o util.o crc.o hamming.o two_layer.o

test.o: test.c
	gcc -c test.c

util.o: util.c util.h
	gcc -c util.c

crc.o: crc.c crc.h
	gcc -c crc.c

hamming.o: hamming.c hamming.h
	gcc -c hamming.c

two_layer.o: two_layer.c two_layer.h
	gcc -c two_layer.c

clean:
	rm *.o test main
