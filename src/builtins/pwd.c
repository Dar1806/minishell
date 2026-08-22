/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:57:14 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/22 17:24:13 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		shell->ex_status = 1;
		return ;
	}
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	shell->ex_status = 0;
}
