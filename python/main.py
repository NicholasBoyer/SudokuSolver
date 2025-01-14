# Custom imports
from solver import SudokuSolver

# Library imports
import argparse
import requests
import json

# Constants
USE_API = True

# Board type setting from command line arguments
parser = argparse.ArgumentParser(description="Specify whether to fetch from API or use the hardcoded board")
board_type = parser.add_argument("-b",
                                 "--board-type",
                                 choices=["default", "api"],
                                 default="default",
                                 help="Choose a method for instantiating unsolved board.")
args = parser.parse_args()
if args.board_type:
    if args.board_type == "default":
        print("Using hardcoded board")
        USE_API = False
    elif args.board_type == "api":
        print("Fetching board from API")
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
print("\nInitial puzzle state:")
solver.display_board()
if solver.solve():
    print("\nSolved puzzle:")
    solver.display_board()
else:
    print("No solution exists.")