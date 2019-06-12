/*
 * Game.c
 *
 *  Created on: 18 ׳‘׳�׳�׳™ 2019
 *      Author: GUY
 */

#include "Game.h"

/** Game * createGame(Cell ** board, int size, Cell ** solution)
 * The function is a constructor for the game struct.
 * It receives a board, its size and its solution and returns a game struct.
 * @param board    = the cell matrix board.
 * 	      size     = the game size
 * 	      solution = the generated matrix solution
 * @return - a game struct for the aforementioned values
 */
Game * createGame(Cell ** board, int size, Cell ** solution){
	Game * s;
	s = (Game*) malloc(sizeof(Solver));
	s -> board = board;
	s -> size = size;
	s -> solution = solution;
	return s;
}

/** void destroyGame(Game * g)
 * The function free the allocated memory for the game board and for the game solution.
 * Finally, it frees the memory allocated for the struct at large.
 *
 * @param g = the generated game board.
 * @return - void
 */
void destroyGame(Game * g){
	destroyBoard(g -> board, g -> size);
	destroyBoard(g -> solution, g -> size);
	free(g);
}

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
int set(int x, int y, int z, Game * g){
	if (g -> board[x - 1][y - 1].fixed == FIXED){
		printf("Error: cell is fixed\n");
		return FAILURE;
	}
	if (checkValidity(x - 1, y - 1, z, g -> board, g -> size) == 0) {
		printf("Error: value is invalid\n");
		return FAILURE;
	}

	g -> board[x - 1][y - 1].value = z;
	printBoard(g);
	if (checkFilledCells(g) == 0) {
		printf("Puzzle solved successfully\n");
		return FINISHED;
	}
	return SUCCESS;
}

/** int checkFilledCells(Game * g)
 * The function checks how many cells in the game's board are unassigned
 * @param   game = the game struct
 * @return - the function returns how many Cells in the board are unassigned, from 1 to size*size.
 */
int checkFilledCells(Game * g) {
	int i, j, counter = 0;
	for (i = 0; i < g -> size; i++)
		for (j = 0; j < g -> size; j++)
			if (g -> board[i][j].value == UNASSIGNED)
				counter++;
	return counter;
}

/** void validate(Game * g)
 * The function checks a given game and prints a message to indicate whether its current state
 * is solvable. Note that the function does not destroy the game if its current state is unsolvable -
 * the user is still allowed to delete values as they wish.
 * If the current state is solvable, the function modifies the "solution" value of g to contain
 * one possible, updated solution.
 * @param game = the game struct
 * @return - The function has no return value.
 */
void validate(Game * g)
{
	Solver * s;
	s = createSolver(copyBoard(g -> board, g -> size), g -> size, NULL);
	if (createDeterminsticSolution(s) == SOLVABLE)
	{
		printf("Validation passed: board is solvable\n");
		destroyBoard(g -> solution, g -> size);
		g -> solution = copyBoard(s -> solution, g -> size);
		destroySolver(s);
		return;
	}
	printf("Validation failed: board is unsolvable\n");
	destroySolver(s);
	return;
}
/** void hint(Game * g, int x, int y)
 * The function prints to the console the current saved solution's value in a given coordinate.
 * Please note that the hint might not be accurate if the solution is inaccurate. In order to receive
 * an accurate hint, please use the validate function before the hint function.
 * @param x = the x value of the coordinate to receive a hint for between 1 and size
 * 		  y = the y value of the coordinate to receive a hint for between 1 and size
 * 		  game = the game struct
 * @return - The function has no return value.
 */
void hint(Game * g, int x, int y) {
	printf("Hint: set cell to %d\n", g -> solution[x - 1][y - 1].value);
}
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
Game * generateBoard(int size, int cellsToFill){
	Cell ** emptyBoard;
	Solver * generatedSolver;
	Game * g;
	emptyBoard = createEmptyBoard(size);
	createRandomizedSolution(emptyBoard, size);
	generatedSolver = createRandomizedBoard(emptyBoard, size, cellsToFill);
	g = createGame(copyBoard(generatedSolver -> board, generatedSolver -> size), size, copyBoard(generatedSolver -> solution, generatedSolver -> size));
	destroySolver(generatedSolver);
	return (g);
}
/** void printBoard(Game * g)
 * The function prints the game board to the console.
 * @param   game = the game struct
 * @return - The function has no return value.
 */
void printBoard(Game * g) {
	int i, j, k, l;
	for(i = 0; i < 3; i++){ /* block */
		printf("----------------------------------\n");
		for (j = 0; j < 3; j++){ /* row */
			for(k = 0; k < 3; k++){
				printf("|");
				for(l = 0; l < 3; l++){
					if((g -> board)[(i * 3) + j][(k * 3) + l].fixed == FIXED){
						printf(" .%d", (g -> board)[(i * 3) + j][(k * 3) + l].value);
					}
					else
					{
						if((g -> board)[(i * 3) + j][(k * 3) + l].value == 0){
							printf("   ");
						}
						else{
							printf("  %d", (g -> board)[(i * 3) + j][(k * 3) + l].value);
						}
					}

				}

				printf(" ");
			}
			printf("|\n");
		}

	}
	printf("----------------------------------\n");
}
