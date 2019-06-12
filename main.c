/*
 * test.c
 *
 *  Created on: 18 במאי 2019
 *      Author: GUY
 */



#include "MainAux.h"

int main(int argc, char *argv[]){
	int cellsToFill, valid, finished, callStatus, validity, c;
	int * status;
	Game * game;
	srand(atoi(argv[1]));
	validity = 1;
	SP_BUFF_SET();
	(void)argc;
	while(1 == 1)
	{
		finished = 0;
		printf("Please enter the number of cells to fill [0-80]:\n");
		valid = scanf("%d", &cellsToFill);
		while((c = getchar()) != '\n' && c != EOF)
				/* Cleans the buffer */ ;
		validity = checkValid(valid, cellsToFill);
		if (validity == 2) /* problem with scanf  while reading input */
		{
			printf("Exiting...\n");
			exit(0);
		}
		if (validity == 0)/* invalid input, back to main loop */
			continue;

		game = generateBoard(9, cellsToFill); /* Creating the game board with cellsToFill fixed cells */
		printBoard(game);
		status = calloc(4, sizeof(int));
		while (1 == 1) /* Flow of the game. reading the user's commends and applies them*/
		{
			readCommand(status, finished); /*Translating the user's input to command*/
			callStatus = callCommand(status, game); /*Perform the command*/
			if (callStatus == FINISHED) /* If the puzzle is solved updates the indicator*/
				finished = 1;
			if (callStatus == RESTART || callStatus == EXIT)
				break;
		}
		destroyGame(game); /* The user command to restart the game or exit */
		free(status);
		if (callStatus == EXIT)
		{
			printf("Exiting...\n");
			exit(0);
		}
	}

	return 0;





}
