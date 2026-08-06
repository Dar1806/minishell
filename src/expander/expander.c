/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 17:52:04 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/06 03:08:26 by akkolitozer      ###   ########.fr       */
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
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	return (ft_substr(word, 0, i));
}

void	envv_handler(char *str, char **expanded, int *i, t_shell *shell)
{
	char	*key;

	key = get_var_key(&word[*i]);
	value = get_envv(shell->envl, key);
	if (!key)
		return ;
	if (str[*i] == '?')
	else
	{
		expanded = ft_strjoin(expanded, value);
		*i += ft_strlen(value);
	}
}

void	expander(char **word, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = -1;
	expanded = ft_strdup("");
	while ((*word)[++i])
	{
		if ((*word)[i] == '$' && (*word)[i + 1] && (ft_isalnum((*word)[i + 1])
				|| (*word)[i + 1] == '?'))
			ennv_handler(*word, &expanded, &(i++), shell);
		else
			expanded = ft_strnjoin(expanded, &(*word)[i++], 1);
	}
	free (*word);
	*word = *expanded;
}