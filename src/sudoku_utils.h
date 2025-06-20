#ifndef SUDOKU_UTILS_H
#define SUDOKU_UTILS_H

#define NROWS 9
#define NCOLS 9
#define BLOCKSIZE 3         // el sudoku se divide en subbloques de 3x3

/* Tipo para guardar el sudoku */
typedef int Sudoku[NROWS][NCOLS];

/**
 * @brief comprobarPistas Combrueba si las pistas en el sudoku que hay que resolver, son correctas
 *
 * Funcion previa al Algoritmo en si
 *
 * @param board Sudoku con pistas
 * @return 0 si las pistas son correctas, 1 si esta mal formado
 */
int comprobarPistas(Sudoku board);

/**
 * @brief imprimirSudoku Imprime por stdout en formato matriz
 * @param s
 */
void imprimirSudoku(Sudoku s);

/**
 * @brief leerSudokuDesdeCadena Convierte una cadena de 81 caracteres en la matriz Sudoku
 * @param cadena [in] ej: "400000020072500000000000600700000000000609000009030100164000702000000000080070000"
 * @param s [out] Matriz de sudoku
 * @return 1 si exito
 */
int leerSudokuDesdeCadena(const char *cadena, Sudoku s);

/**
 * @brief imprimirSudokuCadena Dado un sudoku en formato matriz, imprime por stdout en formato caracteres
 */
void imprimirSudokuCadena(Sudoku s);



#endif // SUDOKU_UTILS_H
