CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o 
clean:
	rm string_driver $(OBJECTS)
