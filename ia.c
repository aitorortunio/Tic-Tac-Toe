    #include <stdlib.h>

    #include "lista.h"
    #include "arbol.h"
    #include "ia.h"
    #include <stdio.h>

    // Prototipos de funciones auxiliares.
    static void ejecutar_min_max(tBusquedaAdversaria b);
    static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
    static int valor_utilidad(tEstado e, int jugador_max);
    static tLista estados_sucesores(tEstado e, int ficha_jugador);
    static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
    static tEstado clonar_estado(tEstado e);

    void fEliminar(tElemento t) {
        free(t);
    }
    void fNoElim(tElemento t) {}

    int MAX(int valor1,int valor2){
        int toret;
        if(valor1>=valor2)
            toret=valor1;
        else
            toret=valor2;

        return toret;
    }
    int MIN(int valor1,int valor2){
        int toret;
        if(valor1>=valor2)
            toret=valor2;
        else
            toret=valor1;
        return toret;
    }
    void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
        int i, j;
        tEstado estado;

        (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
        if ((*b) == NULL)
            exit(IA_ERROR_MEMORIA);

        estado = (tEstado) malloc(sizeof(struct estado));
        if (estado == NULL)
            exit(IA_ERROR_MEMORIA);

        // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                estado->grilla[i][j] = p->tablero->grilla[i][j];
            }
        }

        // Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
        // inicialmente es IA_NO_TERMINO
        estado->utilidad = IA_NO_TERMINO;

        // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
        (*b)->jugador_max = p->turno_de;
        (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

        // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
        crear_arbol(&((*b)->arbol_busqueda));

        // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
        crear_raiz((*b)->arbol_busqueda, estado);

        // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
        ejecutar_min_max((*b));
    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    */
    void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y) {
        tArbol arbol = b->arbol_busqueda;
        tNodo nActual,mejor_sucesor;
        tPosicion actual,fin;
        tEstado estadoActual,aux;
        tLista listaSucesores;
        int mejor_valor = IA_INFINITO_NEG;
        int utilidadActual,valor;

        estadoActual = (tEstado) a_recuperar(arbol,a_raiz(arbol));
        listaSucesores = a_hijos(arbol, a_raiz(arbol));
        actual = l_primera(listaSucesores);
        fin = l_fin(listaSucesores);
        valor = IA_INFINITO_NEG;

        //debe retornar el primer estado sucesor cuyo valor de utilidad coincida con la utilidad del nodo raíz.

        while(actual != fin && valor!=IA_GANA_MAX){
            nActual = (tNodo) l_recuperar(listaSucesores, actual);
            aux = (tEstado) a_recuperar(arbol, nActual);
            utilidadActual = aux->utilidad;
            if(utilidadActual>valor && utilidadActual!=IA_NO_TERMINO){
                mejor_sucesor = nActual;
                valor = utilidadActual;
            }
            actual = l_siguiente(listaSucesores, actual);
        }

        aux = (tEstado) a_recuperar(arbol, mejor_sucesor);
        diferencia_estados(estadoActual, aux, x, y);
    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    **/
    void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
        //tBusquedaAdversaria ba=*b;

        a_destruir(&((*b)->arbol_busqueda),&fEliminar);

        free(*b);
        *b=NULL;
    }

    // ===============================================================================================================
    // FUNCIONES Y PROCEDEMIENTOS AUXILIARES
    // ===============================================================================================================

    /**
    Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
    estado inicial el estado de la partida almacenado en el árbol almacenado en B.
    **/
    static void ejecutar_min_max(tBusquedaAdversaria b){
        tArbol a = b->arbol_busqueda;
        tNodo r = a_raiz(a);
        int jugador_max = b->jugador_max;
        int jugador_min = b->jugador_min;

        crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
    - A referencia al árbol de búsqueda adversaria.
    - N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
    - ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
    - ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
    - JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
    **/
    static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min) {
        tEstado estado = a_recuperar(a, n);
        //nunca asignan la utilidad calculada
        int utilidad = valor_utilidad(estado, jugador_max);
        int mejor_valor_sucesores;
        tEstado sucesor;
        tPosicion actual, fin;
        tNodo nHijo;

        tLista listaSucesores;
        if (utilidad != IA_NO_TERMINO) {
            estado->utilidad = utilidad;
        } else {
            if (es_max) {
                mejor_valor_sucesores = IA_INFINITO_NEG;
                listaSucesores = estados_sucesores(estado, jugador_max);
                actual = l_primera(listaSucesores);
                fin = l_fin(listaSucesores);
                while (actual != fin) {
                    sucesor = (tEstado) l_recuperar(listaSucesores, actual);
                    nHijo = a_insertar(a, n, NULL, sucesor);
                    l_eliminar(listaSucesores,actual,&fNoElim);
                    crear_sucesores_min_max(a,  nHijo, 0, alpha, beta,jugador_max, jugador_min);
                    mejor_valor_sucesores = MAX(mejor_valor_sucesores, sucesor->utilidad);
                    alpha = MAX(alpha, mejor_valor_sucesores);
                    if (beta <= alpha) {
                        break;
                    }
                    actual = l_primera(listaSucesores);
                    fin = l_fin(listaSucesores);
                }
                estado->utilidad = alpha;
            } else {
                mejor_valor_sucesores = IA_INFINITO_POS;
                listaSucesores = estados_sucesores(estado, jugador_min);
                actual = l_primera(listaSucesores);
                fin = l_fin(listaSucesores);
                while (actual != fin) {
                    sucesor = (tEstado) l_recuperar(listaSucesores, actual);
                    l_eliminar(listaSucesores,actual,&fNoElim);
                    nHijo = a_insertar(a, n, NULL, sucesor);
                    crear_sucesores_min_max(a, nHijo, 1, alpha, beta,jugador_max, jugador_min);
                    mejor_valor_sucesores = MIN(mejor_valor_sucesores, sucesor->utilidad);
                    beta = MIN(beta, mejor_valor_sucesores);
                    if (beta <= alpha) {
                        break;
                    }
                    actual = l_primera(listaSucesores);
                    fin=l_fin(listaSucesores);
                }
                estado->utilidad = beta;
            }
            l_destruir(&listaSucesores,&fEliminar);
        }


    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
    - IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
    - IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
    - IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
    - IA_NO_TERMINO en caso contrario.
    **/
    static int valor_utilidad(tEstado e, int jugador_max){
        int utilidad = IA_EMPATA_MAX;
        int ficha_actual;
        int gano=0;

        ficha_actual= e->grilla[0][0];
        if(ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[0][1]==ficha_actual && e->grilla[0][2]==ficha_actual && gano!=1)
            gano = 1 ;
        if(ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[1][1]==ficha_actual && e->grilla[2][2]==ficha_actual && gano!=1)
            gano = 1;
        if(ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[1][0]==ficha_actual && e->grilla[2][0]==ficha_actual && gano!=1)
            gano = 1;

        if(gano!=1) {
            ficha_actual = e->grilla[1][1];
            if (ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[0][1] == ficha_actual && e->grilla[2][1] == ficha_actual && gano != 1)
                gano = 1;
            if (ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[1][0] == ficha_actual && e->grilla[1][2] == ficha_actual && gano != 1)
                gano = 1;
            if (ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[0][2] == ficha_actual && e->grilla[2][0] == ficha_actual && gano != 1)
                gano = 1;
            }
        if(gano!=1) {
            ficha_actual = e->grilla[2][2];
            if (ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[2][1] == ficha_actual && e->grilla[2][0] == ficha_actual && gano!=1)
                gano = 1;
            if (ficha_actual!=PART_SIN_MOVIMIENTO && e->grilla[0][2] == ficha_actual && e->grilla[1][2] == ficha_actual && gano!=1)
                gano = 1;
        }

         if (gano==1){
             if(ficha_actual==PART_JUGADOR_2)
                 utilidad = IA_GANA_MAX;
             else if (ficha_actual==PART_JUGADOR_1)
                 utilidad = IA_PIERDE_MAX;

         }else {
             int i, j, encontre = 0;
             for (i = 0; i < 3 && !encontre; i++) {
                 for (j = 0; j < 3 && !encontre; j++) {
                     if (e->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                         encontre = 1;
                         utilidad = IA_NO_TERMINO;
                     }
                 }
             }
         }

        return utilidad;
    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
    Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporación de un nuevo movimiento
    realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
    La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
    estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
    - L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
    - El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
    **/
    static tLista estados_sucesores(tEstado e, int ficha_jugador){
        tLista lista;
        crear_lista(&lista);
        tEstado estado;
        int i,j;
        for(i=0; i<3;i++) {
            for (j = 0; j < 3; j++) {
                if(e->grilla[i][j]==PART_SIN_MOVIMIENTO) {
                    estado = clonar_estado(e);
                    estado->grilla[i][j] = ficha_jugador;
                    if(rand()%2 == 0) {
                        l_insertar(lista, l_primera(lista), estado);
                    }else {
                        l_insertar(lista, l_fin(lista), estado);
                    }
                }
            }
        }

        return lista;
    }

    /**
    >>>>>  A IMPLEMENTAR   <<<<<
    Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
    Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
    de utilidad.
    **/
    static tEstado clonar_estado(tEstado e){
        tEstado toret=(tEstado)malloc((sizeof(struct estado)));
        if(toret == NULL)
            exit(PART_ERROR_MEMORIA);
        int i,j;
        for(i=0; i<3;i++) {
            for (j = 0; j < 3; j++) {
                toret->grilla[i][j]=e->grilla[i][j];
            }
        }
        toret->utilidad = e->utilidad;
         return toret;
    }

    /**
    Computa la diferencia existente entre dos estados.
    Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
    La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
    **/
    static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
        int i,j, hallado = 0;
        for(i=0; i<3 && !hallado; i++){
            for(j=0; j<3 && !hallado; j++){
                if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                    *x = i;
                    *y = j;
                    hallado = 1;
                }
            }
        }
    }
