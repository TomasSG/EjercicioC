#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "../lib/lista.h"
#include "../lib/lista_articulos.h"

#define ERROR -1
#define OK 1
#define MAX_QUEUE 999
#define PATH_DB "./archivos/db"

t_lista_articulo articulos;
t_lista clientes;
pid_t pid_server;
t_dato matar;
pthread_mutex_t mtx_buffer = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_lista = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_matar = PTHREAD_MUTEX_INITIALIZER;

void* escuchar_cliente(void*);
void* atender_peticiones(void *);
void terminar(int);
void matar_hilo(int);
void interpretar_mensaje(char*,char*,char*);
void buscar_registro(char*,char*,int,const t_lista_articulo*);
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
       	printf("Luego se ejecuta tantos clientes como se quiera\n\n");
       	printf("./cliente IP_servidor puerto_servidor\n\n");		
}

void buscar_registro(char *clave,char *valor ,int socket,const t_lista_articulo *pl)
{
	t_nodo_articulo *aux= *pl, *aux1;
	int id = atoi(valor), campo = -1,cantidad=0;;
	char mensaje[1024];
	if ( strcmp(clave,"ID")==0 )
	{
		campo=0;
	}
	if ( strcmp(clave,"ARTICULO")==0 )
	{
		campo=1;
	}
	if ( strcmp(clave,"PRODUCTO")==0 )
	{
		campo=2;
	}
	if ( strcmp(clave,"MARCA")==0 )
	{
		campo=3;
	}
	if ( campo==-1)
	{
		strcpy(mensaje,"No se pudo realizar la búsqueda, el campo a filtrar es erroneo\n");
		send(socket,mensaje,strlen(mensaje),0);
		return;
	}
	strcpy(mensaje,"INICIO");
	send(socket,(void*)mensaje,strlen(mensaje),0);
	while ( aux!=NULL)
	{
		if(campo==0 && id==aux->dato.id)
		{
			char string[200];
			strcpy(mensaje,"\nID: ");			
			sprintf(string,"%d",aux->dato.id);
			strcat(mensaje,string);			
			strcat(mensaje,"\nPRODUCTO: ");
			strcat(mensaje,aux->dato.producto);
			strcat(mensaje,"\nMARCA: ");
			strcat(mensaje,aux->dato.marca);
			strcat(mensaje,"\nARTICULO: ");
			strcat(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;
		}
		if(campo==1 && strcmp(valor,aux->dato.articulo)==0)
		{
			char string[200];
			strcpy(mensaje,"\nID: ");			
			sprintf(string,"%d",aux->dato.id);
			strcat(mensaje,string);			
			strcat(mensaje,"\nPRODUCTO: ");
			strcat(mensaje,aux->dato.producto);
			strcat(mensaje,"\nMARCA: ");
			strcat(mensaje,aux->dato.marca);
			strcat(mensaje,"\nARTICULO: ");
			strcat(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		if(campo==2 && strcmp(valor,aux->dato.producto)==0)
		{
			char string[200];
			strcpy(mensaje,"\nID: ");			
			sprintf(string,"%d",aux->dato.id);
			strcat(mensaje,string);			
			strcat(mensaje,"\nPRODUCTO: ");
			strcat(mensaje,aux->dato.producto);
			strcat(mensaje,"\nMARCA: ");
			strcat(mensaje,aux->dato.marca);
			strcat(mensaje,"\nARTICULO: ");
			strcat(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		if(campo==3 && strcmp(valor,aux->dato.marca)==0)
		{
			char string[200];
			strcpy(mensaje,"\nID: ");			
			sprintf(string,"%d",aux->dato.id);
			strcat(mensaje,string);			
			strcat(mensaje,"\nPRODUCTO: ");
			strcat(mensaje,aux->dato.producto);
			strcat(mensaje,"\nMARCA: ");
			strcat(mensaje,aux->dato.marca);
			strcat(mensaje,"\nARTICULO: ");
			strcat(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		aux1=aux;
		aux=aux1->psig;
		
	}
	if(cantidad==0)
	{
		strcpy(mensaje,"No hubo coincidencias\n");
		send(socket,(void*)mensaje,strlen(mensaje),0);
	}
	strcpy(mensaje,"FIN");
	send(socket,(void*)mensaje,strlen(mensaje),0);
	return;
}	

void interpretar_mensaje(char *mensaje, char *clave, char *valor)
{
	int ini=0,fin=0;
	while( mensaje[fin] != '=')
	{
		fin++;
	}
	mensaje[fin]='\0';
	strcpy(clave,&mensaje[ini]);
	ini=fin+1;
	while( mensaje[fin] != '\n' && mensaje[fin] != '\0' )
	{
		fin++;
	}
	mensaje[fin]='\0';
	strcpy(valor,&mensaje[ini]);
	printf("%d\n",ini);
}

void matar_hilo (int signal)
{
		
	pthread_mutex_lock(&mtx_matar);			
	pthread_mutex_lock(&mtx_lista);
	borrar_aparicion(&clientes,&matar,comparacion);
	pthread_mutex_unlock(&mtx_lista);
	close(matar.socket);
	printf("------------------------------------------\n");
	printf("Se ha borrado con exito el cliente nro %d\n",matar.socket);
	printf("------------------------------------------\n");
	pthread_join(matar.hilo,NULL);
	pthread_mutex_unlock(&mtx_matar);
	return;
}

void terminar (int signal)
{
}

void* escuchar_cliente(void *psocket)
{
	int* paux= (int*) psocket;	
	int socket_cliente=*paux;
	char buffer [1024], clave[1024], valor[1024];
	char* enviar= "Escriba sus peticiones\n";
	send(socket_cliente,(void*)enviar,strlen(enviar),0);
	while(1)
	{
		bzero(buffer,1024);
		bzero(clave,1024);
		bzero(valor,1024);
		recv(socket_cliente,buffer,1024,0);
		pthread_mutex_lock(&mtx_buffer);	
		if( strcmp(buffer,"QUIT")==0)
		{
			pthread_mutex_lock(&mtx_matar);			
			matar.socket=socket_cliente;
			matar.hilo=pthread_self();
			kill(pid_server,SIGUSR1);
			pthread_mutex_unlock(&mtx_matar);
			pthread_exit(0);
			return 0;
		}
		interpretar_mensaje(buffer,clave,valor);
		printf("Clave: %s Valor: %s Socket: %d\n",clave,valor,socket_cliente);
		buscar_registro(clave,valor,socket_cliente,&articulos);
		pthread_mutex_unlock(&mtx_buffer);
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
	int i=0;
	pid_server=getpid();
	
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

	signal(SIGUSR1,matar_hilo); // comportamiento para que cuando un hilo finalice, se cierre el socket y se haga join al hilo
	//signal(SIGINT,terminar); // comportamiento para que cuando se haga ctrl + c en el servidor se cierren todos los socket, se maten los hilos y finalice el proceso

	crear_lista_articulo(&articulos);
	if (cargar_lista_articulos_con_archivo(&articulos,PATH_DB) != TODO_BIEN)
	{
		return ERROR;
	}
	//recorrer_lista_articulo(&articulos,mostrar_articulo);
	while(1)
	{		
		t_dato dato; 
		dato.socket= accept(servidor_socket,(struct sockaddr *) &ca, &cl);
		pthread_create(&dato.hilo,NULL,escuchar_cliente,(void *)&dato.socket);
		pthread_mutex_lock(&mtx_lista);
		insertar_ordenado(&clientes,&dato,comparacion);		
		pthread_mutex_unlock(&mtx_lista);
		printf("------------------------------------------\n");
		printf("Clientes actuales:\n");	
		recorrer_lista(&clientes,mostrar);	
		printf("------------------------------------------\n");	
			
	}
		
	close(servidor_socket);
	vaciar_lista_articulo(&articulos);
	return OK;
}

