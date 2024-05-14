// INCLUDES
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// DATA
struct termios g_original_termios;

void die(const char *s){
    perror(s);
    exit(1);
}

// TERMINAL
/*
 * Restore the terminal attributes to original state;
 * Flush any inputed values;
 */
void disableRawMode()
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_original_termios) == -1)
        die("tcsetattr");
}

/*
 * Get the original state of terminal attributes;
 * Disable, change and/or fix flags (description in 'man termios');
 * iflag and cflag are not necessary but were used in the old days (tradition);
 * set minimum number of bytes of input;
 * vtime is in the tenths of a second 1/10
 */
void enableRawMode()
{
    if(tcgetattr(STDIN_FILENO, &g_original_termios) == -1)
        die("tcgetattr");
    
    atexit(disableRawMode);

    struct termios raw = g_original_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// INIT
int main()
{
    enableRawMode();

    while (1)
    {
        char c = '\0';
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            die("read");

        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }
        else
        {
            printf("%d ('%c')\r\n", c, c);
        }
        if(c == 'q') break;
    }
    return 0;
}