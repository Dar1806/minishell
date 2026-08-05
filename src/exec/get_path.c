/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:14:49 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/05 18:20:00 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

char	*find_cmd_in_paths(char **path, char *cmd_name)
{
	char	*full_path;
	char	*is_ok;
	int		i;

	i = -1;
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], "/");
		if (!full_path)
			return (NULL);
		is_ok = ft_strjoin(full_path, cmd_name);
		free(full_path);
		if (!is_ok)
			return (NULL);
		if (access(is_ok, F_OK | X_OK) == 0)
			return (is_ok);
		free(is_ok);
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_path(char *cmd_name, char **env)
{
	char	**path;
	char	*env_path;
	char	*result;
	int		i;

	if (!cmd_name || !cmd_name[0])
		return (NULL);
	i = 0;
	while (cmd_name[i] && cmd_name[i] != '/')
		i++;
	if (cmd_name[i] == '/')
	{
		if (access(cmd_name, F_OK | X_OK) == 0)
			return (ft_strjoin(cmd_name, ""));
		return (NULL);
	}
	env_path = ft_getenv(env);
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	result = find_cmd_in_paths(path, cmd_name);
	free_tab(path);
	return (result);
}
