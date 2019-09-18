//
// Created by Aitor Ortuño  and Nahuel Maika on 17/09/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void fEliminar(tElemento elem){
    elem=NULL;
}

int main(){
    tLista l;
    crear_lista(&l);//Creo lista vacía
    printf("CREO LISTA VACÍA\n");
    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 0

    int *e1=(int*)1;
    tElemento elem1=e1;

    l_insertar(l,l, elem1);//Inserto 1 en la primera posicion de la lista
    printf("INSERTO 1 EN LA 1RA POSICION\n");
    printf("El elemento en la 1ra posicion(usando l_primera) es: %i\n",(int)l_primera(l)->elem);//Retorna 1

    printf("El elemento en la 1ra posicion(usando l_recuperar) es: %i\n",(int)l_recuperar(l,l));//Retorna 1
    tPosicion pos1=l_primera(l);//Guardo la pos en memoria de 1

    int *e2=(int*)2;
    tElemento elem2=e2;
    l_insertar(l,l,elem2);//Inserto 2 en la 2da posicion de la lista
    printf("INSERTO 2 EN LA 1RA POSICION\n");
    tPosicion pos2=l_primera(l);//Guardo la pos en memoria de 2
    printf("El elemento en la 1ra posicion(usando l_primera) es: %i\n",(int)pos2->elem);//Retorna 2

    printf("El elemento en la 1ra posicion(usando l_anterior) es: %i\n",(int)l_anterior(l,pos1)->elem);//Retorna 2

    printf("El elemento en la 2da posicion(usando l_siguiente) es: %i\n",(int)l_siguiente(l,pos2)->elem);//Retorna 1


    int*e3=(int*)3;
    tElemento elem3=e3;
    l_insertar(l,pos2,elem3);//Inserto 3 en la 2da posicion de la lista;
    printf("INSERTO 3 EN LA 2DA POSICION\n");
    tPosicion pos3=l_ultima(l);//Guardo la posicion de 3
    printf("El elemento en la 3ra posicion(usando l_fin) es: %i\n",(int)l_fin(l)->elem);//Retorna 1

    printf("El elemento en la 2da posicion(usando l_ultima) es: %i\n",(int)pos3->elem);//Retorna 3

    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 3

    l_eliminar(l,l,&fEliminar);//Elimino el 2
    free(pos2);
    printf("Pos2 es:%i\n",(int)pos2->elem);

    printf("ELIMINO EL 2 EN LA 1RA POSICION\n");

    printf("El 1er elemento de la lista(usando l_primera) es: %i\n",(int)l_primera(l)->elem);//Retorna 3

    printf("El 2do elemento de la lista(usando l_fin) es: %i\n",(int)l_fin(l)->elem);//Retorna 1

    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 2

    l_destruir(&l,&fEliminar);

    printf("DESTRUYO LA LISTA\n");

    free(pos1);
    free(pos3);

    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 0




    return 0;
}
