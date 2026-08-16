/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 17:19:43 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/16 18:31:37 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_key(char *key, t_env **envl)
{
	t_env	*curr;
	t_env	*prev;

	prev = NULL;
	curr = *envl;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*envl = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[++i])
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
	return (1);
}

void	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (cmd->args[++i])
	{
		if (is_valid(cmd->args[i]))
			unset_key(cmd->args[i], &shell->envl);
		else
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			error = 1;
		}
	}
	shell->ex_status = error;
}
