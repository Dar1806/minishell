/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:38:57 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/27 16:55:27 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef enum e_token_type
{
	TOKEN_REDIR_OUT,		/*type = 0 // value = >*/
	TOKEN_REDIR_IN,			/*type = 1 // value = <*/
	TOKEN_REDIR_APPEND,		/*type = 2 // value = >>*/
	TOKEN_HEREDOC,			/*type = 3 // value = <<*/
	TOKEN_PIPE,				/*type = 4 // value = |*/
	TOKEN_WORD,				/*type = 5 // value = abc*/
	TOKEN_SINGLE_QUOTES,	/*type = 6 // value = 'abc'*/
	TOKEN_DOUBLE_QUOTES,	/*type = 7 // value = "abc"*/
}	t_token_type;


/*STRUCT LEXER*/
typedef struct s_token
{
	char					*value;
	struct s_token			*next;
	t_token_type			type;
}	t_token;

/*STRUCT PARSER*/
typedef struct s_cmd
{
	char			*here_doc;
	char			*outfile;
	char			*infile;
	char			**args;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

int		chose_tokens(t_token **tokens, char *line, int *i);
void	free_tokens(t_token *tokens);
t_cmd	*parser(t_token **tokens);
t_token	*lexer(char *line);

#endif