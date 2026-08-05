/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:10:41 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/05 16:40:10 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	syntax_error(t_shell *shell)
{
	ft_putstr_fd("minishell : syntax error\n", 2);
	shell->exit_status = 2;
	return (2);
}


t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*first;
	t_cmd	*last;
	t_token	*cursor;
	int		parse_error;

	parse_error = 0;
	if (!tokens)
		return (NULL);
	first = NULL;
	last = NULL;
	cursor = tokens;
	while (cursor)
	{
		if (cursor->type == TOKEN_PIPE)
			return (syntax_error(shell), free_cmd(first), NULL);
		cmd = new_cmd();
		if (!cmd)
			return (free_cmd(first), NULL);
		cursor = fill_cmd(cmd, cursor, &parse_error);
		if (parse_error)
			return (shell->exit_status = 2,
				free_cmd(cmd), free_cmd(first), NULL);
		add_cmd(&first, &last, cmd);
	}
	return (first);
}
