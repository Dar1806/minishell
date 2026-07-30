/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:44:08 by nmeunier          #+#    #+#             */
/*   Updated: 2026/07/30 17:32:11 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_not_found(char *args)
{
	ft_putstr_fd("minishell: ", 2);
	if (args)
		ft_putstr_fd(args, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		cmd_not_found(NULL);
	path = get_path(cmd->args[0], env);
	if (!path)
		cmd_not_found(cmd->args[0]);
	execve(path, cmd->args, env);
	ft_putstr_fd("minishell: execve failed\n", 2);
	exit(126);
}
