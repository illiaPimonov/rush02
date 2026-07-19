NAME = rush-02
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c utils.c number.c dict.c dict_read.c dict_helpers.c \
	dict_line.c convert.c convert_print.c convert_scale.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
