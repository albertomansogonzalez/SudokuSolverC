# SudokuSolverC

Implementación en C de algoritmo de Backtraking para resolver sudokus.
 - Utiliza funcion solveSudoku como base del backtraking con la recursion y la vuelta atras.
 - Apoyado por la funcion auxiliar isValid para comprobar si cada nuevo numero es valido o no.
 - Implementamos Heuristica Minimum Remaining Value (MRV) heuristic. (Celdas con menos candidatos)
      - Mediante funcion "encontrarCeldaMenosCandidatos" apoyada por "countCandidates" 

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
