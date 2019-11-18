#include "cola_dinamica.h"

void crear_cola (t_cola * cola)
{
    cola->ppri=NULL;
    cola->pult=NULL;
}

int cola_vacia (const t_cola* cola)
{
    return cola->ppri == NULL;
}

int cola_llena (const t_cola* cola)
{
    void * aux;
    aux = malloc(sizeof(t_nodo));
    free (aux);
    return aux== NULL;
}

int acolar (t_cola* cola ,const t_dato* dato )
{
    t_nodo* nuevo;
    nuevo=(t_nodo*)malloc(sizeof(t_nodo));
    if(!nuevo)
        return COLA_LLENA;
    if(cola->ppri)
        cola->pult->psig=nuevo;
    else
        cola->ppri=nuevo;
    cola->pult=nuevo;
    nuevo->dato=*dato;
    nuevo->psig=NULL;
    return TODO_BIEN;
}

int desacolar(t_cola* cola ,t_dato* dato )
{
    t_nodo* aux;
    if (!cola->ppri)
            return COLA_VACIA;
    aux = cola->ppri;
    *dato=aux->dato;
    cola->ppri=aux->psig;
    free(aux);
    if(!cola->ppri)
        cola->pult=NULL;
    return TODO_BIEN;
}

int ver_primero (const t_cola *cola,t_dato *dato)
{
    if(!cola->ppri)
        return COLA_VACIA;
    *dato=cola->ppri->dato;
    return TODO_BIEN;
}

void vaciar_cola (t_cola *cola)
{
    t_nodo *aux;
    while (cola->ppri)
    {
        aux=cola->ppri;
        cola->ppri=aux->psig;
        free(aux);
    }
    cola->pult=NULL;
}
