# Script para comprobar el sudoku solver
#   Compila el binario a traves de los fuentes
#   Testea con los sudokus del fichero "sudokus_test.txt"

import utils
import subprocess


def es_sudoku_valido(cadenacaracteres):
    def es_valido(lista):
        # Verifica que la lista contenga números del 1 al 9 sin repetidos
        nums = [num for num in lista if num != 0]  # Ignorar ceros si los hay
        return len(nums) == len(set(nums)) and all(1 <= num <= 9 for num in nums)

    # Convertir en matriz 9x9
    tablero = [list(cadenacaracteres[i:i+9]) for i in range(0, 81, 9)]
    # convertir cada carácter a entero
    tablero = [[int(char) for char in row] for row in tablero]

    # Comprobar filas
    for fila in tablero:
        if not es_valido(fila):
            return False

    # Comprobar columnas
    for col in range(9):
        columna = [tablero[fila][col] for fila in range(9)]
        if not es_valido(columna):
            return False

    # Comprobar subcuadros 3x3
    for box_fila in range(0, 9, 3):
        for box_col in range(0, 9, 3):
            cuadro = []
            for i in range(3):
                for j in range(3):
                    cuadro.append(tablero[box_fila + i][box_col + j])
            if not es_valido(cuadro):
                return False

    return True

def verificar_modificado(puzzle, resuelto):
    #Para comprobar que no se ha modificado el puzzle en la solucion
    if len(puzzle) != len(resuelto):
        return False  # No tienen la misma longitud

    for i in range(len(puzzle)):
        if puzzle[i] != '0' and puzzle[i] != resuelto[i]:
            return False  # Hay un número fijo que no coincide

    return True


utils.build_cmake_project()

print(f"\n\n\tIniciando Tests\n")

# Leer el sudokus.txt línea por línea
with open("sudokus_test.txt", 'r') as archivo:
    for sudoku_input in archivo:
        sudoku_input = sudoku_input.strip()  # Quita el salto de línea y espacios
        print(f"Sudoku leído: {sudoku_input}")
        

        # Ejecutar el programa en C
        result = subprocess.run(
            ['../build/Release/SudokuSolver', sudoku_input],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        # Capturar la salida
        output = result.stdout.strip()
        print("resuelto:     " + output)

        # Comprobar si el sudoku es correcto
        if '0' not in output and es_sudoku_valido(output) and verificar_modificado(sudoku_input, output):
            print("✅ Test pasado\n")
        else:
            print("❌ Test fallido")
            print("Entrada:         ", sudoku_input)
            print("Salida obtenida: ", output)
            print("Stderr:          ", result.stderr.strip())
            print('\n')