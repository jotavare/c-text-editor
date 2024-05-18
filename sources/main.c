#include "../includes/library.h"

struct editorConfig G;

int main(int argc, char **argv)
{
    enableRawMode();
    initEditor();
    if (argc >= 2)
    {
        editorOpen(argv[1]);
    }

      editorSetStatusMessage("HELP: Ctrl-Q = quit");

    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
