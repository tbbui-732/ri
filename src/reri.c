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
    mvprintw(screen_height-1, 0, "<normal mode>");
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

    // user defined methods go here
    draw_tildes();
    display_status_bar();
    process_user_input();

    // kill ncurses here
    refresh();
    endwin();
    return 0;
}
