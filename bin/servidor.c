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
#include "../lib/cola.h"

#define ERROR -1
#define OK 1
#define MAX_QUEUE 999
#define PATH_DB "./archivos/db"

t_lista_articulo articulos;
t_lista clientes;
t_cola peticiones;
pid_t pid_server;
t_dato matar;
pthread_mutex_t mtx_cola = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_lista = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_matar = PTHREAD_MUTEX_INITIALIZER;

void* escuchar_cliente(void*);
void* atender_peticiones(void *);
void terminar(int);
void matar_hilo(int);
void interpretar_mensaje(char*,char*,char*);
void buscar_registro(char*,char*,int,const t_lista_articulo*);

void buscar_registro(char *clave,char *valor ,int socket,const t_lista_articulo *pl)
{
	t_nodo_articulo *aux= *pl, *aux1;
	int id = atoi(valor), campo = -1,cantidad=0;;
	char *mensaje;
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
		mensaje="No se pudo realizar la búsqueda, el campo a filtrar es erroneo\n";
		send(socket,mensaje,strlen(mensaje),0);
		return;
	}
	while ( aux!=NULL)
	{
		if(campo==0 && id==aux->dato.id)
		{
			char *string;
			sprintf(string,"%d",aux->dato.id);			
			strcpy(mensaje,string);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.producto);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.marca);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		if(campo==1 && strcmp(valor,aux->dato.articulo))
		{
			char *string;
			sprintf(string,"%d",aux->dato.id);
			strcpy(mensaje,string);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.producto);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.marca);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		if(campo==2 && strcmp(valor,aux->dato.producto))
		{
			char *string;
			sprintf(string,"%d",aux->dato.id);			
			strcpy(mensaje,string);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.producto);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.marca);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		if(campo==3 && strcmp(valor,aux->dato.marca))
		{
			char *string;
			sprintf(string,"%d",aux->dato.id);			
			strcpy(mensaje,string);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.producto);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.marca);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			strcpy(mensaje,aux->dato.articulo);
			send(socket,(void*)mensaje,strlen(mensaje),0);
			cantidad++;		
		}
		aux1=aux;
		aux=aux1->psig;
		
	}
	if(cantidad==0)
	{
		mensaje="No hubo coincidencias\n";
		send(socket,(void*)mensaje,strlen(mensaje),0);
	}
	return;
}	

void interpretar_mensaje(char *mensaje, char *clave, char *valor)
{
	int ini=0,fin=0;
	char aux[256];
	while( mensaje[fin] != '=')
	{
		fin++;
	}
	strncpy(aux,&mensaje[ini],fin);
	aux[fin-ini]='\0';
	strcpy(clave,aux);
	ini=++fin;
	while( mensaje[fin] != '\n' && mensaje[fin] != '\0' )
	{
		fin++;
	}
	strncpy(aux,&mensaje[ini],fin);
	aux[fin-ini]='\0';
	strcpy(valor,aux);
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
	char buffer [256], clave[256], valor[256];
	t_dato_c aux;
	char* enviar= "Escriba sus peticiones\n";
	send(socket_cliente,(void*)enviar,strlen(enviar),0);
	while(1)
	{
		bzero(buffer,256);
		recv(socket_cliente,buffer,256,0);
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
		/*		
		strcpy(aux.buffer, buffer);
		aux.socket=socket_cliente;
		pthread_mutex_lock(&mtx_cola);
		if(!cola_llena(&peticiones))
		{
			acolar(&peticiones,&aux);
		}
		pthread_mutex_unlock(&mtx_cola);
		*/
		interpretar_mensaje(buffer,clave,valor);
		printf("Clave: %s Valor: %s Socket: %d\n",clave,valor,socket_cliente);
		buscar_registro(clave,valor,socket_cliente,&articulos);
	}

}

void* atender_peticiones(void* nro)
{
	t_dato_c aux;
	char clave[256], valor[256];	
	while(1)
	{
		pthread_mutex_lock(&mtx_cola);	
		if(!cola_vacia(&peticiones))
		{
			desacolar(&peticiones,&aux);
			interpretar_mensaje(aux.buffer,clave,valor);
			printf("Clave: %s Valor: %s Socket: %d\n",clave,valor,aux.socket);
			buscar_registro(clave,valor,aux.socket,&articulos);
						
		}
		pthread_mutex_unlock(&mtx_cola);
	}
	
}

int main (int argc, char *argv[])
{
	socklen_t cl=sizeof(struct sockaddr_in);
	struct sockaddr_in sa;
	struct sockaddr_in ca;
	int servidor_socket;
	pthread_t hilo_peticiones;
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

	crear_cola(&peticiones);

	listen(servidor_socket,MAX_QUEUE);

	pthread_create(&hilo_peticiones,NULL,atender_peticiones,NULL);

	signal(SIGUSR1,matar_hilo); // comportamiento para que cuando un hilo finalice, se cierre el socket y se haga join al hilo
	//signal(SIGINT,terminar); // comportamiento para que cuando se haga ctrl + c en el servidor se cierren todos los socket, se maten los hilos y finalice el proceso

	crear_lista_articulo(&articulos);
	if (cargar_lista_articulos_con_archivo(&articulos,PATH_DB) != TODO_BIEN)
	{
		return ERROR;
	}
	
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
		
	pthread_join(hilo_peticiones,NULL);
	close(servidor_socket);
	vaciar_lista_articulo(&articulos);
	return OK;
}

