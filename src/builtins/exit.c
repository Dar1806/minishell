/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:50:11 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/18 02:01:14 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_non_num(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	exarg;
	int	error;

	error = 0;
	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
		exit(shell->ex_status);
	exarg = ft_atoi(cmd->args[1], &error);
	if (error)
		handle_non_num(cmd->args[1]);
	else if (!cmd->args[2])
		exit(exarg);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	shell->ex_status = 1;
}