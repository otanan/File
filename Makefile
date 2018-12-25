CC = gcc
CFLAGS = -Wall

OBJECTS = main.o file.o

#main is used for testing purposes
main : $(OBJECTS)
	$(CC) -o $@ $^

#file is used for exporting as a library object file
file : file.c
	@echo "Creating object file without main..."
	$(CC) $(CFLAGS) -c $^

.PHONY : clean

clean:
	rm *.o