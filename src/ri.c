/* --- Libraries --- */
#include <stdlib.h>
#include <sys/termios.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

/* --- Data --- */
struct termios default_terminal_settings;


/* --- Program Failure --- */
void die(char* message) {
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */

    printf("%s\n", message);    
    exit(1);
}

/* --- Terminal Specific Helper --- */
int termiosEqual(struct termios* first_term, struct termios* second_term) {
    if ((first_term->c_iflag    == second_term->c_iflag)    &&
        (first_term->c_oflag    == second_term->c_oflag)    &&
        (first_term->c_cflag    == second_term->c_cflag)    &&
        (first_term->c_lflag    == second_term->c_lflag)    &&
        // (first_term->c_cc[NCCS] == second_term->c_cc[NCCS]) &&  NOTE: I don't know if this is important
        (first_term->c_ispeed   == second_term->c_ispeed)   &&
        (first_term->c_ospeed   == second_term->c_ospeed)) {
        return 0;
    }
    return -1;
}

/* --- Terminal Specific --- */
void turnRawModeOn(void) {
    /* 
     * Sets terminal to raw mode. 
     * Raw mode reads values from stdin 
     * immediately.
     */


}

void turnRawModeOff(void) {
    /*
     * Sets terminal back to canonical 
     * mode. 
     *
     * Set when exiting the program or 
     * when a failure occurs
     */
}

/* --- Main --- */
int main(void) {
    return 0;
}
