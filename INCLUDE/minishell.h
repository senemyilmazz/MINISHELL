/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 17:50:53 by senyilma         ###   ########.fr       */
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
# include "struct.h"

//---MAIN----
void	ft_readline(t_prime *g_prime, char **env);
void	print_error(char *str);
void	free_prime(t_prime *g_prime);
void	free_lexer(t_lexer **lexer);

//*-------LEXER--------*//

void	lexer(t_prime *g_prime);

int		chrchr_quotes(char c);
int		strchr_quotes(char *str);
int		quotes_check(char *line);

int		chrchr_wspace(char c);
int		strchr_wspace(char *str);
t_list	*wspace_split(char *line, int start, int end, int quotes);

int		chrchr_metachar(char c);
int		strchr_metachar(char *content);
t_list	*metachar_split(t_list *lex_slist);

void	create_nodes(t_prime *g_prime, t_list *lex_mlist);

void	lexer_add_node(t_lexer **lexer, char *str, int type);

void	type_check(t_prime *g_prime);
void	type_match(t_lexer *temp);
int		syntax_check(t_prime *g_prime);

void	print_lexer(t_prime *g_prime);

//*------ENV-----*//
void	env_init(t_prime *g_prime, char **env);


void	expander(t_prime *g_prime);
void	expander_add_node(t_expander **expander, char *str, int type);

//char	*lexer_trim(char const *s, char set);
//parser veya expander kısmında lazım olacak?

#endif