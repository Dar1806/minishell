/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 13:14:58 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/23 17:21:42 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_stdin_fd(t_cmd *cmd)
{
	cmd->fd_in = 0;
	if (cmd->here_doc != NULL)
	{
		cmd->fd_in = exec_here_doc(cmd->here_doc);
		if (cmd->fd_in == -1)
			return (-1);
	}
	else if (cmd->infile)
	{
		cmd->fd_in = write_read(cmd->infile, 0);
		if (cmd->fd_in == -1)
			return (-1);
	}
	return (0);
}

int	set_stdout_fd(t_cmd *cmd)
{
	cmd->fd_out = 1;
	if (cmd->outfile)
	{
		if (cmd->append)
			cmd->fd_out = write_read(cmd->outfile, 2);
		else
			cmd->fd_out = write_read(cmd->outfile, 1);
		if (cmd->fd_out == -1)
			return (-1);
	}
	return (0);
}

int	is_built_ins(char *args)
{
	if (ft_strncmp(args, "echo", 4) == 0 && ft_strlen(args) == 4)
		return (0);
	else if (ft_strncmp(args, "cd", 2) == 0 && ft_strlen(args) == 2)
		return (1);
	else if (ft_strncmp(args, "pwd", 3) == 0 && ft_strlen(args) == 3)
		return (2);
	else if (ft_strncmp(args, "export", 6) == 0 && ft_strlen(args) == 6)
		return (3);
	else if (ft_strncmp(args, "unset", 5) == 0 && ft_strlen(args) == 5)
		return (4);
	else if (ft_strncmp(args, "env", 3) == 0 && ft_strlen(args) == 3)
		return (5);
	else if (ft_strncmp(args, "exit", 4) == 0 && ft_strlen(args) == 4)
		return (6);
	else
		return (-1);
}

void	exec_built_ins(t_cmd *cmd, t_shell *shell, int code)
{
	if (set_stdout_fd(cmd) || set_stdin_fd(cmd))
		shell->ex_status = 1;
	else if (code == 0)
		ft_echo(cmd, shell);
	else if (code == 1)
		ft_cd(cmd, shell);
	else if (code == 2)
		ft_pwd(cmd, shell);
	else if (code == 3)
		ft_export(cmd, shell);
	else if (code == 4)
		ft_unset(cmd, shell);
	else if (code == 5)
		ft_env(cmd, shell->envl);
	else if (code == 6)
		ft_exit(cmd, shell);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	ft_free();
}
