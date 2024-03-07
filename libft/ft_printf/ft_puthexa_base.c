/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:39:20 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/19 10:53:57 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa_base(unsigned long nbr, char *base)
{
	int	size;

	size = 0;
	if (nbr >= 16)
		size += ft_puthexa_base(nbr / 16, base);
	ft_putchar(base[nbr % 16]);
	size++;
	return (size);
}
