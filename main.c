//
// Created by Aitor Ortuño and Nahuel Maika on 17/09/2019.
//


#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"

void mostrarGrilla(tTablero tablero);


int main(){

    ///Declaracion de variables.
    tPartida part = (tPartida)malloc(sizeof(struct partida));
    tTablero tab = (tTablero)malloc(sizeof(struct tablero));
    ///Declaro todas las cosas de una partida
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0;
    int modo=0;
    int modoValido = 0;
    int estadoPartida=111;
    int fila;
    int columna;
    tBusquedaAdversaria busquedaAdversaria = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));

    while(!modoValido){
        printf("Indique el modo de partida\n1.Jugador vs Jugador\n2.Jugador vs Maquina\n");
        scanf("%i",&modo);

        if(modo!=1 && modo!=2){
            printf("No selecciono un modo correcto de partida\n");
        }
        else
            modoValido = 1;
    }

    printf("Indique nombre de Jugador 1.\n");
    scanf("%s",nombreJugador1);

    if(modo==1){
        printf("Indique nombre de Jugador 2.\n");
        scanf("%s",nombreJugador2);
    }

    if(modo==2){
        nombreJugador2[0] = 'M';
        nombreJugador2[1] = 'a';
        nombreJugador2[2] = 'q';
        nombreJugador2[3] = 'u';
        nombreJugador2[4] = 'i';
        nombreJugador2[5] = 'n';
        nombreJugador2[6] = 'a';
    }

    printf("'1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para selección aleatoria.\n");
    scanf("%i",&turno);
    printf("posiciones válidas entre 1 y 3\n");
    if(turno==1)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
    if(turno==2)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
    if(turno==3)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);

    ///Muestro el tablero vacio.
    tab = part->tablero;

    mostrarGrilla(tab);
    printf("\n");
    ///Modo usario vs usuario
    if(modo==1){
        ///Empieza la partida y no termina hasta que gana el jugador 1, el 2 o empatan.
        while(part->estado==PART_EN_JUEGO){
            modoValido=0;

            ///Turno Jugador 1.
            if(part->turno_de == PART_JUGADOR_1)
                printf("Jugador:%s Indique su movimiento\n",nombreJugador1);
            else
                printf("Jugador:%s Indique su movimiento\n",nombreJugador2);

            while(!modoValido){
                printf("Ingrese fila: ");
                scanf("%i",&fila);
                printf("Ingrese columna: ");
                scanf("%i",&columna);

                if((fila != 1 && fila != 2 && fila != 3 ) || (columna != 1 && columna != 2 && columna != 3)){
                    printf("El movimiento no es valido\n");
                }
                else{
                    modoValido=1;
                }
            }
            estadoPartida = nuevo_movimiento(part, fila - 1, columna - 1);
            if(estadoPartida==PART_MOVIMIENTO_ERROR)
                printf("Intenta en un lugar disponible\n");
            mostrarGrilla(tab);
            printf("\n");

        }
    }

    if(modo==2){
        while(estadoPartida == PART_EN_JUEGO){
            modoValido=0;
            if(part->turno_de == PART_JUGADOR_1){
                while(!modoValido){
                    printf("Ingrese fila: ");
                    scanf("%i",&fila);
                    printf("Ingrese columna: ");
                    scanf("%i",&columna);

                    if((fila != 3 && fila != 1 && fila != 2 ) || (columna != 3 && columna != 1 && columna != 2)){
                        printf("El movimiento no es valido\n");
                    }
                    else{
                        modoValido=1;
                    }
                }
                estadoPartida = nuevo_movimiento(part, fila - 1, columna - 1);
                if(estadoPartida==PART_MOVIMIENTO_ERROR)
                    printf("Intenta en un lugar disponible\n");
                mostrarGrilla(tab);
                printf("\n");

            }
            if(part->turno_de == PART_JUGADOR_2 && (estadoPartida==PART_MOVIMIENTO_OK || part->estado==PART_EN_JUEGO)){
                printf("Movimiento de la maquina\n");
                crear_busqueda_adversaria(&busquedaAdversaria, part);
                proximo_movimiento(busquedaAdversaria, &fila, &columna);
                estadoPartida = nuevo_movimiento(part, fila, columna);
                destruir_busqueda_adversaria(&busquedaAdversaria);
                mostrarGrilla(tab);
            }
        }
    }

    if(estadoPartida== PART_GANA_JUGADOR_1){
        printf("Gano %s!!",nombreJugador1);
    }
    if(estadoPartida == PART_GANA_JUGADOR_2){
        printf("Gano %s!!",nombreJugador2);
    }
    if(estadoPartida  == PART_EMPATE){
        printf("La partida termino en empate");
    }
    finalizar_partida(&part);

    return 0;
}
void printPositionLateral(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("|   |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf("| X |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf("| O |");
}
void PrintPositionMid(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
        printf("   ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf(" X ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf(" O ");
}
void mostrarGrilla(tTablero tablero){
    printf("|---|---|---|\n");
    printPositionLateral(tablero,0,0);
    PrintPositionMid(tablero,0,1);
    printPositionLateral(tablero,0,2);
    printf("\n");
    printf("|---|---|---|\n");
    printPositionLateral(tablero,1,0);
    PrintPositionMid(tablero,1,1);
    printPositionLateral(tablero,1,2);
    printf("\n");
    printf("|---|---|---|\n");
    printPositionLateral(tablero,2,0);
    PrintPositionMid(tablero,2,1);
    printPositionLateral(tablero,2,2);
    printf("\n");
    printf("|---|---|---|\n");

}