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
        if (y >= G.numrows)
        {
            if (y == G.screenrows / 3)
            {
                char welcome[80];
                int welcomelen = snprintf(welcome, sizeof(welcome), "vimwannabe -- version %s", VIMWANNABE_VERSION);
                if (welcomelen > G.screencols)
                    welcomelen = G.screencols;
                int padding = (G.screencols - welcomelen) / 2;
                if (padding)
                {
                    abAppend(ab, "~", 1);
                    padding--;
                }
                while (padding--)
                {
                    abAppend(ab, " ", 1);
                }
                abAppend(ab, welcome, welcomelen);
            }
            else
            {
                abAppend(ab, "~", 1);
            }
        }
        else
        {
            int len = G.row.size;
            if (len > G.screencols)
                len = G.screencols;
            abAppend(ab, G.row.chars, len);
        }
        abAppend(ab, "\x1b[K", 3);
        if (y < G.screenrows - 1)
        {
            abAppend(ab, "\r\n", 2);
        }
    }
}

/*
 * For description, search for VT100 escape sequences;
 * Clear the screen and redraw the rows;
 * Position the cursor at the middle;
 */
void editorRefreshScreen()
{
    struct appendBuffer ab = BUFF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", G.cy + 1, G.cx + 1);
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}
