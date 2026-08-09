/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 21:10:56 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/09 22:02:51 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envl_size(t_env **envl)
{
	t_env	*tmp;
	int		i;
	
	tmp = *envl;
	i = 1;
	if (!tmp)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	envl_sort(t_env **envl)
{
	t_env	*tmp;
	int		s;
	int		i;
	int		j;
	
	s = envl_size(envl);
	i = -1;
	while (i++ < s)
	{
		
	}
}