/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/24 01:48:20 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include "struct.h"

# define S_QUOTES '\''
# define D_QUOTES '\"'
# define PIPE '|'
# define SOR '>'
# define SIR '<'
# define DIR "<<" 
# define DOR ">>"
# define TIR "<<<"
# define TEXT 0
# define SIGN_PIPE 1
# define SIGN_SOR 2
# define SIGN_SIR 3
# define SIGN_DIR 4
# define SIGN_DOR 5
# define SIGN_TIR 6

typedef struct s_lexer
{
	char			*content;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_prime
{
	char	*line;
	t_lexer	*lexer;
	t_env_l	*env_l;

}			t_prime;

t_prime	g_prime;

//---MAIN----
void	ft_readline(void);
void	print_error(char *str);

//*-------LEXER--------*//

void	lexer(void);

int		chrchr_quotes(char c);
int		strchr_quotes(char *str);
int		quotes_check(char *line);
char	**quotes_split(char *str, int size);

t_list	*wspace_split(char **lex_flist);

int		chrchr_metachar(char c);
int		strchr_metachar(char *content);
void	metachar_split(char *content);

void	create_nodes(t_list *lex_slist);
void	lexer_add_node(char *str, int type);
t_lexer	*lexer_listnew(char *content, int type);
void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new);
t_lexer	*lexer_lstlast(t_lexer	*lst);
char	*lexer_trim(char const *s, char set);

int		syntax_check(void);
void	init_env(char **env);

#endif