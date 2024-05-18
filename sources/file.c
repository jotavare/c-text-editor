#include "../includes/library.h"

void editorOpen(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        die("fopen");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    linelen = getline(&line, &linecap, fp);
    if (linelen != -1)
    {
        while (linelen > 0 && (line[linelen - 1] == '\n' ||
                               line[linelen - 1] == '\r'))
            linelen--;
        G.row.size = linelen;
        G.row.chars = malloc(linelen + 1);
        memcpy(G.row.chars, line, linelen);
        G.row.chars[linelen] = '\0';
        G.numrows = 1;
    }
    free(line);
    fclose(fp);
}