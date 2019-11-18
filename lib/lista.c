#include "lista.h"

t_lista* buscar_menor(t_lista*,t_cmp);
void poner_al_principio(t_lista*,t_lista*);

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

int insertar_ordenado_SD(t_lista *pl,const t_dato *pd,t_cmp cmp)
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
    int n=0;
    printf("\n\n");
    while(*pl)
    {
        printf("NODO %d----> ",n);
        fun(&(*pl)->dato);
        n++;
        pl=&(*pl)->psig;
    }
    printf("\n\n");
}

int insertar_ordenado_CD(t_lista *pl,const t_dato *pd,t_cmp cmp)
{
    t_nodo *pnodo;
    while(*pl && cmp(pd,&(*pl)->dato)>0)
        pl=&(*pl)->psig;
    pnodo=(t_nodo*)malloc(sizeof(t_nodo));
    if(!pnodo)
        return LISTA_LLENA;
    pnodo->dato=*pd;
    pnodo->psig=*pl;
    *pl=pnodo;
    return TODO_BIEN;
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

int  borrar_duplicados(t_lista *pl,const t_dato *pd,t_cmp cmp)
{
    while(*pl && cmp(pd,&(*pl)->dato)!=0)
        pl=&(*pl)->psig;
    if(*pl && cmp(pd,&(*pl)->dato)==0)
        pl=&(*pl)->psig;
    else
        return NO_EXISTE;
    while(*pl)
    {
       if(borrar_aparicion(pl,pd,cmp)==NO_EXISTE)
            pl=&(*pl)->psig;
    }
    return TODO_BIEN;
}

int insertar_final(t_lista *pl,const t_dato *pd)
{
   t_nodo *pnodo=(t_nodo*)malloc(sizeof(t_nodo));
   if(!pnodo)
    return LISTA_LLENA;
   while(*pl)
        pl=&(*pl)->psig;
   pnodo->dato=*pd;
   pnodo->psig=*pl;
   *pl=pnodo;
   return TODO_BIEN;
}

void borrar_todos_duplicados(t_lista *pl,t_cmp cmp)
{
    t_nodo *pborrar;
    t_lista *pmover;
    t_dato dato;
    while(*pl)
    {
        dato=(*pl)->dato;
        pmover=&(*pl)->psig;
        while(*pmover)
        {
            if(cmp(&dato,&(*pmover)->dato)==0)
            {
                pborrar=*pmover;
                *pmover=pborrar->psig;
                free(pborrar);
            }
            else
                pmover=&(*pmover)->psig;
        }
        if(*pl)
            pl=&(*pl)->psig;
    }
}

void ordenar_lista(t_lista* lista,t_cmp comparacion)
{
    t_lista* menor;
    while(*lista)
    {
        menor=buscar_menor(lista,comparacion);
        if(*lista!=*menor)
            poner_al_principio(lista,menor);
        lista=&(*lista)->psig;
    }
}

t_lista* buscar_menor(t_lista* lista,t_cmp comparacion)
{
    t_lista *menor=lista;
    t_lista *aux=&(*lista)->psig;
    while (*aux)
    {
        if(comparacion(&(*menor)->dato,&(*aux)->dato)>0)
            menor=aux;
        aux=&(*aux)->psig;
    }
    return menor;
}

void poner_al_principio(t_lista*lista,t_lista*menor)
{
    t_nodo* aux=*menor;
    *menor=aux->psig;
    aux->psig=*lista;
    *lista=aux;
}

////////////////////////////////////UTILITARIAS//////////////////////////////////

int comparacion(const t_dato *pd1,const t_dato *pd2)
{
    return *(int*)pd1-*(int*)pd2;
}

void mostrar(const t_dato *pd)
{
    printf("%d\n",*pd);
}
