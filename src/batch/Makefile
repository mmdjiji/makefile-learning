# batch

TAR = batch
OBJ = alpha.o bravo.o charlie.o delta.o main.o
CC = gcc

$(TAR): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@
