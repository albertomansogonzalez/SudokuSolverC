# SudokuSolverC

Implementación en C de algoritmo de Backtraking para resolver sudokus.
 - Utiliza matriz de candidatos como estructura principal.
 - Funcion solveSudoku para inicializar la matriz de candidatos y llamar a backtrakingSudoku como base del backtraking con la recursion y la vuelta atras.
 - Implementamos Heuristica Minimum Remaining Value (MRV) heuristic. (Celdas con menos candidatos)
 - "backtrakingSudoku" utiliza "encontrarCeldaMenosCandidatos" para la heuristica y "modificarCandidatos" para eliminar los candidatos
 - Nota: Al utilizar la matriz de candidatos se obtiene menos tiempos que cuando se calculaban directamente
---

## Ejemplo de uso:  
```bash
      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000"  
      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --human"  
      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --delay 1"  
      "SudokuSolver 000000000300500007800030000700002000600700100400000000000000520040075000509600000 --benchmark"  
```

---

## Tests y Benchmark:  

Incluye test de pruebas que testea los sudokus del fichero "sudokus_test.txt"  
```bash
python .\test_correctness.py
```

Y tambien un script de benchmark  
```bash
python .\benchmark.py
```
