#include "arbol.h"
#include "lista.c"
#include <stdio.h>
#include <stdlib.h>

void crear_arbol(tArbol * a){
    *a=(tArbol)malloc(sizeof(struct arbol));
    (*a)->raiz = NULL;
}

void crear_raiz(tArbol a, tElemento e){
    if(a==NULL || a->raiz!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    tNodo nuevaraiz=(tNodo)malloc(sizeof(struct nodo));//Creo la nueva raiz
    nuevaraiz->elemento=e;
    tLista listah=(tLista)malloc(sizeof(struct Nodo));//Creo la lista de hijos de esa raiz
    crear_lista(&listah);
    nuevaraiz->hijos=listah;
    nuevaraiz->padre=NULL;
    a->raiz=nuevaraiz;
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
     if(a==NULL || a->raiz==NULL) //Si el arbol es null o la raiz es null
        exit(ARB_ERROR_MEMORIA);
     if(nh!=NULL && lRecuperar(np->hijos,nh)==NULL)//Si nh no es null y no pertenece a los hijos de np
        exit(ARB_POSICION_INVALIDA);
     if(np==NULL) //Si el padre es null
        exit(ARB_POSICION_INVALIDA);

     tNodo nuevonodo=(tNodo)malloc(sizeof(struct nodo));
     nuevonodo->elemento=e;
     nuevonodo->padre=np;
     tLista listah=(tLista)malloc(sizeof(struct Nodo));//Creo la lista de hijos de esa raiz
     crear_lista(&listah);
     nuevonodo->hijos=listah;

     if(nh==NULL){
        l_insertar(np->hijos,np->hijos,nuevonodo);//Agrego el nuevonodo como ultimo hijo
     }else{
        l_insertar(np->hijos,l_recuperar(np->hijos,),nuevonodo);//Agrego el nuevonodo antes de nh
     }
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    if(a->raiz==n && l_longitud(n->hijos)>1)
        exit(ARB_OPERACION_INVALIDA);
    if(a->raiz==n){
        if(l_longitud(n->hijos)=1){
            a->raiz=l_primera(n->hijos)->elem;

        }

    }

}
