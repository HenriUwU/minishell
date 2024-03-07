/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:27:24 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/13 12:57:01 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int			i;
	long long	minus;
	long long	nb;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	minus = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus *= -1;
		i++;
	}
	nb = 0;
	while (ft_isdigit(nptr[i]) == 1)
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (nb < 0)
			return (0);
		if (nb * minus < LONG_MIN)
			return (0);
		i++;
	}
	return (minus * nb);
}
