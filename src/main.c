/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/27 16:13:08 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	t_token	*tokens;

	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		line = readline("[minishell]$ ");
		if (!line)
			break ;
		tokens = lexer(line);
		t_token *temp = tokens;
		while (temp)
		{
			printf("value = %s type = %d\n", temp->value, temp->type);
    		temp = temp->next;
		}
		free_tokens(tokens);
		free(line);
	}
	rl_clear_history();
	return (0);
}
   