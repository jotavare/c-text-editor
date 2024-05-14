#include "../includes/text_editor.h"

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
        abAppend(ab, "~", 1);
        if (y < G.screenrows - 1)
        {
            abAppend(ab, "\r\n", 2);
        }
    }
}

/*
 * Escape character = 27 = '\\x1b';
 * 'J' = Erase in display;
 * Other examples:
 * - '<esc>[1J' = clear the screen up to where the cursor is;
 * - '<esc>[0J' || '<esc>[J' = clear the screen from the cursor up to the end of the screen;
 * - '<esc>[H' || <esc>[1;1H = position the cursor at the first row and first column;
 * Search for VT100 escape sequences;
 * Clear the screen and redraw the rows;
 * Position the cursor at the top left corner again;
 */
void editorRefreshScreen()
{
    struct appendBuffer ab = BUFF_INIT;
    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    abAppend(&ab, "\x1b[H", 3);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}
