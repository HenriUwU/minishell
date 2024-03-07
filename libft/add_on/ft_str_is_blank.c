/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_blank.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:34:55 by laprieur          #+#    #+#             */
/*   Updated: 2023/03/24 10:34:51 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (0);
	return (1);
}
