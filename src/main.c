/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:21 by nmeunier          #+#    #+#             */
/*   Updated: 2026/05/22 14:04:25 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	t_token *tokens;

	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		tokens = lexer(line);
		t_token *tmp = tokens;
		while (tmp)
		{
			printf("value = %s type = %d\n", tmp->value, tmp->type);
    		tmp = tmp->next;
		}
	}
	return (0);
}
   