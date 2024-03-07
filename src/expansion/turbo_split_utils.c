/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:44:54 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/14 13:50:35 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_char(char *str, char *charset)
{
	char	i;
	char	j;

	i = *str;
	if (i != '\0')
		j = *(str + 1);
	else
		j = 0;
	if (i != '\0' && is_charset(charset, i) == 1)
		return (1);
	else if (i == '<' || i == '>')
		return (1);
	else if (i == '<' && j != '<')
		return (1);
	else if (i == '>' && j != '>')
		return (1);
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (str[i] != '\0')
	{
		while (str[i] && is_valid_char(&str[i], charset) == 1)
			i++;
		while (str[i] && is_valid_char(&str[i], charset) == 0)
		{
			if (str[i] == '\'' || str[i] == '\"')
				i += skip_quotes(&str[i], str[i]) + 1;
			else
				i++;
		}
		wordcount++;
		if (str[i])
			i++;
	}
	return (wordcount);
}

int	get_redir_len(char *str, char *charset, int len, int i)
{
	while (str[len] != '\0' && is_charset(charset, str[len]) == 0)
	{
		if (str[len] == '\'' || str[len] == '\"')
			len += skip_quotes(&str[len], str[len]) + 1;
		else if (str[len] == '<' || str[len] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				len += 2;
			else
				len++;
			while (str[len] != '\0' && is_charset(charset, str[len]) == 1)
				len++;
			if (str[len] == '\'' || str[len] == '\"')
						len += skip_quotes(&str[len], str[len]) + 1;
			while (str[len] != '\0' && ft_isprint(str[len]) == 1
				&& is_charset(charset, str[len]) == 0)
				len++;
		}
		else
			len++;
	}
	return (len);
}

char	*get_next_word(char *str, char *charset)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	i = 0;
	len = get_redir_len(str, charset, len, i);
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	mfree(char **words, int position)
{
	int	i;

	i = 0;
	while (i <= position)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
}
