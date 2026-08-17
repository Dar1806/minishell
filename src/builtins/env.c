/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:02:13 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/17 18:47:32 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *envl)
{
	while(envl)
	{
		if (envl->value[0])
		{
			ft_putstr_fd(envl->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(envl->value, 1);
		}
		envl = envl->next;
	}
}