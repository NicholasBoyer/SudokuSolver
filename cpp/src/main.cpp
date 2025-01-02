// Standard library headers
#include <array>
#include <iostream>

// Custom library headers
#include "../include/SudokuSolver.hpp"

int main() {
    std::array<std::array<int, 9>, 9> board = {{
        {{5, 3, 0, 0, 7, 0, 0, 0, 0}},
        {{6, 0, 0, 1, 9, 5, 0, 0, 0}},
        {{0, 9, 8, 0, 0, 0, 0, 6, 0}},
        {{8, 0, 0, 0, 6, 0, 0, 0, 3}},
        {{4, 0, 0, 8, 0, 3, 0, 0, 1}},
        {{7, 0, 0, 0, 2, 0, 0, 0, 6}},
        {{0, 6, 0, 0, 0, 0, 2, 8, 0}},
        {{0, 0, 0, 4, 1, 9, 0, 0, 5}},
        {{0, 0, 0, 0, 8, 0, 0, 7, 9}}
    }};

    SudokuSolver solver;
    std::cout << "Initial board:\n";
    solver.printBoard(board);

    if (solver.solve(board)) {
        std::cout << "\nSolution:\n";
        solver.printBoard(board);
    } else {
        std::cout << "\nNo solution.\n";
    }

    return 0;

}