#include "lista.h"

void crear_lista(t_lista *pl)
{
    *pl=NULL;
}

void vaciar_lista(t_lista *pl)
{
    t_nodo *pnodo;
    while(*pl)
    {
        pnodo=*pl;
        *pl=pnodo->psig;
        free(pnodo);
    }
}

int insertar_ordenado(t_lista *pl,const t_dato *pd,t_cmp cmp)
{
    t_nodo *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return DUPLICADO;
    pnodo=(t_nodo*)malloc(sizeof(t_nodo));
    if(!pnodo)
        return LISTA_LLENA;
    pnodo->dato=*pd;
    pnodo->psig=*pl;
    *pl=pnodo;
    return TODO_BIEN;
}

void recorrer_lista(const t_lista *pl,t_fun fun)
{
    //int n=0;
    printf("\n\n");
    while(*pl)
    {
        //printf("NODO %d----> ",n);
        fun(&(*pl)->dato);
        //n++;
        pl=&(*pl)->psig;
    }
    printf("\n\n");
}

int existe_nodo(const t_lista *pl,const t_dato *pd,t_cmp cmp)
{
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        return EXISTE;
    return NO_EXISTE;
}

int borrar_aparicion(t_lista *pl,const t_dato *pd,t_cmp cmp)
{
    t_nodo *pnodo;
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

////////////////////////////////////UTILITARIAS//////////////////////////////////

int comparacion(const t_dato *pd1,const t_dato *pd2)
{
    return pd1->socket-pd2->socket;
}

void mostrar(const t_dato *pd)
{
    printf("El nro de socket es: %d y el TID es: %ld\n",pd->socket,pd->hilo);
}
