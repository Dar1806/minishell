/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 17:52:04 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/24 18:22:13 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*get_var_key(char *word)
{
	int	i;

	i = 0;
	if (word[i] == '?')
		return (ft_ft_strdup("?"));
	while (word[i] && (ft_isalpha(word[i]) || word[i] == '_'
			|| (ft_isdigit(word[i]) && i != 0)))
		i++;
	return (ft_ft_substr(word, 0, i));
}

void	envv_handler(char *word, char **expanded, int *i, t_shell *shell)
{
	char	*key;
	char	*value;

	(*i)++;
	key = get_var_key(word + *i);
	if (!key)
		return ;
	if (word[*i] == '?')
	{
		value = ft_ft_itoa(shell->ex_status);
		*expanded = ft_ft_strjoin(*expanded, value);
		(*i)++;
	}
	else
	{
		value = get_envv(shell->envl, key);
		*expanded = ft_ft_strjoin(*expanded, value);
		*i += ft_strlen(key);
	}
}

void	expander(char **word, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	expanded = ft_ft_strdup("");
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
			expanded = ft_ft_strnjoin(expanded, &(*word)[i++], 1);
	}
	*word = expanded;
}
