CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

kilo: kilo.c
		$(CC) $(CFLAGS) kilo.c -o kilo