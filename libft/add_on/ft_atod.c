/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:09:08 by laprieur          #+#    #+#             */
/*   Updated: 2023/02/27 16:03:03 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	decimal_part(const char *nptr)
{
	int		i;
	double	nb;
	double	decimal;

	i = 0;
	while (nptr[i] != '.')
		i++;
	i++;
	nb = 0.0;
	decimal = 0.1;
	while (ft_isdigit(nptr[i]) == 1)
	{
		nb = nb + decimal * (nptr[i] - 48);
		decimal /= 10;
		i++;
	}
	return (nb);
}

static double	integer_part(const char *nptr)
{
	int		i;
	double	nb;

	i = 0;
	nb = 0;
	while (ft_isdigit(nptr[i]) == 1 && nptr[i] != '.')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

double	ft_atod(const char *nptr)
{
	int		i;
	int		minus;
	double	integer;
	double	decimal;
	double	nb;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	minus = 1.0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus *= -1.0;
		i++;
	}
	integer = integer_part(&nptr[i]);
	decimal = decimal_part(&nptr[i]);
	nb = (integer + decimal) * minus;
	return (nb);
}
