/* --- Libraries --- */
#include <stdio.h>

/* --- Program Failure --- */
void die(char* die_message) {
    
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
    printf("Hello world");
    return 0;
}
