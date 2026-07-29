/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 23:19:15 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/07/29 23:55:06 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_size(t_env *envl)
{
	int	i;

	i = 0;
	while (envl)
	{
		envl = envl->next;
		i++;
	}
	return (i);
}

char	**env_list_to_array(t_env *envl)
{
	char	**enva;
	char	*tmp;
	int		lsize;
	int		i;
	
	i = -1;
	lsize = env_size(envl);
	enva = malloc((lsize + 1) * sizeof(char *));
	if (!enva)
		return (NULL);
	while (++i < lsize)
	{
		tmp = ft_strjoin(envl->key, "=");
		enva[i] = ft_strjoin(tmp, envl->value);
		envl = envl->next;
		free(tmp);
	}
	enva[i] = NULL;
	return (enva);
}