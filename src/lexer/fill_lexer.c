/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:52:09 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/04 14:09:47 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

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

static int	choose_quote(t_token **tokens, char *line, int *i)
{
	int				j;
	char			*str;
	char			quote;
	t_token_type	type;

	j = *i;
	quote = line[j];
	if (quote == '\'')
		type = TOKEN_SINGLE_QUOTES;
	else
		type = TOKEN_DOUBLE_QUOTES;
	j++;
	while (line[j] && line[j] != quote)
		j++;
	if (!line[j])
	{
		ft_putstr_fd("minishell: EOF while looking for matching quote\n", 2);
		return (-1);
	}
	str = ft_substr(line, (*i) + 1, j - *i - 1);
	add_token(tokens, type, str);
	*i = j;
	return (0);
}

static void	choose_redir(t_token **tokens, char *line, int *i)
{
	int	j;

	j = (*i);
	if (line[j] == '>')
	{
		if (line[j + 1] == '>')
		{
			add_token(tokens, TOKEN_REDIR_APPEND, ft_strdup(">>"));
			j++;
		}
		else
			add_token(tokens, TOKEN_REDIR_OUT, ft_strdup(">"));
	}
	else if (line[j] == '<')
	{
		if (line[j + 1] == '<')
		{
			add_token(tokens, TOKEN_HEREDOC, ft_strdup("<<"));
			j++;
		}
		else
			add_token(tokens, TOKEN_REDIR_IN, ft_strdup("<"));
	}
	(*i) = j;
}

static void	read_word(t_token **tokens, char *line, int *i)
{
	int		j;
	char	*str;

	j = (*i);
	while (line[j] != ' ' && line[j] != '\t' && line[j] != '|'
		&& line[j] != '<' && line[j] != '>' && line[j] != '\0'
		&& line[j] != '\'' && line[j] != '"')
		j++;
	if (j == *i)
	{
		(*i)++;
		return ;
	}
	str = ft_substr(line, (*i), j - *i);
	add_token(tokens, TOKEN_WORD, str);
	(*i) = j;
}

int	choose_tokens(t_token **tokens, char *line, int *i)
{
	if (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	else if (line[*i] == '|')
	{
		add_token(tokens, TOKEN_PIPE, ft_strdup("|"));
		(*i)++;
	}
	else if (line[*i] == '>' || line[*i] == '<')
	{
		choose_redir(tokens, line, i);
		(*i)++;
	}
	else if (line[*i] == '\'' || line[*i] == '"')
	{
		if (choose_quote(tokens, line, i) == -1)
			return (-1);
		if (line[*i])
			(*i)++;
	}
	else
		read_word(tokens, line, i);
	return (0);
}
