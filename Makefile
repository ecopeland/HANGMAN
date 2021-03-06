CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o vector.o hangman.o

all: string_driver unit_test

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test my_string.o unit_test.o test_def.o
unit_test.o: unit_test.c unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
hangman.o: hangman.c hangman.h
	$(CC) $(CFLAGS) -c hangman.c -o hangman.o
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c -o vector.o
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm unit_test unit_test.o test_def.o
	rm string_driver $(OBJECTS)