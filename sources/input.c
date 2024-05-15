#include "../includes/library.h"

/*
 * Handle the keypress and return the key;
 */
void editorMoveCursor(int key)
{
	switch (key)
	{
	case ARROW_LEFT:
		if (G.cx != 0)
			G.cx--;
		break;
	case ARROW_RIGHT:
		if (G.cx != G.screencols - 1)
			G.cx++;
		break;
	case ARROW_UP:
		if (G.cy != 0)
			G.cy--;
		break;
	case ARROW_DOWN:
		if (G.cy != G.screenrows - 1)
			G.cy++;
		break;
	}
}

/*
 * Wait for a keypress and handle it;
 * Clear the screen on exit;
 */
void editorProcessKeypress()
{
	int c = editorReadKey();
	switch (c)
	{
	case CTRL_KEY('q'):
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		exit(0);
		break;
	case HOME_KEY:
		G.cx = 0;
		break;
	case END_KEY:
		G.cx = G.screencols - 1;
		break;
	case PAGE_UP:
	case PAGE_DOWN:
	{
		int times = G.screenrows;
		while (times--)
			editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
	}
	break;
	case ARROW_UP:
	case ARROW_DOWN:
	case ARROW_LEFT:
	case ARROW_RIGHT:
		editorMoveCursor(c);
		break;
	}
}
