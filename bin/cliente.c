#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ERROR -1
#define TODO_BIEN 0

void ayuda();

void ayuda()
{
	printf("\nNombre Script: cliente.c - server.c\n");
        printf("Trabajo practico nro: 3\n");
        printf("Ejercicio nro: 4\n");
        printf("Integrantes:\n");
        printf("\n");
        printf("    Costa Lautaro DNI:36.396.983\n");
        printf("    Gonzalez Giselle Rocio DNI: 41.292.355\n");
        printf("    Grigioni Sanchez Tomas DNI: 41.589.109\n");
        printf("    Rossi Alan Gustavo DNI: 37.250.221\n");
        printf("    Stanko, Diego DNI: 39.372.117\n");
        printf("\n");
        printf("Primera entrega\n");
        printf("-----------------------------\n");
        printf("Objetivo.\n");
        printf("Generar un servicio en red a traves de un modelo servidor-clientes\n");
        printf("\n");
        printf("\tEjemplo de ejecución:\n\n");
        printf("Primero se debe ejecutar el servidor\n\n");
        printf("./server puerto_escucha \n\n");
	printf("./server 5000 \n\n");
       	printf("Luego se ejecuta tantos clientes como se quiera\n\n");
       	printf("./cliente IP_servidor puerto_servidor\n\n");
	printf("./cliente 127.0.0.1 5000\n\n");	
}

int main(int argc, char *argv[]){
	int resultado = 0;
	int x=0;
	int i=0;
	char buffer[1024];
	struct sockaddr_in sa;

	if( argc == 2 && (strcmp(argv[1],"-h") ==0 || strcmp(argv[1],"-help") ==0 ) )
	{
		ayuda();
		return 0;
	}	
	if(argc < 3 || argc >=4)
	{
		printf("Cantidad de parámetros erroneos\n");
		return ERROR;
	}	
	
	x = socket(AF_INET,SOCK_STREAM,0);
	if(x==-1){
		printf("No se pudo crear el socket\n");
		return ERROR;		
	}

	bzero( (char *) &sa, sizeof(struct sockaddr_in) );
	sa.sin_family=AF_INET;
	sa.sin_port=htons(atoi(argv[2]));
	sa.sin_addr.s_addr=inet_addr(argv[1]);

	resultado = connect(x,(struct sockaddr *) &sa, sizeof(sa));
	if( resultado == -1){
		printf("Solicitud rechazada\n");
		return ERROR;	
	}
	printf("------------------------------------------\n");
	printf("CONEXION REALIZADA\n");
	printf("------------------------------------------\n");
	while(1)
	{
		bzero(buffer,1024);
		recv(x,buffer,1024,0);
		if(strcmp(buffer,"INICIO")==0)
		{
			while(strcmp(buffer,"FIN")!=0)
			{
				bzero(buffer,1024);
				recv(x,buffer,1024,0);
				if(strcmp(buffer,"FIN")!=0)
				{
					printf("%s\n",buffer);
				}			
			}
		} else
		{
			printf("%s\n",buffer);
		} 
		printf("---------------------\n");
		bzero(buffer,1024);
		scanf("%s",buffer);
		send(x,(void*)buffer,strlen(buffer),0);
		if (strcmp(buffer,"QUIT")==0)
		{
			printf("Se ha salido del servidor\n");
			close(x);
			return TODO_BIEN;
		}	
	}
}
