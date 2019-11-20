#include "lista_articulos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crear_lista_articulo(t_lista_articulo *pl)
{
    *pl=NULL;
}

void vaciar_lista_articulo(t_lista_articulo *pl)
{
    t_nodo_articulo *pnodo;
    while(*pl)
    {
        pnodo=*pl;
        *pl=pnodo->psig;
        free(pnodo);
    }
}

int insertar_ordenado_articulo(t_lista_articulo *pl,const t_dato_articulo *pd,t_cmp_articulo cmp)
{
    t_nodo_articulo *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return DUPLICADO;
    pnodo=(t_nodo_articulo*)malloc(sizeof(t_nodo_articulo));
    if(!pnodo)
        return LISTA_LLENA;
    pnodo->dato=*pd;
    pnodo->psig=*pl;
    *pl=pnodo;
    return TODO_BIEN;
}

void recorrer_lista_articulo(const t_lista_articulo *pl,t_fun_articulo fun)
{
    printf("\n\n");
    while(*pl)
    {
        fun(&(*pl)->dato);
        pl=&(*pl)->psig;
    }
    printf("\n\n");
}

int existe_nodo_articulo(const t_lista_articulo *pl,const t_dato_articulo *pd,t_cmp_articulo cmp)
{
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return EXISTE;
    return NO_EXISTE;
}

int borrar_nodo_articulo(t_lista_articulo *pl,const t_dato_articulo *pd,t_cmp_articulo cmp)
{
    t_nodo_articulo *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)!=0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        {
            pnodo=*pl;
            *pl=pnodo->psig;
            free(pnodo);
            return TODO_BIEN;
        }
    return NO_EXISTE;
}

int cargar_lista_articulos_con_archivo(t_lista_articulo *pl,const char *path)
{
	t_dato_articulo registro;
	char linea[200];
	int ini;
	int fin;
	FILE *fp;
	fp=fopen(path,"rt");
	if(!fp)
	{	
		printf("Error al abrir la base de datos :\n");
		perror(path); //esto es para mostrar el error en caso de que no funcione		
		return ERROR_ARCHIVO;
	}
	fgets(linea,200,fp);
	while( fgets(linea,200,fp) )
	{
		ini=0;
		fin=0;
		while( linea[fin] != ';' )
		{
			fin++;
		}
		linea[fin]='\0';
		registro.id=atoi(&linea[ini]);
		//printf("%d\n",registro.id);
		fin++;
		ini=fin;
		while( linea[fin] != ';' )
		{
			fin++;
		}
		linea[fin]='\0';
		strcpy(registro.articulo,&linea[ini]);
		//printf("%s\n",registro.articulo);
		fin++;
		ini=fin;
		while( linea[fin] != ';' )
		{
			fin++;
		}
		linea[fin]='\0';
		strcpy(registro.producto,&linea[ini]);
		//printf("%s\n",registro.producto);
		fin++;
		ini=fin;
		while( linea[fin] != '\n' && linea[fin] != '\0' )
		{
			fin++;
		}
		linea[fin]='\0';
		strcpy(registro.marca,&linea[ini]);
		//printf("%s\n",registro.marca);
		if ( insertar_ordenado_articulo(pl, &registro, comparacion_articulo) != TODO_BIEN)
		{
			printf("Error al poner en lista\n");
			return ERROR_ARCHIVO;
		}	
	}
	
	fclose(fp);
	return TODO_BIEN;	
}


////////////////////////////////////UTILITARIAS//////////////////////////////////

int comparacion_articulo(const t_dato_articulo *pd1,const t_dato_articulo *pd2)
{
    return pd1->id-pd2->id;
}

void mostrar_articulo(const t_dato_articulo *pd)
{
    printf("id: %d\n producto: %s\n marca: %s\n articulo: %s\n",pd->id,pd->producto,pd->marca,pd->articulo);
}
