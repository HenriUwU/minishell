/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:13:58 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/19 12:07:23 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_conversiontype(char c, va_list ap);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putadd(unsigned long nb);
int		ft_putnbr(int nb);
int		ft_putunsignedint(unsigned int nb);
int		ft_puthexa_lower(unsigned int nb);
int		ft_puthexa_upper(unsigned int nb);
int		ft_puthexa_base(unsigned long nbr, char *base);

#endif
