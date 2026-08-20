/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/20 22:16:59 by akkolitozer      ###   ########.fr       */
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
	free_tokens(tokens);
	free_cmd(cmd);
	free(line);
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
	rl_clear_history();
	env_free_list(shell.envl);
	return ((void)av, shell.ex_status);
}
