#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef uint16_t ui;


void clear_con(void)
{
    system("clear");
}

int load_file(const char* fname)
{
    int fd = open(fname, O_RDONLY);
    return fd;
}

void render(int c)
{
    struct winsize win;

    // get win size and win width
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    ui winWidth = win.ws_col;
    ui winHeight = win.ws_row;
    
    // print win height and width for starters
    printf("window width: %d\n", winWidth);
    printf("window height: %d\n", winHeight);

    int i;

    for (i = 0; i<winWidth; i++)
    {
        printf("%c", c);
    }

    printf("%c", '\n');

    for (i = 0; i<winWidth; i++)
    {
        printf("%c", c);
    }
}

int get_user_input(void)
{
    int c = getchar();
    return c;
}

int main(int argc, char* argv[])
{
    clear_con();
    int fd = load_file("/home/scwfri/tmp.txt");
    printf("Got fd: %d\n", fd);


    int c = get_user_input();
    printf("got char: %c", c);
    render(c);
}
