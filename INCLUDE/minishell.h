/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 07:31:33 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>

# define S_QUOTES '\''
# define D_QUOTES '\"'
# define PIPE '|'
# define SIR '<'
# define SOR '>'
# define DIR "<<" 
# define DOR ">>"
# define TEXT 0
# define SIGN_PIPE 1
# define SIGN_SIR 2
# define SIGN_SOR 3
# define SIGN_DIR 4
# define SIGN_DOR 5

typedef struct s_lexer
{
	char	*content;
	int		type;
	void	*next;
}			t_lexer;

typedef struct s_prime
{
	char	*line;
	t_lexer	*lexer;

}			t_prime;

t_prime	g_prime;

//---MAIN----
void	ft_readline(void);
void	print_error(char *str);

//----LEXER
void	lexer(void);
int		quotes_check(char *line);
int		chrchr_quotes(char c);
char	**quotes_split(char *str, int size);
t_list	*wspace_split(char **lex_flist);
t_lexer	*lexer_listnew(char *content, int type);
void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new);
t_lexer	*lexer_lstlast(t_lexer	*lst);
char	*lexer_trim(char const *s, char set);
void	lexer_add_node(char *str, int type);

void create_nodes(t_list *lex_slist);
void    metachar_split(char *content);
int strchr_metachar(char *content);
int chrchr_metachar(char c);
int syntax_check(void);

int	strchr_quotes(char *str);

void	type_init(void);




#endif