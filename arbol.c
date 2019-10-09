#include "arbol.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void crear_arbol(tArbol * a){
    *a = (tArbol) malloc(sizeof(struct arbol));
    (*a) -> raiz = NULL;
}

void crear_raiz(tArbol a, tElemento e){
    if(a==NULL || a->raiz!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    tNodo nuevaRaiz = (tNodo) malloc(sizeof(struct nodo));//Creo la nueva raiz
    nuevaRaiz -> elemento = e;
    tLista listah = (tLista) malloc(sizeof(struct Nodo));//Creo la lista de hijos de esa raiz
    crear_lista(&listah);
    nuevaRaiz -> hijos = listah;
    nuevaRaiz -> padre = NULL;
    a -> raiz = nuevaRaiz;
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
     if(a==NULL || a->raiz==NULL) //Si el arbol es null o la raiz es null
        exit(ARB_ERROR_MEMORIA);
     if(nh!=NULL && lRecuperar(np->hijos,nh)==NULL)//Si nh no es null y no pertenece a los hijos de np
        exit(ARB_POSICION_INVALIDA);
     if(np==NULL) //Si el padre es null
        exit(ARB_POSICION_INVALIDA);

     tNodo nuevonodo = (tNodo) malloc(sizeof(struct nodo));
     nuevonodo -> elemento = e;
     nuevonodo -> padre = np;
     tLista listah = (tLista) malloc(sizeof(struct Nodo));//Creo la lista de hijos de esa raiz
     crear_lista(&listah);
     nuevonodo -> hijos = listah;

     if(nh==NULL){
        l_insertar(np->hijos,np->hijos,nuevonodo);//Agrego el nuevonodo como ultimo hijo
     }else{
        l_insertar(np->hijos,l_recuperar(np->hijos,),nuevonodo);//Agrego el nuevonodo antes de nh
     }
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)) {
    if (a->raiz == n && l_longitud(n->hijos) > 1)
        exit(ARB_OPERACION_INVALIDA);
    if (a->raiz == n) {
        if (l_longitud(n->hijos) = 1) {
            a -> raiz = l_primera(n->hijos) -> elem;
        }
    }
}

void n_destruir(tNodo * n, void (*fEliminar)(tElemento)) {
    tPosicion ultima, actual, posEnListaHijos;
    tNodo aDestruir;
    int encontre;
    if (l_longitud((*n)->hijos) > 0) {
        ultima = l_fin((*n)->hijos);
        actual = l_primera((*n)->hijos);
        while (actual != ultima) {
            aDestruir = l_recuperar((*n)->hijos, actual);
            n_destruir(&aDestruir, fEliminar);
            free(l_recuperar((*n)->hijos, actual));
            actual = l_siguiente((*n)->hijos, actual);
        }
    }

    posEnListaHijos = l_primera(((*n)->padre)->hijos);
    ultima = l_fin(((*n)->padre)->hijos);
    encontre = 0;

    while (!encontre && posEnListaHijos != ultima) {
        found = l_recuperar(((*n)->padre)->hijos, posEnListaHijos) == *n;
        if (!encontre)
            posPadre = l_siguiente(((*n)->padre)->hijos, posEnListaHijos);
    }

    l_eliminar(((*n)->padre)->hijos, posEnListaHijos, &fNoEliminar);
    (*n)->padre = NULL;
    l_destruir(&((*n)->hijos), fEliminar);
    fEliminar((*n)->elemento);
}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
    n_destruir(&( (*a) -> raiz), fEliminar);
    (*a)->raiz = NULL;
    free(*a);
}

tElemento a_recuperar(tArbol a, tNodo n) {
    if(a==NULL || n==NULL)
        exit(ARB_OPERACION_INVALIDA);
    return n->elemento;
}


tNodo a_raiz(tArbol a) {
    if(a==NULL )
        exit(ARB_OPERACION_INVALIDA);
    return a->raiz
}

tLista a_hijos(tArbol a, tNodo n) {
    if (n == NULL || a == NULL)
        exit(ARB_POSICION_INVALIDA);
    return n->hijos;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) {
    tNodo padre;
    tPosicion actual, ultima;
    int found;

    if (a == NULL || n == NULL || sa == NULL || *sa == NULL)
        exit(ARB_POSICION_INVALIDA);

    if (a->raiz != n) {
        (*sa)->raiz = n;
        padre = n->padre;
        actual = l_primera(padre->hijos);
        ultima = l_fin(padre->hijos);
        found = 0;

        while (!found && actual != ultima) {
            found = l_recuperar(padre->hijos, actual) == n;
            if (!found)
                actual = l_siguiente(padre->hijos, actual);
        }

        if (!found)
            exit(ARB_POSICION_INVALIDA);

        l_eliminar(padre->hijos, actual, &fNoEliminar);
    }
    else {
        (*sa)->raiz = n;
        a->raiz = NULL;
    }
}

