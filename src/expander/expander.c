/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 17:52:04 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/06 18:49:19 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	*env_get_value(t_env *envl, char *key)
//{
//	int len;

//	len = ft_strlen(key);
//	while (envl)
//	{
//		if (!ft_strncmp(envl->key, key, len) && len == ft_strlen(envl->key))
//			return (ft_strdup(envl->value));
//		envl = envl->next;
//	}
//	return (ft_strdup(""));
//}

char	*get_var_key(char *word)
{
	int	i;

	i = 0;
	if (word[i] == '?')
		return (ft_strdup("?"));
	while (word[i] && (ft_isalpha(word[i]) || (word[i] == '_' 
				|| (ft_isalnum(word[i] && i != 0)))))
		i++;
	return (ft_substr(word, 0, i));
}

void	envv_handler(char *word, char **expanded, int *i, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*old;
	
	(*i)++;
	key = get_var_key(word + *i);
	if (!key)
		return ;
	old = *expanded;
	if (word[*i] == '?')
	{
		value = ft_itoa(shell->ex_status);
		*expanded = ft_strjoin(*expanded, value);
		(*i)++;
	}
	else
	{
		value = get_envv(shell->envl, key);
		*expanded = ft_strjoin(*expanded, value);
		*i += ft_strlen(key);
	}
	free(old);
	free (key);
	free (value);
}

void	expander(char **word, t_shell *shell)
{
	char	*expanded;
	char	*old;
	int		i;

	i = 0;
	expanded = ft_strdup("");
	while ((*word)[i])
	{
		if ((*word)[i] == '$' && (*word)[i + 1] && (ft_isalnum((*word)[i + 1])
				|| (*word)[i + 1] == '?' || (*word)[i + 1] == '_'))
		{
			if (ft_isdigit((*word)[i + 1]))
				i += 2;
			else
				envv_handler(*word, &expanded, &i, shell);
		}
		else
		{
			old = expanded;
			expanded = ft_strnjoin(expanded, &(*word)[i++], 1);
			free(old);
		}
	}
	free (*word);
	*word = expanded;
}
