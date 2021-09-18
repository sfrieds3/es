#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios termios_restore, termios_es;

// clear the console
void clear_con(void)
{
    system("clear");
}

// restore stdio buffering
void restore_stdio_buffering(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_restore);
}

// eliminate buffering for stdio
void eliminate_stdio_buffering(void)
{
    //tcgetattr(0, &termios_restore);
    //termios_es = termios_restore;
    //termios_es.c_lflag &= ~ICANON;
    //termios_es.c_lflag &= ~ECHO;
    //tcsetattr(0, TCSANOW, &termios_es);

    // save our current termios so we can restore
    tcgetattr(STDIN_FILENO, &termios_restore);
    atexit(restore_stdio_buffering);

    // eliminiate stdio buffering
    struct termios raw = termios_restore;
    raw.c_lflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}

