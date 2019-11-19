#ifndef LISTA_ARTICULOS_H_INCLUDED
#define LISTA_ARTICULOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define TODO_BIEN 1
#define LISTA_LLENA 0
#define LISTA_VACIA -1
#define DUPLICADO -2
#define NO_EXISTE -3
#define EXISTE -4
#define ERROR_ARCHIVO -5

typedef struct
{
	int id;
	char producto[100];
	char marca[100];
	char articulo[100];
} t_dato_articulo;
typedef struct s_nodo_articulo
{
    t_dato_articulo dato;
    struct s_nodo_articulo *psig;
}t_nodo_articulo;
typedef t_nodo_articulo* t_lista_articulo;
typedef int(*t_cmp_articulo)(const t_dato_articulo*,const t_dato_articulo*);
typedef void(*t_fun_articulo)(const t_dato_articulo*);

void crear_lista_articulo(t_lista_articulo*);
void vaciar_lista_articulo(t_lista_articulo*);
int insertar_articulo(t_lista_articulo*,const t_dato_articulo*,t_cmp_articulo);
void recorrer_lista_articulo(const t_lista_articulo*,t_fun_articulo);
int existe_nodo_articulo(const t_lista_articulo*,const t_dato_articulo*,t_cmp_articulo);
int borrar_nodo_articulo(t_lista_articulo*,const t_dato_articulo*,t_cmp_articulo);
int cargar_lista_articulos_con_archivo(t_lista_articulo*,const char*);

int comparacion_articulo(const t_dato_articulo*,const t_dato_articulo*);
void mostrar_articulo(const t_dato_articulo*);
#endif // LISTA_ARTICULOS_H_INCLUDED
