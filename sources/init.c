#include "../includes/library.h"

/*
 * Get the size of the terminal window;
 * If it fails, exit;
 */
void initEditor()
{
    if (getWindowSize(&G.screenrows, &G.screencols) == -1)
        die("getWindowSize");
}
