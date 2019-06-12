/*
 * Cell.c
 *
 *  Created on: 21 במאי 2019
 *      Author: GUY
 */

#include "Cell.h"

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

int checkValidity(int x, int y, int z, Cell ** board, int size) {
	int i, j;
	if (z == 0)
		return VALID;
	for (i = 0; i < size; i++)
	{
		if (i != x) {
			if (board[i][y].value == z)
				return INVALID;
		}
		if (i != y) {
			if (board[x][i].value == z)
				return INVALID;
		}
	}

	for (i = (x / 3) * 3; i <= ((x / 3) * 3) + 2; i++)
	{
		for (j = (y / 3) * 3; j <= ((y / 3) * 3) + 2; j++)
		{
			if (i == x && j == y)
				continue;
			if (board[i][j].value == z)
				return INVALID;
		}
	}
	return VALID;

}


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
Cell ** copyBoard(Cell ** board, int size)
{
	int i, j;
	Cell ** copiedBoard = createEmptyBoard(size);
	for(i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			copiedBoard[i][j].value = board[i][j].value;
			copiedBoard[i][j].fixed = board[i][j].fixed;
		}
	}
	return copiedBoard;
}
/** void destroyBoard(Cell ** board, int size)
 * The function frees all memory associated with a cell matrix.
 *
 * @param   board = the cell matrix.
 * 			size = the size of the cell matrix
 */
void destroyBoard(Cell ** board, int size) {
	int i;
	for (i = 0;i < size; i++)
	{
		free(board[i]);
	}
	free(board);
}


/** Cell ** createEmptyBoard(int size)
 * The function creates an empty cell matrix of size "size"
 *
 * @param size = the size of the cell matrix
 * @return - the function returns :
 * 			NULL = the allocation failed
 * 			else it returns the new cell matrix.
 */
Cell ** createEmptyBoard(int size){
	int i,j;
	Cell** cellMatrix = (Cell**) malloc(size * sizeof(Cell*));
	if (cellMatrix == NULL)
		return NULL;
	for (i=0;i<size;i++){
		cellMatrix[i] = (Cell*)malloc(size * sizeof(Cell));
		if (cellMatrix[i] == NULL)
				return NULL;
	}


	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++){
		cellMatrix[i][j].value = UNASSIGNED;
		cellMatrix[i][j].fixed = FREE;
		}
	}
	return cellMatrix;
}
