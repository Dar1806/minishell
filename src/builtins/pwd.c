/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:57:14 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/16 17:36:32 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		shell->ex_status = 1;
		return ;
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	shell->ex_status = 0;
}
