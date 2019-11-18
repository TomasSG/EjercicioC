.PHONY: clean
all: ../servidor ../cliente

../servidor: servidor.o lista.o cola.o
	gcc -o servidor servidor.o lista.o cola.o -lpthread
servidor.o: servidor.c
	gcc -c servidor.c -lpthread
lista.o: ../lib/lista.c
	gcc -c ../lib/lista.c
cola.o: ../lib/cola.c
	gcc -c ../lib/cola.c
../cliente: cliente.o
	gcc -o cliente cliente.o
cliente.o: cliente.c
	gcc -c cliente.c
clean:
	rm *.o
