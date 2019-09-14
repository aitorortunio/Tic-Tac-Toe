//
// Created by Aitor Ortuño  on 14/09/2019.
//
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    return 0;
}

void crear_lista(tLista *l){
    tLista lista = (tLista) malloc(sizeof(struct Nodo));
    lista->elem = NULL;
    lista->sig = NULL;
    *l = lista;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e){
    if(l == NULL){

    }
    else{
        tElemento elem = p->sig->elem;
        struct Nodo *actual = l->sig;
        while (actual->sig->elem != elem) { //Comparación por punteros????
            *actual = *actual->sig;
        }
        tPosicion nuevo = (tPosicion) malloc(sizeof(struct Nodo)); //Por qué tengo que usar tPosicion
        nuevo->elem = e;
        nuevo->sig = actual->sig;
        actual->sig = nuevo;//Nuevo debería ser un puntero??
    }
}