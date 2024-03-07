/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:59:03 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/19 10:52:24 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadd(unsigned long nb)
{
	int	size;

	if (!nb)
	{
		ft_putstr("(nil)");
		return (5);
	}
	size = ft_putstr("0x");
	size += ft_puthexa_base(nb, "0123456789abcdef");
	return (size);
}
