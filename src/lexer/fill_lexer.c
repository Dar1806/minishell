/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:52:09 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/06 02:28:41 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choose_quote(t_token **tokens, char *line, int *i, t_shell *shell)
{
	int				j;
	char			*str;
	char			quote;
	t_token_type	type;

	j = *i;
	quote = line[j];
	type = TOKEN_DOUBLE_QUOTES;
	if (quote == '\'')
		type = TOKEN_SINGLE_QUOTES;
	j++;
	while (line[j] && line[j] != quote)
		j++;
	if (!line[j])
	{
		ft_putstr_fd("minishell: EOF while looking for matching quote\n", 2);
		return (-1);
	}
	str = ft_substr(line, (*i) + 1, j - *i - 1);
	if (type == TOKEN_DOUBLE_QUOTES)
		expander(&str, shell);
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

static void	read_word(t_token **tokens, char *line, int *i, t_shell *shell)
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
	expander(&str, shell);
	if (str && str[0])
		add_token(tokens, TOKEN_WORD, str);
	else
		free(str);
	(*i) = j;
}

static int	handle_quote_token(t_token **tokens, char *line, int *i, t_shell *shell)
{
	if (choose_quote(tokens, line, i, shell) == -1)
		return (-1);
	if (line[*i])
		(*i)++;
	set_last_joined(*tokens, line, *i);
	return (0);
}

int	choose_tokens(t_token **tokens, char *line, int *i, t_shell *shell)
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
	else if (line[*i] == '&')
		return (ft_putstr_fd("minishell: syntax error"
			" near unexpected token `&&'\n", 2), -1);
	else if (line[*i] == '\'' || line[*i] == '"')
		return (handle_quote_token(tokens, line, i, shell));
	else
	{
		read_word(tokens, line, i, shell);
		set_last_joined(*tokens, line, *i);
	}
	return (0);
}
