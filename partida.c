//
// Created by Aitor Ortuño & Nahuel Maika on 23/10/2019.
//
#include <stdlib.h>
#include <string.h>
#include "partida.h"

/**
Inicializa una nueva partida, indicando:
- Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
- Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
- Nombre que representa al Jugador 1.
- Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre) {
    //Reservo espacio en memoria para la partida
    (*p) = (tPartida) malloc(sizeof(struct partida));
    if (*p == NULL)
        exit(PART_ERROR_MEMORIA);
    //Asigno el modo de partida a la partida.
    (*p)->modo_partida = modo_partida;

    (*p)->estado = PART_EN_JUEGO;

    //Si el modo de juego es random
    if (comienza == PART_JUGADOR_RANDOM) {
        //selecciono un jugador random para comenzar
        if (rand() % 2 == 0)
            (*p)->turno_de = PART_JUGADOR_1;
        else
            (*p)->turno_de = PART_JUGADOR_2;
    }
        //Si no, asigno el turno al que comienza segun el parámetro 'comienza'.
    else
        (*p)->turno_de = comienza;

    //reservo el espacio en memoria para el tablero
    (*p)->tablero = (tTablero) malloc(sizeof(struct tablero));
    if ((*p)->tablero == NULL)
        exit(PART_ERROR_MEMORIA);
    //incializo el tablero sin movimientos
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            (*p)->tablero->grilla[i][j] = PART_SIN_MOVIMIENTO;
        }
    }
    //strcpy( char *destino, const char *origen );
    strcpy((*p)->nombre_jugador_1, j1_nombre);
    strcpy((*p)->nombre_jugador_2, j2_nombre);
}

void chequearEstadoDePartida(tPartida p){
    tTablero t = p->tablero;
    int ficha_actual;
    int gano=0;


    ficha_actual= t->grilla[0][0];
    if(ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[0][1]==ficha_actual && t->grilla[0][2]==ficha_actual && gano!=1)
        gano = 1 ;
    if(ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[1][1]==ficha_actual && t->grilla[2][2]==ficha_actual && gano!=1)
        gano = 1;
    if(ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[1][0]==ficha_actual && t->grilla[2][0]==ficha_actual && gano!=1)
        gano = 1;

    if(gano!=1) {
        ficha_actual = t->grilla[1][1];
        if (ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[0][1] == ficha_actual && t->grilla[2][1] == ficha_actual && gano != 1)
            gano = 1;
        if (ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[1][0] == ficha_actual && t->grilla[1][2] == ficha_actual && gano != 1)
            gano = 1;
        if (ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[0][2] == ficha_actual && t->grilla[2][0] == ficha_actual && gano != 1)
            gano = 1;
    }
    if(gano!=1) {
        ficha_actual = t->grilla[2][2];
        if (ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[2][1] == ficha_actual && t->grilla[2][0] == ficha_actual && gano!=1)
            gano = 1;
        if (ficha_actual!=PART_SIN_MOVIMIENTO && t->grilla[0][2] == ficha_actual && t->grilla[1][2] == ficha_actual && gano!=1)
            gano = 1;
    }

    if (gano==1){
        if(ficha_actual==PART_JUGADOR_1)
            p->estado = PART_GANA_JUGADOR_1;
        else if (ficha_actual==PART_JUGADOR_2)
            p->estado = PART_GANA_JUGADOR_2;

    }else {
        int i, j, encontre = 0;
        for (i = 0; i < 3 && !encontre; i++) {
            for (j = 0; j < 3 && !encontre; j++) {
                if (t->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                    encontre = 1;
                }
            }
        }
        if(encontre==0)
            p->estado = PART_EMPATE;

    }
}

/**         }
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    int i, j, movimientos = 0;
    for (i = 0; i < 3 ; i++) {
        for (j = 0; j < 3; j++) {
            if (p->tablero->grilla[i][j] != PART_SIN_MOVIMIENTO) {
                movimientos ++;
            }
        }
    }

    if( mov_x < 0 ||  //Si mov_x o mov_y estan fuera de rango -> PART_MOVIMIENTO_ERROR
        mov_x > 2 ||
        mov_y < 0 ||
        mov_y > 2 ||
        p->tablero->grilla[mov_x][mov_y] == PART_JUGADOR_1 || // o si esa posición ya está ocupada
        p->tablero->grilla[mov_x][mov_y] == PART_JUGADOR_2 ||
        movimientos==9
    )
        return PART_MOVIMIENTO_ERROR;

    //Si el movimiento era válido -> Registro el nuevo movimiento.
    // Luego -> PART-MOVIMIENTO_OK
    if(p->turno_de == PART_JUGADOR_1) {
        p->tablero->grilla[mov_x][mov_y] = PART_JUGADOR_1;
        p->turno_de = PART_JUGADOR_2;
    }

    else {
        p->tablero->grilla[mov_x][mov_y] = PART_JUGADOR_2;
        p->turno_de = PART_JUGADOR_1;
    }

    chequearEstadoDePartida(p);
    if(p->estado!=PART_EN_JUEGO)
        return PART_MOVIMIENTO_OK;
    return PART_EN_JUEGO;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
void finalizar_partida(tPartida *p){
    free((*p)->tablero);
    (*p)->tablero = NULL;

    free(*p);
    (*p) = NULL;
    }