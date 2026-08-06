/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 23:19:15 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/06 02:49:58 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envv(t_env *envl, char *key)
{
	t_env	*curr;

	curr = envl;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr->value);
		curr = curr->next;
	}
	return ("");
}

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

void	free_errorj(char **enva)
{
	int	i;
	i = -1;

	while (enva[++i])
		free(enva[i]);
	free(enva);
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
		if (!tmp)
			return(free_errorj(enva), NULL);
		enva[i] = ft_strjoin(tmp, envl->value);
		if (!enva[i])
			return(free_errorj(enva), NULL);
		envl = envl->next;
		free(tmp);
	}
	enva[i] = NULL;
	return (enva);
}