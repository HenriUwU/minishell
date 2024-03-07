/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:45:33 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 11:09:28 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unclosed_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] != '\0' && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	forbidden_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]);
		if (str[i] == '\\' || str[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

static int	pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isblank(str[i]) == 1)
		i++;
	if (str[i] == '|')
		return (1);
	while (i <= (int)ft_strlen(str) && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]) + 1;
		if (i <= (int)ft_strlen(str) && str[i] == '|')
		{
			i++;
			while (ft_isblank(str[i]) == 1)
				i++;
			if (is_charset("|", str[i]) == 1 || str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	redirections(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]);
		if (str[i] == '<')
		{
			if (left_redirections(&i, str) == 1)
				return (1);
			continue ;
		}
		else if (str[i] == '>')
		{
			if (right_redirections(&i, str) == 1)
				return (1);
			continue ;
		}
		i++;
	}
	return (ret);
}

int	syntax(char *line)
{
	if (unclosed_quotes(line) == 1 || forbidden_characters(line) == 1
		|| pipes(line) == 1 || redirections(line) == 1)
	{
		g_exit_code = 2;
		ft_putstr_fd("Error: syntax error\n", 2);
		return (1);
	}
	return (0);
}
