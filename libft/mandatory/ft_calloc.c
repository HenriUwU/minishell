/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:23:30 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/03 14:54:51 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memblock;

	if ((int) nmemb < 0 && (int)size < 0)
		return (NULL);
	memblock = malloc(sizeof(char) * (nmemb * size));
	if (memblock == NULL)
		return (NULL);
	ft_bzero(memblock, (nmemb * size));
	return (memblock);
}
