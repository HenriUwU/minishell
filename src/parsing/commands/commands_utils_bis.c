/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:47:20 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 10:08:52 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_removal_core(char **str, char **new_str)
{
	int		i;
	int		j;
	char	**split_str;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (is_there_quote(str[i]) == false)
		{
			new_str[i] = ft_strdup(str[i]);
			i++;
			continue ;
		}
		split_str = mini_split(str[i]);
		new_str[i] = ft_strdup(split_str[0]);
		while (split_str[j + 1] != NULL)
		{
			new_str[i] = ft_strjoin(new_str[i], split_str[j + 1]);
			j++;
		}
		ft_free_taboftab(split_str);
		i++;
	}
	new_str[i] = NULL;
}

char	*quote_removal_bis(char *str)
{
	char	**split_str;
	char	*new_str;
	int		i;

	if (is_there_quote(str) == false)
		return (str);
	i = 0;
	split_str = mini_split(str);
	new_str = ft_strdup(split_str[0]);
	while (split_str[i + 1] != NULL)
	{
		new_str = ft_strjoin(new_str, split_str[i + 1]);
		if (new_str == NULL)
		{
			free(str);
			ft_free_taboftab(split_str);
			return (NULL);
		}
		i++;
	}
	free(str);
	str = NULL;
	ft_free_taboftab(split_str);
	return (new_str);
}

char	**quote_removal(char **str)
{
	char	**new_str;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char *) * (i + 1));
	if (new_str == NULL)
		return (NULL);
	quote_removal_core(str, new_str);
	ft_free_taboftab(str);
	return (new_str);
}
