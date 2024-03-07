/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:16:06 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/04 11:08:44 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkchar(char const c, char const *set)
{
	int	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*new_s;
	unsigned int	start;
	unsigned int	end;
	size_t			len;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0' || set[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_checkchar(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_checkchar(s1[end], set) == 1)
		end--;
	len = end - start;
	new_s = ft_substr(s1, start, len + 1);
	return (new_s);
}
