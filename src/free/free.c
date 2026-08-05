/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:01:55 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/05 18:20:00 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		free(cmd->here_doc);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = next;
	}
}
