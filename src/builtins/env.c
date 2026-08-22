/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:02:13 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/22 17:32:21 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd, t_env *envl)
{
	while (envl)
	{
		if (envl->value[0])
		{
			ft_putstr_fd(envl->key, cmd->fd_out);
			ft_putchar_fd('=', cmd->fd_out);
			ft_putendl_fd(envl->value, cmd->fd_out);
		}
		envl = envl->next;
	}
}
