// Custom includes
#include "../include/SudokuSolver.hpp"

// Library includes
#include <iostream>

bool SudokuSolver::solve(Board& board) {
    // Find empty cell
    auto [foundEmpty, index] = findEmptySlot(board);
    if (!foundEmpty) {
        // board solved
        return true;
    }

    int row = index / 9;
    int col = index % 9;

    // Try placing digits in empty cell
    for (int val = 1; val <= 9; ++val) {
        if (isValid(board, row, col, val)) {
            board[row][col] = val;

            // Recurse
            if (solve(board)) {
                return true;
            }

            // Undo if unsuccessful
            board[row][col] = 0;
        }
    }
    // Backtrack
    return false;
}

bool SudokuSolver::isValid(const Board& board, int row, int col, int val) const {
    // Check row
    for (int c = 0; c < 9; ++c) {
        if (board[row][c] == val) {
            return false;
        }
    }

    // Check column
    for (int r = 0; r < 9; ++r) {
        if (board[r][col] == val) {
            return false;
        }
    }

    // Check box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[boxRow + r][boxCol + c] == val) {
                return false;
            }
        }
    }

    // All checks passed
    return true;
}

std::pair<bool, int> SudokuSolver::findEmptySlot(const Board& board) const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                return {true, i * 9 + j};
            }
        }
    }
    return {false, -1};
}

void SudokuSolver::printBoard(const Board& board) const {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::cout << board[row][col] << " ";
        }
        std::cout << "\n";
    }
}