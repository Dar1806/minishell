/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 14:46:22 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/22 19:20:15 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_newline(char *args)
{
	int		i;

	if (args == NULL)
		return (0);
	i = 0;
	if (args[i] == '-')
	{
		i++;
		if (args[i] == 'n')
			while (args[i] == 'n')
				i++;
		else
			return (0);
		if (ft_strlen(args) == i)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int	newline;
	int	i;

	i = 1;
	newline = 0;
	while (is_newline(cmd->args[i]))
	{
		i++;
		newline = 1;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (!newline)
		ft_putstr_fd("\n", cmd->fd_out);
	shell->ex_status = 0;
}
