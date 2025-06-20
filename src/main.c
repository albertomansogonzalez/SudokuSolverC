/**
 *
 * Sudoku solver mediante Backtraking.
 *
 * Utiliza funcion solveSudoku como base del backtraking con la recursion y la vuelta atras.
 * Apoyado por la funcion auxiliar isValid para comprobar si cada nuevo numero es valido o no.
 *
 * Uso: "SudokuSolver 704305600693000852210000003009008230031092764400610900300059106008060390020001008 [--human | --all | --benchmark | --delay <N>]"
 *   Con el sudoku en formato de string con numeros de izquierda a derecha, y de arriba a abajo
 *   Y el digito 0 representa las celdas vacias
 *
 *  Donde opciones:
 *      "" modo normal, devuelve la primera solucion encontrada
 *      "--human" muestra solucion en formato cuadricula
 *      "--all" para buscar todas las soluciones y las imprime por pantalla
 *      "--benchmark" para benchmark, solo imprime el tiempo del algoritmo en milisegundos
 *      "--delay <N>" imprime paso a paso por consola, con N tiempo de delay en milisegundos entre cada iteracion
 *
 *  Ejemplo de uso:
 *      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000"
 *      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --human"
 *      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --delay 1"
 *      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --benchmark"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "solver.h"
#include "sudoku_utils.h"

enum TipoEjecucion{
    NORMAL,
    HUMAN,
    BENCHMARK,
    DELAY,
    ALL
}tipoEjecucion = NORMAL;



/**
 * @brief main Lee los argumentos de entrada, genera el sudoku y ejecuta la resolucion
 */
int main(int argc, char *argv[])
{
    Sudoku sudoku_puzzle; // sudoku del problema que hay que resolver
    Sudoku sudoku_resolver; // aqui se resolvera el sudoku
    const char* sudokuCadena = argv[1];
    clock_t inicio, fin;
    bool haySolucion = false;
    int nSoluciones = 0;
    int delay = 0;
    bool allFlag = false;

    if (argc < 2){
        printf("Uso: ./exe 704305600693000852210000003009008230031092764400610900300059106008060390020001008 [--human | --all | --benchmark | --delay <N>]\n");
    }

    //Interpretar argumentos de entrada, para elegir el modo de ejecucion
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--all") == 0) {
            tipoEjecucion = ALL;
            allFlag = true;
        } else if (strcmp(argv[i], "--benchmark") == 0) {
            tipoEjecucion = BENCHMARK;
        } else if (strcmp(argv[i], "--delay") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: se esperaba un valor despues de 'show'.\n");
                return 1;
            }
            tipoEjecucion = DELAY;
            delay = atoi(argv[i + 1]);
            i++;  // saltar el numero
        } else if (strcmp(argv[i], "--human") == 0){
            tipoEjecucion = HUMAN;
        }
        else {
            fprintf(stderr, "Error: argumento desconocido '%s'\n", argv[i]);
            return 1;
        }
    }

    // Generar el sudoku segun la entrada
    if (!leerSudokuDesdeCadena(sudokuCadena, sudoku_puzzle)) {
        printf("Error: cadena de sudoku invalida\n");
        return 1;
    }

    // Comprobar si las pistas con correctas
    if (comprobarPistas(sudoku_puzzle) != 0){
        printf("Error, las pistas no son correctas\n");
        return 1;
    }

    memcpy(sudoku_resolver, sudoku_puzzle, sizeof(sudoku_puzzle));

    // Resolver el sudoku y medir el tiempo
    inicio = clock();
    haySolucion = solveSudoku(sudoku_resolver, &nSoluciones, delay, allFlag);
    fin = clock();

    // imprimir los resultados
    switch(tipoEjecucion){
    case NORMAL:
        if (haySolucion)
            imprimirSudokuCadena(sudoku_resolver);
        else
            printf("No tiene solucion\n");
        break;
    case HUMAN:
        imprimirSudoku(sudoku_puzzle);
        printf(" --- \n");
        if (haySolucion){
            imprimirSudoku(sudoku_resolver);
        }
        else{
            printf("No tiene solucion\n");
        }
        break;
    case BENCHMARK:
        printf("%ld\n", (fin - inicio)*1000/CLOCKS_PER_SEC);
        break;
    case ALL:
        // ya se imprimen todas las soluciones dentro del algoritmo
        printf("Numero soluciones encontradas: %d\n", nSoluciones);
        break;
    case DELAY:
        // ya se imprimen todas las soluciones dentro del algoritmo
        break;
    }

    return 0;
}
