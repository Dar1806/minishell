/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 04:02:04 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/09 21:10:06 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env **envl)
{
	t_env	*tmp;
	
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
		key = ft_strjoin(key, str[i]);
		free(old);
	}
	return (key);
}

int	set_env_value(t_env *new, char *envv)
{
	new->key = get_envk(envv);
	if (!new->key)
    	return (0);
	if (find_feq(envv))
	{
		if (!(find_feq(envv) == ft_strlen(envv)))
			new->value = ft_strdup(envv + find_feq(envv));
		else
			new->value = ft_strdup("");
	}
	else
		new->value = NULL;
	return (1);
}

void	env_export(t_env **envl, char *envv)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
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
	char	*args;

	args = cmd->args;
	i = 0;
	if (args[i + 1])
	{
		while (args[++i])
		{
			if (is_alpha(args[i][0]) || args[i][0] == '_')
				env_export(shell->envl, args[i])
			else
				printf("minishell : export: `%s': not a valid identifier", args[i]); // A REVOIR JE CONNAIS PAS LES CODES ERROR/EXIT
		}
	}
	else
		print_env(*env, shell->envl)
}