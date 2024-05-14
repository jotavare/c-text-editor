#include <termios.h>

struct editorConfig
{
    int cx, cy;
    int screenrows;
    int screencols;
    struct termios original_termios;
};

extern struct editorConfig G;

struct appendBuffer
{
    char *b;
    int len;
};