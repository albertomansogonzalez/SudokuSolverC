#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>        //para el Sleep(delayShow), IMPORTANTE: modificar para Linux
#include "solver.h"
#include "sudoku_utils.h"

/**
 * @brief Bitmask tipo para representar los candidatos de una celda
 *
 * 0b000111111 → 1,2,3,4,5 son candidatos
 * 0b000000100 → solo el número 3 es candidato
 */
typedef uint16_t Bitmask;

#define ALL_CANDIDATES 0x1FF // 9 bits en 1 => 0b0000000111111111

// El número n (1-9) en forma de bitmask
#define BIT(n) (1 << ((n) - 1))

static inline void quitarCandidato(Bitmask candidatos[NROWS][NCOLS], int row, int col, int n) {
    candidatos[row][col] &= ~BIT(n);
}

// Agregar un candidato n
static inline void addCandidato(Bitmask candidatos[NROWS][NCOLS], int row, int col, int n) {
    candidatos[row][col] |= BIT(n);
}

static inline int esCandidato(Bitmask candidatos[NROWS][NCOLS], int row, int col, int n) {
    return candidatos[row][col] & BIT(n);
}

// Contar el número de candidatos (número de bits en 1)
static inline int contarCandidatos(Bitmask bm) {
    int count = 0;
    while (bm) {
        count += bm & 1;
        bm >>= 1;
    }
    return count;
}

// Obtener el único candidato (si hay solo uno)
static inline int get_single_candidate(Bitmask bm) {
    if (contarCandidatos(bm) != 1) return 0;
    for (int i = 0; i < 9; i++) {
        if (bm & (1 << i)) return i + 1;
    }
    return 0;
}




/**
 * @brief modificarCandidatos Funcion auxiliar utilizada en "backtrakingSudoku"
 *
 * Elimina de la matriz de candidatos, el numero "num" como candidatos en la celdas:
 * - propia celda, quita todos los candidatos
 * - de la columna
 * - de la fila
 * - del bloque 3x3
 */
static void modificarCandidatos(Bitmask candidatos[NROWS][NCOLS], int row, int col, int num){

    // quita todos los candidatos de la celda
    candidatos[row][col] = 0;

    //quitar el numero como candidato de las celdas correspondientes (propia, fila y columna
    for (int i = 0; i < 9; i++){
        quitarCandidato(candidatos, row, i, num);
        quitarCandidato(candidatos, i, col, num);
    }


    // Quitar candidato del bloque 3x3
    int startRow = row - (row % BLOCKSIZE); //encontrar fila donde comienza su bloque
    int startCol = col - (col % BLOCKSIZE); //encontrar columna donde comienza su bloque
    for (int i = 0; i < BLOCKSIZE; ++i) { //2 bucles para recorrer el bloque
        for (int j = 0; j < BLOCKSIZE; ++j) {
            quitarCandidato(candidatos, startRow + i, startCol + j, num);
        }
    }
}


/**
 * @brief encontrarCeldaMenosCandidatos Funcion auxiliar utilizada en "backtrakingSudoku"
 *
 * Recorre la matriz de candidatos y encuentra la celda con el menor numero de candidatos
 * Heuristica de Minimum Remaining Value (MRV)
 *
 * @pos "row" y "col" indican la celda con el menor numero de candidatos
 *
 * @return -1 si ya esta completado, 0 si no hay candidatos disponibles (podar), 1 exito seteando row y col
 */
static int encontrarCeldaMenosCandidatos(Sudoku board, Bitmask candidatos[NROWS][NCOLS], int *row, int *col) {
    int minOptions = 10; // mayor que 9
    int found = false;
    bool sudokuCompleto = true;

    for (int r = 0; r < NROWS; ++r) {
        for (int c = 0; c < NCOLS; ++c) {
            if (board[r][c] != 0) continue; //celda ya resuelta

            sudokuCompleto = false; //quedan huecos

            //contar los candidatos de la celda
            int count = contarCandidatos(candidatos[r][c]);

            if (count > 0 && count < minOptions) {
                minOptions = count;
                *row = r;
                *col = c;
                found = 1;
                if (minOptions == 1) return 1; // heurística: salir temprano si es muy bueno
            }
        }
    }

    if (sudokuCompleto){
        return -1;
    }else{
        return found; //return 0 si no hay candidatos (podar rama), 1 si si hay candidatos
    }

}

/**
 * @brief backtrakingSudoku Realiza el backtraking, utilizando la matriz de candidatos
 * @pre La matriz de candidatos tiene que estar inicializada
 */
static bool backtrakingSudoku(Sudoku board, Bitmask candidatos[NROWS][NCOLS], int* nSoluciones, int delay, bool allFlag) {

    int row, col; //celda a rellenar

    //MVR Heuristica
    int valor = encontrarCeldaMenosCandidatos(board, candidatos, &row, &col);
    if ( valor == -1){
        //no quedan huecos, sudoku completo
        if (allFlag) imprimirSudokuCadena(board); //imprime esta solucion
        (*nSoluciones)++;
        return true;
    }else if (valor == 0){
        return false;
    }else{ /* valor == 1*/
        /* si hay candidatos, en (row,col) */
    }

    // Intenta colocar digito 1-9
    for (int num = 1; num <= 9; ++num) {
        // Verifica si el numero elegido es un candidato
        if (!esCandidato(candidatos, row, col, num)){
            continue;
        }

        //Coloca el digito en la celda
        board[row][col] = num;
        //modificar estructuras de datos de candidatos
        Bitmask new_candidatos[NROWS][NCOLS];
        //copiamos la matriz de candidatos para la siguiente llamada recursiva
        memcpy(new_candidatos, candidatos, sizeof(new_candidatos)); // si pongo sizeof(candidatos) falla por "decay" en Lenguaje C!!!
        //eliminamos los candidatos tras colocar el "num"
        modificarCandidatos(new_candidatos, row, col, num);

        /* en modo delay, se imprime el estado actual*/ if(delay > 0){printf("\033[H");imprimirSudoku(board);Sleep(delay);}
        // LLAMADA RECURSIVA, con la nueva matriz de candidatos
        if (backtrakingSudoku(board, new_candidatos, nSoluciones, delay, allFlag)){
            if (allFlag){board[row][col] = 0; continue;} // en caso de querer seguir buscando mas soluciones
            // Volver todas las llamadas recursivas, cuando solucion encontrada
            return true; //deshace hacia arriba todas las llamadas recursivas
        }else{
            // BACKTRACK, solveSudoku ha devuelto false, se corta esta rama porque no funciona
            board[row][col] = 0; // se vuelve a dejar la celda como desconocida
            //se retorna a la llamada anterior, con la matriz de candidatos anterior
        }
    }

    // No hay ningun digito valido posible, backtrack
    return false;
}


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

    /**
    * @brief candidatos Bitmask de digitos candidatos posibles para cada celda:
    *
    * 0b000111111 → 1,2,3,4,5 son candidatos
    * 0b000000100 → solo el número 3 es candidato
    */
    Bitmask candidatos[NROWS][NCOLS] = {0}; // Matriz de candidatos

    //Rellenamos la primera vez la matriz de candidatos
    for (int r = 0; r < NROWS; r++) {
        for (int c = 0; c < NCOLS; c++) {
            if (board[r][c] != 0) continue; //es una pista, por lo que no tiene candidatos

            for (int num = 1; num <= 9; num++) {
                if (isValid(board, r, c, num)) {
                    addCandidato(candidatos, r,c,num);
                }
            }
        }
    }

    //ejecutamos el Backtraking
    return backtrakingSudoku(board, candidatos, nSoluciones, delay, allFlag);
}


