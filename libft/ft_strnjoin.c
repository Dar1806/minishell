/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 01:33:16 by akkolitozer       #+#    #+#             */
/*   Updated: 2026/08/06 01:57:16 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	char	*new;
	int		i;
	int		j;
	int		len_s1;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	new = ft_malloc((len_s1 + n + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && j < n)
		new[i + j] = s2[j];
	new[i + j] = '\0';
	return (new);
}