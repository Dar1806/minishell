/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:47:15 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/06 16:52:44 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_feq(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (0);
	return (i);
}

char	*splitenv(char *env, int w)
{
	char *s;
	int	i;
	int	start;
	int	len;

	i = -1;
	if (w == 1)
	{
		start = 0;
		len = find_feq(env);
	}
	else if (w == 2)
	{
		start = find_feq(env) + 1;
		len = ft_strlen(env) - start;
	}
	else 
		return (NULL);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (++i < len)
		s[i] = env[start + i];
	s[i] = 0;
	return (s);
}

void	env_free_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

t_env	*env_new_node(t_env **head, char *env)
{
	t_env	*new;
	t_env	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->key = splitenv(env, 1);
	new->value = splitenv(env, 2);
	if (!new->value || !new->key)
		return(free(new->key), free(new->value), free(new), NULL);
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

t_env	*env_init_list(char **env)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		if (!env_new_node(&head, env[i]))
			return (env_free_list(head), NULL);
		i++;
	}
	return (head);
}

// int main(void)
// {
// 	char *env = "HOME=/home/toto";
// 	char *key;
// 	char *value;
// 	key = splitenv(env, 1);
// 	value = splitenv(env, 2);
// 	printf("%s, %s", key, value);
// }