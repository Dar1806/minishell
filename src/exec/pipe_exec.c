/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:33:25 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/03 17:12:15 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

int	*open_pipes(int n_cmds)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = malloc(sizeof(int) * (n_cmds - 1) * 2);
	while (i < n_cmds - 1)
	{
		if (pipe(pipes + i * 2) == -1)
			return (ft_putstr_fd("Error : pipe failed\n", 2), NULL);
		i++;
	}
	return (pipes);
}

void	close_all(int *pipes, int n_cmds)
{
	int	i;

	i = 0;
	while (i < (n_cmds - 1) * 2)
		close(pipes[i++]);
}

static void	wait_all(pid_t *pids, int n_cmds)
{
	int	i;
	int	status;

	i = 0;
	while (i < n_cmds)
		waitpid(pids[i++], &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = (128 + WTERMSIG(status));
}

void	clean_all(pid_t *pids, int *pipes, int n_cmds)
{
	close_all(pipes, n_cmds);
	wait_all(pids, n_cmds);
	free(pipes);
	free(pids);

}
