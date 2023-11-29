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
		./SRC/EXPANDER/MAIN_EXPANDER/main_expander.c \
		./SRC/EXPANDER/EXPANDER_LIST_INIT/expand_content.c \
		./SRC/EXPANDER/EXPANDER_LIST_INIT/dollar_analysis.c \
		./SRC/EXPANDER/EXPANDER_LIST_INIT/dollar_utils.c \
		./SRC/EXPANDER/EXPANDER_LIST_INIT/expander_init_utils.c \
		./SRC/EXPANDER/print_expander.c \
		./SRC/PARSER/MAIN_PARSER/main_parser.c \
		./SRC/PARSER/HEREDOC/heredoc_init.c \
		./SRC/PARSER/PARSER_LIST_INIT/parser_init_utils.c \
		./SRC/PARSER/PARSER_LIST_INIT/t_file_init_utils.c \
		./SRC/PARSER/PARSER_LIST_INIT/renew_parser.c \
		./SRC/PARSER/PARSER_LIST_INIT/infile_init.c \
		./SRC/PARSER/PARSER_LIST_INIT/outfile_init.c \
		./SRC/PARSER/UTILS/parser_utils.c \
		./SRC/PARSER/print_parser.c \
		./SRC/EXECUTER/BUILTIN/is_builtin.c \
		./SRC/EXECUTER/BUILTIN/run_builtin.c \
		./SRC/EXECUTER/BUILTIN/run_cd.c \
		./SRC/EXECUTER/BUILTIN/run_echo.c \
		./SRC/EXECUTER/BUILTIN/run_env.c \
		./SRC/EXECUTER/BUILTIN/run_pwd.c \
		./SRC/EXECUTER/BUILTIN/run_exit.c \
		./SRC/EXECUTER/BUILTIN/run_export.c \
		./SRC/EXECUTER/BUILTIN/run_unset.c \
		./SRC/EXECUTER/EXECMAIN/execmain.c \
		./SRC/EXECUTER/EXECMAIN/execve.c \
		./SRC/EXECUTER/EXECMAIN/run_process.c \
		./SRC/EXECUTER/UTILS/exec_utils.c \
		./SRC/EXECUTER/UTILS/exec_utils2.c \
		./SRC/EXECUTER/UTILS/exec_utils3.c \
		./SRC/EXECUTER/UTILS/env_arg_control.c \
		./SRC/EXECUTER/UTILS/pipe_utils.c


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf
LIBFT = libft/libft.a
READLINE = readline

OBJ = $(SRC:.c=.o)

all : $(READLINE) $(LIBFT) $(NAME) 

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline 
	cd readline-8.2 && make install

$(LIBFT):
	@make -C libft
	@make bonus -C libft
	@make clean -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(SRC) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline -o $(NAME)
	@ make clean


clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean
	@rm -rf readline-8.2 readline-8.2.tar.gz

re: fclean all

.PHONY: all clean fclean re