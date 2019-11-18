.PHONY: clean
all: servidor cliente

servidor: servidor.o lista.o
	gcc -o servidor servidor.o lista.o -lpthread
servidor.o: ./arch/servidor.c
	gcc -c ./arch/servidor.c -lpthread
lista.o: ./lib/lista.c
	gcc -c ./lib/lista.c
cliente: cliente.o
	gcc -o cliente cliente.o
cliente.o: ./arch/cliente.c
	gcc -c ./arch/cliente.c
clean:
	rm *.o
