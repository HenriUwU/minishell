/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:26 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/14 13:12:57 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_spaces(char *str)
{
	int	i;
	int	nb_spaces;

	i = 0;
	nb_spaces = 0;
	while (str[i])
	{
		if ((ft_isprint(str[i]) == 1
				&& is_charset("<> ", str[i]) == 0
				&& is_charset("<>", str[i + 1]) == 1
				&& str[i + 1] != ' '
				&& is_in_quotes(str, &str[i]) == 0)
			|| (is_charset("<>", str[i]) == 1
				&& ft_isprint(str[i + 1]) == 1
				&& is_charset("<> ", str[i + 1]) == 0
				&& is_in_quotes(str, &str[i]) == 0))
			nb_spaces++;
		i++;
	}
	return (nb_spaces);
}

static void	new_string(char *str, char *new_str, int i, int j)
{
	while (str[i] != '\0' && i < (int)ft_strlen(str))
	{
		if (is_charset("\'\"", str[i]) == 1)
			while (str[i] != '\0' && is_in_quotes(str, &str[i]) != 0)
				new_str[j++] = str[i++];
		else if (is_charset(" \t\n", str[i]) == 1
			&& is_charset(" \t\n", str[i + 1]) == 1)
		{
			new_str[j++] = str[i++];
			while (str[i] != '\0' && is_charset(" \t\n", str[i]) == 1)
				i++;
		}
		else if ((ft_isprint(str[i]) == 1 && is_charset("<> ", str[i]) == 0
				&& is_charset("<>", str[i + 1]) == 1 && str[i + 1] != ' ')
			|| (is_charset("<>", str[i]) == 1 && ft_isprint(str[i + 1]) == 1
				&& is_charset("<> ", str[i + 1]) == 0))
		{
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
}

char	*restructure_string(char *str)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + define_spaces(str) + 1));
	if (new_str == NULL)
		return (NULL);
	new_string(str, new_str, 0, 0);
	return (new_str);
}
