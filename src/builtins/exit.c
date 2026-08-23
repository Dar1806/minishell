/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 00:50:11 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/23 17:32:31 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_clean(t_shell *shell, int exit_code)
{
	env_free_list(shell->envl);
	ft_free();
	exit(exit_code);
}

void	handle_non_num(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit_clean(shell, 2);
}

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	exarg;
	int	error;

	error = 0;
	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
		exit_clean(shell, shell->ex_status);
	exarg = ft_atoi(cmd->args[1], &error);
	if (!cmd->args[2])
	{
		if (error)
			handle_non_num(cmd->args[1], shell);
		exit_clean(shell, exarg);
	}
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	shell->ex_status = 1;
}
