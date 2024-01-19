/*
 * Prototypes for functions declared in ri.c
 */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H


/* --- Libraries --- */
#include <stdlib.h>
#include <sys/termios.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <ncurses.h>

/* --- Constants --- */
#define TURN_ON 2000
#define TURN_OFF 2001
#define ESC_SEQ 27

/* --- Program Failure --- */
void die(char*);


/* --- Terminal Specific --- */
void turnRawModeOn(void);
void turnRawModeOff(void);


/* --- Input --- */
void mapKey(char key);
void processUserInput(void);


/* --- Main --- */
int main(void);


#endif // PROTOTYPES_H
