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

/* --- Program Failure --- */
void die(char*);

/* --- Terminal Specific Helper --- */
int termiosEqual(struct termios*, struct termios*);

/* --- Terminal Specific --- */
void turnRawModeOn(void);
void turnRawModeOff(void);

/* --- Main --- */
int main(void);

#endif // PROTOTYPES_H
