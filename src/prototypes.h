/*
 * Prototypes for functions declared in ri.c
 */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

/* --- Definitions --- */
#define KEY_CTRL(key) ((key) & 0x1F)
#define KEY_END 360
#define KEY_PGUP 339
#define KEY_PGDN 338

/* --- Libraries --- */
#include <stdlib.h>
#include <sys/termios.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>

/* --- Constants --- */
#define TURN_ON 2000
#define TURN_OFF 2001
#define ESC_SEQ 27

/* --- Program Failure --- */
void die(char*);


/* --- Input --- */
void processUserInput(void);


/* --- Output --- */
void drawToTerminal(void);


/* --- Main --- */
int main(void);


#endif // PROTOTYPES_H
