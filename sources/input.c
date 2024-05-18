#include "../includes/library.h"

/*
 * Handle the keypress and return the key;
 */
void editorMoveCursor(int key)
{
	erow *row = (G.cy >= G.numrows) ? NULL : &G.row[G.cy];

	switch (key)
	{
	case ARROW_LEFT:
		if (G.cx != 0)
		{
			G.cx--;
		}
		else if (G.cy > 0)
		{
			G.cy--;
			G.cx = G.row[G.cy].size;
		}
		break;
	case ARROW_RIGHT:
		if (row && G.cx < row->size)
		{
			G.cx++;
		}
		else if (row && G.cx == row->size)
		{
			G.cy++;
			G.cx = 0;
		}
		break;
	case ARROW_UP:
		if (G.cy != 0)
		{
			G.cy--;
		}
		break;
	case ARROW_DOWN:
		if (G.cy < G.numrows)
		{
			G.cy++;
		}
		break;
	}

	row = (G.cy >= G.numrows) ? NULL : &G.row[G.cy];
	int rowlen = row ? row->size : 0;
	if (G.cx > rowlen)
	{
		G.cx = rowlen;
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
		if (G.cy < G.numrows)
        	G.cx = G.row[G.cy].size;
		break;
	case PAGE_UP:
	case PAGE_DOWN:
	{
		if (c == PAGE_UP)
		{
			G.cy = G.rowoff;
		}
		else if (c == PAGE_DOWN)
		{
			G.cy = G.rowoff + G.screenrows - 1;
			if (G.cy > G.numrows)
				G.cy = G.numrows;
		}

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
