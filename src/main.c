/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/07/30 16:07:39 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;
	t_shell	shell;
	
	if (ac != 1)
		return (ft_putstr_fd("Error : No arguments needed", 2), 1);
	shell.env = env;
	shell.exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		tokens = lexer(line);
		cmd = parser(tokens, &shell);
		execution(cmd, &shell);
		free_tokens(tokens);
		free_cmd(cmd);
		free(line);
	}
	rl_clear_history();
	return ((void)av, shell.exit_status);
}
