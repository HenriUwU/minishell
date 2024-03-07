/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:01:33 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/10 10:27:01 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (lst != NULL)
	{
		i = 0;
		while (lst != NULL)
		{
			i++;
			lst = lst->next;
		}
		return (i);
	}
	return (0);
}
