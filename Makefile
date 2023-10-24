#SRCS = 	./SRC/main.c \ 
#		./SRC/LEXER/MAIN_LEXER/main_lexer.c \
#		./SRC/LEXER/QUOTES/quotes_check.c \
#		./SRC/LEXER/QUOTES/quotes_split.c \
#
#
##SRC_DIR = SRC/
#DIR = ./obj/
##SRC = ${addprefix ${SRC_DIR}, ${SRCS}}
##OBJ = ${addprefix ${DIR}, ${SRCS:.c=.o}}
#OBJ = $(patsubst %.c, $(DIR)%.o, $(notdir $(SRCS)
#CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#RM = rm -rf
#LIBFT = libft/libft.a
#NAME = minishell
#
##$(DIR)%.o : $(SRC_DIR)%.c
#$(DIR)%.o : %.c
#	@mkdir -p $(DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@ -I INCLUDE
#
#all : $(LIBFT) $(NAME)
#$(NAME): $(OBJ)
#	@$(CC) $(CFLAGS) -L./lib/lib -lreadline $^ $(LIBFT) -o $(NAME) 
#
#$(LIBFT):
#	@make -C libft
#
#clean:
#	@$(RM) $(OBJ) $(NAME) ./obj 
#
#fclean: clean
#	@make -C $(LIBFT) fclean
#
#re: fclean all
#
#.PHONY: all fclean re

#SRCS = 	./SRC/main.c \
#		./SRC/LEXER/MAIN_LEXER/main_lexer.c \
#		./SRC/LEXER/QUOTES/quotes_check.c \
#		./SRC/LEXER/QUOTES/quotes_split.c
#
#DIR = ./obj/
#OBJ = $(patsubst %.c, $(DIR)%.o, $(notdir $(SRCS)))
#CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#RM = rm -rf
#LIBFT = libft/libft.a
#NAME = minishell
#
#$(DIR)%.o : %.c
#	@mkdir -p $(DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@ -I INCLUDE
#
#all : $(LIBFT) $(NAME)
#
#$(NAME): $(OBJ)
#	@$(CC) $(CFLAGS) -L./lib/lib -lreadline $^ $(OBJ) $(LIBFT) -o $@
#
#$(LIBFT):
#	@make -C libft
#
#clean:
#	@$(RM) $(OBJ) $(NAME) $(DIR)
#
#fclean: clean
#	@make -C libft fclean
#
#re: fclean all
#
#.PHONY: all fclean re clean

#------------------------------------------------
#SRC_MAIN = 	main.c \
#		
#SRC_LEXER_MAIN =	main_lexer.c
#
#SRC_LEXER_QUOTES =	quotes_check.c \
#					quotes_split.c
#
#DIR = ./OBJ/
#SRC_MAINN = $(addprefix ./SRC/, $(SRC_MAIN))
#SRC_LEXER_MAINN = $(addprefix ./SRC/LEXER/MAIN_LEXER/, $(SRC_LEXER_MAIN))
#SRC_LEXER_QUOTESN = $(addprefix ./SRC/LEXER/QUOTES, $(SRC_LEXER_QUOTES))
##OBJ = $(addprefix $(DIR), $(SRCS:.c=.o))
#OBJ_MAIN = $(patsubst %.c, $(DIR)%.o, $(notdir $(SRC_MAINN)))
#OBJ_LEXER_MAIN = $(patsubst %.c, $(DIR)%.o, $(notdir $(SRC_LEXER_MAINN)))
#OBJ_LEXER_QUOTES = $(patsubst %.c, $(DIR)%.o, $(notdir $(SRC_LEXER_QUOTESN)))
#CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#RM = rm -rf
#LIBFT = libft/libft.a
#NAME = minishell
#
#$(DIR)%.o : ./SRC/%.c
#	@mkdir -p $(DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@
#
#$(DIR)%.o : ./SRC/LEXER/MAIN_LEXER/%.c
#	@cd -p $(DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@
#
#$(DIR)%.o : ./SRC/LEXER/QUOTES/%.c
#	@cd -p $(DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@
#
#all : $(LIBFT) $(NAME)
#
#$(NAME): $(OBJ_MAIN) $(OBJ_LEXER_MAIN) $(OBJ_LEXER_QUOTES)
#	@$(CC) $(CFLAGS) -L./lib/lib -lreadline $(LIBFT) -o $@
#
#$(LIBFT):
#	@make -C libft
#
#clean:
#	@$(RM) $(DIR)/*.o
#
#fclean: clean
#	@$(RM) $(NAME)
#	@make -C libft fclean
#
#re: fclean all
#
#.PHONY: all fclean re clean


SRC_MAIN = 	main.c \
				init_env.c
SRC_LEXER_MAIN =	main_lexer.c
SRC_LEXER_QUOTES =	quotes_check.c \
					quotes_split.c
SRC_LEXER_WSPACE =	wspace_split.c
SRC_LEXER_LISTINIT =	metachar_split.c \
						content_init.c \
						syntax_check.c
					

DIR = ./OBJ
SRC_MAINN = $(addprefix ./SRC/, $(SRC_MAIN))
SRC_LEXER_MAINN = $(addprefix ./SRC/LEXER/MAIN_LEXER/, $(SRC_LEXER_MAIN))
SRC_LEXER_QUOTESN = $(addprefix ./SRC/LEXER/QUOTES/, $(SRC_LEXER_QUOTES))
SRC_LEXER_WSPACEN = $(addprefix ./SRC/LEXER/WSPACE_SPLIT/, $(SRC_LEXER_WSPACE))
SRC_LEXER_LISTINITN = $(addprefix ./SRC/LEXER/LEXER_LIST_INIT/, $(SRC_LEXER_LISTINIT))

OBJ_MAIN = $(patsubst %.c, $(DIR)/%.o, $(notdir $(SRC_MAINN)))
OBJ_LEXER_MAIN = $(patsubst %.c, $(DIR)/%.o, $(notdir $(SRC_LEXER_MAINN)))
OBJ_LEXER_QUOTES = $(patsubst %.c, $(DIR)/%.o, $(notdir $(SRC_LEXER_QUOTESN)))
OBJ_LEXER_WSPACE = $(patsubst %.c, $(DIR)/%.o, $(notdir $(SRC_LEXER_WSPACE)))
OBJ_LEXER_LISTINIT = $(patsubst %.c, $(DIR)/%.o, $(notdir $(SRC_LEXER_LISTINIT)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -rf
LIBFT = libft/libft.a
NAME = minishell

$(DIR)/%.o : ./SRC/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR)/%.o : ./SRC/LEXER/MAIN_LEXER/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR)/%.o : ./SRC/LEXER/QUOTES/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR)/%.o : ./SRC/LEXER/WSPACE_SPLIT/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR)/%.o : ./SRC/LEXER/LEXER_LIST_INIT/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) -c $< -o $@



all : $(LIBFT) $(NAME)

$(NAME): $(OBJ_MAIN) $(OBJ_LEXER_MAIN) $(OBJ_LEXER_QUOTES) $(OBJ_LEXER_WSPACE) $(OBJ_LEXER_LISTINIT)
	@$(CC) $(CFLAGS) -l readline $^ $(LIBFT) -o $@

$(LIBFT):
	@make -C libft
	@make bonus -C libft

clean:
	@$(RM) $(DIR)/*.o

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re