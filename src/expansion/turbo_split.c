/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:56:19 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/07 11:56:47 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	skip_char(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && is_charset(charset, str[i]) == 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]);
		i++;
	}
	if (str[i] != '\0')
		i++;
	return (i);
}

static void	process_string_core(char *str, char *charset, char **words)
{
	int	i;
	int	j;
	int	wordlen;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (is_charset(charset, str[i]) == 1)
			i++;
		if (i == 0 || is_charset(charset, str[i - 1]) == 1)
		{
			words[j] = get_next_word(&str[i], charset);
			if (words[j] == NULL)
				mfree(words, j);
			wordlen = ft_strlen(words[j]);
			j++;
			i += wordlen;
		}
		else
			i += skip_char(&str[i], charset);
	}
	words[j] = NULL;
}

static char	**process_string(char *str, char *charset)
{
	char	**words;

	words = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (words == NULL)
		return (NULL);
	process_string_core(str, charset, words);
	return (words);
}

char	**turbo_split(char *str, char *charset)
{
	char	**words;
	char	*tmp;

	tmp = str;
	str = ft_strtrim(tmp, charset);
	words = process_string(str, charset);
	free(str);
	str = NULL;
	return (words);
}
