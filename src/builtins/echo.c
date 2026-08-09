/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 14:46:22 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/09 04:19:53 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_newline(t_cmd *cmd)
{
	int		i;
	char	*args;

	if (cmd->args[1] == NULL)
		return (1);
	args = cmd->args[1];
	i = 0;
	if (args[i] == '-')
	{
		i++;
		if (args[i] == 'n')
			while (args[i] == 'n')
				i++;
		else
			return (1);
		if (ft_strlen(args) == i)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int	newline;
	int	i;

	(void)shell;
	if (is_newline(cmd) == 0)
	{
		i = 2;
		newline = 0;
	}
	else
	{
		i = 1;
		newline = 1;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 1)
		ft_putstr_fd("\n", 1);
}
