/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:34:17 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/05 18:20:00 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_type(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

int	is_word_type(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTES
		|| type == TOKEN_DOUBLE_QUOTES);
}
