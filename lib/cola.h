#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define COLA_LLENA 0
#define COLA_VACIA 0
#define TODO_BIEN 1
typedef struct
{
	char buffer [256] ;
	int socket;
} t_dato_c;
typedef struct s_nodo_c
{
    t_dato_c dato;
    struct s_nodo_c *psig;
} t_nodo_c;

typedef struct
{
    t_nodo_c *ppri;
    t_nodo_c *pult;

} t_cola;

void crear_cola (t_cola *);
int cola_vacia (const t_cola*);
int cola_llena (const t_cola*);
int acolar (t_cola*,const t_dato_c*);
int desacolar (t_cola*,t_dato_c*);
int ver_primero (const t_cola*,t_dato_c*);
void vaciar_cola (t_cola*);



#endif // COLADINAMICA_H_INCLUDED
