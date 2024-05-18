NAME = vimwannabe
CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
RM = rm -f

SRCS =	sources/main.c \
		sources/terminal.c \
		sources/buffer.c \
		sources/output.c \
		sources/input.c \
		sources/init.c \
		sources/file.c \
		sources/find.c \
		sources/row_operations.c \
		sources/editor_operations.c \
		sources/syntax_highlight.c \

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(NAME)
