#include "../includes/library.h"

/*
 * Handle errors and exit and clear the screen on exit;
 */
void die(const char *s)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

/*
 * Restore the terminal attributes to their original state and flush any inputted values;
 */
void disableRawMode()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &G.original_termios) == -1)
		die("tcsetattr");
}

/*
 * Get and save the original state of terminal attributes;
 * Disable, change, and/or fix with flags (description in 'man termios');
 * The iflag and cflag are not necessary but were used in the old days;
 * VMIN set minimum number of bytes of input before read() returns;
 * Vtime value of time to wait before read() return (in tenths of a second 1/10);
 */
void enableRawMode()
{
	if (tcgetattr(STDIN_FILENO, &G.original_termios) == -1)
		die("tcgetattr");

	atexit(disableRawMode);

	struct termios raw = G.original_termios;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
 * Wait for a keypress and return the pressed key;
 */
int editorReadKey()
{
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			die("read");
	}
	if (c == '\x1b')
	{
		char seq[3];
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return '\x1b';
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return '\x1b';
		if (seq[0] == '[')
		{
			if (seq[1] >= '0' && seq[1] <= '9')
			{
				if (read(STDIN_FILENO, &seq[2], 1) != 1)
					return '\x1b';
				if (seq[2] == '~')
				{
					switch (seq[1])
					{
					case '1': return HOME_KEY;
					case '3': return DEL_KEY;
					case '4': return END_KEY;
					case '5': return PAGE_UP;
					case '6': return PAGE_DOWN;
					case '7': return HOME_KEY;
					case '8': return END_KEY;
					}
				}
			}
			else
			{
				switch (seq[1])
				{
				case 'A': return ARROW_UP;
				case 'B': return ARROW_DOWN;
				case 'C': return ARROW_RIGHT;
				case 'D': return ARROW_LEFT;
				case 'H': return HOME_KEY;
				case 'F': return END_KEY;
				}
			}
		}
		else if (seq[0] == 'O')
		{
			switch (seq[1])
			{
			case 'H': return HOME_KEY;
			case 'F': return END_KEY;
			}
		}
		return '\x1b';
	}
	else
		return c;
}

/*
 * Use ioctl to get the size of the terminal window, if ioctl fails, return -1, else return 0;
 */
int getWindowSize(int *rows, int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (-1);
	else
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return (0);
	}
}
