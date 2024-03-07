/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:02:46 by laprieur          #+#    #+#             */
/*   Updated: 2022/10/12 10:13:00 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;

	if (lst != NULL && f != NULL && del != NULL)
	{
		head = NULL;
		while (lst != NULL)
		{
			new_node = ft_lstnew(f(lst->content));
			if (new_node == NULL)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, new_node);
			lst = lst->next;
		}
		return (head);
	}
	return (NULL);
}
