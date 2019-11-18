#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define TODO_BIEN 1
#define LISTA_LLENA 0
#define LISTA_VACIA -1
#define DUPLICADO -2
#define NO_EXISTE -3
#define EXISTE -4

typedef int t_dato;
typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo *psig;
}t_nodo;
typedef t_nodo* t_lista;
typedef int(*t_cmp)(const t_dato*,const t_dato*);
typedef void(*t_fun)(const t_dato*);

void crear_lista(t_lista*);
void vaciar_lista(t_lista*);
int insertar_ordenado_SD(t_lista*,const t_dato*,t_cmp);
int insertar_ordenado_CD(t_lista*,const t_dato*,t_cmp);
int insertar_final(t_lista*,const t_dato*);
void recorrer_lista(const t_lista*,t_fun);
int existe_nodo(const t_lista*,const t_dato*,t_cmp);
int borrar_aparicion(t_lista*,const t_dato*,t_cmp);
int borrar_duplicados(t_lista*,const t_dato*,t_cmp); ///Solamente deja una aparicion del nodo
void borrar_todos_duplicados(t_lista*,t_cmp); ///Borra todos los duplicados de todos los nodos
void ordenar_lista(t_lista*,t_cmp);

int comparacion(const t_dato*,const t_dato*);
void mostrar(const t_dato*);
#endif // LISTA_H_INCLUDED
