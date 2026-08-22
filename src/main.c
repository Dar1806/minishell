/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/22 19:35:27 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	routine(t_shell *shell)
{
	t_token	*tokens;
	char	*line;
	t_cmd	*cmd;

	line = readline("minishell$ ");
	if (!line)
		return (0);
	if (line[0])
		add_history(line);
	tokens = lexer(line, shell);
	cmd = parser(tokens, shell);
	execution(cmd, shell);
	ft_free();
	free(line);
	if (g_signal == 1)
	{
		shell->ex_status = 130;
		g_signal = 0;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_shell				shell;

	sigint_setup();
	sigquit_ignore();
	shell.envl = env_init_list(env);
	if (ac != 1)
		return (ft_putstr_fd("Error : No arguments needed", 2), 1);
	shell.env = env;
	shell.ex_status = 0;
	while (1)
		if (!routine(&shell))
			break ;
	env_free_list(shell.envl);
	rl_clear_history();
	return ((void)av, shell.ex_status);
}
