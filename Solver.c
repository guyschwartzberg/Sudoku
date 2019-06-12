/*
 * Solver.c
 *
 *  Created on: 21 במאי 2019
 *      Author: GUY
 */

#include "Solver.h"

/** Solver * createSolver(Cell ** board, int size, Cell ** solution)
 * The function is a constructor for the solver struct.
 * It receives a board, its size and its solution and returns a solver struct.
 * @param board    = the cell matrix board.
 * 	      size     = the game size
 * 	      solution = the generated matrix solution
 * @return - a solver struct for the aforementioned values
 */
Solver * createSolver(Cell ** board, int size, Cell ** solution){
	Solver * s = (Solver*) malloc(sizeof(Solver));
	s -> board = board;
	s -> size = size;
	s -> solution = solution;
	return s;
}
/** int createDeterminsticSolution(Solver * s)
 * The function receives a solver struct and solves it using the deterministic backtracking algorithm.
 * It edit's the solver's solution to contain the generated solution
 * @param s = the solver struct
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */
int createDeterminsticSolution(Solver * s) {
	s -> solution = copyBoard(s -> board, s-> size);
	return (createDeterminsticSolution_rec(s));
}

/** int createDeterminsticSolution_rec(Solver * s)
 * The function receives a solver struct and recursively applies the deterministic backtracking algorithm to generate a solution.
 * @param s = the solver struct
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */

int createDeterminsticSolution_rec(Solver * s) {
	int val, i, j;
	if (FindUnassigned(s -> solution, s -> size, &i, &j) == FULL)
	{
		return SOLVABLE;
	}

	for (val = 1; val <= s -> size; val++)
	{
		if (s -> solution[i][j].fixed == FREE)
		{
			if (checkValidity(i, j, val, s -> solution, s -> size) == VALID)
			{
				s -> solution[i][j].value = val;
				if (createDeterminsticSolution_rec(s) == 1)
					return SOLVABLE;
				s -> solution[i][j].value = UNASSIGNED;
			}
		}
	}
	return UNSOLVABLE;
}

/** int createRandomizedSolution(Cell ** board, int size)
 * 		  This function receives a sudoku board and solves it using the randomized backtracking algorithm.
 * @param board    = the cell matrix board.
 * 		  size = the size of the board's side
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */

int createRandomizedSolution(Cell ** board, int size){
	int numberOfPossibleValues, randomizedIndex, value, i, j;
	int * possibleValues;
	if (FindUnassigned(board, size, &i, &j) == FULL)
	{
		return SOLVABLE;
	}
	possibleValues = calloc(size, sizeof(int));
	numberOfPossibleValues = findPossibleValues(i, j, board, size, possibleValues);
	while (numberOfPossibleValues > 0)
	{
		if (numberOfPossibleValues == 1)
			randomizedIndex = 0;
		else
			randomizedIndex = rand() % numberOfPossibleValues;
		value = possibleValues[randomizedIndex];
		board[i][j].value = value;
		if (createRandomizedSolution(board, size) == SOLVABLE)
		{
			free(possibleValues);
			return SOLVABLE;
		}
		board[i][j].value = UNASSIGNED;
		possibleValues[randomizedIndex] = 0;
		sortPossibleValues(possibleValues, randomizedIndex, numberOfPossibleValues);
		numberOfPossibleValues--;

	}
	free(possibleValues);
	return UNSOLVABLE;
}

/** Solver * createRandomizedBoard(Cell ** solution, int size, int cellsToFill)
 * 		  This function receives a solved sudoku board and generates a
 * 		  sudoku solver with cellsToFill cells to fill.
 * @param solution    = the solved cell matrix board.
 * 		  size = the size of the board's side
 * 		  cellsToFill = how many cells the function should erase from the solution
 * @return - s = A generated solver with the original solution as its solution and the generated
 * 				 board as its board.
 */
Solver * createRandomizedBoard(Cell ** solution, int size, int cellsToFill) {
	int i = 0;
	int x, y, j;
	Cell ** board = copyBoard(solution, size);
	while (i < cellsToFill)
	{
		x = rand() % size;
		y = rand() % size;
		if (board[y][x].fixed == FIXED)
			continue;
		board[y][x].fixed = FIXED;
		i++;
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (board[i][j].fixed == FREE)
				board[i][j].value = 0;
	return (createSolver(board, size, solution));
}
/** int findPossibleValues(int x, int y, Cell ** board, int size, int * possibleValues)
 * This utility function receives a coordinate indicating a cell in the board and calculates all
 * of the possible values for that coordinate that are legal for insertion under the current state of the board.
 * The function puts those values into the "possibleValues" array
 * @param board = the sudoku board
 * 		  x = the x value of the coordinate to check between 1 and size
 * 		  y = the y value of the coordinate to check between 1 and size
 * 		  size = the size of the board's side
 * 		  possibleValues = an empty array of size "size"
 * @return - n = how many possibleValues there are
 */
int findPossibleValues(int x, int y, Cell ** board, int size, int * possibleValues)
{
	int i, index = 0;
	for (i = 1; i <= size; i++)
	{
		if (checkValidity(x, y, i, board, size) == 1)
		{
			possibleValues[index] = i;
			index++;
		}
	}
	return index;
}

/** int FindUnassigned(Cell ** board, int size, int * i, int * j)
 * 		  This function receives a sudoku board and its size and two pointers for a coordinate.
 * 		  The function finds the first coordinate, going from top left to right that is unassigned
 * 		  The function places the coordinate values into the pointer's value.
 * 		  The function indicates whether or not the board is full.
 * @param board    = the cell matrix board.
 * 		  size = the size of the board's side
 * 		  i = the pointer to the x value of the first unassigned coordinate
 * 		  j = the pointer to the y value of the first unassigned coordinate
 * @return - FULL = If the board is full
 * 			 NON-FULL = if the board is not full.
 */
int FindUnassigned(Cell ** board, int size, int * i, int * j) {
	for (*i = 0; *i < size; (*i)++)
		for (*j = 0; *j < size; (*j)++)
			if (board[*i][*j].value == UNASSIGNED)
			{
				return NON_FULL;
			}
	return FULL;
}

/** void destroySolver(Solver * s);
 * 		  This function uses the cell module's destroyBoard in order to free the memory of a given solver.
 * @param s = the solver to free.
 * @return this function has no return value.
 *
 */

void destroySolver(Solver * s) {
	destroyBoard(s -> board, s -> size);
	destroyBoard(s -> solution, s -> size);
	free(s);
}

/** void sortPossibleValues(int * arr, int x, int y)
 * 		  This function is a utility function.
 * 		  It receives an array that contains numerical values from its x index to its y index.
 * 		  It sorts those values so that if any zeros appear, they will be at the end.
 * 		  For instance, 2 3 0 4 will become 2 3 4 0.
 * @param arr = the array to sort
 * 		  x = the starting index
 * 		  y = the final index (is actually y-1)
 * @return this function has no return value.
 */
void sortPossibleValues(int * arr, int x, int y)
{
   int i, temp;
   for (i = x; i < y - 1; i++)
   {
	   temp = arr[i];
	   arr[i] = arr[i + 1];
	   arr[i + 1] = temp;
   }
}



