CC = clang
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex
LIBFT = ./libft/libft.a
SRC_1 = pipex.c \
		pipex_utils.c \

OBJ_1 = $(SRC_1:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJ_1) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_1) $(LIBFT) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_1)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all