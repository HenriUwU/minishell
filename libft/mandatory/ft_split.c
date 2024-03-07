/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:28:04 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/14 11:27:36 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	char	**new_s;

	if (s == NULL)
		return (NULL);
	new_s = malloc(sizeof(char *) * (ft_definewordcount(s, c) + 1));
	if (new_s == NULL)
		return (NULL);
	new_s = ft_split_core(s, c, new_s);
	return (new_s);
}
