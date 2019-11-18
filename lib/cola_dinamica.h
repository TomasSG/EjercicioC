#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define COLA_LLENA 0
#define COLA_VACIA 0
#define TODO_BIEN 1
typedef int t_dato;
typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo *psig;
}t_nodo;

typedef struct
{
    t_nodo *ppri;
    t_nodo *pult;

} t_cola;

void crear_cola (t_cola *);
int cola_vacia (const t_cola*);
int cola_llena (const t_cola*);
int acolar (t_cola*,const t_dato*);
int desacolar (t_cola*,t_dato*);
int ver_primero (const t_cola*,t_dato*);
void vaciar_cola (t_cola*);



#endif // COLADINAMICA_H_INCLUDED
