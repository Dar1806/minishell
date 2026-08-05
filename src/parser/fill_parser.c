/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:37:35 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/05 18:06:41 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	append_to_arg(t_cmd *cmd, int i, char *value)
{
	char	*tmp;

	if (!cmd->args[i])
		cmd->args[i] = ft_strdup(value);
	else
	{
		tmp = ft_strjoin(cmd->args[i], value);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
	}
}

static int	count_args(t_token *cursor)
{
	int	count;
	int	is_join;

	count = 0;
	is_join = 0;
	while (cursor && cursor->type != TOKEN_PIPE)
	{
		if (is_redir_type(cursor->type))
		{
			is_join = 0;
			if (cursor->next)
				cursor = cursor->next;
		}
		else if (is_word_type(cursor->type))
		{
			if (!is_join)
				count++;
			is_join = cursor->joined;
		}
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

static	int	handle_redir(t_cmd *cmd, t_token **token, int *parse_error)
{
	t_token_type	type;
	int				fd;

	if (nothing_after(token) == -1)
		return (ft_putstr_fd("minishell : syntax error\n", 2),
			*parse_error = 1, -1);
	type = (*token)->type;
	(*token) = (*token)->next;
	if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APPEND)
	{
		if (cmd->outfile)
		{
			fd = write_read(cmd->outfile, cmd->append + 1);
			if (fd != -1)
				close(fd);
			free(cmd->outfile);
		}
		cmd->outfile = ft_strdup((*token)->value);
		cmd->append = (type == TOKEN_REDIR_APPEND);
	}
	else if (type == TOKEN_REDIR_IN)
		cmd->infile = ft_strdup((*token)->value);
	else if (type == TOKEN_HEREDOC)
		handle_heredoc(cmd, *token);
	return (0);
}

t_token	*fill_cmd(t_cmd *cmd, t_token *cursor, int *parse_error)
{
	int	i;

	i = 0;
	cmd->args = ft_calloc(count_args(cursor) + 1, sizeof(char *));
	if (!cmd->args)
		return (NULL);
	while (cursor && cursor->type != TOKEN_PIPE)
	{
		if (is_word_type(cursor->type))
		{
			append_to_arg(cmd, i, cursor->value);
			if (!cursor->joined)
				i++;
		}
		else if (handle_redir(cmd, &cursor, parse_error) == -1)
			return (cmd->args[i] = NULL, NULL);
		if (cursor)
			cursor = cursor->next;
	}
	cmd->args[i] = NULL;
	if (cursor && cursor->type == TOKEN_PIPE)
		return (cursor->next);
	return (NULL);
}
