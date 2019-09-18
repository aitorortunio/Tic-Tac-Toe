//
// Created by Aitor Ortuño and Nahuel Maika on 14/09/2019.
//

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/**
 Crea una lista vacía, solo tiene el nodo centinela
**/
void crear_lista(tLista *l){
    *l = (tLista) malloc(sizeof(struct Nodo));
    (*l)->elem = NULL;
    (*l)->sig = NULL;
}

/**
 Inserta un elemento nuevo ´e´ antes de la posicion ´p´ en la lista ´l´
 Si tengo A,B,C y quiero insertar D, entonces me queda A,B,D,C.
 Si tengo una lista vacía y quiero insertar A, entonces me queda A
**/
void l_insertar(tLista l, tPosicion p, tElemento e){
    if(p==NULL)
        exit(LST_POSICION_INVALIDA);
    tPosicion nuevo=(tPosicion)malloc(sizeof(struct Nodo));
    nuevo->elem=e;//Le asigno a nuevo el elemento e
    nuevo->sig=p->sig;//Le asigno a nuevo como siguiente al siguiente de p(ya que usamos posicion indirecta)
    p->sig=nuevo;//Le asigno a p como siguiente a nuevo
}

/**
 Elimina el elemento en la posicion ´p´ de la lista ´l´
 Si tengo A,B,C y quiero eliminar B, me queda A,C.
 Si tengo A y quiero eliminar A, me queda una lista vacía
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){//Me pasan una función ??
    if(p==NULL || p->sig==NULL)
        exit(LST_POSICION_INVALIDA);
    tPosicion eliminar=p->sig;
    p->sig=eliminar->sig;
    eliminar->sig=NULL;
    fEliminar(eliminar->elem);
    free(eliminar);
}

void l_destruirAux(tPosicion p,void (*fEliminar)(tElemento));

/**
 *
 * Elimina todos los elementos de la lista de forma recursiva.
 * Si la lista ya es vacía no realiza cambios
 */
void l_destruirAux(tPosicion aux,void (*fEliminar)(tElemento)){
    if(aux->sig==NULL){
        fEliminar(aux->elem);
        free(aux);
    }
    else{
        aux= aux->sig;
        l_destruirAux(aux,fEliminar);
        aux->sig=NULL;
        fEliminar(aux->elem);
        free(aux);
    }
}

/**
 Destruye la lista y la deja vacía
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    tPosicion aux = *l;
    l_destruirAux(aux,fEliminar);
    (*l)->sig=NULL;
}

/**
 Recupera y retorna el elemento en la posicion ´p´
**/
tElemento l_recuperar(tLista l, tPosicion p){
    if(p==NULL || p->sig==NULL)
        exit(LST_POSICION_INVALIDA);
    return p->sig->elem;
}

/**
 Retorna la primera posicion de la lista ´l´
 Si la lista esta vacía, retorna NULL
**/
tPosicion l_primera(tLista l){
    if(l==NULL)
        exit(LST_ELEMENTO_NULO);
    return l->sig;
}

/**
 Retorna la posicion siguiente a ´p´
**/
tPosicion l_siguiente(tLista l, tPosicion p){
    if(p==NULL)
        exit(LST_POSICION_INVALIDA);
    if(p->sig==NULL)//Si el siguiente al siguiente de la pos p ==null
        exit(LST_NO_EXISTE_SIGUIENTE);
    return p->sig;
}

/**
 Retorna la posicion anterior a ´p´
**/
tPosicion l_anterior(tLista l, tPosicion p){
    if(p==NULL)
        exit(LST_POSICION_INVALIDA);
    if(p==l || p==l->sig)//l es la referencia al primer elemento (centinel) de la lista
        exit(LST_NO_EXISTE_ANTERIOR);
    tPosicion aux = l;
    while(aux->sig!=p){
        aux = aux->sig;
    }
    return aux;
}

/**
 Retorna la ultima posicion de la lista ´l´
 Si ´l´ esta vacía retorna NULL
**/
tPosicion l_ultima(tLista l){
    if(l==NULL)
        exit(LST_ELEMENTO_NULO);
    tPosicion posToRet;
    tPosicion aux=l;
    if(l->sig==NULL){//Si la lista es vacía retorna NULL
        posToRet=l;
    }else{
        while(aux->sig->sig!=NULL)//Se repite hasta que aux apunte al último
            aux=aux->sig;
        posToRet=aux;
    }
    return posToRet;
}

/**
**/
tPosicion l_fin(tLista l){
    if(l==NULL)
        exit(LST_ELEMENTO_NULO);
    tPosicion posToRet;
    tPosicion aux=l;
    if(l->sig==NULL){//Si la lista es vacía retorna NULL
        posToRet=l;
    }else{
        while(aux->sig!=NULL)//Se repite hasta que aux apunte al último
            aux=aux->sig;
        posToRet=aux;
    }
    return posToRet;
}

/**
 Retorna la longitud de ´l´
**/
int l_longitud(tLista l){
    int size=0;
    tPosicion aux=l;
    while(aux->sig!=NULL){
        aux=aux->sig;
        size=size+1;
    }
    return size;
}
