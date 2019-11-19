//
// Created by Aitor Ortuño and Nahuel Maika on 17/09/2019.
//


#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"

void mostrarGrilla(tTablero tablero);


int main(){

    tPartida part = (tPartida)malloc(sizeof(struct partida));
    tTablero tab = (tTablero)malloc(sizeof(struct tablero));
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0,modo =0,modoValido=0,fila,columna,movimiento = PART_MOVIMIENTO_OK,jugando=1;
    tBusquedaAdversaria busquedaAdversaria = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));

    while(jugando!=0) {
        while (!modoValido) {
            printf("Modo de juego: \n1.Jugador vs Jugador\n2.Jugador vs Maquina\n");
            scanf("%i", &modo);

            if (modo != 1 && modo != 2) {
            printf("Seleccione un modo correcto de partida\n");
        } else
            modoValido = 1;
    }

    printf("Nombre de Jugador 1.\n");
    scanf("%s", nombreJugador1);

    if (modo == 1) {
        printf("Nombre de Jugador 2.\n");
        scanf("%s", nombreJugador2);
    }

    if (modo == 2) {
        nombreJugador2[0] = 'M';
        nombreJugador2[1] = 'a';
        nombreJugador2[2] = 'q';
        nombreJugador2[3] = 'u';
        nombreJugador2[4] = 'i';
        nombreJugador2[5] = 'n';
        nombreJugador2[6] = 'a';
    }
    while(turno!=1 && turno !=2 && turno !=3) {
        printf("'1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para selección aleatoria.\n");
        scanf("%i", &turno);
    }
        printf("posiciones válidas entre 1 y 3\n");
        if (turno == 1)
            nueva_partida(&part, PART_MODO_USUARIO_VS_USUARIO, PART_JUGADOR_1, nombreJugador1, nombreJugador2);
        if (turno == 2)
            nueva_partida(&part, PART_MODO_USUARIO_VS_USUARIO, PART_JUGADOR_2, nombreJugador1, nombreJugador2);
        if (turno == 3)
            nueva_partida(&part, PART_MODO_USUARIO_VS_USUARIO, PART_JUGADOR_RANDOM, nombreJugador1, nombreJugador2);

        tab = part->tablero;

        mostrarGrilla(tab);
        printf("\n");
        if (modo == 1) {
            while (part->estado == PART_EN_JUEGO) {
                modoValido = 0;

                if (part->turno_de == PART_JUGADOR_1)
                    printf("Jugador: %s Indique su movimiento\n", nombreJugador1);
                else
                    printf("Jugador: %s Indique su movimiento\n", nombreJugador2);

                while (!modoValido) {
                    printf("Ingrese fila: ");
                    scanf("%i", &fila);
                    printf("Ingrese columna: ");
                    scanf("%i", &columna);

                    if ((fila != 1 && fila != 2 && fila != 3) || (columna != 1 && columna != 2 && columna != 3)) {
                        printf("El movimiento no es valido\n");
                    } else {
                        modoValido = 1;
                    }
                }
                movimiento = nuevo_movimiento(part, fila - 1, columna - 1);
                if (movimiento == PART_MOVIMIENTO_ERROR) {
                    printf("Intenta en un lugar disponible\n");
                }
                mostrarGrilla(tab);
                printf("\n");

            }

        } else {
            if (modo == 2) {
                while (part->estado == PART_EN_JUEGO) {
                    modoValido = 0;
                    if (part->turno_de == PART_JUGADOR_1) {
                        while (!modoValido) {
                            printf("Ingrese fila: ");
                            scanf("%i", &fila);
                            printf("Ingrese columna: ");
                            scanf("%i", &columna);

                            if ((fila != 3 && fila != 1 && fila != 2) ||
                                (columna != 3 && columna != 1 && columna != 2)) {
                                printf("El movimiento no es valido\n");
                            } else {
                                modoValido = 1;
                            }
                        }
                        movimiento = nuevo_movimiento(part, fila - 1, columna - 1);
                        if (movimiento == PART_MOVIMIENTO_ERROR)
                            printf("Intenta en un lugar disponible\n");
                        mostrarGrilla(tab);
                        printf("\n");

                    }
                    if (part->turno_de == PART_JUGADOR_2 &&
                        (movimiento == PART_MOVIMIENTO_OK || part->estado == PART_EN_JUEGO)) {
                        printf("Jugada de la maquina\n");
                        crear_busqueda_adversaria(&busquedaAdversaria, part);
                        proximo_movimiento(busquedaAdversaria, &fila, &columna);
                        movimiento = nuevo_movimiento(part, fila, columna);
                        destruir_busqueda_adversaria(&busquedaAdversaria);
                        mostrarGrilla(tab);
                    }
                }
            }
        }
        if (part->estado == PART_GANA_JUGADOR_1) {
            printf("Gano %s!!", nombreJugador1);
        }
        if (part->estado == PART_GANA_JUGADOR_2) {
            printf("Gano %s!!", nombreJugador2);
        }
        if (part->estado == PART_EMPATE) {
            printf("La partida termino en empate");
        }
        finalizar_partida(&part);
        printf("\nDesea volver a jugar?\n");
        printf("0 para salir.\n");
        printf("1 para jugar nuevamente.\n");
        scanf("%d", &jugando);
        modoValido = 0;
        modo = 0;
        turno = 0;
}
    return 0;
}
void imprimirPosLateral(tTablero tablero, int fila, int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("|   |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf("| X |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf("| O |");
}
void imprimirPosMedio(tTablero tablero, int fila, int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("   ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf(" X ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf(" O ");
}
void mostrarGrilla(tTablero tablero){
    printf("|---|---|---|\n");
    imprimirPosLateral(tablero, 0, 0);
    imprimirPosMedio(tablero, 0, 1);
    imprimirPosLateral(tablero, 0, 2);
    printf("\n");
    printf("|---|---|---|\n");
    imprimirPosLateral(tablero, 1, 0);
    imprimirPosMedio(tablero, 1, 1);
    imprimirPosLateral(tablero, 1, 2);
    printf("\n");
    printf("|---|---|---|\n");
    imprimirPosLateral(tablero, 2, 0);
    imprimirPosMedio(tablero, 2, 1);
    imprimirPosLateral(tablero, 2, 2);
    printf("\n");
    printf("|---|---|---|\n");

}