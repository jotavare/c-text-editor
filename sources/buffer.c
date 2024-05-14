#include "../includes/library.h"

/*
 * Append a string to the buffer;
 * If the buffer is full, reallocate memory;
 * Copy the string to the buffer;
 * Update the length of the buffer;
 * 
*/
void abAppend(struct appendBuffer *ab, const char *s, int len)
{
    char *new = realloc(ab->b, ab->len + len);

    if (new == NULL)
        return;

    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}

/*
 * Free the buffer;
 */
void abFree(struct appendBuffer *ab)
{
    free(ab->b);
}
