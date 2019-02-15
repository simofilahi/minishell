:NAME= minishell
SRCS= srcs/*.c
CC= gcc
CFLAGS= -Wall -Werror -Wextra
INC= inc/.
OBJS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			make -C libft/
			$(CC) $(CFLAGS) $(SRCS) -L ./libft -lft -o $(NAME)
%.o: %.c 
			$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

clean:
			make -C libft/ clean
			rm -f $(OBJ)

fclean: clean
			make -C libft/ fclean
			rm -f $(NAME)

re: fclean all
