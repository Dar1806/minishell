/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:17:03 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/05 16:03:43 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_read(char *file, int mode)
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
		ft_putstr_fd(": cannot open file\n", 2);
	}
	return (fd);
}

static int	set_stdin(t_cmd *cmd)
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

static int	set_stdout(t_cmd *cmd)
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
	close_all(pipes, n_cmds);
	if (set_stdin(cmd) || set_stdout(cmd))
		exit(1);
	exec_cmd(cmd, shell->env);
}
