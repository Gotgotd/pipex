CC = clang
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
NAME = pipex
BONUS = pipex_bonus
LIBFT = ./libft/libft.a
SRC_1 = $(wildcard src/*.c)
SRC_BONUS = $(wildcard src_bonus/*.c) $(wildcard gnl/*.c)

OBJ_1 = $(SRC_1:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME) $(BONUS)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJ_1) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_1) $(LIBFT)

$(BONUS) : $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS) $(LIBFT)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_1) $(OBJ_BONUS)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@$(RM) $(LIBFT)

re: fclean all