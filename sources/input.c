#include "../includes/library.h"

/*
 * handle w, a, s, d keypresses;
 */
void editorMoveCursor(int key)
{
    switch (key)
    {
    case ARROW_LEFT:
        G.cx--;
        break;
    case ARROW_RIGHT:
        G.cx++;
        break;
    case ARROW_UP:
        G.cy--;
        break;
    case ARROW_DOWN:
        G.cy++;
        break;
    }
}

/*
 * Wait for a keypress and handle it;
 * Clear the screen on exit;
 */
void editorProcessKeypress()
{
    int c = editorReadKey();

    switch (c)
    {
    case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        exit(0);
        break;
    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
        editorMoveCursor(c);
        break;
    }
}
