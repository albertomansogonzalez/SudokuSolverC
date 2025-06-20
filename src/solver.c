#include <stdbool.h>
#include <stdio.h>
#include <windows.h>        //para el Sleep(delayShow), IMPORTANTE: modificar para Linux
#include "solver.h"
#include "sudoku_utils.h"



/**
 * @brief isValid Funcion privada auxiliar, comprueba si colocar un nuevo digito num en la posicion (row,col) es valido en el board actual
 *
 * @pre board[row][col] == 0, es decir, el numero num todavia no esta en el sudoku
 *
 * @param board tablero actual, sin el nuevo numero colocado
 * @param row fila donde probar el nuevo digito
 * @param col columna donde probar el nuevo digito
 * @param num Digito para probar
 * @return True si el nuevo digito es valido
 */
static bool isValid(const Sudoku board, int row, int col, int num) {

    // Chequear fila
    for (int x = 0; x < NCOLS; ++x) {
        if (board[row][x] == num) return false;
    }

    // Chequear columna
    for (int y = 0; y < NROWS; ++y) {
        if (board[y][col] == num) return false;
    }

    // Chequear bloque 3x3
    int startRow = row - (row % BLOCKSIZE); //encontrar fila donde comienza su bloque
    int startCol = col - (col % BLOCKSIZE); //encontrar columna donde comienza su bloque
    for (int i = 0; i < BLOCKSIZE; ++i) { //2 bucles para recorrer el bloque
        for (int j = 0; j < BLOCKSIZE; ++j) {
            if (board[startRow + i][startCol + j] == num) return false;
        }
    }

    //si no ha habido colision -> numero valido
    return true;
}




bool solveSudoku(Sudoku board, int* nSoluciones, int delay, bool allFlag) {

    //Recorre por filas, de arriba a abajo
    for (int row = 0; row < NROWS; ++row) {
        // Recorre dentro de cada fila, las columnas de izquierda a derecha
        for (int col = 0; col < NCOLS; ++col) {

            // Comprueba si la celda esta vacia, para buscar su valor
            if (board[row][col] != 0) continue;

            // Intenta colocar digito 1-9
            for (int num = 1; num <= 9; ++num) {
                // Verifica si el numero elegido es valido, segun el estado actual
                if (isValid(board, row, col, num)) {
                    //Coloca el digito en la celda
                    board[row][col] = num;
                    /* en modo delay, se imprime el estado actual*/ if(delay > 0){printf("\033[H");imprimirSudoku(board);Sleep(delay);}
                    // LLAMADA RECURSIVA
                    if (solveSudoku(board, nSoluciones, delay, allFlag)){
                        if (allFlag){board[row][col] = 0; continue;} // en caso de querer seguir buscando mas soluciones
                        // Volver todas las llamadas recursivas, cuando solucion encontrada
                        return true; //deshace hacia arriba todas las llamadas recursivas
                    }else{
                        // BACKTRACK, solveSudoku ha devuelto false, se corta esta rama porque no funciona
                        board[row][col] = 0; // se vuelve a dejar la celda como desconocida
                    }
                }else{
                    //Numero no es valido, se prueba con el siguiente digito
                }
            }
            // No hay ningun digito valido posible, backtrack
            return false;

        } // fin recorrer columnas
    } // fin recorrer filas

    //Caso base de la recursion, se termina de recorrer la matriz por lo que no quedan celdas vacias
    if (allFlag) imprimirSudokuCadena(board); //imprime esta solucion
    (*nSoluciones)++;
    return true;  //Sudoku esta solucionado
}
