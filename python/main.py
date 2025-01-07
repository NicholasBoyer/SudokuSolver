# Custom imports
from solver import SudokuSolver

# Library imports
import requests
import json

# Constants
USE_API = True

"""
Fetch a sudoku board using the Dosuku API.
:param difficulty: Board difficulty
:return: Unsolved Sudoku board
:raise: API failure
"""
def fetch_sudoku(difficulty='easy'):
    url = 'https://sudoku-api.vercel.app/api/dosuku'
    params = {'difficulty' : difficulty}

    response = requests.get(url, params=params)

    if response.status_code == 200:
        board = response.json()['newboard']['grids'][0]['value']
        return board
    else:
        raise Exception(f"Failed to fetch Sudoku puzzle. Error code: {response.status_code}")

# Initialize board
if USE_API:
    board = fetch_sudoku()
else:
    board = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9],
    ]

# Solve board, print before and after states
solver = SudokuSolver(board)
print("\nUnsolved board")
solver.display_board()
if solver.solve():
    print("\nSolved Puzzle:")
    solver.display_board()
else:
    print("No solution exists.")