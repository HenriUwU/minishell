/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:31:50 by laprieur          #+#    #+#             */
/*   Updated: 2023/05/05 11:32:14 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if (s[i] != reject[j])
			{
				count++;
				break ;
			}
			j++;
		}
		if (reject[j] == '\0')
			break ;
		i++;
	}
	return (count);
}
