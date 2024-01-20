#include "prototypes.h"

/* --- Definitions --- */
#define KEY_CTRL(key) ((key) & 0x1F)

/* --- Program Failure --- */
void die(char *message)
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
void processUserInput(void)
{
    int ch;
    ch = getch();
    while (ch != KEY_CTRL('q'))
    {
        printw("%d\n", ch);
        // if (ch == KEY_UP)
        // {
        //     printw("going up\n");
        //     getch();
        // }
        // else if (ch == KEY_DOWN)
        // {
        //     printw("going down\n");
        //     getch();
        // }
        // else if (ch == KEY_LEFT)
        // {
        //     printw("going left\n");
        //     getch();
        // }
        // else if (ch == KEY_RIGHT)
        // {
        //     printw("going right\n");
        //     getch();
        // }
        // else if (ch == KEY_HOME)
        // {
        //     printw("going home\n");
        //     getch();
        // }
        // else if (ch == KEY_LL)
        // {
        //     printw("going end\n");
        //     getch();
        // }
        // else {
        //     printw("%d", ch);
        //     getch();
        // }
    }

    refresh();
}

/* --- Main --- */
int main(void)
{
    initscr(); // Initialize ncurses
    raw();
    noecho();
    keypad(stdscr, TRUE);

    processUserInput();

    refresh();
    endwin(); // Kill ncurses

    return 0;
}
