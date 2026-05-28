/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:10:41 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/28 18:17:43 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
