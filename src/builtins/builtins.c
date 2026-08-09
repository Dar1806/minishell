/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 13:14:58 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/09 04:01:47 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_ins(char *args)
{
	if (ft_strncmp(args, "echo", 4) == 0 && ft_strlen(args) == 4)
		return (0);
	else if (ft_strncmp(args, "cd", 2) == 0 && ft_strlen(args) == 2)
		return (1);
	else if (ft_strncmp(args, "pwd", 3) == 0 && ft_strlen(args) == 3)
		return (2);
	else if (ft_strncmp(args, "export", 6) == 0 && ft_strlen(args) == 6)
		return (3);
	else if (ft_strncmp(args, "unset", 5) == 0 && ft_strlen(args) == 5)
		return (4);
	else if (ft_strncmp(args, "env", 3) == 0 && ft_strlen(args) == 3)
		return (5);
	else if (ft_strncmp(args, "exit", 4) == 0 && ft_strlen(args) == 4)
		return (6);
	else
		return (-1);
}

void	exec_built_ins(t_cmd *cmd, t_shell *shell, int code)
{
	if (code == 0)
		ft_echo(cmd, shell);
	//if (code == 1)
	//	ft_cd(cmd, shell);
	//if (code == 2)
	//	ft_pwd(cmd, shell);
	if (code == 3)
		ft_export(cmd, shell);
	//if (code == 4)
	//	ft_unset(cmd, shell);
	//if (code == 5)
	//	ft_env(cmd, shell);
	//if (code == 6)
	//	ft_exit(cmd, shell);
}
