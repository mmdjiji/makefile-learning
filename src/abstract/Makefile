# abstract

TAR = abstract
OBJ = main.o
CC = gcc

$(TAR): $(OBJ)
	$(CC) $(OBJ) -o $(TAR)

main.o: main.c
	$(CC) -c main.c -o main.o

.PHONY: clean

clean:
	${RM} $(OBJ)
