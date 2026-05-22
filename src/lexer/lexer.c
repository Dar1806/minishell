/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:24:07 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/22 14:02:53 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token *new;
	t_token *last;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static void	read_word(t_token **tokens, char *line, int *i)
{
	int	j;
	char	*str;

	j = (*i);
	while (line[j] != ' ' && line[j] != '|'
		&& line[j] != '<' && line[j] != '>' && line[j] != '\0')
		j++;
	str = ft_substr(line, (*i), j - *i);
	add_token(tokens, TOKEN_WORD, str);
	(*i) = j;
}

static void	shoes_tokens(t_token **tokens, char *line, int *i)
{
	if (line[*i] == ' ')
		(*i)++;
	else if (line[*i] == '|')
	{
		add_token(tokens, TOKEN_PIPE, "|");
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		add_token(tokens, TOKEN_REDIR_OUT, ">");
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		add_token(tokens, TOKEN_REDIR_IN, "<");
		(*i)++;
	}
	else
		read_word(tokens, line, i);
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		shoes_tokens(&tokens, line, &i);
	}
	return (tokens);
}
