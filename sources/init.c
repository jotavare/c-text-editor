#include "../includes/library.h"

/*
 * Get the size of the terminal window and initialize cursor position;
 * If the terminal window size cannot be obtained, exit;
 */
void initEditor()
{
    G.cx = 0;
    G.cy = 0;
    G.rx = 0;
    G.rowoff = 0;
    G.coloff = 0;
    G.numrows = 0;
    G.row = NULL;
    G.filename = NULL;
      G.statusmsg[0] = '\0';
  G.statusmsg_time = 0;

    if (getWindowSize(&G.screenrows, &G.screencols) == -1)
    {
        die("getWindowSize");
    }

    G.screenrows -= 2;
}
