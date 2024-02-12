#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

/* DEFINITIONS */
#define KEY_CTRL(key) ((key) & 0x1F)
#define KEY_PGUP 339
#define KEY_PGDN 338

/* GLOBAL METHODS */
void die(char *message) {
    refresh();
    endwin();
    fprintf(stderr, "%s\n", message);
    exit(1);
}

/* WINDOW CREATION AND DELETION METHODS */
WINDOW *create_curse_window(int win_height, int win_width, int start_y, int start_x) {
    WINDOW *new_window;
    new_window = newwin(win_height, win_width, start_y, start_x);
    // box(new_window, 0, 0); // uncomment to visualize windows
    wrefresh(new_window);
    return new_window;
}

void destroy_curse_window(WINDOW *local_win) {
    wborder(local_win, ' ', ' ' , ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}

/* USER INTERFACE RELATED METHODS */
// TODO: draw line numbers... eventually...
void draw_tildes(WINDOW *side_bar_win, int status_bottom_pad) {
    int y_axis;
    for (y_axis = 0; y_axis < LINES - status_bottom_pad; y_axis++) {
        mvwprintw(side_bar_win, y_axis, 0, "~");
    }
    wrefresh(side_bar_win);
}

void draw_status_bar(WINDOW *stat_bar_win) {
    mvwprintw(stat_bar_win, 0, 0, "---normal mode---"); // TODO: make this dynamic in the future
    wrefresh(stat_bar_win);
}

/* INPUT RELATED METHODS */
void process_user_input(void) {
    int ch;
    ch = getch();
    while (ch != KEY_CTRL('q')) {
        int ypos, xpos; // cursor position
        int max_y, max_x; // screen dimension
        getyx(stdscr, ypos, xpos);
        getmaxyx(stdscr, max_y, max_x);

        if (ch == KEY_UP || ch == 'k')           // move up
            --ypos;
        else if (ch == KEY_DOWN  || ch == 'j')   // move down
            ++ypos;
        else if (ch == KEY_LEFT  || ch == 'h')   // move left
            --xpos;
        else if (ch == KEY_RIGHT || ch == 'l')   // move right
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
        refresh();
        ch = getch();
    }
    refresh();
}

/* START HERE */
// TODO: don't allow cursor to overlap status_bar or side_bar
// TODO: read in a file and display it; allow user to scroll up and down
int main(int argc, char *argv[]) {

    // initialize ncurses here
    initscr();
    raw(); 
    noecho();
    keypad(stdscr, TRUE);

    WINDOW *side_bar, *status_bar, *view_screen;
    const int STATUS_BOTTOM_PAD = 1;
    const int SIDE_BAR_WIDTH = 2; // tildes idx 0, line number idx 1 (2 total)

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

    // Initialize view_screen window
    view_screen = create_curse_window(
            LINES - STATUS_BOTTOM_PAD,
            COLS - SIDE_BAR_WIDTH,
            0,
            SIDE_BAR_WIDTH);


    // User defined methods go here
    draw_tildes(side_bar, STATUS_BOTTOM_PAD);
    draw_status_bar(status_bar);
    move(0, SIDE_BAR_WIDTH);
    process_user_input();

    // Kill all ncurses related structures here
    destroy_curse_window(side_bar);
    destroy_curse_window(status_bar);
    destroy_curse_window(view_screen);
    refresh();
    endwin();
    return 0;
}
