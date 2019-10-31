//
// Created by Aitor Ortuño and Nahuel Maika on 17/09/2019.
//
/**
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"

void fEliminar(tElemento t) {
    free(t);
}

void imprimir(tLista list) {
    tPosicion temp = l_primera(list);
    if(l_longitud(list)==0)
        printf("La lista está vacía.\n");
    else {
        printf("%d ", *((int *) l_recuperar(list, list)));
        while (temp != l_fin(list)) {
            printf("%d ", *((int *) l_recuperar(list, temp)));
            temp = temp->sig;
        }
    }
    printf("\n");
}

void a_imprimir(tLista lista,tArbol arbol)
{
    tPosicion cursor    = l_primera(lista);
    tPosicion fin       = l_fin(lista);
    printf("Lista completa: ");

    while (cursor != fin)
    {
        tNodo nodo = (tNodo) l_recuperar(lista,cursor);
        printf("%d ,",*(int*)a_recuperar(arbol,nodo));
        cursor = l_siguiente(lista,cursor);
    }
    printf("\n");
}


void imprimir_ArbolRec(tArbol arbol, tNodo nodo)
{
    printf("Rotulo nodo: %d\n", *((int*) a_recuperar(arbol,nodo)));
    tLista hijos = a_hijos(arbol,nodo);
    a_imprimir(hijos,arbol);
    tPosicion cursor = l_primera(hijos);
    tPosicion fin = l_fin(hijos);
    while (cursor != fin)
    {
        imprimir_ArbolRec(arbol,(tNodo)l_recuperar(hijos,cursor));
        cursor = l_siguiente(hijos,cursor);
    }

}

void imprimir_Arbol (tArbol arbol){

    tNodo raiz= a_raiz(arbol);
    printf("--------------\n");
    printf("Arbol: \n");
    imprimir_ArbolRec(arbol,raiz);
    printf("--------------\n");
}

int main() {
    int *e1,*e2,*e3;
    tLista l;
    crear_lista(&l);//Creo lista vacía
    printf("-----------------------------------\n");

    printf("INICIO TESTER DE LISTA:\n");
    printf("Creo una nueva lista l vacía.\n");
    printf("El tamaño de la lista (usando l_longitud) es: %i\n", l_longitud(l));
    printf("-----------------------------------\n");
    printf("Estado actual de la lista: ");
    imprimir(l);

    printf("-----------------------------------------\n");

    printf("Creo un nuevo elemento '1' y lo inserto al comienzo de la lista: \n");
    e1 = (int*) malloc(sizeof(int));
    *e1 = 1;
    //tElemento elem1 = e1;
    l_insertar(l, l, e1);//Inserto 1 en la primera posicion de la lista

    //No usar elem para mostrar.
    //Estaba yendo a buscar la referencia de donde se almacena e1, no
    printf("El elemento en la 1ra posicion (usando l_primera) es: %i\n",  *((int *) l_recuperar(l, l)));//Retorna 1
    printf("El elemento en la 1ra posicion(usando l_recuperar) es: %i\n", *((int *) l_recuperar(l, l)));//Retorna 1
    tPosicion pos1 = l_primera(l);//Guardo la pos en memoria de 1
    printf("Estado actual de la lista: ");
    imprimir(l);

    printf("-----------------------------------------\n");

    printf("Creo un nuevo elemento '2' y lo inserto en la primera posición de la lista: \n");
    e2 = (int*) malloc(sizeof(int));
    *e2 = 2;
    //tElemento elem2 = e2;
    l_insertar(l, l, e2);//Inserto 2 en la 2da posicion de la lista
    tPosicion pos2 = l_primera(l);//Guardo la pos en memoria de 2
    printf("El elemento en la 1ra posicion(usando l_primera) es: %i\n", *((int *) l_recuperar(l, pos2)));//Retorna 2
    printf("El elemento en la 1ra posicion(usando l_anterior) es: %i\n", *((int *) l_recuperar(l, l_anterior(l, pos1))));//Retorna 2

    printf("Estado actual de la lista: ");
    imprimir(l);

    printf("-----------------------------------------\n");

    printf("Creo un nuevo elemento '3' y lo inserto antes del elemento '1': \n");
    e3 = (int*) malloc(sizeof(int));
    *e3 = 3;
    //tElemento elem3 = e3;
    l_insertar(l, pos2, e3);//Inserto 3 en la segunda posicion de la lista
    tPosicion pos3 = l_ultima(l);//Guardo la posicion de 3
    printf("El elemento en la 3ra posicion(usando l_fin) es: %i\n",*((int *)l_recuperar(l, pos3)));//Retorna 1
    printf("El elemento en la 2da posicion(usando l_ultima) es: %i\n",*((int *)l_recuperar(l, pos3)));//Retorna 3
    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 3
    printf("Estado actual de la lista: ");
    imprimir(l);

    printf("-----------------------------------------\n");

    printf("El elemento en la 1ra posicion(usando l_anterior) es: %i\n",*((int *)l_recuperar(l, l_anterior(l,pos3))));//Retorna 2
    printf("El elemento en la 2da posicion(usando l_siguiente) es: %i\n",*((int *)l_recuperar(l, l_siguiente(l,pos2))));//Retorna 1
    l_eliminar(l,l,&fEliminar);//Elimino el 2
    printf("ELIMINO EL 2 EN LA 1RA POSICION\n");
    printf("Estado actual de la lista: ");
    imprimir(l);

    printf("-----------------------------------------\n");

    printf("El 1er elemento de la lista(usando l_primera) es: %i\n",*((int *)l_recuperar(l,l_primera(l))));//Retorna 3
    printf("El 2do elemento de la lista(usando l_fin) es: %i\n",*((int*)l_recuperar(l,l_ultima(l))));//Retorna 1
    printf("El tamaño de la lista(usando l_longitud) es: %i\n",l_longitud(l));//Retorna 2
    printf("-----------------------------------------\n");
    l_destruir(&l,&fEliminar);
    printf("DESTRUYO LA LISTA\n");
    printf("FIN TESTER DE LISTA.\n");
}


    int *e1, *e2, *e3, *e4, *e5;
    tArbol arbol;
    crear_arbol(&arbol);

    e1 = (int *) malloc(sizeof(int));
    *e1 = 1;

    crear_raiz(arbol, e1);
    printf("%i\n", *((int *) a_recuperar(arbol, a_raiz(arbol))));

    e2 = (int *) malloc(sizeof(int));
    *e2 = 2;
    a_insertar(arbol, a_raiz(arbol), NULL, e2);

    e3 = (int *) malloc(sizeof(int));
    *e3 = 3;
    a_insertar(arbol, a_raiz(arbol), NULL, e3);

    //imprimir_Arbol(arbol);

    tLista hijose1 = a_hijos(arbol, a_raiz(arbol));
    tNodo nodo3 = l_recuperar(hijose1, l_ultima(hijose1));
    e4 = (int *) malloc(sizeof(int));
    *e4 = 4;

    e5 = (int *) malloc(sizeof(int));
    *e5 = 5;

    a_insertar(arbol, nodo3, NULL, e4);

    a_insertar(arbol, nodo3, NULL, e5);

    tArbol subArbol3;

    a_sub_arbol(arbol, nodo3, &subArbol3);

    imprimir_Arbol(arbol);

    imprimir_Arbol(subArbol3);

    a_destruir(&subArbol3,&fEliminar);

    crear_arbol(&subArbol3);

    crear_raiz(subArbol3,e2);

    a_insertar(subArbol3, a_raiz(subArbol3), NULL, e4);


    tLista hijos2=a_hijos(subArbol3,a_raiz(subArbol3));
    tNodo nodo4=l_recuperar(hijos2,l_primera(hijos2));




   a_insertar(subArbol3, a_raiz(subArbol3),nodo4, e5);

    a_insertar(subArbol3, a_raiz(subArbol3),nodo4, e1);

    imprimir_Arbol(subArbol3);
}**/

#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"
#include "arbol.h"
#include "lista.h"


//Declaracion de funciones.

void printActualGame(tTablero tablero);


int main(){

    ///Declaracion de variables.
    tPartida part = (tPartida)malloc(sizeof(struct partida));
    tTablero tab = (tTablero)malloc(sizeof(struct tablero));
    ///Declaro todas las cosas de una partida
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0;
    int modo=0;
    ///banderas
    int buenModo = 0;
    int estadoPartida=111;
    ///posiciones
    int coordenadaX;
    int coordenadaY;
    ///alojo la memoria necesaria para una busqueda adversaria
    tBusquedaAdversaria maqBusqueda = (tBusquedaAdversaria)malloc(sizeof(struct busqueda_adversaria));

    ///escaneo el modo de juego
    while(!buenModo){
        printf("Indique el modo de partida\n1.Jugador vs Jugador\n2.Jugador vs Maquina\n");
        scanf("%i",&modo);

        ///msj de error si el modo de juego no es correcto
        if(modo!=1 && modo!=2){
            printf("No selecciono un modo correcto de partida\n");
        }

        else
            buenModo = 1;
    }
    ///Escaneo el nombre del jugador 1
    printf("Indique nombre de Jugador 1.\n");
    scanf("%s",nombreJugador1);
    ///Modo usario vs usario
    if(modo==1){
        ///Guardo nombre jugador 2
        printf("Indique nombre de Jugador 2.\n");
        scanf("%s",nombreJugador2);
    }
    ///Modo usuario vs maquina
    if(modo==2){
        ///guardo nombre de la maquina
        nombreJugador2[0] = 'M';
        nombreJugador2[1] = 'a';
        nombreJugador2[2] = 'q';
        nombreJugador2[3] = 'u';
        nombreJugador2[4] = 'i';
        nombreJugador2[5] = 'n';
        nombreJugador2[6] = 'a';
    }

    ///escaneo el turno del jugador
    printf("Indique '1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para seleccion aleatoria.\n");
    scanf("%i",&turno);
    printf("los movimientos validos son entre 1 y 3 tanto para filas y columnas\n");
    ///Dependiendo el turno inicio un tipo de partida
    if(turno==1)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
    if(turno==2)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
    if(turno==3)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);

    ///Muestro el tablero vacio.
    tab = part->tablero;

    printActualGame(tab);
    printf("\n");
    ///Modo usario vs usuario
    if(modo==1){
        ///Empieza la partida y no termina hasta que gana el jugador 1, el 2 o empatan.
        while(part->estado==PART_EN_JUEGO){
            buenModo=0;

            ///Turno Jugador 1.
            if(part->turno_de == PART_JUGADOR_1)
                printf("Jugador:%s Indique su movimiento\n",nombreJugador1);
            else
                printf("Jugador:%s Indique su movimiento\n",nombreJugador2);

            while(!buenModo){
                ///escaneo la fila
                printf("Fila: ");
                scanf("%i",&coordenadaX);
                ///escaneo la columna
                printf("Columna: ");
                scanf("%i",&coordenadaY);

                ///Chequeo si son coordenadas validas.
                if((coordenadaX!=3 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=3 && coordenadaY!=1 &&coordenadaY!=2)){
                    printf("El movimiento no es valido\n");
                }
                    ///si no salgo del while
                else{
                    buenModo=1;
                }
            }
            ///Actualizo el estado de la partida actual con un nuevo movimiento a las coordenadas
            estadoPartida = nuevo_movimiento(part,coordenadaX-1,coordenadaY-1);
            ///msg de error
            if(estadoPartida==PART_MOVIMIENTO_ERROR)
                printf("Intenta en un lugar que no este ocupado\n");
            printActualGame(tab);
            printf("\n");

        }
    }
    ///Modo usario vs maquina
    if(modo==2){
        ///Empieza la partida y no termina hasta que gana el jugador 1 el 2 o empatan.
        while(estadoPartida ==PART_EN_JUEGO){
            buenModo=0;
            ///Turno Jugador 1.
            if(part->turno_de == PART_JUGADOR_1){
                while(!buenModo){
                    ///escaneo fila
                    printf("Indique su movimiento\n");
                    printf("Fila: ");
                    scanf("%i",&coordenadaX);
                    ///escaneo columna
                    printf("Columna: ");
                    scanf("%i",&coordenadaY);

                    ///Chequeo si son coordenadas validas.
                    if((coordenadaX!=3 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=3 && coordenadaY!=1 &&coordenadaY!=2)){
                        printf("El movimiento no es valido\n");
                    }
                        ///si no salgo del while
                    else{
                        buenModo=1;
                    }
                }
                ///Realizo el movimiento.
                estadoPartida = nuevo_movimiento(part,coordenadaX-1,coordenadaY-1);
                ///msg de ERROR
                if(estadoPartida==PART_MOVIMIENTO_ERROR)
                    printf("Intenta en un lugar que no este ocupado\n");
                printActualGame(tab);
                printf("\n");

            }
            ///Turno Maquina.
            ///si el jugador 1 no termino la partida
            if(part->turno_de == PART_JUGADOR_2 && (estadoPartida==PART_MOVIMIENTO_OK || part->estado==PART_EN_JUEGO)){
                printf("Movimiento de la maquina\n");
                ///Creo el arbol de busqueda adversaria.
                crear_busqueda_adversaria(&maqBusqueda,part);
                ///Le pido el proximo movimiento a la maquina y realizo el movimiento.
                proximo_movimiento(maqBusqueda,&coordenadaX,&coordenadaY);
                estadoPartida = nuevo_movimiento(part,coordenadaX,coordenadaY);
                ///Destruyo la busqueda
                destruir_busqueda_adversaria(&maqBusqueda);
                printActualGame(tab);
            }
        }
    }

    ///Muestro el resultado de la partida.
    if(estadoPartida== PART_GANA_JUGADOR_1){
        printf("Gano %s!!",nombreJugador1);
    }
    if(estadoPartida == PART_GANA_JUGADOR_2){
        printf("Gano %s!!",nombreJugador2);
    }
    if(estadoPartida  == PART_EMPATE){
        printf("La partida termino en empate");
    }
    ///Finalizo la partida.
    finalizar_partida(&part);

    return 0;
}
///metodo que imprime las columnas de los extremos segun corresponda
void printPositionLateral(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("|   |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf("| X |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf("| O |");
}
///metodo que imprime la columna del medio segun corresponda
void PrintPositionMid(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("   ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf(" X ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf(" O ");
}
///metodo que imprime el tablero actual
void printActualGame(tTablero tablero){
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///imprimo primera fila.
    printPositionLateral(tablero,0,0);
    PrintPositionMid(tablero,0,1);
    printPositionLateral(tablero,0,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///Imprimo segunda linea.
    printPositionLateral(tablero,1,0);
    PrintPositionMid(tablero,1,1);
    printPositionLateral(tablero,1,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///Imprimo tercera linea.
    printPositionLateral(tablero,2,0);
    PrintPositionMid(tablero,2,1);
    printPositionLateral(tablero,2,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");

}