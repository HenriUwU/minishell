/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:44:54 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 10:01:54 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		if (((char *)lst->content)[0] != '\0')
		{
			free(lst->content);
			lst->content = NULL;
		}
		lst = lst->next;
		free(tmp);
	}
}

char	is_in_quotes(char *str, char *substr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i += skip_quotes(&str[i], str[i]);
		}
		if (&str[i] >= substr)
			break ;
		i++;
	}
	if (str[i] == '\"' || str[i] == '\'')
		return (str[i]);
	return (0);
}
