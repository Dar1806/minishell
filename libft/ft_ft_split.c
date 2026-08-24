/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:43:39 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/24 18:28:58 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_isc(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	ft_count(const char *s, char c)
{
	int	i;
	int	cmp;

	i = 0;
	cmp = 0;
	while (s[i])
	{
		while (s[i] && ft_isc(s[i], c))
			i++;
		if (s[i] && !ft_isc(s[i], c))
		{
			cmp++;
			while (s[i] && !ft_isc(s[i], c))
				i++;
		}
	}
	return (cmp);
}

static char	*ft_ft_stock(const char *str, char c)
{
	int		i;
	int		len;
	char	*dest;

	len = 0;
	while (str[len] && !ft_isc(str[len], c))
		len++;
	dest = ft_malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	process(const char **str, char c, char **tab, int *j)
{
	char	*nvstr;

	while (**str && ft_isc(**str, c))
		(*str)++;
	if (!**str)
		return (0);
	nvstr = ft_ft_stock(*str, c);
	if (!nvstr)
	{
		return (-1);
	}
	tab[*j] = nvstr;
	(*j)++;
	while (**str && !ft_isc(**str, c))
		(*str)++;
	return (0);
}

char	**ft_ft_split(char const *s, char c)
{
	char		**tab;
	const char	*str;
	int			count;
	int			j;
	int			res;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	tab = ft_malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	j = 0;
	str = s;
	while (*str)
	{
		res = process(&str, c, tab, &j);
		if (res == -1)
			return (NULL);
	}
	tab[j] = NULL;
	return (tab);
}
