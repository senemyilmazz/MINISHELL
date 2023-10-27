/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 16:14:05 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include "errors.h"
# include "chars.h"

typedef struct s_lexer
{
	char			*content;
	int				type;
	int				expand;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_env_l
{
	char			*name;
	char			*content;
	struct s_env_l	*next;
}					t_env_l;

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

int		chrchr_wspace(char c);
int		strchr_wspace(char *str);
t_list	*wspace_split(char *line, int start, int end, int quotes);

int		chrchr_metachar(char c);
int		strchr_metachar(char *content);
void	metachar_split(char *content);

void	create_nodes(t_list *lex_slist);
void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new);
t_lexer	*lexer_lstlast(t_lexer	*lst);
t_lexer	*lexer_listnew(char *content, int type);
void	lexer_add_node(t_lexer **lexer, char *str, int type);
char	*lexer_trim(char const *s, char set);

void	type_check(void);
void	type_match(t_lexer *temp);
int		syntax_check(void);

void	init_env(char **env);

#endif