#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 100
#define HEIGHT 35
#define MAX_LEN_STR 255

int main(int argc, char** argv) {
    FILE *fp;
    int size = 0;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Не удалось открыть файл");
        getchar();
        return 0;
    }
    while (!feof(fp)) {
        size += fgetc(fp) == '\n';
    }
    ++size;
    fseek(fp, SEEK_SET, 0);
    char mass[size][MAX_LEN_STR];
    for (int i = 0; i < size; ++i) {
        fgets(mass[i], MAX_LEN_STR, fp);
    }
    fclose(fp);

    if (!initscr()) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    printw("File: %s, size: %d", argv[1], size);
    refresh();

    int offsetx = (COLS - WIDTH) / 2;
    int offsety = (LINES - HEIGHT) / 2;
    int n_cur_line = 0;
    int n_cur_col = 0;
    bool end = false;

    WINDOW *win = newwin(HEIGHT, WIDTH, offsety, offsetx);

    while (!end) {
        for (int i = 0; (i < HEIGHT - 2) && (i < size); ++i) {
            int offset_col = 0, tp = i + n_cur_line;
            while (tp /= 10) {
                ++offset_col;
            }
            move(offsety + i + 1, offsetx + 1);
            printw("%d: ", i + n_cur_line);
            for (int j = 0; j + n_cur_col < strlen(mass[i + n_cur_line]) && j < WIDTH - 5 - offset_col &&
                        mass[i + n_cur_line][j + n_cur_col] != '\0' && mass[i + n_cur_line][j + n_cur_col] != '\n'; ++j) {
                addch(mass[i + n_cur_line][j + n_cur_col]);
            }
            offset_col = 0;
        }
        box(win, 0, 0);
        wrefresh(win);

        switch (getch()) {
                case 'q': end = true; break;
                case KEY_DOWN: n_cur_line += (size - n_cur_line) > HEIGHT - 2; break;
                case KEY_UP: n_cur_line -= n_cur_line > 0; break;
                case KEY_RIGHT: n_cur_col += (n_cur_col + WIDTH) < MAX_LEN_STR; break;
                case KEY_LEFT: n_cur_col -= n_cur_col > 0; break;
        }
    }

    delwin(win);
    endwin();
    return 0;
}
