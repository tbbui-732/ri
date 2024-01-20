#include "prototypes.h"

/* --- Definitions --- */
#define KEY_CTRL(key) ((key) & 0x1F)

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

void processUserInput(void) 
{
    char ch = getch();
    while (ch != KEY_CTRL('q')) {
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
