NAME		= codexion
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread
SRCS		= initialize.c \
			  util.c \
			  more_util.c \
			  dongle_actions.c \
			  simulation.c \
			  monitor.c \
			  cleanup.c \
			  even_more_util.c \
			  scheduler.c \
			  parsing_input.c \
			  codexion.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c headerfile.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
