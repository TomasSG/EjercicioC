#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "../lib/lista.h"

#define ERROR -1
#define OK 1
#define MAX_QUEUE 999

t_lista clientes;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* escuchar_cliente(void*);

void* escuchar_cliente(void* socket)
{
	int* paux= (int*) socket;	
	int socket_cliente=*paux;
	char buffer[256];
	while(1)
	{
		bzero(buffer,256);
		char* enviar = "Esto es una prueba de mutex";
		send(socket_cliente,(void*)enviar,strlen(enviar),0);
		pthread_mutex_lock(&mtx);
		recv(socket_cliente,buffer,256,0);
		printf("%s\n",buffer);
		pthread_mutex_unlock(&mtx);
	}

}

int main (int argc, char *argv[])
{
	socklen_t cl=sizeof(struct sockaddr_in);
	struct sockaddr_in sa;
	struct sockaddr_in ca;
	int servidor_socket;
	int habilitar = 1;
	int resultado=0;
	
	if( argc < 2)
	{
		printf("Debe ingresar el puerto de escucha!\n");
		return ERROR;	
	}
	
	servidor_socket = socket(AF_INET,SOCK_STREAM,0);
	if(servidor_socket==-1)
	{
		printf("No se pudo crear el server\n");
		return ERROR;		
	}	
	
	resultado = setsockopt(servidor_socket, SOL_SOCKET, SO_REUSEADDR, &habilitar, sizeof(int));
	if (resultado <0)
	{
		printf("No se pudo configurar opciones del socket\n");
		return ERROR;
	}

	bzero( (char*) &sa, sizeof(struct sockaddr_in) );
	sa.sin_family=AF_INET;
	sa.sin_port=htons(atoi(argv[1]));
	sa.sin_addr.s_addr= INADDR_ANY;

	bind(servidor_socket, (struct sockaddr *) &sa, sizeof(struct sockaddr_in) );
	
	crear_lista(&clientes);

	listen(servidor_socket,MAX_QUEUE);
	while(1)
	{		
		t_dato dato; 
		dato.socket= accept(servidor_socket,(struct sockaddr *) &ca, &cl);
		pthread_create(&dato.hilo,NULL,escuchar_cliente,(void *)&dato.socket);
		insertar_ordenado(&clientes,&dato,comparacion);		
		printf("Conexión esablecida con el cliente %d\n",dato.socket);
		printf("Clientes actuales:\n");		
		recorrer_lista(&clientes,mostrar);	
			
	}
	
	//close(cliente_socket);
	//close(servidor_socket);

	return OK;
}

