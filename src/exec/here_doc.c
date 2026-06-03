/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:25:57 by nmeunier          #+#    #+#             */
/*   Updated: 2026/06/03 15:59:05 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_here_doc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error : pipe failed\n", 2);
		exit(1);
	}
	ft_putstr_fd("> ", 1);
	line = readline("");
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		ft_putstr_fd("> ", 1);
		line = readline("");
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
