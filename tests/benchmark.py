# Script para comparar el tiempo del algoritmo implementado
#   Compila el binario a traves de los fuentes
#   Ejecuta con los sudokus del fichero "sudokus_test.txt"
#   Utilizando la flag --benchmark, el binario devuelve el tiempo

import utils
import subprocess


utils.build_cmake_project()

print(f"\n\n\tIniciando Benchmark\n")

tiempo_ms = 0

# Leer el sudokus.txt línea por línea
with open("sudokus_test.txt", 'r') as archivo:
    for sudoku_input in archivo:
        sudoku_input = sudoku_input.strip()  # Quita el salto de línea y espacios
        
        print(f"\n{sudoku_input}: ", end="")
        # Ejecuta el programa con el argumento
        resultado = subprocess.run(['../build/Release/SudokuSolver', sudoku_input, "--benchmark"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        output = resultado.stdout.strip()

        print(f"{output} ms")
        tiempo_ms += int(output)

print(f"\nTiempo de ejecución total: {tiempo_ms} milisegundos")

