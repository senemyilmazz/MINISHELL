/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:33:46 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 02:03:30 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env_l
{
	char			*name;
	char			*content;
	struct s_env_l	*next;
}					t_env_l;

typedef struct s_lexer
{
	char			*content;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_expander
{
	char				*content;
	int					type;
	struct s_expander	*next;
}						t_expander;

typedef struct s_prime
{
	char		*line;
	t_lexer		*lexer;
	t_env_l		*env_l;
	t_expander	*expander;
}			t_prime;

#endif