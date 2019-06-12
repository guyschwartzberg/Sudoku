/*
 * Game.h
 *
 *  Created on: 18 במאי 2019
 *      Author: GUY
 */

/**
 * Game Summary :
 *
 * Game represents a Full Sudoku game and its solution.
 * The game struct contains the Sudoku square matrix using the Cell module as a building block,
 * a size value to indicate one side's size and a possible solution matrix.
 * The module supports the following functions :
 *
 * destroyGame          -  Frees both the game and solution boards using the destroyBoard function
 *                         of the cell module and frees the game struct.
 * set                  -  inserts a given value to a given coordinate on the board, provided the
 * 						   coordinate & values are legal for insertion.
 * checkFilledCells     -  Checks how many cells on the board are unassigned.
 * printBoard           -  Prints the current state of the board to the console.
 * generateBoard        -  Generates a randomized solvable size x size Sudoku game object with a given amount of empty cells.
 * 						   The attached solution is derived from the randomized backtracking algorithm.
 * validate             -  Verifies that the current board is solvable and prints an appropriate message to the console.
 * 						   If it is solvable, updates the solution to it using the deterministic backtracking algorithm.
 * hint                 -  Prints a hint to a requested coordinate. Note that the hint might not be accurate for the current state of the board.
 * 						   For the hint to be accurate, use validate first and then use hint.
 *
 */

#ifndef GAME_H_
#define GAME_H_

#include "Cell.h"
#include "Solver.h"

/*
 * defines for set retvals.
 */

#define FAILURE 0
#define SUCCESS 1
#define FINISHED 2

/**
 * The struct Game encapsulates a sudoku game square matrix & one of its possible solutions.
 * it contains three values - the game matrix "board" which is implemented using a Cell double
 * pointer (Cell ** board), a value to indicate the matrix's side's size (int size) and
 * a possible solution to the board. Note the the given solution MIGHT not be accurate for the
 * current state of the board and needs to be updated using the "validate" function to be accurate
 * (given that the current state of the board is solvable).
 */

typedef struct game_t{
	Cell** board;
	int size;
	Cell** solution;
} Game;

/** Game * createGame(Cell ** board, int size, Cell ** solution)
 * The function is a constructor for the game struct.
 * It receives a board, its size and its solution and returns a game struct.
 * @param board    = the cell matrix board.
 * 	      size     = the game size
 * 	      solution = the generated matrix solution
 * @return - a game struct for the aforementioned values
 */
Game * createGame(Cell ** board, int size, Cell ** solution);

/** void destroyGame(Game * g)
 * The function free the allocated memory for the game board and for the game solution.
 * Finally, it frees the memory allocated for the struct at large.
 *
 * @param g = the generated game board.
 * @return - void
 */
void destroyGame(Game * g);

/** int set(int x, int y, int z, Game * g)
 * The function inserts a given value between 1 and size in a given coordinate on the board
 * if : a. All parameters are legal integers, value between 0 and 9 and the coordinates between 1 and 9
 * 		   * note that if the function receives the value zero, it deletes the value from the cell
 * 		b. the value is a legal value in regards to the rules of classic Sudoku, i.e it is unique in the cell's column, row and block.
 *		c. The requested cell is not a fixed cell
 *		- The function then prints the game board if the insertion was successful
 *		- If the requested insertion completes the board, the function prints a message to the console
 *		  & returns a FINISHED value to indicate so.
 * @param x = the x value of the coordinate to insert to between 1 and size
 * 		  y = the y value of the coordinate to insert to between 1 and size
 * 		  z = the value to insert between 0 and size
 * 		  game = the game struct
 * @return - the function returns :
 * 			0 = the insertion was unsuccessful, whether due to illegal value or fixed coordinate
 * 			1 = the insertion was successful and the board is yet to be completed.
 * 			2 = the insertion was successful and the board is complete.
 */
int set(int x, int y, int z, Game * g);

/** int checkFilledCells(Game * g)
 * The function checks how many cells in the game's board are unassigned
 * @param   game = the game struct
 * @return - the function returns how many Cells in the board are unassigned, from 1 to size*size.
 */
int checkFilledCells(Game * g);

/** void printBoard(Game * g)
 * The function prints the game board to the console.
 * @param   game = the game struct
 * @return - The function has no return value.
 */
void printBoard(Game * g);

/** Game * generateBoard(int size, int cellsToFill)
 * The function creates a randomized square Sudoku game struct of size x size dimensions.
 * The game will have exactly cellsToFill cells that are fixed and cannot be modified by the user.
 * The game is generated using the randomized backtracking algorithm and its solution is the
 * solved board it was generated from. Please note that this is not a canonical solution and other solutions
 * may be appropriate as well. The solution does not update itself with insertions to the board
 * and therefore might be inaccurate at some stage after the initial generation, however the solution
 * is accurate when this function finishes.
 * @param size 		  = An integer to indicate the desired size of the board's side.
 * 		  cellsToFill = an integer between 0 and (size*size) - 1 to indicate how many cells
 * 		  				on the board will be fixed and unmodifiable by the user.
 * @return - the function returns :
 * 			g = the generated board & its solution encapsulated in a Game struct object.
 */
Game * generateBoard(int size, int cellsToFill);

/** void validate(Game * g)
 * The function checks a given game and prints a message to indicate whether its current state
 * is solvable. Note that the function does not destroy the game if its current state is unsolvable -
 * the user is still allowed to delete values as they wish.
 * If the current state is solvable, the function modifies the "solution" value of g to contain
 * one possible, updated solution.
 * @param game = the game struct
 * @return - The function has no return value.
 */
void validate(Game * g);

/** void hint(Game * g, int x, int y)
 * The function prints to the console the current saved solution's value in a given coordinate.
 * Please note that the hint might not be accurate if the solution is inaccurate. In order to receive
 * an accurate hint, please use the validate function before the hint function.
 * @param x = the x value of the coordinate to receive a hint for between 1 and size
 * 		  y = the y value of the coordinate to receive a hint for between 1 and size
 * 		  game = the game struct
 * @return - The function has no return value.
 */
void hint(Game * g, int x, int y);

#endif /* GAME_H_ */
