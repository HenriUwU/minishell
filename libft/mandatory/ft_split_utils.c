/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:11:47 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/19 19:55:02 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_quotes(const char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	return (i);
}

int	ft_definewordcount(char const *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\''))
		{
			i += skip_quotes(&s[i], s[i]);
			wordcount++;
		}
		else if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') \
		|| (s[0] != c && i == 0))
			wordcount++;
		i++;
	}
	return (wordcount);
}

static int	ft_definewordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += skip_quotes(&s[i], s[i]);
		i++;
	}
	return (i);
}

static void	ft_mfree(char **new_s, int position)
{
	int	i;

	i = 0;
	while (i <= position)
	{
		free(new_s[i]);
		new_s[i] = NULL;
		i++;
	}
}

char	**ft_split_core(char const *s, char c, char **new_s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i != 0 && (s[i] == '\"' || s[i] == '\'') && s[i - 1] != c)
			i += skip_quotes(&s[i], s[i]);
		else if ((i == 0 && s[i] != c)
			|| (i != 0 && s[i - 1] == c && s[i] != c))
		{
			new_s[j] = ft_substr(s, i, ft_definewordlen(&s[i], c));
			if (new_s[j] == NULL)
				ft_mfree(new_s, j);
			j++;
			if (s[i] == '\'' || s[i] == '\"')
				i += skip_quotes(&s[i], s[i]);
		}
		if (s[i])
			i++;
	}
	new_s[j] = NULL;
	return (new_s);
}
