/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:17:03 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/24 17:10:54 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_read(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": cannot open file\n", 2);
	}
	return (fd);
}

int	set_stdin(t_cmd *cmd)
{
	int	fd;

	if (cmd->here_doc != NULL)
	{
		fd = exec_here_doc(cmd->here_doc);
		if (fd == -1)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->infile)
	{
		fd = write_read(cmd->infile, 0);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	set_stdout(t_cmd *cmd)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->append)
			fd = write_read(cmd->outfile, 2);
		else
			fd = write_read(cmd->outfile, 1);
		if (fd == -1)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (0);
	}
	return (0);
}

void	run_child(t_cmd *cmd, t_shell *shell, int *pipes, int n_cmds)
{
	int		out_err;
	int		in_err;
	char	**envl;
	int		code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_all(pipes, n_cmds);
	in_err = set_stdin(cmd);
	out_err = set_stdout(cmd);
	if (in_err || out_err)
		exit_clean(shell, 1);
	if (!cmd->args || !cmd->args[0])
		exit_clean(shell, 0);
	code = is_built_ins(cmd->args[0]);
	if (code != -1)
	{
		exec_built_ins(cmd, shell, code);
		exit_clean(shell, shell->ex_status);
	}
	envl = env_list_to_array(shell->envl);
	exec_cmd(cmd, envl, shell);
}
