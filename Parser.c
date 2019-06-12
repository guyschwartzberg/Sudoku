/*
 * Parser.c
 *
 *  Created on: 18 במאי 2019
 *      Author: GUY
 */

#include "Parser.h"

/**
 * Parsing the user's input.
 * files the array given as an argument with  the description of the command
 * and it's parameters as received from the user.
 * @param  status a pointer to array.
 * @param finished - an indicator to the puzzle status.
 *                   1 - if the puzzle is solved.
 *                   0 - if the puzzle is nor solved.
 *                   if 1: only returns the commands restart and exit.
 * status[0] = type of command. 0 - set
 *                              1 - hint
 *                              2- validate
 *                              3- restart
 *                              4 - exit
 * status[0] == 0:
 * status[1] = number of column
 * status[2] = number of row
 * status[3] = number to set
 * status[0] == 1:
 * status[1] = number of column
 * status[2] = number of row
 *
 *
 */
void readCommand(int * status, int finished) {
	char * command;
	const char * commandList[] =
	{
			"set",
			"hint",
			"validate",
			"restart",
			"exit"
	};
	int i;
	char* token;
	const char delim[8] = " \t\r\n";
	command = malloc(sizeof(char) * MAXSIZE);
	if (status == NULL)
	{
		printf("Error: readCommand has failed\n");
		free(command);
		return;
	}
	while (1 == 1)
	{
		if (fgets(command, MAXSIZE, stdin) == NULL){
			status[0] = EXIT; /* EOF */
			return;
		}
		else
		{
			if (command[0] == '\n')
				continue;
			/* token = command */

			token = strtok(command, delim);
			for (i = 0; i < 5; i++)
			{
				if (strcmp(token, commandList[i]) == 0)
				{
					if (finished == 1 && i >= 0 && i <= 2)
						break;
					if (determineStatus(i, status) == 1)
					{	free(command);
						return;
					}
					else
						break;
				}
			}

			printf("Error: invalid command\n");
			continue;
		}

	}


}

/**
 *extracts the additional parameters of set and hint commands.
 *@param j = an integer represents the type of command.
 *@param status = a pointer to an integer array sent from readCommand.
                  will be filled with parameters related to commands set or hint.
 * returns SUCCESS on success.
 * else FAILURE.
 */
int determineStatus (int j, int* status){
	int i;
	char* token;
	const char delim[8] = " \t\r\n";
	status[0] = j;
	if (j == SET)
		j = 3;
	else if (j == HINT)
		j = 2;
	else
		return 1;
	for (i = 1; i <= j; i++)
	{
		token = strtok(NULL, delim);
		if (token == NULL || isNumber(token, strlen(token)) == FAILURE)
		{
			break;
		}

		else
		{
			status[i] = atoi(token);
			if (i == j)
			{
				return SUCCESS;
			}
		}
	}
	return FAILURE;
}

/**
 * checks if a given string of size size is a number
 *@param token = the string
 *@param size = the size of the string
 * returns SUCCESS if the string is a number.
 * else FAILURE.
 */
int isNumber(char* token, int size){
	int i;
	for (i = 0; i < size - 1; i++)
		if (isdigit(token[i]) == 0)
			return FAILURE;
	return SUCCESS;
}
