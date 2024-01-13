/* --- Libraries --- */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* --- Program Failure --- */
void die(char* message) {
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */

    printf("%s\n", message);    
    exit(1);
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
