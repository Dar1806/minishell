/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 11:48:03 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/21 18:57:46 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char *path, t_shell *shell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	shell->ex_status = 1;
}

void	cd_home(t_shell *shell)
{
	char	*path;

	path = get_envv(shell->envl, "HOME");
	if (path[0] == '\0')
	{
		shell->ex_status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	if (chdir(path) == -1)
	{
		shell->ex_status = 1;
		cd_error(path, shell);
	}
	else
		shell->ex_status = 0;
}

void	cd_path(t_cmd *cmd, t_shell *shell)
{
	if (chdir(cmd->args[1]) == -1)
	{
		shell->ex_status = 1;
		cd_error(cmd->args[1], shell);
	}
	else
		shell->ex_status = 0;
}

void	update_pwd(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	if (!old_pwd)
		tmp = ft_ft_strjoin("OLDPWD=", "");
	else
		tmp = ft_ft_strjoin("OLDPWD=", old_pwd);
	env_export(&shell->envl, tmp);
	tmp = ft_ft_strjoin("PWD=", new_pwd);
	env_export(&shell->envl, tmp);
	free(new_pwd);
}

void	ft_cd(t_cmd *cmd, t_shell *shell)
{
	char	*old_pwd;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->ex_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (!cmd->args[1])
		cd_home(shell);
	else
		cd_path(cmd, shell);
	if (shell->ex_status == 0)
		update_pwd(shell, old_pwd);
	free(old_pwd);
}
