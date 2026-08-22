/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:16:32 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/22 19:22:34 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_free_nodes(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

t_env	*ft_expnew(t_env **dup, t_env *envl)
{
	t_env	*tmp;
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
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
