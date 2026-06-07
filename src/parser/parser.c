/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:10:41 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/05 15:36:15 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_type(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

int	is_word_type(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTES
		|| type == TOKEN_DOUBLE_QUOTES);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->append = 0;
	cmd->args = NULL;
	cmd->here_doc = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_cmd(t_cmd **first, t_cmd **last, t_cmd *cmd)
{
	if (!*first)
		*first = cmd;
	else
		(*last)->next = cmd;
	*last = cmd;
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;
	t_cmd	*first;
	t_cmd	*last;
	t_token	*cursor;

	if (!tokens)
		return (NULL);
	first = NULL;
	last = NULL;
	cursor = tokens;
	while (cursor)
	{
		cmd = new_cmd();
		if (!cmd)
		{
			free_cmd(first);
			return (NULL);
		}
		cursor = fill_cmd(cmd, cursor);
		add_cmd(&first, &last, cmd);
	}
	return (first);
}
