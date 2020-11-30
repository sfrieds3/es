#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "io.h"

typedef uint16_t ui;

struct winsize win;
ui cursorx, cursory;

int load_file(const char* fname)
{
    int fd = open(fname, O_RDONLY);
    return fd;
}

void write_char(ui cursrox, ui cursory, char c)
{
    
}

// get win size and win width
void get_win_details(void)
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
}

void _putc(char c)
{
    printf("%c", c);
}

void con_putc(ui cursorx, ui cursory, char c)
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

void render(int c)
{
    ui winWidth = win.ws_col;
    ui winHeight = win.ws_row;
    // print win height and width for starters
    printf("window width: %d\n", winWidth);
    printf("window height: %d\n", winHeight);

    int i;
    for (i = 0; i < winWidth; i++)
    {
        printf("%c", c);
    }

    printf("%c", '\n');

    for (i = 0; i < winWidth; i++)
    {
        printf("%c", c);
    }

    for (i = 0; i<3; i++)
    {
        printf("%c", ' ');
    }

    printf("%c", 'l');
}

int main(int argc, char* argv[])
{
    eliminate_stdio_buffering();
    clear_con();
    get_win_details();
    int fd = load_file("/home/scwfri/tmp.txt");
    printf("Got fd: %d\n", fd);

    char c = getchar();
    //while (c != 'q')
    //{
    //    render(c);
    //    c = getchar();
    //}

    con_putc(10, 10, c);

    c = getchar();

    restore_stdio_buffering();
}
