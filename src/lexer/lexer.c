/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 12:24:07 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/21 19:11:53 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_joined(t_token *tokens, char *line, int i)
{
	t_token	*last;

	if (!tokens || !line[i])
		return ;
	if (line[i] == '\'' || line[i] == '"'
		|| (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '|' && line[i] != '<' && line[i] != '>'))
	{
		last = tokens;
		while (last->next)
			last = last->next;
		last->joined = 1;
	}
}

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = ft_malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = value;
	new->joined = 0;
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

t_token	*lexer(char *line, t_shell *shell)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (choose_tokens(&tokens, line, &i, shell) == -1)
		{
			// free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
