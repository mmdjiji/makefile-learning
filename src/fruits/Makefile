# fruits

fruits: apple.o banana.o coconut.o main.o
	gcc apple.o banana.o coconut.o main.o -o fruits

apple.o: apple.c
	gcc -c apple.c -o apple.o

banana.o: banana.c
	gcc -c banana.c -o banana.o

coconut.o: coconut.c
	gcc -c coconut.c -o coconut.o

main.o: main.c
	gcc -c main.c -o main.o

.PHONY: clean install uninstall

clean:
	rm -rf *.o

install:
	sudo cp fruits /usr/local/bin

uninstall:
	sudo rm /usr/local/bin/fruits
