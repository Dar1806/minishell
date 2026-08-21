/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:36:20 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/21 19:03:51 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_exec(t_cmd *cmd, t_shell *shell)
{
	pid_t				pid;
	int					status;

	sigint_ignore();
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork failed\n", 2);
		return ;
	}
	if (pid == 0)
		run_child(cmd, shell, NULL, 0);
	waitpid(pid, &status, 0);
	sigint_setup();
	if (WIFEXITED(status))
		shell->ex_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->ex_status = (128 + WTERMSIG(status));
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 1);
	}
}

static int	*setup_pipes(int *pipes, int i, int n_cmds)
{
	if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (i < n_cmds - 1)
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
	return (pipes);
}

void	pipe_exec(t_cmd *cmd, t_shell *shell)
{
	pid_t	*pids;
	int		n_cmds;
	int		*pipes;
	int		i;

	n_cmds = count_cmds(cmd);
	pids = ft_malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
		return ;
	pipes = open_pipes(n_cmds);
	if (!pipes)
		return ;
	i = -1;
	sigint_ignore();
	while (++i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (sigint_setup(), ft_putstr_fd("Error : fork failed\n", 2));
		if (pids[i] == 0)
			run_child(cmd, shell, setup_pipes(pipes, i, n_cmds), n_cmds);
		cmd = cmd->next;
	}
	shell->ex_status = clean_all(pids, pipes, n_cmds);
	sigint_setup();
}

void	execution(t_cmd *cmd, t_shell *shell)
{
	int	code;

	if (!cmd)
		return ;
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->infile || cmd->outfile)
			simple_exec(cmd, shell);
		return ;
	}
	if (cmd->next == NULL)
	{
		code = is_built_ins(cmd->args[0]);
		if (code != -1)
			exec_built_ins(cmd, shell, code);
		else
			simple_exec(cmd, shell);
	}
	else
		pipe_exec(cmd, shell);
}
