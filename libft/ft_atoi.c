/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeunier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:51:44 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/22 18:58:16 by nmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nb, int *error)
{
	int			i;
	int			s;
	int			start;
	long int	num;

	i = 0;
	s = 1;
	num = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if ((nb[i] == '-' || nb[i] == '+') && nb[i + 1])
		if (nb[i++] == '-')
			s = -1;
	start = i;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		num = num * 10 + (nb[i] - '0');
		if ((s == 1 && num > INT_MAX) || (s == -1 && num * s < INT_MIN))
			*error = 1;
		i++;
	}
	if (nb[i] || i == start)
		*error = 1;
	return (num * s);
}
