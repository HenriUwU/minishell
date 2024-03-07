/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:50 by laprieur          #+#    #+#             */
/*   Updated: 2022/12/05 16:09:24 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	minus;
	long	nb;

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
		if (nb * minus > 2147483647)
			return (-1);
		if (nb * minus < -2147483648)
			return (0);
		i++;
	}
	return (minus * nb);
}
