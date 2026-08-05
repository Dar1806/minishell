/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 17:52:04 by hulescur          #+#    #+#             */
/*   Updated: 2026/07/30 18:06:45 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_envv(char c, int first)
{
	if (first)
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
			return (1);
	else
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
				|| (c >= '0' && c <= '9'))
			return (1);
	return (0);
}

char	*read_envv(char *line, int size);
{
	int	i;

	i = -1;
	while (line[++i] && is_valid_envv(line[i]))
	{
		
	}
}

char	*expander(char *line)
{
	int	i;
	int	total_len;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			
		}
	}
}
