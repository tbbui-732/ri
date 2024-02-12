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

/* user interface related methods */
void draw_tildes(void) {
    int screen_height, y_axis;
    screen_height = getmaxy(stdscr);
    for (y_axis = 0; y_axis < screen_height-1; y_axis++) { // NOTE: screen_height - 1 to account for status bar
        mvprintw(y_axis, 0, "~");
    }
    refresh();
}

void display_status_bar(void) {
    int screen_height;
    screen_height = getmaxy(stdscr);
    mvprintw(screen_height-1, 0, "<normal mode>"); // TODO: make this dynamic in the future
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

    // create window for sidebar (location for line number/tildes) and status bar (modes, writes, etc)
    WINDOW *side_bar, *status_bar;
    int screen_height = getmaxy(stdscr);
    int screen_width = getmaxx(stdscr);

    // TODO: why are my screens/windows not showing?!!!!!!
    side_bar = newwin(screen_height, 1, 0, 0); // dim: screen height, 1 width | start: top-left corner
    status_bar = newwin(1, screen_width, screen_height - 1, 0); // dim: 1 height, screen width | start: bottom-left corner
    
    // TODO: remove once windows actually work
    box(side_bar, 0, 0);
    box(status_bar, 0, 0);
    wrefresh(side_bar);
    wrefresh(status_bar);

    // user defined methods go here
    // draw_tildes(); // TODO: uncomment this code once figure out why screens are not showing
    // display_status_bar();
    process_user_input();

    // kill ncurses here
    refresh();
    delwin(side_bar);
    delwin(status_bar);
    endwin();
    return 0;
}
