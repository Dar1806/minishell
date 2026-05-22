/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:38:57 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/22 14:06:15 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef enum e_token_type 
{
	TOKEN_REDIR_OUT, /*value = 0*/
	TOKEN_REDIR_IN,  /*value = 1*/
	TOKEN_WORD,		 /*value = 2*/
	TOKEN_PIPE,		 /*value = 3*/
}	t_token_type;

typedef struct s_token
{
	char					*value;
	struct s_token			*next;
	t_token_type			type;
}	t_token; 

t_token	*lexer(char *line);

#endif