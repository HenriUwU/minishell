/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:00:00 by laprieur          #+#    #+#             */
/*   Updated: 2022/09/29 11:27:23 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*firstblock;
	unsigned char	*secblock;
	size_t			i;

	firstblock = (unsigned char *)s1;
	secblock = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (firstblock[i] != secblock[i])
			return (firstblock[i] - secblock[i]);
		i++;
	}
	return (0);
}
