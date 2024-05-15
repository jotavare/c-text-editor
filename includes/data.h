#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f) // Bitwise AND operation with 00011111
#define BUFF_INIT {NULL, 0}
#define VIMWANNABE_VERSION "0.0.1"

/*
 * Assign large int values so that they don't conflict with ASCII values
*/
enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DEL_KEY,
};

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