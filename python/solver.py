class SudokuSolver:

    def __init__(self, board):
        """
        Initialize the Sudoku solver with a given board.
        :param board: 9x9 grid (list of lists) representing the Sudoku puzzle.
        """
        self.board = board
    
    def is_valid(self, num, row, col):
        """
        Check if placing `num` in position (row, col) is valid.
        :param num: Number to place (1-9).
        :param row: Row index (0-8).
        :param col: Column index (0-8).
        :return: True if valid, False otherwise.
        """
        # Check row and column
        for i in range(9):
            if self.board[row][i] == num or self.board[i][col] == num:
                return False
        
        # Check box
        box_row, box_col = 3 * (row // 3), 3 * (col // 3)
        for i in range(box_row, box_row + 3):
            for j in range(box_col, box_col + 3):
                if self.board[i][j] == num:
                    return False
            
        return True

    def naked_single(self):
        """
        Implements the naked single deduction technique.
        Finds cells where only one number can fit and fills them.
        :return: True if any cell was updated, False otherwise.
        """
        updated = False
        for row in range(9):
            for col in range(9):
                if self.board[row][col] == 0:
                    candidates = []
                    for num in range(1, 10):
                        if self.is_valid(num, row, col):
                            candidates.append(num)
                    if len(candidates) == 1:
                        self.board[row][col] = candidates[0]
                        updated = True
        return updated
    
    def hidden_single(self):
        '''
        Implements the hidden single deduction technique.
        Finds numbers that can only fit in one cell of a row, column, or box.
        :return: True if any cell was updated, False otherwise.
        '''
        updated = False

        for num in range(1, 10): 
            # Check rows
            for row in range(9):
                candidates = []
                for col in range(9):
                    if self.board[row][col] == 0 and self.is_valid(num, row, col):
                        candidates.append((row, col))
                if len(candidates) == 1:
                    r, c = candidates[0]
                    self.board[r][c] = num
                    updated = True
                
            # Check columns
            for col in range(9):
                candidates = []
                for row in range(9):
                    if self.board[row][col] == 0 and self.is_valid(num, row, col):
                        candidates.append((row, col))
                if len(candidates) == 1:
                    r, c = candidates[0]
                    self.board[r][c] = num
                    updated = True
            
            # Check boxes
            for box_row in range(0, 9, 3):
                for box_col in range(0, 9, 3):
                    candidates = []
                    for i in range(box_row, box_row + 3):
                        for j in range(box_col, box_col + 3):
                            if self.board[i][j] == 0 and self.is_valid(num, i, j):
                                candidates.append((i, j))
                    if len(candidates) == 1:
                        r, c = candidates[0]
                        self.board[r][c] = num
                        updated = True

        return updated

    def solve(self):
        """
        Solve the Sudoku puzzle using deduction techniques and backtracking.
        :return: True if solved, False if no solution exists.
        """
        # Apply deduction techniques
        while (
            self.naked_single() or
            self.hidden_single()
        ):
            pass

        # Find empty cell
        for row in range(9):
            for col in range(9):
                if self.board[row][col] == 0:
                    # Try placing numbers 1 through 9
                    for num in range(1, 10):
                        if self.is_valid(num, row, col):
                            self.board[row][col] = num
                            if self.solve():
                                return True
                            # Invalid placement, backtrack
                            self.board[row][col] = 0
                    return False # No solution
        return True # Board solved
    
    def display_board(self):
        """
        Prints the board.
        """
        for i in range(9):
            for j in range(8):
                print(self.board[i][j], " ", end="")
            print(self.board[i][8])       