#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f) // Bitwise AND operation with 00011111
#define BUFF_INIT \
    {             \
        NULL, 0   \
    }
#define VIMWANNABE_VERSION "0.0.1"
#define VIMWANNABE_TAB_STOP 8

/*
 * Assigned large int values so that they don't conflict with ASCII values
 */
enum editorKey
{
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

/*
 * Data types to store the rows of the text editor;
 */
typedef struct erow
{
    int size;
    int rsize;
    char *chars;
    char *render;
} erow;

struct editorConfig
{
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    char *filename;
      char statusmsg[80];
  time_t statusmsg_time;
    struct termios original_termios;
};

extern struct editorConfig G;

struct appendBuffer
{
    char *b;
    int len;
};