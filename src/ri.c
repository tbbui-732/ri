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
        int ypos, xpos;
        int max_y, max_x;
        getyx(stdscr, ypos, xpos);
        getmaxyx(stdscr, max_y, max_x);

        if (ch == KEY_UP || ch == 'k')          --ypos;
        else if (ch == KEY_DOWN || ch == 'j')   ++ypos;
        else if (ch == KEY_LEFT || ch == 'h')   --xpos;
        else if (ch == KEY_RIGHT || ch == 'l')  ++xpos;
        else if (ch == KEY_HOME)                xpos = 0;
        else if (ch == KEY_END)                 xpos = max_x - 1;
        else if (ch == KEY_PGUP)                ypos = 0;
        else if (ch == KEY_PGDN)                ypos = max_y - 1;
        else printw("%c\n", ch);

        move(ypos, xpos);
        ch = getch();
        refresh();
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

    move(0, 0);                         // Resets cursor position

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
