#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

/* definitions */
#define KEY_CTRL(key) ((key) & 0x1F)
#define KEY_PGUP 339
#define KEY_PGDN 338

/* global methods */
void die(char *message) {
    refresh();
    endwin();
    fprintf(stderr, "%s\n", message);
    exit(1);
}

/* window creation and deletion methods */
WINDOW *create_curse_window(int win_height, int win_width, int start_y, int start_x) {
    WINDOW *new_window;
    new_window = newwin(win_height, win_width, start_y, start_x);
    box(new_window, 0, 0);
    wrefresh(new_window);
    return new_window;
}

void destroy_curse_window(WINDOW *local_win) {
    wborder(local_win, ' ', ' ' , ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}

/* user interface related methods */
void draw_tildes(void) {
    int y_axis;
    for (y_axis = 0; y_axis < LINES-1; y_axis++) { // NOTE: screen_height - 1 to account for status bar
        mvprintw(y_axis, 0, "~");
    }
    refresh();
}

void display_status_bar(void) {
    mvprintw(LINES-1, 0, "<normal mode>"); // TODO: make this dynamic in the future
    move(0, 1);
    refresh();
}

/* input related methods */
void process_user_input(void) {
    int ch;
    ch = getch();
    while (ch != KEY_CTRL('q')) {
        int ypos, xpos; // cursor position
        int max_y, max_x; // screen dimension
        getyx(stdscr, ypos, xpos);
        getmaxyx(stdscr, max_y, max_x);

        if (ch == KEY_UP || ch == 'k')          --ypos;
        else if (ch == KEY_DOWN  || ch == 'j')  ++ypos;
        else if (ch == KEY_LEFT  || ch == 'h')  --xpos;
        else if (ch == KEY_RIGHT || ch == 'l')  ++xpos;
        else if (ch == KEY_HOME)                xpos = 0;
        else if (ch == KEY_END)                 xpos = max_x - 1;
        else if (ch == KEY_PGUP)                ypos = 0;
        else if (ch == KEY_PGDN)                ypos = max_y - 1;
        else printw("%c\n", ch);

        move(ypos, xpos);
        refresh();
        ch = getch();
    }
    refresh();
}

/* start here */
int main(int argc, char *argv[]) {

    // initialize ncurses here
    initscr();
    raw(); 
    noecho();
    keypad(stdscr, TRUE);

    // Create window for sidebar (location for line number/tildes) and status bar (modes, writes, etc)
    WINDOW *side_bar, *status_bar;
    const int STATUS_BOTTOM_PAD = 2;
    const int SIDE_BAR_WIDTH = 2;

    // Must refresh stdscr before new windows can appear!
    refresh(); 

    // Initialize sidebar window
    side_bar = create_curse_window(
            LINES - STATUS_BOTTOM_PAD, // STATUS_BOTTOM_PAD accounts for status_bar height
            SIDE_BAR_WIDTH,
            0, 
            0); 

    // Initialize status bar window
    status_bar = create_curse_window(
            STATUS_BOTTOM_PAD,
            COLS,
            LINES - STATUS_BOTTOM_PAD,
            0);

    move(0, SIDE_BAR_WIDTH);

    // User defined methods go here
    // draw_tildes(); // TODO: uncomment this code once figure out why screens are not showing
    // display_status_bar();
    process_user_input();

    // Kill all ncurses related structures here
    destroy_curse_window(side_bar);
    destroy_curse_window(status_bar);
    refresh();
    endwin();
    return 0;
}
