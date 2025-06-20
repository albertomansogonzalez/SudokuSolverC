cmake_minimum_required(VERSION 3.5)

project(SudokuSolver LANGUAGES C)

add_executable(SudokuSolver src/main.c
    src/sudoku_utils.h
    src/sudoku_utils.c
    src/solver.h
    src/solver.c)

include(GNUInstallDirs)
install(TARGETS SudokuSolver
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
