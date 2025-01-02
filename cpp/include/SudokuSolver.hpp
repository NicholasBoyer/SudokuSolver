#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include <array>

using Board = std::array<std::array<int, 9>, 9>;

/*
    Sudoku solver class encapsulates Sudoku solving logic.
*/
class SudokuSolver {
    public:
        /*
        Attemps to solve the given board using backtracking and deduction.
        Returns true if solved, false otherwise.
        */
        bool solve(Board& board);

        /*
        Prints the board to stdout.
        */
        void printBoard(const Board& board) const;

    private:
        /*
        Checks if placing value at position specified by row and col
        violates sudoku constraints.
        */
        bool isValid(const Board& board, int row, int col, int val) const;
       
        /*
        Finds next empty cell. Returns a pair:
        bool for whether an empty cell was found
        int for index of cell
        row = index / 9, col = index % 9
        */
        std::pair<bool, int> findEmptySlot(const Board& board) const; 
};

#endif // SUDOKUSOLVER_HPP