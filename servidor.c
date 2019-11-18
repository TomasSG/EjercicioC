#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#include "./lib/lista.h"

#define ERROR -1
#define OK 1
#define MAX_QUEUE 2

int main (int argc, char *argv[]){
	socklen_t cl=sizeof(struct sockaddr_in);
	struct sockaddr_in sa;
	struct sockaddr_in ca;
	int server_socket;
	int client_socket;
	int habilitar = 1;
	char buffer[256];
	int resultado=0;
	int i = 0;
	
	if( argc < 2){
		printf("Debe ingresar el puerto de escucha!\n");
		return ERROR;	
	}
	
	server_socket = socket(AF_INET,SOCK_STREAM,0);
	if(server_socket==-1){
		printf("No se pudo crear el server\n");
		return ERROR;		
	}	
	
	resultado = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &habilitar, sizeof(int));
	if (resultado <0){
		printf("No se pudo configurar opciones del socket\n");
		return ERROR;
	}

	bzero( (char*) &sa, sizeof(struct sockaddr_in) );
	sa.sin_family=AF_INET;
	sa.sin_port=htons(atoi(argv[1]));
	sa.sin_addr.s_addr= INADDR_ANY;

	bind(server_socket, (struct sockaddr *) &sa, sizeof(struct sockaddr_in) );

	listen(server_socket,MAX_QUEUE);

	client_socket= accept(server_socket,(struct sockaddr *) &ca, &cl);
	
	for(i = 0; i < 2; i++){
		bzero(buffer,256);
		send(client_socket,"uno",4,0);
		printf("uno\n");
		recv(client_socket,buffer,256,0);
		printf("%s\n",buffer);
	}
	send(client_socket,"Comunicacion terminada",strlen("Comunicacion terminada"),0);
	close(client_socket);
	close(server_socket);

	return OK;
}

