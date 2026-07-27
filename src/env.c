/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 20:47:15 by hulescur          #+#    #+#             */
/*   Updated: 2026/07/26 21:26:39 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i++]);
	return (i);
}

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

	i = -1;
	if (w == 1)
	{
		s = malloc(find_feq(env) + 1);
		while (++i < find_feq(env))
			s[i] = env[i];
	}
	else if (w == 2)
	{
		s = malloc(ft_strlen(env) - find_feq(env));
		while (++i < ft_strlen(env) - find_feq(env))
			s[i] = env[i + find_feq(env) + 1];
	}
	else 
		return (NULL);
	return (s);
}

void	*ft_newnode(t_env **head, char *env)
{
	t_env	*new;
	t_env	*temp;
	void	*ptr;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = splitenv(env, 1);
	if (!new->key)
		return(free(new), NULL);
	new->value = splitenv(env, 2);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (ptr);
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