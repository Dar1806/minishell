/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/06 18:49:25 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;
	t_shell	shell;

	shell.envl = env_init_list(env);
	if (ac != 1)
		return (ft_putstr_fd("Error : No arguments needed", 2), 1);
	shell.env = env;
	shell.ex_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		tokens = lexer(line, &shell);
		cmd = parser(tokens, &shell);
		execution(cmd, &shell);
		free_tokens(tokens);
		free_cmd(cmd);
		free(line);
	}
	rl_clear_history();
	env_free_list(shell.envl);
	return ((void)av, shell.ex_status);
}
