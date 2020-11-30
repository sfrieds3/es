#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios termios_restore, termios_es;

// clear the console
void clear_con(void)
{
    system("clear");
}

// eliminate buffering for stdio
void eliminate_stdio_buffering(void)
{
    tcgetattr(0, &termios_restore);
    termios_es = termios_restore;
    termios_es.c_lflag &= ~ICANON;
    termios_es.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &termios_es);
}

// restore stdio buffering
void restore_stdio_buffering(void)
{
    tcsetattr(0, TCSANOW, &termios_restore);
}

