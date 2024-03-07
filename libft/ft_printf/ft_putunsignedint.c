/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignedint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:15:14 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/18 17:00:43 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsignedint(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb >= 10)
	{
		size += ft_putnbr(nb / 10);
		size += ft_putnbr(nb % 10);
	}
	if (nb < 10)
	{
		ft_putchar(nb + '0');
		size++;
	}
	return (size);
}
