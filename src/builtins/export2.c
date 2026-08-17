/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 21:10:56 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/18 00:28:00 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[++i] && str[i] != '=')
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
	return (1);
}

int	envl_size(t_env **envl)
{
	t_env	*tmp;
	int		i;

	tmp = *envl;
	i = 1;
	if (!tmp)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	envl_switch(t_env *env1, t_env *env2)
{
	char	*tmp;

	if (ft_strcmp(env1->key, env2->key) > 0)
	{
		tmp = env1->key;
		env1->key = env2->key;
		env2->key = tmp;
		tmp = env1->value;
		env1->value = env2->value;
		env2->value = tmp;
	}
}

void	envl_sort(t_env **envl)
{
	t_env	*envt;
	int		s;
	int		i;
	int		j;

	s = envl_size(envl);
	i = -1;
	while (++i < s - 1)
	{
		j = -1;
		envt = *envl;
		while (++j < (s - 1) - i)
		{
			envl_switch(envt, envt->next);
			envt = envt->next;
		}
	}
}

void	env_print(t_env **envl)
{
	t_env	*tmp;
	t_env	*head;

	tmp = ft_expdup(envl);
	head = tmp;
	envl_sort(&tmp);
	while (tmp)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	env_free_nodes(head);
}
