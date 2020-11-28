#include <termios.h>
#include <unistd.h>

struct termios termios_restore, termios_es;

// eliminate buffering for stdio
void eliminate_stdio_buffering()
{
    tcgetattr(0, &termios_restore);
    termios_es = termios_restore;
    tcsetattr(0, TCSANOW, &termios_es);
}

// restore stdio buffering
void resotre_stdio_buffering()
{
    tcsetattr(0, TCSANOW, &termios_restore);
}

