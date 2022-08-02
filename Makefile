

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CLIENT_NAME = client
SERVER_NAME = server

SERVER_SRCS = server.c comms.c comms_utils.c
CLIENT_SRCS = client.c comms.c comms_utils.c


SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(SERVER_NAME) $(CLIENT_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	make -C libft
	make -C ft_printf
	$(CC) $(CFLAGS) $(CLIENT_OBJS) libft/libft.a ft_printf/libftprintf.a -o $(CLIENT_NAME)


$(SERVER_NAME): $(SERVER_OBJS)
	make -C libft
	make -C ft_printf
	$(CC) $(CFLAGS) $(SERVER_OBJS) libft/libft.a ft_printf/libftprintf.a -o $(SERVER_NAME)


.PHONY: all clean fclean re


clean:
	rm $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm $(SERVER_NAME) $(CLIENT_NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: clean fclean all