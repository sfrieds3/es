#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "io.h"

typedef uint16_t ui;

struct winsize win;
ui cursorx, cursory;
ui visible_line;

char* _bptr;

int load_file(const char* fname)
{
    int fd = open(fname, O_RDONLY);
    return fd;
}

// get win size and win width
void get_win_details(void)
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
}

void set_buf_ptr()
{
    _bptr = (char*)malloc(win.ws_col * win.ws_row);
    memset((void*)_bptr, ' ', win.ws_col * win.ws_row);
}

void _putc(ui xpos, ui ypos, char c)
{
    *(_bptr + (xpos * ypos)) = c;
}

/*
void con_putc_at_pos(ui cursorx, ui cursory, char c)
{
    ui winWidth = win.ws_col;
    ui winHeight = win.ws_row;
    int i;
    // get to the correct row
    for (i = 0; i < (cursory * winWidth); i++)
    {
        _putc(' ');
    }
    for (i = 0; i < cursorx; i++)
    {
        _putc(' ');
    }
    _putc(c);
}
*/

void clear_buffer(ui winWidth, ui winHeight)
{
    int i, j;
    for (i = 0; i < winHeight; i++)
    {
        for (j = 0; j < winWidth; j++)
        {
            putchar(' ');
        }
    }
}

void render_buffer()
{
    ui winWidth = win.ws_col;
    ui winHeight = win.ws_row;
    // print win height and width for starters
    //printf("window width: %d\n", winWidth);
    //printf("window height: %d\n", winHeight);

    clear_buffer(winWidth, winHeight);

    int i, j;
    // fill buffer with contents from _bptr
    for (i = 0; i < winHeight; i++)
    {
        for (j = 0; j < winWidth; j++)
        {
            putchar(*(_bptr + (j * i)));
        }
    }
}

void process_char(char c)
{
    _putc(cursorx, cursory, c);
    cursorx++;
    render_buffer();
}

void init_display(void)
{
    // init cursor position
    cursorx = 1;
    cursory = 1;
    // init line
    visible_line = 0;

    render_buffer();
}

int main(int argc, char* argv[])
{
    eliminate_stdio_buffering();
    clear_con();
    get_win_details();
    set_buf_ptr();
    init_display();
    // printf(_bptr);

    // default cursor pos = (0, 0)
    int fd = load_file("/home/scwfri/tmp.txt");
    //printf("Got fd: %d\n", fd);

    char c = getchar();
    bool done = false;

    while (!done)
    {
        switch (c)
        {
            case ':':
                done = true;
                break;
            default:
                process_char(c);
        }
        c = getchar();
    }

    free(_bptr);
    restore_stdio_buffering();
}
