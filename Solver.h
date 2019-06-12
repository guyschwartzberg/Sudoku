/*
 * Solver.h
 *
 *  Created on: 21 במאי 2019
 *      Author: GUY
 */

/**
 * Solver Summary :
 *
 * Solver represents a Full Sudoku Solver.
 * The Solver struct contains the Sudoku square matrix using the Cell module as a building block,
 * a size value to indicate one side's size and a solution matrix.
 * The module supports the following functions :
 *
 * createSolver                   -  Generates a solver struct given a cell matrix, size and solution.
 * createDeterminsticSolution     -  Receives a solver object and creates a solution for it using the determinstic
 * 								     backtracking algorithm. Updates the solution attribute for the Solver.
 * createDeterminsticSolution_rec -  Utility function. Recursively applies the determinstic backtracking algorithm to the given solver.
 * findPossibleValues             -  Utility function. Generates an array of possible values to a given cell
 * 									 that are legal under classic Sudoku rules.
 * FindUnassigned                 -  This function iterates the board from left to right and finds the first
 * 									 unassigned cell.
 * createRandomizedSolution       -  Receives a board and Solves it in place using the randomzied backtracking algorithm.
 * createRandomizedBoard          -  Receives a full sudoku board and the number of cells to fill and returns a
 * 									 sudoku board with a given amount of cells (chosen randomly) unfilled
 * sortPossibleValues			  -	 Utility function. Receives a semi-sorted arrays of possible values and sorts them.
 * destroySolver               -  -  Uses the cell module destroyBoard's function to free memory allocated for a given solver.
 *
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "Cell.h"
#include <time.h>
#include <stdlib.h>

/*
 * defines for createDeterminsticSolution retvals.
 */

#define UNSOLVABLE 0
#define SOLVABLE 1

/*
 * defines for FindUnassigned retvals.
 */

#define FULL 1
#define NON_FULL 0

/**
 * The struct Solver encapsulates a sudoku game square matrix & its possible solutions.
 * it contains three values - the game matrix "board" which is implemented using a Cell double
 * pointer (Cell ** board), a value to indicate the matrix's side's size (int size) and
 * a solution to the board. Note the the given solution MIGHT not be accurate for the
 * current state of the board and needs to be updated using the "validate" function to be accurate
 * (given that the current state of the board is solvable).
 */

typedef struct solver_t{
	Cell** board;
	int size;
	Cell** solution;
} Solver;

/** Solver * createSolver(Cell ** board, int size, Cell ** solution)
 * The function is a constructor for the solver struct.
 * It receives a board, its size and its solution and returns a solver struct.
 * @param board    = the cell matrix board.
 * 	      size     = the game size
 * 	      solution = the generated matrix solution
 * @return - a solver struct for the aforementioned values
 */

Solver * createSolver(Cell ** board, int size, Cell ** solution);

/** int createDeterminsticSolution(Solver * s)
 * The function receives a solver struct and solves it using the deterministic backtracking algorithm.
 * It edit's the solver's solution to contain the generated solution
 * @param s = the solver struct
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */
int createDeterminsticSolution(Solver * s);

/** int createDeterminsticSolution_rec(Solver * s)
 * The function receives a solver struct and recursively applies the deterministic backtracking algorithm to generate a solution.
 * @param s = the solver struct
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */
int createDeterminsticSolution_rec(Solver * s);

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
int findPossibleValues(int x, int y, Cell ** board, int size, int * possibleValues);

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
int FindUnassigned(Cell ** board, int size, int * i, int * j);
/** int createRandomizedSolution(Cell ** board, int size)
 * 		  This function receives a sudoku board and solves it using the randomized backtracking algorithm.
 * @param board    = the cell matrix board.
 * 		  size = the size of the board's side
 * @return - SOLVABLE = if the board is solvable using the algorithm
 * 			 UNSOLVABLE = if the board is unsolvable using the algorithm.
 */
int createRandomizedSolution(Cell ** board, int size);

/** Solver * createRandomizedBoard(Cell ** solution, int size, int cellsToFill)
 * 		  This function receives a solved sudoku board and generates a
 * 		  sudoku solver with cellsToFill cells to fill.
 * @param solution    = the solved cell matrix board.
 * 		  size = the size of the board's side
 * 		  cellsToFill = how many cells the function should erase from the solution
 * @return - s = A generated solver with the original solution as its solution and the generated
 * 				 board as its board.
 */
Solver * createRandomizedBoard(Cell ** solution, int size, int cellsToFill);

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
void sortPossibleValues(int * arr, int x, int y);

/** void destroySolver(Solver * s);
 * 		  This function uses the cell module's destroyBoard in order to free the memory of a given solver.
 * @param s = the solver to free.
 * @return this function has no return value.
 *
 */
void destroySolver(Solver * s);

#endif /* SOLVER_H_ */
