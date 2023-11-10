/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/10 18:47:09 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "errors.h"
# include "chars.h"
# include "struct.h"

//---MAIN----
void	ft_readline(t_prime *g_prime);
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

//*------EXPANDER-------*//

void	expander(t_prime *g_prime);
char	*quotes_trim(char *content, int *end, char quotes);
char	*d_quotes_expand(t_prime *g_prime, char *content, int *end);
char	*straight_expand(t_prime *g_prime, char *content, int *end);
char	*dollar_analysis(char *content, int *end, t_prime *g_prime);
int		special_chars(char c);
int		ret_null(char c);
int		put_directly(char c);
int		put_synerror(char c);
int		special_chars(char c);
void	expander_add_node(t_expander **expander, char *str, int type);
void	free_expander(t_expander **expander);
void	print_expander(t_prime	*g_prime);

//*------PARSER-----*//

void	parser(t_prime *g_prime);

int		pipe_count(t_expander *expander);
void	parser_addnode(t_parser **parser, int pipe_count);

void	heredoc_init(t_prime *g_prime);
char	*pars_strjoin(char *s1, char *s2);
int		pars_strcmp(char *s1, char *s2);

void	renew_parser(t_prime *g_prime);
void	files_add_node(t_files **files, char *name, int type, int fd);
char	**dynamic_malloc(char **path, char *new);

void	print_parser(t_prime *g_prime);
void	free_parser(t_parser **parser);

#endif