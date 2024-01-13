#include "prototypes.h"

/* --- Data --- */
struct termios default_terminal_settings;


/* --- Program Failure --- */
void die(char* message) 
{
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */

    turnRawModeOff();

    printf("%s\n", message);    
    exit(1);
}


/* --- Terminal Specific --- */
void turnRawModeOn(void) 
{
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
}

void turnRawModeOff(void) 
{
    /*
     * Sets terminal back to canonical 
     * mode. 
     *
     * Set when exiting the program or 
     * when a failure occurs
     */
    
    // Set terminal back to default settings
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &default_terminal_settings);
}


/* --- Input --- */
enum keys {
    UP_ARROW = 65,
    DOWN_ARROW,
    RIGHT_ARROW,
    LEFT_ARROW
};

void mapKey(char key) 
{
    // arrow keys
    // Up arrow:    27 91 65
    // Down:        27 91 66
    // Right:       27 91 67
    // Left:        27 91 68 
    if (key == ESC_SEQ) 
    {
        if (getchar() == '[') 
        {
            switch (getchar()) 
            {
                case UP_ARROW:
                    write(STDOUT_FILENO, "yes", sizeof("yes"));
                    break;
                case DOWN_ARROW:
                    write(STDOUT_FILENO, "yes", sizeof("yes"));
                    break;
                case RIGHT_ARROW:
                    write(STDOUT_FILENO, "yes", sizeof("yes"));
                    break;
                case LEFT_ARROW:
                    write(STDOUT_FILENO, "yes", sizeof("yes"));
                    break;
            }
        }
    }
}

void processUserInput(void) {
    char read_value;
    while (read(STDIN_FILENO, &read_value, 1) == 1 && read_value != 'q')
        // printf("%d %lu\r\n", read_value, sizeof(read_value));
        mapKey(read_value);
}


/* --- Main --- */
int main(void) {
    turnRawModeOn();
    processUserInput();
    turnRawModeOff();           // NOTE: Okay here for now, may need to be removed in the future IDK
    return 0;
}
