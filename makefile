CC = gcc

file: main.o file.o
	$(CC) -o file main.o file.o

clean:
	rm *.o