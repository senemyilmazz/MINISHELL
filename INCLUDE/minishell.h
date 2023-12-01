/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:57:30 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/01 04:14:31 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "errors.h"
# include "chars.h"
# include "struct.h"

//---MAIN----//

void	ft_readline(t_prime *g_prime);
void	print_error(char *cmd, char *str);
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
void	env_lstadd_back(t_env_l	**lst, t_env_l	*new);
t_env_l	*env_lstlast(t_env_l	*lst);
t_env_l	*env_listnew(char *name, char *content);

//*------EXPANDER-------*//

void	expander(t_prime *g_prime);
char	*quotes_trim(char *content, int *end, char quotes);
char	*d_quotes_expand(t_prime *g_prime, char *content, int *end, int *env);
char	*straight_expand(t_prime *g_prime, char *content, int *end, int *env);
char	*dollar_analysis(char *content, int *end, t_prime *g_prime, int *env);
int		special_chars(char c);
int		ret_null(char c);
int		put_directly(char c);
int		put_synerror(char c);
int		special_chars(char c);
void	expander_add_node(t_expander **expan, char *str, t_lexer *lex, int env);
void	free_expander(t_expander **expander);
void	print_expander(t_prime	*g_prime);

//*------PARSER-----*//

void	parser(t_prime *g_prime);

int		pipe_count(t_prime *g_prime);
void	parser_addnode(t_parser **parser, int pipe_count);

void	heredoc_init(t_prime *g_prime);
char	*pars_strjoin(char *s1, char *s2);
int		ownstrcmp(char *s1, char *s2);

void	renew_parser(t_prime *g_prime);
int		infile_init(t_expander *expander, t_parser *parser);
int		outfile_init(t_expander *expander, t_parser *parser);
void	files_add_node(t_files **files, char *name, int type, int fd);
char	**dynamic_malloc(char **path, char *new);

void	print_parser(t_prime *g_prime);
void	free_parser(t_parser **parser);

//*------EXEC-----*//
void	executer(t_prime *g_prime);
void	run_command(t_prime *g_prime, t_parser *parser);
char	*check_cmd(char *cmd);
int		is_builtin(char *str);
void	run_builtin(t_prime *g_prime, t_parser *parser, int cmd_type);
void	dup_stdio(t_prime *g_prime, t_parser *parser);
void	run_execve(t_prime *g_prime, t_parser *parser);
char	**get_env_cpy(t_prime *g_prime);
void	free_env_cpy(char **envlist);

void	run_echo(t_parser *parser);
void	run_env(t_prime	*g_prime, t_parser *parser);



void	run_cd(t_prime *g_prime);
void	cd_one_arg(t_prime *g_prime);
void	cd_two_arg(t_prime *g_prime);
int		change_dir(t_prime *g_prime, char *parameters);
int		update_pwd_from_export(t_prime *g_prime, char *pwd_name, char *pwd_content);
int		n_control(char *str);
void	run_pwd(t_parser *parser);
void	run_exit(t_prime *g_prime);
void	str_addchar(char **dst, char c);
void	own_strjoin(char **dst, char *src);
int		str_compare(char *str1, char *str2);
void	delete_env(t_prime *g_prime, char *name);
int		get_env_name_count(char *env_arg);
char	*get_env_name(char *content);
void	run_export(t_prime *g_prime, t_parser *parser);
void	single_export_arg(t_prime *g_prime, t_parser *parser);
void	double_export_arg(t_prime *g_prime, char *env_cmd);
int		change_env(t_prime *g_prime, char *envname, char *arg, int is_equal);
void	run_unset(t_prime *g_prime);
int		env_arg_control(t_prime *g_prime, char *env);
char	*valid_env(char *env);

int		env_name_control(char *env);
void	add_newenv(t_prime *g_prime, char *env);
int		update_env(t_prime *g_prime, char *env_name, char *new_arg);
void	free_env_cpy(char **envlist);
int		parameters_count(char **str);
char	*get_command(t_prime *g_prime, t_parser *parser);
void	dup_stdio(t_prime *g_prime, t_parser *parser);
void	tempfd_init(t_prime *g_prime);
void	fd_closer(t_prime *g_prime);

#endif