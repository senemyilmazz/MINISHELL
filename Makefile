NAME = minishell

SRC =	./SRC/MAIN/main.c \
		./SRC/MAIN/init_env.c \
		./SRC/MAIN/free_prime.c \
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
		./SRC/LEXER/SYNTAX_CHECK/syntax_check.c \
		./SRC/LEXER/print_lexer.c \
		./SRC/EXPANDER/main_expander.c \
		./SRC/EXPANDER/expand_content_utils.c \
		./SRC/EXPANDER/dollar_analysis.c \
		./SRC/EXPANDER/dollar_utils.c \
		./SRC/EXPANDER/expander_init_utils.c \
		./SRC/EXPANDER/print_expander.c \
		./SRC/PARSER/MAIN_PARSER/main_parser.c \
		./SRC/PARSER/HEREDOC/heredoc_init.c \
		./SRC/PARSER/PARSER_LIST_INIT/parser_init_utils.c \
		./SRC/PARSER/PARSER_LIST_INIT/t_file_init_utils.c \
		./SRC/PARSER/PARSER_LIST_INIT/renew_parser.c \
		./SRC/PARSER/UTILS/parser_utils.c \
		./SRC/PARSER/print_parser.c

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