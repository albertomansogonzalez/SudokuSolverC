#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include "sudoku_utils.h"


/**
 * @brief solveSudoku Algoritmo de Backtraking, sin ninguna optimizacion
 *
 *  Modifica el estado de Sudoku board
 *
 *  Imprime por pantalla solo si:
 *      - delay > 0. Mediante imprimirSudoku()
 *      - allFlag=True. Mediante imprimirSudokuCadena()
 *
 * Utiliza funcion auxiliar isValid() para comprobar si un nuevo digito es valido
 *
 * @pre nSolciones=0
 * @post board esta resuelto
 * @post nSoluciones con el numero de soluciones posibles
 *
 * @param board [in]
 * @param nSoluciones [out] Devuelve el numero de solcuiones existentes
 * @param delay [in] >0 para mostrar por pantalla los estados intermedios cada ciertos milisegundos
 * @param allFlag [in] True para buscar todas las soluciones he imprimirlas por pantalla
 * @return True si ha encontrado al menos una solucion
 */
bool solveSudoku(Sudoku board, int* nSoluciones, const int delay, const bool allFlag);


#endif // SOLVER_H
