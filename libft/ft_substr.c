/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:32:38 by nmeunier          #+#    #+#             */
/*   Updated: 2026/07/20 16:50:32 by hulescur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	slen;
	char	*subs;

	j = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		subs = malloc(1);
		if (!subs)
			return (0);
		subs[0] = '\0';
		return (subs);
	}
	if (len > slen - start)
		len = slen - start;
	subs = malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (0);
	while (s[start] && j < len)
		subs[j++] = s[start++];
	subs[j] = '\0';
	return (subs);
}

char	*ft_ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	slen;
	char	*subs;

	j = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		subs = ft_malloc(1);
		if (!subs)
			return (0);
		subs[0] = '\0';
		return (subs);
	}
	if (len > slen - start)
		len = slen - start;
	subs = ft_malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (0);
	while (s[start] && j < len)
		subs[j++] = s[start++];
	subs[j] = '\0';
	return (subs);
}
