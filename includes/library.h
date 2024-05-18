#pragma once

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

// LIBRARIES

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// DEFINES

#define VIMWANNABE_VERSION "0.0.1"
#define VIMWANNABE_TAB_STOP 8
#define VIMWANNABE_QUIT_TIMES 3
#define CTRL_KEY(k) ((k) & 0x1f)
#define BUFF_INIT {NULL, 0}

// DATA

// Enumeration for special keys
enum editorKey
{
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

// Enumeration for syntax highlighting
enum editorHighlight
{
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

// Syntax highlighting rules
struct editorSyntax
{
    char *filetype;                  // Type of file being edited
    char **filematch;                // File extensions associated with this syntax
    char **keywords;                 // Keywords to highlight
    char *singleline_comment_start;  // Start of single-line comment
    char *multiline_comment_start;   // Start of multi-line comment
    char *multiline_comment_end;     // End of multi-line comment
    int flags;                       // Additional flags
};

// Editor row
typedef struct erow
{
    int idx;                         // Index of row
    int size;                        // Size of the row
    int rsize;                       // Render size of the row
    char *chars;                     // Characters in the row
    char *render;                    // Rendered characters
    unsigned char *hl;               // Highlighting information
    int hl_open_comment;             // Flag indicating if a multi-line comment is open
} erow;

// Editor configuration
struct editorConfig
{
    int cx, cy;                      // Cursor position
    int rx;                          // Render cursor position
    int rowoff;                      // Row offset
    int coloff;                      // Column offset
    int screenrows;                  // Number of rows on screen
    int screencols;                  // Number of columns on screen
    int numrows;                     // Number of rows
    erow *row;                       // Rows of the editor
    int dirty;                       // Flag indicating if the editor is dirty
    char *filename;                  // Name of the file being edited
    char statusmsg[80];              // Status message
    time_t statusmsg_time;           // Time when the status message was set
    struct editorSyntax *syntax;     // Syntax highlighting information
    struct termios orig_termios;     // Original terminal settings
};

// Append buffer
struct abuf
{
    char *b;                         // Buffer
    int len;                         // Length of buffer
};

extern struct editorConfig E;

// BUFFER
void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);

// EDITOR OPERATIONS
void editorInsertChar(int c);
void editorInsertNewline();
void editorDelChar();

// FILE
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();

// FIND
void editorFindCallback(char *query, int key);
void editorFind();

// INIT
void initEditor();

// INPUT
char *editorPrompt(char *prompt, void (*callback)(char *, int));
void editorMoveCursor(int key);
void editorProcessKeypress();

// OUTPUT
void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();
void editorSetStatusMessage(const char *fmt, ...);

// ROW OPERATIONS
int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);

// SYNTAX_HIGHLIGHT
int is_separator(int c);
void editorUpdateSyntax(erow *row);
int editorSyntaxToColor(int hl);
void editorSelectSyntaxHighlight();

// TERMINAL
void die(const char *s);
void disableRawMode();
void enableRawMode();
int editorReadKey();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);
