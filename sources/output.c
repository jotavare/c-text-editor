#include "../includes/library.h"

/*
 * Check if the cursor is above or below the visible window;
 */
void editorScroll()
{
    G.rx = 0;

    if (G.cy < G.numrows)
    {
        G.rx = editorRowCxToRx(&G.row[G.cy], G.cx);
    }

    if (G.cy < G.rowoff)
    {
        G.rowoff = G.cy;
    }
    if (G.cy >= G.rowoff + G.screenrows)
    {
        G.rowoff = G.cy - G.screenrows + 1;
    }
    if (G.rx < G.coloff)
    {
        G.coloff = G.rx;
    }
    if (G.rx >= G.coloff + G.screencols)
    {
        G.coloff = G.rx - G.screencols + 1;
    }
}

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
        int filerow = y + G.rowoff;
        if (filerow >= G.numrows)
        {
            if (G.numrows == 0 && y == G.screenrows / 3)
            {
                char welcome[80];
                int welcomelen = snprintf(welcome, sizeof(welcome),
                                          "vimwannabe editor -- version %s", VIMWANNABE_VERSION);
                if (welcomelen > G.screencols)
                    welcomelen = G.screencols;
                int padding = (G.screencols - welcomelen) / 2;
                if (padding)
                {
                    abAppend(ab, "~", 1);
                    padding--;
                }
                while (padding--)
                    abAppend(ab, " ", 1);
                abAppend(ab, welcome, welcomelen);
            }
            else
            {
                abAppend(ab, "~", 1);
            }
        }
        else
        {
            int len = G.row[filerow].rsize - G.coloff;
            if (len < 0)
                len = 0;
            if (len > G.screencols)
                len = G.screencols;
            abAppend(ab, &G.row[filerow].render[G.coloff], len);
        }
        abAppend(ab, "\x1b[K", 3);
        abAppend(ab, "\r\n", 2);
    }
}

/*
 * Draw the status bar;
 * Inverse video mode is used;
 * The status bar is filled with spaces;
 */
void editorDrawStatusBar(struct abuf *ab)
{
    abAppend(ab, "\x1b[7m", 4);

    char status[80], rstatus[80];
    int len = snprintf(status, sizeof(status), "%.20s - %d lines", G.filename ? G.filename : "[No Name]", G.numrows);
    int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", G.cy + 1, G.numrows);

    if (len > G.screencols)
        len = G.screencols;

    abAppend(ab, status, len);

    while (len < G.screencols)
    {
        if (G.screencols - len == rlen)
        {
            abAppend(ab, rstatus, rlen);
            break;
        }
        else
        {
            abAppend(ab, " ", 1);
            len++;
        }
    }

    abAppend(ab, "\x1b[m", 3);
    abAppend(ab, "\r\n", 2);
}

/*
 * Draw the message bar;
 */
void editorDrawMessageBar(struct abuf *ab)
{
    abAppend(ab, "\x1b[K", 3);

    int msglen = strlen(G.statusmsg);

    if (msglen > G.screencols)
        msglen = G.screencols;
    if (msglen && time(NULL) - G.statusmsg_time < 5)
        abAppend(ab, G.statusmsg, msglen);
}

/*
 * For description, search for VT100 escape sequences;
 * Clear the screen and redraw the rows;
 * Position the cursor at the middle;
 */
void editorRefreshScreen()
{
    editorScroll();

    struct appendBuffer ab = BUFF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);
    editorDrawStatusBar(&ab);
    editorDrawMessageBar(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (G.cy - G.rowoff) + 1, (G.rx - G.coloff) + 1);
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

/*
 * Set the status message;
 * The message is displayed for 5 seconds;
 */
void editorSetStatusMessage(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(G.statusmsg, sizeof(G.statusmsg), fmt, ap);
    va_end(ap);
    G.statusmsg_time = time(NULL);
}