#include "prototypes.h"

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
        if (ch == KEY_UP || ch == 'k')
        {
            printw("going up\n");
        }
        else if (ch == KEY_DOWN || ch == 'j')
        {
            printw("going down\n");
        }
        else if (ch == KEY_LEFT || ch == 'h')
        {
            printw("going left\n");
        }
        else if (ch == KEY_RIGHT || ch == 'l')
        {
            printw("going right\n");
        }
        else if (ch == KEY_HOME)
        {
            printw("going home\n");
        }
        else if (ch == KEY_END)
        {
            printw("going end\n");
        }
        else if (ch == KEY_PGUP)
        {
            printw("going page up\n");
        }
        else if (ch == KEY_PGDN)
        {
            printw("going page down\n");
        }
        else {
            printw("%d", ch);
        }
        ch = getch();
    }

    refresh();
}


/* --- Output --- */
void drawToTerminal(void) {
    int x = 0, y;
    int height = getmaxy(stdscr);

    for (y = 0; y < height; ++y) {      // Draw tildes like unused columns in vim
        mvaddch(y, x, '~');
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
    
    drawToTerminal();
    processUserInput();

    refresh();
    endwin(); // Kill ncurses

    return 0;
}
