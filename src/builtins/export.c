/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 04:02:04 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/09 05:15:49 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envk(char *str)
{
	int		i;
	char	*key;
	char	*old;
	
	i = -1;
	key = ft_strdup("");
	while (str[++i] && str[i] != '=')
	{
		old = key;
		key = ft_strjoin(key, str[i]);
		free(old);
	}
	return (key);
}

void	env_export(t_env **envl, char *envv)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->key = get_envk(envv);
	new->value = splitenv(env, 2);
	if (!new->value || !new->key)
		return (free(new->key), free(new->value), free(new), NULL);
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*args;

	args = cmd->args;
	i = 0;
	if (args[i + 1])
	{
		while (args[++i])
		{
			if (is_alpha(args[i][0]) || args[i][0] == '_')
			{
				env_export(shell->envl, args[i])
			}
		}
	}
}