/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:36:20 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/03 17:14:37 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	simple_exec(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : fork failed\n", 2);
		return ;
	}
	if (pid == 0)
		run_child(cmd, env, NULL, 0, 0);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = (128 + WTERMSIG(status));
}

void	pipe_exec(t_cmd *cmd, char **env)
{
	pid_t	*pids;
	int		n_cmds;
	int		*pipes;
	int		i;

	n_cmds = count_cmds(cmd);
	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
		return ;
	pipes = open_pipes(n_cmds);
	if (!pipes)
		return (free(pids));
	i = 0;
	while (i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_putstr_fd("Error : fork failed\n", 2));
		if (pids[i] == 0)
			run_child(cmd, env, pipes, i, n_cmds);
		cmd = cmd->next;
		i++;
	}
	clean_all(pids, pipes, n_cmds);
}

void	execution(t_cmd *cmd, char **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (cmd->next == NULL)
		simple_exec(cmd, env);
	else
		pipe_exec(cmd, env);
}
