/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:34:55 by laprieur          #+#    #+#             */
/*   Updated: 2023/02/07 12:17:16 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversiontype(char c, va_list ap)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_putchar(va_arg(ap, int));
	if (c == 's')
		size += ft_putstr(va_arg(ap, char *));
	if (c == 'p')
		size += ft_putadd(va_arg(ap, unsigned long));
	if (c == 'd' || c == 'i')
		size += ft_putnbr(va_arg(ap, int));
	if (c == 'u')
		size += ft_putunsignedint(va_arg(ap, unsigned int));
	if (c == 'x')
		size += ft_puthexa_lower(va_arg(ap, unsigned int));
	if (c == 'X')
		size += ft_puthexa_upper(va_arg(ap, unsigned int));
	if (c == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		size;

	if (str == NULL)
		return (-1);
	va_start(ap, str);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			size += ft_conversiontype(str[i + 1], ap);
			i++;
		}
		else
			size += ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (size);
}
