#include "arbol.h"
#include "lista.h"
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
    crear_lista(&nuevaraiz->hijos);
    nuevaraiz->padre=NULL;
    a->raiz=nuevaraiz;
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
     if(a==NULL || a->raiz==NULL) //Si el arbol es null o la raiz es null
        exit(ARB_ERROR_MEMORIA);
     if(nh!=NULL && nh->padre!=np)//Si nh no es null y no pertenece a los hijos de np
        exit(ARB_POSICION_INVALIDA);
     if(np==NULL) //Si el padre es null
        exit(ARB_POSICION_INVALIDA);

     tNodo nuevonodo=(tNodo)malloc(sizeof(struct nodo));
     nuevonodo->elemento=e;
     nuevonodo->padre=np;
     crear_lista(&nuevonodo->hijos);

     if(nh==NULL){
        l_insertar(np->hijos,np->hijos,nuevonodo);//Agrego el nuevonodo como ultimo hijo
     }else{
         tPosicion nodol = l_primera(np->hijos);
         while(nodol->elem!=nh){
            nodol=l_siguiente(np->hijos,nodol);
         }
        l_insertar(np->hijos,nodol,nuevonodo);//Agrego el nuevonodo antes de nh
     }

     return nuevonodo;
}

void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    if(a->raiz==n && l_longitud(n->hijos)>1)
        exit(ARB_OPERACION_INVALIDA);
    if(a->raiz==n){//Si n es la raiz de a
        if(l_longitud(n->hijos)==0){//Si n no tiene hijos
            n->padre=NULL;
            //l_destruir(n->hijos);
            fEliminar(n->elemento);
            free(n);
            a->raiz=NULL;
        }else if(l_longitud(n->hijos)==1){//Si n tiene un unico hijo
            tNodo nuevaraiz=l_primera(n->hijos)->elem;
            nuevaraiz->padre=NULL;

            n->padre=NULL;
            //l_destruir(n->hijos);
            fEliminar(n->elemento);
            free(n);

            a->raiz=nuevaraiz;
        }

    }else{
        tNodo padren=n->padre;
        tPosicion nEnPadre = l_primera(padren->hijos);//Guardo la posicion de n en la lista de hijos de su padre
         while(nEnPadre->elem!=n){
            nEnPadre=l_siguiente(padren->hijos,nEnPadre);
         }
        tPosicion hijon=l_primera(n->hijos);//Guarda la posicion de hijon en la lista de hijos de n

        for(int i=0;i<l_longitud(n->hijos);i++){
            l_insertar(padren->hijos,nEnPadre,hijon->elem);
            hijon=l_siguiente(n->hijos,hijon);
        }
        //l_eliminar(padren->hijos,nEnPadre,)
        //l_destruir(&n->hijos,)
        n->padre=NULL;
        fEliminar(n->elemento);
        free(n);

    }

}

void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
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
}

