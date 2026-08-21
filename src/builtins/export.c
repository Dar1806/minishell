/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 04:02:04 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/21 19:55:04 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_existing_key(t_env *envl, char *key)
{
	while (envl)
	{
		if (!ft_strncmp(envl->key, key, ft_strlen(key))
			&& ft_strlen(key) == ft_strlen(envl->key))
			return (envl);
		envl = envl->next;
	}
	return (NULL);
}

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
		key = ft_strnjoin(key, str + i, 1);
		free(old);
	}
	return (key);
}

int	set_env_value(t_env *new, char *envv)
{
	if (new->key)
		free(new->key);
	if (new->value)
		free(new->value);
	new->key = get_envk(envv);
	if (!new->key)
		return (0);
	if (find_feq(envv))
	{
		if (!(find_feq(envv) == ft_strlen(envv)))
			new->value = ft_strdup(envv + find_feq(envv) + 1);
		else
			new->value = ft_strdup("");
	}
	else
		new->value = ft_strdup("");
	return (1);
}

void	env_export(t_env **envl, char *envv)
{
	t_env	*new;
	t_env	*temp;
	t_env	*existing;
	char	*key;

	key = get_envk(envv);
	existing = find_existing_key(*envl, key);
	free(key);
	if (existing)
		return (set_env_value(existing, envv), (void)0);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	if (!set_env_value(new, envv))
		return (free(new), (void)0);
	if (*envl == NULL)
		*envl = new;
	else
	{
		temp = *envl;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**args;

	args = cmd->args;
	i = 0;
	if (!args[i + 1])
	{
		env_print(&shell->envl);
		shell->ex_status = 0;
		return ;
	}
	shell->ex_status = 0;
	while (args[++i])
	{
		if (is_valid_key(args[i]))
			env_export(&shell->envl, args[i]);
		else
		{
			ft_putstr_fd("minishell : export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->ex_status = 1;
		}
	}
}
