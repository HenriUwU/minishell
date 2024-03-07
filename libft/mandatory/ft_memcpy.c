/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:37:06 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/11 13:41:50 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpy;
	unsigned char	*origin;
	size_t			i;

	cpy = (unsigned char *)dest;
	origin = (unsigned char *)src;
	if (cpy == NULL && origin == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cpy[i] = origin[i];
		i++;
	}
	return (cpy);
}
