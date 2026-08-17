/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:16:32 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/17 18:36:21 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_expnew(t_env **dup, t_env *envl)
{
	t_env	*tmp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = envl->key;
	new->value = envl->value;
	if (!(*dup))
		*dup = new;
	else
	{
		tmp = *dup;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_env	*ft_expdup(t_env **envl)
{
	t_env	*dup;
	t_env	*tmp;

	tmp = *envl;
	dup = NULL;
	while (tmp)
	{
		if (!ft_expnew(&dup, tmp))
			return (env_free_list(dup), NULL);
		tmp = tmp->next;
	}
	return (dup);
}