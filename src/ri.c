#include "prototypes.h"

/* --- Data --- */
struct termios default_terminal_settings;


/* --- Program Failure --- */
void die(char* message) {
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */

    turnRawModeOff();

    printf("%s\n", message);    
    exit(1);
}

/* --- Terminal Specific Helper --- */
void validateTermiosSet(struct termios* first_term, struct termios* second_term, const int mode) {
    /*
     * Validates that the terminal is properly set 
     * and exits based on whether rawMode is being turned on
     * or off.
     */

    // Checks that mode is either ON or OFF.
    if (mode != TURN_ON && mode != TURN_OFF) die("validateTermiosSet failed");
    
    // Verifies values of both termios structs.
    int result = -1;
    if ((first_term->c_iflag    == second_term->c_iflag)    &&
        (first_term->c_oflag    == second_term->c_oflag)    &&
        (first_term->c_cflag    == second_term->c_cflag)    &&
        (first_term->c_lflag    == second_term->c_lflag)    &&
        // (first_term->c_cc[NCCS] == second_term->c_cc[NCCS]) &&  NOTE: I don't know if this is important so it's commented out
        (first_term->c_ispeed   == second_term->c_ispeed)   &&
        (first_term->c_ospeed   == second_term->c_ospeed)) {
        result = 0;
    }
    
    // Exits accordingly if the structures are different.
    if (result == -1) {
        if (mode == TURN_ON)
            die("tcsetattr failed while turning on raw mode");
        else {
            printf("tcsetattr failed while turning off raw mode\n \
                    You might need to reset your terminal.");
            exit(1);
        }
    }
}

/* --- Terminal Specific --- */
void turnRawModeOn(void) {
    /* 
     * Sets terminal to raw mode. 
     * Raw mode reads values from stdin 
     * immediately.
     */
    
    // Get the default terminal settings
    tcgetattr(STDOUT_FILENO, &default_terminal_settings);

    // Create termios struct to store raw mode settings
    struct termios rawmode_settings = default_terminal_settings;
  
    // Set flags to make terminal "raw"
    rawmode_settings.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    rawmode_settings.c_oflag &= ~(OPOST);
    rawmode_settings.c_cflag |= (CS8);
    rawmode_settings.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // Set terminal to raw mode
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &rawmode_settings);
    
    // Handle tcsetattr errors
    struct termios check;
    tcgetattr(STDOUT_FILENO, &check);
    validateTermiosSet(&check, &rawmode_settings, TURN_ON);
}

void turnRawModeOff(void) {
    /*
     * Sets terminal back to canonical 
     * mode. 
     *
     * Set when exiting the program or 
     * when a failure occurs
     */
    
    // Set terminal back to default settings
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &default_terminal_settings);
    
    // Handle tcsetattr errors
    struct termios check;
    tcgetattr(STDOUT_FILENO, &check);
    validateTermiosSet(&check, &default_terminal_settings, TURN_OFF);
}


/* --- Main --- */
int main(void) {
    turnRawModeOn();

    return 0;
}
