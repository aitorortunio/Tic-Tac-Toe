//
// Created by Aitor Ortuño  and Nahuel Maika on 17/09/2019.
//
#include <stdio.h>
#include "lista.c"
int main(){
    tLista l;
    int *e=4;
    tElemento elem=e;
    crear_lista(&l);
    l_insertar(l,l, elem);
    printf("%i",l_primera(l)->elem);
    return 0;
}
