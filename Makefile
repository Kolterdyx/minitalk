

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CLIENT_NAME = client
SERVER_NAME = server

SERVER_SRCS = server.c comms.c
CLIENT_SRCS = client.c comms.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(SERVER_NAME) $(CLIENT_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(CLIENT_OBJS) libft/libft.a -o $(CLIENT_NAME)


$(SERVER_NAME): $(SERVER_OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(SERVER_OBJS) libft/libft.a -o $(SERVER_NAME)


.PHONY: all clean fclean re


clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C libft clean

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	make -C libft fclean

re: clean fclean all