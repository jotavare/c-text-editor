#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

/*
 * Compiler will complain about implicit declaration of functions, getline for example.
 * So I define this macros to request additional features from the system/headers bellow.
 */
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

/* INCLUDES*/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
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

// FILE
void editorOpen();

// ROW OPERATIONS
void editorAppendRow(char *s, size_t len);

#endif
