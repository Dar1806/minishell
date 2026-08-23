/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:44:08 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/23 17:14:49 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_not_found(char *args, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	if (args)
		ft_putstr_fd(args, 2);
	ft_putstr_fd(": command not found\n", 2);
	env_free_list(shell->envl);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_free();
	exit(127);
}

static void	error_enoent(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_free();
	exit(127);
}

static void	error_eisdir(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

static void	error_eacces_enoexec(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	exec_cmd(t_cmd *cmd, char **env, t_shell *shell)
{
	char	*path;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		cmd_not_found(NULL, shell);
	path = get_path(cmd->args[0], env);
	if (!path)
		cmd_not_found(cmd->args[0], shell);
	execve(path, cmd->args, env);
	if (errno == ENOENT)
		error_enoent(cmd->args[0]);
	if (errno == EISDIR)
		error_eisdir(cmd->args[0]);
	else if (errno == EACCES || errno == ENOEXEC)
		error_eacces_enoexec(cmd->args[0]);
	else
		ft_putstr_fd("minishell: execve failed\n", 2);
	ft_free();
	exit(126);
}
