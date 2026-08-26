/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:25:57 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/26 17:24:27 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_cmd *cmd, t_token *token)
{
	free(cmd->here_doc);
	cmd->here_doc = ft_ft_strdup(token->value);
}

int	exec_here_doc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("minishell : error : pipe failed\n", 2);
		exit(1);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
