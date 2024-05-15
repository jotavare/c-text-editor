#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

/* INCLUDES*/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "data.h"

// TERMINAL
void die(const char *s);
void disableRawMode();
void enableRawMode();
int editorReadKey();
int getWindowSize(int *rows, int *cols);

// BUFFER
void abAppend(struct appendBuffer *ab, const char *s, int len);
void abFree(struct appendBuffer *ab);

// OUTPUT
void editorDrawRows();
void editorRefreshScreen();

// INPUT
void editorMoveCursor(int key);
void editorProcessKeypress();

// INIT
void initEditor();

#endif
