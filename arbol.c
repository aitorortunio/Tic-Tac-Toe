#include "arbol.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void (*fElim)(tElemento) = NULL;

void fNoEliminar(tElemento e){}

void fNodoEliminar(tNodo n, void (*fEliminar)(tElemento)) {
    fEliminar(n->elemento);

    if (n->hijos != NULL) {
        l_destruir(&(n->hijos), &fNoEliminar);
        n->hijos = NULL;
    }
    n->padre = NULL;
    free(n);
}

void crear_arbol(tArbol * a){
    *a = (tArbol) malloc(sizeof(struct arbol));
    (*a) -> raiz = NULL;
}

void crear_raiz(tArbol a, tElemento e){
    if(a==NULL || a->raiz!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    tNodo nuevaRaiz = (tNodo) malloc(sizeof(struct nodo));//Creo la nueva raiz
    nuevaRaiz -> elemento = e;
    crear_lista(&nuevaRaiz->hijos);
    nuevaRaiz -> padre = NULL;
    a -> raiz = nuevaRaiz;
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    if(a==NULL || a->raiz==NULL || np==NULL) //Si el arbol es NULL o la raiz es NULL
        exit(ARB_POSICION_INVALIDA);
    if(nh!=NULL && nh->padre!=np)//Si nh no es NULL y su padre no es np
        exit(ARB_POSICION_INVALIDA);

    tNodo nuevonodo;
    tPosicion nActual=l_primera(np->hijos);
    tPosicion nFin=l_fin(np->hijos);

    if(nh==NULL){//Si nh es NULL
        nuevonodo=(tNodo)malloc(sizeof(struct nodo));
        nuevonodo->elemento=e;
        nuevonodo->padre=np;
        crear_lista(&nuevonodo->hijos);
        l_insertar(np->hijos,nFin,nuevonodo); //Agrego el nuevo nodo despues del ultimo nodo de la lista
    }

    if(nh!=NULL){//Si nh no es NULL
        int esHijonp=0;

        while(esHijonp==0 && nActual!=nFin){//Veo si nh pertenece a la lista de hijos de np
            if(l_recuperar(np->hijos,nActual)==nh)
                esHijonp=1;
            if(esHijonp==0)
                nActual=l_siguiente(np->hijos,nActual);
        }

        if(esHijonp==0)//Si nh no pertenece a la lista de hijos de np
            exit(ARB_POSICION_INVALIDA);

        nuevonodo=(tNodo)malloc(sizeof(struct nodo));
        nuevonodo->elemento=e;
        nuevonodo->padre=np;
        crear_lista(&nuevonodo->hijos);
        l_insertar(np->hijos,nActual,nuevonodo);
    }

    //modularizar la creacion del nodo.

    return nuevonodo;
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)) {
    if(a->raiz==n){//Si n es la raiz de a
        if(l_longitud(n->hijos)==0){//Si n no tiene hijos
            fNodoEliminar(n,fEliminar);//NO SE SI ESTA BIEN
            a->raiz=NULL;

        }else if(l_longitud(n->hijos)==1){//Si n tiene un unico hijo
            tNodo nuevaraiz=l_primera(n->hijos)->elem;
            nuevaraiz->padre=NULL;
            a->raiz=nuevaraiz;

            fNodoEliminar(n,fEliminar);//NO SE SI ESTA BIEN

        }else if(a->raiz == n && l_longitud(n->hijos)>1){//Si n tiene mas de un hijo
            exit(ARB_OPERACION_INVALIDA);
        }

    }else{//Si n no es raiz de a
        tNodo padren = n->padre;
        tPosicion nEnPadre = l_primera(padren->hijos);//Guardo la posicion de n en la lista de hijos de su padre
        tPosicion ultimo=l_fin(padren->hijos);

        int encontre = 0;

        while(nEnPadre!=ultimo && !encontre)  {
            encontre= l_recuperar(padren->hijos,nEnPadre) == n;

            if (!encontre)
                nEnPadre = l_siguiente(padren->hijos, nEnPadre);
        }
        if(!encontre)
            exit(ARB_POSICION_INVALIDA);

        tPosicion hijon;
        tNodo hijoactualn;

        if(n->hijos!=NULL)
           hijon = l_primera(n->hijos);//Guarda la posicion de hijon en la lista de hijos de n
        else
            hijon=NULL;

        while(hijon!=NULL && hijon!=l_fin(n->hijos)){//Inserto hijos de n en la lista de hijos  del padre de n
            hijoactualn =l_recuperar(n->hijos,hijon);
            l_insertar(padren->hijos,nEnPadre,hijoactualn);
            hijoactualn->padre=padren;
            nEnPadre=l_siguiente(padren->hijos,nEnPadre);//Mantiene actualizada la pos de n en la lista de hijos del padre
            hijon = l_siguiente(n->hijos,hijon);
        }
        l_eliminar(padren->hijos,nEnPadre,fNoEliminar);

        if (l_longitud(padren->hijos) == 0) {
            l_destruir(&(padren->hijos), fNoEliminar);
            padren->hijos = NULL;
        }

        fNodoEliminar(n,fEliminar);
    }

}

void eliminar (tNodo n,void (*fEliminar)(tElemento)){
    tLista listaDeHijosDeN = n->hijos;
    if(listaDeHijosDeN != NULL && l_longitud(listaDeHijosDeN)>0){
        tPosicion actual = l_primera(listaDeHijosDeN);
        tPosicion fin = l_ultima(listaDeHijosDeN);
        while(actual != fin){
            eliminar((tNodo)l_recuperar(listaDeHijosDeN,actual),fEliminar);
            actual = l_siguiente(listaDeHijosDeN,actual);
        }
        eliminar((tNodo)l_recuperar(listaDeHijosDeN,actual),fEliminar);
    }
    fNodoEliminar(n,fEliminar);
}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    if(*a==NULL)
        exit(ARB_OPERACION_INVALIDA);
    if((*a)->raiz!=NULL){
        eliminar(((*a)->raiz),fEliminar);
    }
    (*a)->raiz = NULL;
    free(*a);
    (*a) = NULL;
}

tElemento a_recuperar(tArbol a, tNodo n) {
    if(a==NULL || n==NULL)
        exit(ARB_OPERACION_INVALIDA);
    return n->elemento;
}


tNodo a_raiz(tArbol a) {
    if(a==NULL )
        exit(ARB_OPERACION_INVALIDA);
    return a->raiz;
}

tLista a_hijos(tArbol a, tNodo n) {
    if (n == NULL || a == NULL)
        exit(ARB_POSICION_INVALIDA);
    return n->hijos;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa) {
    tNodo padre;
    tPosicion actual, ultima;
    int encontre;

    if (a == NULL || n == NULL || sa == NULL || *sa == NULL)
        exit(ARB_POSICION_INVALIDA);

    crear_arbol(sa);

    if (a->raiz != n) {
        (*sa)->raiz = n;
        padre = n->padre;
        actual = l_primera(padre->hijos);
        ultima = l_fin(padre->hijos);
        encontre = 0;
        while (!encontre && actual != ultima) {
            encontre = l_recuperar(padre->hijos, actual) == n;
            if (!encontre)
                actual = l_siguiente(padre->hijos, actual);
        }
        if (!encontre)
            exit(ARB_POSICION_INVALIDA);
        l_eliminar(padre->hijos, actual, &fNoEliminar);
    }
    else {
        (*sa)->raiz = n;
        a->raiz = NULL;
    }
}
