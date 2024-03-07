/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:49:51 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/12 13:56:10 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_definesize(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	res;
	int		size_n;
	char	*tab;

	res = (long) n;
	size_n = ft_definesize(res);
	tab = malloc(sizeof(char) * (size_n + 1));
	if (tab == NULL)
		return (NULL);
	tab[size_n] = '\0';
	if (res < 0)
	{
		tab[0] = '-';
		res *= -1;
	}
	if (res == 0)
		tab[0] = '0';
	while (res > 0)
	{
		tab[size_n - 1] = (res % 10) + 48;
		res /= 10;
		size_n--;
	}
	return (tab);
}
