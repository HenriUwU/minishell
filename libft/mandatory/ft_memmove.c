/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:31:56 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/12 10:39:40 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cpy;
	unsigned char	*origin;
	int				i;

	cpy = (unsigned char *)dest;
	origin = (unsigned char *)src;
	if (cpy == NULL && origin == NULL)
		return (NULL);
	if (cpy < origin)
		ft_memcpy(cpy, origin, n);
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			cpy[i] = origin[i];
			i--;
		}
	}
	return (cpy);
}
