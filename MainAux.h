/*
 * MainAux.h
 *
 *  Created on: May 22, 2019
 *      Author: galiheim
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

#include "Parser.h"
#include "Game.h"
#include "Solver.h"
#include "Cell.h"


/*
 * defines for callCommand retvals.
 */
#define FAILURE 0
#define SUCCESS 1
#define FINISHED 2
#define RESTART 3
#define EXIT 4

/**
 *
 *if the number the user entered is a legal the function returns 1.
 *if the number the user entered is not legal the function returns 0.
 *If an error caused by the use of scanf occurred returns 2.
 * @param scanfOutPut = the integer returned by function scanf in main.
 * @param cellsToFill = the number the user entered in main.
 */
int checkValid(int scanfOutput,int cellsToFill);

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
int callCommand(int * status, Game * g);


#endif /* MAINAUX_H_ */
