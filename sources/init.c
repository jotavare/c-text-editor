#include "../includes/library.h"

/*
 * Get the size of the terminal window and initialize cursor position;
 * If the terminal window size cannot be obtained, exit;
 */
void initEditor()
{
    G.cx = 0;
    G.cy = 0;
    G.numrows = 0;

    if (getWindowSize(&G.screenrows, &G.screencols) == -1)
        die("getWindowSize");
}
