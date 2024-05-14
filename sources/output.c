#include "../includes/library.h"

/*
 * Draw the rows of the text editor;
 * The '~' character is used as a placeholder;
 * The last row is not followed by a newline;
*/
void editorDrawRows(struct appendBuffer *ab)
{
    int y;
    for (y = 0; y < G.screenrows; y++)
    {
        abAppend(ab, "\x1b[K", 3);
        abAppend(ab, "~", 1);
        if (y < G.screenrows - 1)
        {
            abAppend(ab, "\r\n", 2);
        }
    }
}

/*
 * Description: search for VT100 escape sequences;
 * Clear the screen and redraw the rows;
 * Position the cursor at the top left corner again;
 */
void editorRefreshScreen()
{
    struct appendBuffer ab = BUFF_INIT;
    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    abAppend(&ab, "\x1b[H", 3);
    abAppend(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}
