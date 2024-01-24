#include "prototypes.h"
#include <stdio.h>

/* --- Global Data --- */
struct globalData {
    // TODO: Insert some of the struct elements in here
};

struct globalData data;

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
    }

    refresh();
}


/* --- Output --- */
// TODO: Only draw line number if the current line contains a buffer
// TODO: Rename this function name
// TODO: Draw this on a separate window, NOT on stdscr!
void drawToTerminal(void) 
{
    int x = 0, y;
    int height = getmaxy(stdscr);

    for (y = 0; y < height; ++y) 
    {      
        char ln[10];
        sprintf(ln, "%d ", y);
        mvaddstr(y, x, ln);                 // Line numbers

        if (y == 0) 
        {                                   // Handle the special case when the number is 0
            mvaddch(y, x + 2, '~');         // Draw tildes like unused columns in vim
        } 
        else 
        {
            int num_digit = (int)log10(abs(y)) + 1;
            mvaddch(y, x + num_digit + 1, '~');
        }
    }

    move(0, 0);                             // Resets cursor position
    refresh();
}

/* --- Initialize Global Data --- */
// TODO: Write a function to initialize some global data
// TODO: Global data struct should include -> WINDOW(s) for line number and tildes
// TODO: Also thinking about creating a separate window for actual text editor screen

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
