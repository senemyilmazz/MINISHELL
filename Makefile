NAME = minishell

SRC =	./SRC/main.c \
		./SRC/init_env.c \
		./SRC/LEXER/MAIN_LEXER/main_lexer.c \
		./SRC/LEXER/QUOTES/quotes_check.c \
		./SRC/LEXER/QUOTES/quotes_utils.c \
		./SRC/LEXER/WSPACE/wspace_split.c \
		./SRC/LEXER/WSPACE/wspace_utils.c \
		./SRC/LEXER/LEXER_LIST_INIT/create_nodes.c \
		./SRC/LEXER/METACHAR/metachar_split.c \
		./SRC/LEXER/METACHAR/metachar_utils.c \
		./SRC/LEXER/LEXER_LIST_INIT/lexer_init_utils.c \
		./SRC/LEXER/LEXER_LIST_INIT/type_init.c \
		./SRC/LEXER/SYNTAX_CHECK/syntax_check.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf
LIBFT = libft/libft.a

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(CFLAGS) -l readline $(LIBFT) $(SRC) -o $(NAME)
	@ make clean

$(LIBFT):
	@make -C libft
	@make bonus -C libft
	@make clean -C libft

all : $(LIBFT) $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re