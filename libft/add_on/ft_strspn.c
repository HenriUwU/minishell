/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:29:54 by laprieur          #+#    #+#             */
/*   Updated: 2023/05/05 11:30:27 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				count++;
				break ;
			}
			j++;
		}
		if (accept[j] == '\0')
			break ;
		i++;
	}
	return (count);
}
