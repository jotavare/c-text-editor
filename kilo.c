#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios g_original_termios;

/*
 * restore terminal attributes to original state + flush any inputed values
*/
void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_original_termios);
}

/*
 * get the original state of terminal attributes
 * disable ECHO (print to console) and ISIG flags (ctrl+z and ctrl+c)
*/
void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &g_original_termios);
    atexit(disableRawMode);

    struct termios raw = g_original_termios;

    raw.c_lflag &= ~(ECHO);
    raw.c_lflag &= ~(ISIG);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    enableRawMode();

    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}