/* --- Libraries --- */
#include <stdlib.h>
#include <sys/termios.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <math.h>

/* --- Constants --- */
#define TURN_ON 2000
#define TURN_OFF 2001
#define ESC_SEQ 27

/* --- Definitions --- */
#define KEY_CTRL(key) ((key) & 0x1F)
// #define KEY_END 360
#define KEY_PGUP 339
#define KEY_PGDN 338
#define VBAR_WIDTH 3            // arbitrary value for now
#define STATUS_BAR_HEIGHT 3     // arbitrary value for now


/* --- Global Data --- */
struct globalData {
    WINDOW *vbar;   // Vertical bar: Includes line-numbers, git signs, tildes.
    WINDOW *screen; // Screen: Section where the user can interact with text.
    WINDOW *sbar;   // Status bar: Information for the user at the bottom of the screen.
};

struct globalData editor;


/* --- Program Failure --- */
void die(char *message) {
    /*
     * Write error message to standard output
     * and exit with 1 status.
     */


    // Prevents terminal from acting strangely upon termination
    refresh();
    endwin();

    printf("%s\n", message);
    exit(1);
}


/* --- Input --- */
void processUserInput(void) {
    int ch;
    ch = getch();
    while (ch != KEY_CTRL('q')) {
        int ypos, xpos;
        int max_y, max_x;
        getyx(stdscr, ypos, xpos);
        getmaxyx(stdscr, max_y, max_x);

        if (ch == KEY_UP || ch == 'k')
            --ypos;
        else if (ch == KEY_DOWN || ch == 'j')
            ++ypos;
        else if (ch == KEY_LEFT || ch == 'h')
            --xpos;
        else if (ch == KEY_RIGHT || ch == 'l')
            ++xpos;
        else if (ch == KEY_HOME)
            xpos = 0;
        else if (ch == KEY_END)
            xpos = max_x - 1;
        else if (ch == KEY_PGUP)
            ypos = 0;
        else if (ch == KEY_PGDN)
            ypos = max_y - 1;
        else
            printw("%c\n", ch);

        move(ypos, xpos);
        ch = getch();
    }

    refresh();
}


/* --- Output --- */
void drawToVBar(void) {
    int x = 0, y, height;
    height = getmaxy(editor.vbar);

    int max_width = (int)log10(abs(height - 1)) + 1; // Maximum width of line numbers

    wmove(editor.vbar, 0, 0);

    for (y = 0; y < height; ++y) {
        // TODO: Implement line numbers
        // char ln[10];
        // sprintf(ln, "%d", y);

        if (y == 0) {
            mvwaddch(editor.vbar, y, x + 2, '~');
        } else {
            // TODO: Implement line numbers
            // int num_digit = (int)log10(abs(y)) + 1;
            // int padding = max_width - num_digit;
            // mvwprintw(editor.vbar, y, x, "%*s%s", padding, " ", ln);
            mvwaddch(editor.vbar, y, x + max_width, '~');
        }
    }

    wrefresh(editor.vbar);
    refresh();
}


/* --- Initialize Global Data --- */
WINDOW *initializeNewWindow(int nrows, int ncols, int start_y, int start_x) {
    WINDOW *new_win = newwin(nrows, ncols, start_y, start_x);
    box(new_win, 0, 0);
    wrefresh(new_win);
    return new_win;
}

void initializeGlobalData(void) {
    int term_ncols, term_nrows; // Get terminal dimensions
    getmaxyx(stdscr, term_nrows, term_ncols);

    editor.vbar = initializeNewWindow(term_nrows - STATUS_BAR_HEIGHT, // Initialize vertical bar
            VBAR_WIDTH,
            0,
            0);

    // TODO; Once the vertical bar works, come back to these windows
    // initializeNewWindow(&editor.screen,                                  // Initialize text-editor screen
    //                     term_nrows - STATUS_BAR_HEIGHT,
    //                     term_ncols - VBAR_WIDTH,
    //                     0,
    //                     VBAR_WIDTH);
    //
    // initializeNewWindow(&editor.sbar,                                    // Initialize status bar
    //                     STATUS_BAR_HEIGHT,
    //                     term_ncols,
    //                     term_nrows - STATUS_BAR_HEIGHT,
    //                     0);

    refresh();
}


/* --- Main --- */
int main(void) {
    // Initialize ncurses
    // Take keyboard input byte-by-byte
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    initializeGlobalData();
    drawToVBar();
    processUserInput();

    // Terminate ncurses
    refresh();
    endwin();
    return 0;
}
