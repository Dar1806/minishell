/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:37:35 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/28 18:37:33 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	count_args(t_token *cursor)
{
	int	count;

	count = 0;
	while (cursor && cursor->type != TOKEN_PIPE)
	{
		if (cursor->type == TOKEN_REDIR_IN
			|| cursor->type == TOKEN_REDIR_OUT
			|| cursor->type == TOKEN_REDIR_APPEND
			|| cursor->type == TOKEN_HEREDOC)
		{
			if (cursor->next)
				cursor = cursor->next;
		}
		else if (cursor->type == TOKEN_WORD
			|| cursor->type == TOKEN_SINGLE_QUOTES
			|| cursor->type == TOKEN_DOUBLE_QUOTES)
			count++;
		cursor = cursor->next;
	}
	return (count);
}

static	int	nothing_after(t_token **token)
{
	t_token_type	next_type;

	if (!(*token)->next)
		return (-1);
	next_type = (*token)->next->type;
	if (next_type == TOKEN_WORD
		|| next_type == TOKEN_SINGLE_QUOTES
		|| next_type == TOKEN_DOUBLE_QUOTES)
		return (0);
	return (-1);
}

static	int	handle_redir(t_cmd *cmd, t_token **token)
{
	t_token_type	type;

	if (nothing_after(token) == -1)
		return (ft_putstr_fd("minishell : syntax error\n", 2), -1);
	type = (*token)->type;
	(*token) = (*token)->next;
	if (type == TOKEN_REDIR_OUT)
	{
		cmd->outfile = ft_strdup((*token)->value);
		cmd->append = 0;
	}
	else if (type == TOKEN_REDIR_APPEND)
	{
		cmd->outfile = ft_strdup((*token)->value);
		cmd->append = 1;
	}
	else if (type == TOKEN_REDIR_IN)
		cmd->infile = ft_strdup((*token)->value);
	else if (type == TOKEN_HEREDOC)
		cmd->here_doc = ft_strdup((*token)->value);
	return (0);
}

t_token	*fill_cmd(t_cmd *cmd, t_token *cursor)
{
	int	i;

	i = 0;
	cmd->args = malloc(sizeof(char *) * (count_args(cursor) + 1));
	if (!cmd->args)
		return (NULL);
	while (cursor && cursor->type != TOKEN_PIPE)
	{
		if (cursor->type == TOKEN_SINGLE_QUOTES
			|| cursor->type == TOKEN_DOUBLE_QUOTES
			|| cursor->type == TOKEN_WORD)
			cmd->args[i++] = ft_strdup(cursor->value);
		else if (handle_redir(cmd, &cursor) == -1)
			return (NULL);
		if (cursor)
			cursor = cursor->next;
	}
	cmd->args[i] = NULL;
	if (cursor && cursor->type == TOKEN_PIPE)
		return (cursor->next);
	return (NULL);
}
