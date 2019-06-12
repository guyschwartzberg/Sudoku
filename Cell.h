/*
 * Cell.h
 *
 *  Created on: 21 במאי 2019
 *      Author: GUY
 */


/**
 * Cell Summary :
 *
 * Cell represents a solumn Soduku board cell.
 * The cell sets a convention that all the other modules use.
 * The cell struct contains the value within the sudoku cell and a value to indicate
 * whether it's fixed or not. The module supports the following functions :
 *
 * checkValidity        -  checks if adding a given number in a given coordinate to a given Cell matrix is legal
 *                         according to classic sudoku rules.
 * copyBoard            -  creates a copy of a given cell matrix.
 * createEmptyBoard     -  creates an empty cell matrix.
 * destroyBoard         -  frees all memory resources associated with a given cell matrix.
 *
 */
#ifndef CELL_H_
#define CELL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"

/*
 * defines for cell.value values
 */
#define UNASSIGNED 0

/*
 * defines for cell.fixed values
 */
#define FIXED 1
#define FREE 0


/*
 * defines for checkValidity retvals.
 */
#define VALID 1
#define INVALID 0


/**
 * The struct cell encapsulates a sudoku game matrix cell.
 * it contains two values - the given value (0-9 whereas 0 = empty cell) and
 * a value to indicate whether or not a cell is a fixed cell (unmodifiable by the user).
 * 0 = FREE, 1 = FIXEd. Use defined keyword FIXED & FREE.
 */
typedef struct cell_t{
	int value;
	int fixed; /* 1 = fixed, 0 = not fixed */
} Cell;

/** int checkValidity(int x, int y, int z, Cell ** board, int size)
 * The function checks a given cell matrix and a sudoku move for legality.
 * the zero value indicates removal of a value from the cell.
 *
 * @param x = the x value of the coordinate to check between 1 and 9
 * 		  y = the y value of the coordinate to check between 1 and 9
 * 		  z = the value to check for validity between 0 and 9
 * 		  board = the cell matrix (size x size)
 * 		  size = the size of the cell matrix
 * @return - the function returns :
 * 			0 = the value is invalid,
 * 			1 = the value is valid.
 */
int checkValidity(int x, int y, int z, Cell ** board, int size);

/** Cell ** copyBoard(Cell ** board, int size)
 * The function creates an empty cell matrix using createEmptyMatrix of size "size" and copies
 * the given board's elements to the new board.
 *
 * @param board = the cell matrix (size x size)
 * 		  size = the size of the cell matrix
 * @return - the function returns :
 * 			NULL = the allocation failed
 * 			else it returns the new cell matrix.
 */
Cell ** copyBoard(Cell ** board, int size);

/** Cell ** createEmptyBoard(int size)
 * The function creates an empty cell matrix of size "size"
 *
 * @param size = the size of the cell matrix
 * @return - the function returns :
 * 			NULL = the allocation failed
 * 			else it returns the new cell matrix.
 */
Cell ** createEmptyBoard(int size);

/** void destroyBoard(Cell ** board, int size)
 * The function frees all memory associated with a cell matrix.
 *
 * @param   board = the cell matrix.
 * 			size = the size of the cell matrix
 */
void destroyBoard(Cell ** board, int size);

#endif /* CELL_H_ */
