#include "prototypes.h"

/* --- Data --- */
struct global_data {
    struct termios default_term;
};

struct global_data GDATA;


/* --- Program Failure --- */
void die(char* message) 
{
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */

    refresh();
    endwin();

    printf("%s\n", message);    
    exit(1);
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
    if (key == ESC_SEQ) 
    {
        if (getchar() == '[') 
        {
            // These are probably arrow keys if it made it this far
            // TODO: Actually give arrow keys functionality
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

void processUserInput(void) 
{
    char ch = getch();
    while (ch != 17) {
        attron(A_BOLD);
        printw("%d, %c\n", ch, ch);
        attroff(A_BOLD);
        ch = getch();
    }
    refresh();
}


/* --- Main --- */
int main(void) 
{
    initscr();              // Initialize ncurses
    raw();
    noecho();
    keypad(stdscr, TRUE);

    processUserInput();

    refresh();
    endwin();               // Kill ncurses

    return 0;
}
