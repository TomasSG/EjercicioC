.PHONY: clean
all: servidor cliente

servidor: servidor.o lista.o lista_articulos.o
	gcc -o ../servidor servidor.o lista.o lista_articulos.o -lpthread
servidor.o: servidor.c
	gcc -c servidor.c -lpthread
lista.o: ../lib/lista.c
	gcc -c ../lib/lista.c
lista_articulos.o: ../lib/lista_articulos.c
	gcc -c ../lib/lista_articulos.c
cliente: cliente.o
	gcc -o ../cliente cliente.o
cliente.o: cliente.c
	gcc -c cliente.c
clean:
	rm *.o
