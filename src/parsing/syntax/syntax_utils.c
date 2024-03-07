/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:32:09 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 18:35:46 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	return (i);
}

int	left_redirections(int *i, char *str)
{
	(*i)++;
	if (str[*i] == '<')
		(*i)++;
	else if (str[*i] == '>')
		return (1);
	while (ft_isblank(str[*i]) == 1)
		(*i)++;
	if (is_charset("<>|", str[*i]) == 1 || str[*i] == '\0')
		return (1);
	return (0);
}

int	right_redirections(int *i, char *str)
{
	(*i)++;
	if (str[*i] == '>')
		(*i)++;
	else if (str[*i] == '<')
		return (1);
	while (ft_isblank(str[*i]) == 1)
		(*i)++;
	if (is_charset("<>|", str[*i]) == 1 || str[*i] == '\0')
		return (1);
	return (0);
}
