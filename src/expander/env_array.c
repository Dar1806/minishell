/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 23:19:15 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/16 18:53:56 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envv(t_env *envl, char *key)
{
	t_env	*curr;

	curr = envl;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key))
			&& ft_strlen(key) == ft_strlen(curr->key))
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
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

int	add_env_to_array(char **enva, t_env *envl, int i)
{
	char	*tmp;

	tmp = ft_strjoin(envl->key, "=");
	if (!tmp)
		return (0);
	enva[i] = ft_strjoin(tmp, envl->value);
	free(tmp);
	if (!enva[i])
		return (0);
	return (1);
}

char	**env_list_to_array(t_env *envl)
{
	char	**enva;
	int		lsize;
	int		i;

	i = 0;
	lsize = env_size(envl);
	enva = malloc((lsize + 1) * sizeof(char *));
	if (!enva)
		return (NULL);
	while (envl)
	{
		if (envl->value)
		{
			if (!add_env_to_array(enva, envl, i))
				return (free_errorj(enva), NULL);
			i++;
		}
		envl = envl->next;
	}
	enva[i] = NULL;
	return (enva);
}
