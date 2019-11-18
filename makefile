.PHONY: clean
all: servidor cliente

servidor: servidor.o lista.o
	gcc -o servidor servidor.o lista.o
servidor.o: servidor.c
	gcc -c servidor.c
lista.o: ./lib/lista.c
	gcc -c ./lib/lista.c
cliente: cliente.o
	gcc -o cliente cliente.o
cliente.o: cliente.c
	gcc -c cliente.c
clean:
	rm *.o
