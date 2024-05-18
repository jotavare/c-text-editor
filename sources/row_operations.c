#include "../includes/library.h"

/*
 * Convert a chars index into a render index.
 */
int editorRowCxToRx(erow *row, int cx)
{
    int rx = 0;
    int j;
    for (j = 0; j < cx; j++)
    {
        if (row->chars[j] == '\t')
            rx += (VIMWANNABE_TAB_STOP - 1) - (rx % VIMWANNABE_TAB_STOP);
        rx++;
    }
    return rx;
}

/*
 * Update the row;
 * Free the memory of the row;
 * Allocate memory for the row;
 * Copy the string to the row and update the length of the row;
 */
void editorUpdateRow(erow *row)
{
    int tabs = 0;
    int j;

    for (j = 0; j < row->size; j++)
        if (row->chars[j] == '\t')
            tabs++;

    free(row->render);
    row->render = malloc(row->size + tabs * (VIMWANNABE_TAB_STOP - 1) + 1);

    int idx = 0;

    for (j = 0; j < row->size; j++)
    {
        if (row->chars[j] == '\t')
        {
            row->render[idx++] = ' ';
            while (idx % VIMWANNABE_TAB_STOP != 0)
                row->render[idx++] = ' ';
            row->render[idx++] = ' ';
        }
        else
        {
            row->render[idx++] = row->chars[j];
        }
    }

    row->render[idx] = '\0';
    row->rsize = idx;
}

/*
 * Append a row to the editor;
 * If the row is full, reallocate memory;
 * Copy the string to the row and update the length of the row;
 */
void editorAppendRow(char *s, size_t len)
{
    G.row = realloc(G.row, sizeof(erow) * (G.numrows + 1));

    int at = G.numrows;
    G.row[at].size = len;
    G.row[at].chars = malloc(len + 1);
    memcpy(G.row[at].chars, s, len);
    G.row[at].chars[len] = '\0';

    G.row[at].rsize = 0;
    G.row[at].render = NULL;
    editorUpdateRow(&G.row[at]);

    G.numrows++;
}