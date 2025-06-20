#include <stdio.h>
#include "sudoku_utils.h"


int comprobarPistas(Sudoku board){
    //Recorre por filas, de arriba a abajo
    for (int row = 0; row < NROWS; ++row) {
        // Recorre dentro de cada fila, las columnas de izquierda a derecha
        for (int col = 0; col < NCOLS; ++col) {

            int num = board[row][col];
            if (num == 0) continue; // celdas vacias siempre estan bien

            // Verificar fila
            for (int x = 0; x < NCOLS; ++x) {
                if (x != col && board[row][x] == num) return 1;
            }

            // Verificar columna
            for (int y = 0; y < NROWS; ++y) {
                if (y != row && board[y][col] == num) return 1;
            }

            // Verificar bloque 3x3
            int startRow = row - (row % BLOCKSIZE);
            int startCol = col - (col % BLOCKSIZE);
            for (int i = 0; i < BLOCKSIZE; ++i) {
                for (int j = 0; j < BLOCKSIZE; ++j) {
                    int r = startRow + i;
                    int c = startCol + j;
                    if ((r != row || c != col) && board[r][c] == num) return 1;
                }
            }
        }
    }
    return 0; // no se han encontrado pistas erroneas;
}

void imprimirSudoku(Sudoku s) {
    for (int fila = 0; fila < NROWS; fila++) {
        for (int col = 0; col < NCOLS; col++) {
            printf("%d ", s[fila][col]);
        }
        printf("\n");
    }
}


void imprimirSudokuCadena(Sudoku s){
    for (int fila = 0; fila < NROWS; fila++) {
        for (int col = 0; col < NCOLS; col++) {
            printf("%d", s[fila][col]);
        }
    }
    printf("\n");
}

int leerSudokuDesdeCadena(const char *cadena, Sudoku s) {

    for (int i = 0; i < 81; i++) {
        char c = cadena[i];
        int valor;

        if (c >= '1' && c <= '9') {
            valor = c - '0'; // número 1-9
        } else if (c == '0' || c == '.') {
            valor = 0; // celda vacía
        } else {
            return 0; // caracter invalido
        }

        s[i / 9][i % 9] = valor;
    }

    return 1; // exito
}
