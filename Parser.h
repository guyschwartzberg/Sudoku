/*
 * Parser.h
 *
 *  Created on: 18 במאי 2019
 *      Author: GUY
 */

#ifndef PARSER_H_
#define PARSER_H_

#define MAXSIZE 1024

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*
 * defines for readCommand retvals.
 */

#define SET 0
#define HINT 1
#define VALIDATE 2
#define RESTART 3
#define EXIT 4

/*
 * defines for determineStatus & isNumber retvals.
 */
#define SUCCESS 1
#define FAILURE 0
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

void readCommand(int * status, int finished);

/**
 *extracts the additional parameters of set and hint commands.
 *@param j = an integer represents the type of command.
 *@param status = a pointer to an integer array sent from readCommand.
                  will be filled with parameters related to commands set or hint.
 * returns SUCCESS on success.
 * else FAILURE.
 */
int determineStatus (int j, int* status);

/**
 * checks if a given string of size size is a number
 *@param token = the string
 *@param size = the size of the string
 * returns SUCCESS if the string is a number.
 * else FAILURE.
 */
int isNumber(char* token, int size);


#endif /* PARSER_H_ */
