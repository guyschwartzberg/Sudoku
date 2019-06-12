/*
 * MainAux.c
 *
 *  Created on: May 22, 2019
 *      Author: galiheim
 */

#include "MainAux.h"


/**
 *
 *if the number the user entered is a legal the function returns 1.
 *if the number the user entered is not legal the function returns 0.
 *If an error caused by the use of scanf occurred returns 2.
 * @param scanfOutPut = the integer returned by function scanf in main.
 * @param cellsToFill = the number the user entered in main.
 */
int checkValid(int scanfOutput,int cellsToFill){
	if (scanfOutput!=1){
		return 2;

	}
	else if(cellsToFill>80 || cellsToFill<0){
		printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		return 0;


	}
	else{
		return 1;
	}

}

/**
 *The function commits the command the parser translated.
 *Except for  the commands: exit, restart.
 *The main function performs them.
 *The function returns SUCCESS - if the command run successfully.
 *                     FINISHED - if the puzzle was solved.
 *                     EXIT - if the command is exit.
 *                     RESTART - if command is restart.
 *                     FAILURE  - default value.
 * @param status = pointer to integer array described the command read from the user.
 * @param game = the struct Game represents the current game.
 */
int callCommand(int * status, Game * g) {
	if (status[0] == SET)
		return (set(status[2], status[1], status[3], g));
	if (status[0] == HINT)
	{
		hint(g, status[2], status[1]);
		return SUCCESS;
	}
	if (status[0] == VALIDATE)
	{
		validate(g);
		return SUCCESS;
	}
	if (status[0] == RESTART)
		return RESTART;
	if (status[0] == EXIT)
		return EXIT;
	return FAILURE;
}
