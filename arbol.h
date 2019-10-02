#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "lista.h"

#define ARB_OPERACION_INVALIDA      10
#define ARB_POSICION_INVALIDA       11
#define ARB_ERROR_MEMORIA           12

struct nodo{
    tElemento elemento;
    struct nodo * padre;
    tLista hijos;
};

struct arbol{
    struct nodo * raiz;
};

typedef struct nodo * tNodo;
typedef struct arbol * tArbol;


/**
Inicializa un �rbol vac�o.
Una referencia al �rbol creado es referenciado en *A.
**/
extern void crear_arbol(tArbol * a);

/**
Crea la ra�z de A.
Si A no es vac�o, finaliza indicando ARB_OPERACION_INVALIDA.
**/
extern void crear_raiz(tArbol a, tElemento e);

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r�tulo es E.
 Si NH es NULL, el nuevo nodo se agrega como �ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
extern tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e);

/**
 Elimina el nodo N de A.
 El elemento almacenado en el �rbol es eliminado mediante la funci�n fEliminar parametrizada.
 Si N es la ra�z de A, y tiene un s�lo hijo, este pasa a ser la nueva ra�z del �rbol.
 Si N es la ra�z de A, y a su vez tiene m�s de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra�z de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici�n que ocupa N en la lista de hijos de su padre.
**/
extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento));

/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

/**
Recupera y retorna el elemento del nodo N.
*/
extern tElemento a_recuperar(tArbol a, tNodo n);

/**
Recupera y retorna el nodo correspondiente a la ra�z de A.
**/
extern tNodo a_raiz(tArbol a);

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n);

/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
extern void a_sub_arbol(tArbol a, tNodo n, tArbol * sa);

#endif // ARBOL_H_INCLUDED
