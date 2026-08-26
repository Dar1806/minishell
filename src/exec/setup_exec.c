/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:36:20 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/26 16:58:24 by nmeunier         ###   ########.fr       */
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

void	fork_error(t_shell *shell, pid_t *pids, int *pipes, int *var)
{
	ft_putstr_fd("Error : fork failed\n", 2);
	close_all(pipes, var[1]);
	if (var[0] > 0)
		shell->ex_status = wait_all(pids, var[0]);
	sigint_setup();
}

void	pipe_exec(t_cmd *cmd, t_shell *shell)
{
	pid_t	*pids;
	int		*pipes;
	int		var[2];

	var[1] = count_cmds(cmd);
	pids = ft_malloc(sizeof(pid_t) * var[1]);
	if (!pids)
		return ;
	pipes = open_pipes(var[1]);
	if (!pipes)
		return ;
	var[0] = -1;
	sigint_ignore();
	while (++var[0] < var[1])
	{
		pids[var[0]] = fork();
		if (pids[var[0]] == -1)
			return (fork_error(shell, pids, pipes, var));
		if (pids[var[0]] == 0)
			run_child(cmd, shell, setup_pipes(pipes, var[0], var[1]), var[1]);
		cmd = cmd->next;
	}
	shell->ex_status = clean_all(pids, pipes, var[1]);
	sigint_setup();
}

void	execution(t_cmd *cmd, t_shell *shell)
{
	int	code;

	if (!cmd)
		return ;
	if (cmd->next != NULL)
	{
		pipe_exec(cmd, shell);
		return ;
	}
	if (!cmd->args || !cmd->args[0])
	{
		if (cmd->infile || cmd->outfile || cmd->here_doc)
			simple_exec(cmd, shell);
		return ;
	}
	code = is_built_ins(cmd->args[0]);
	if (code != -1)
		exec_built_ins(cmd, shell, code);
	else
		simple_exec(cmd, shell);
}
