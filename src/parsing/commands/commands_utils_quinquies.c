/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_quinquies.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:20:33 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 10:19:01 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_wordcount(char *str)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += skip_quotes(&str[i], str[i]);
			i++;
			wordcount++;
			continue ;
		}
		while (str[i + 1] != '\0' && is_charset("\'\"", str[i + 1]) == 0)
			i++;
		wordcount++;
		i++;
	}
	return (wordcount);
}

static void	mini_split_core(int start, int end, char *str, char **split_str)
{
	int	i;

	i = 0;
	while (str[start] != '\0')
	{
		if (str[start] == '\"' || str[start] == '\'')
		{
			end = (start + 1);
			while (str[end] != str[start])
				end++;
			split_str[i] = ft_substr(str, start + 1, (end - 1) - start);
			i++;
			start = end;
		}
		else if (str[start] != '\'' && str[start] != '\"')
		{
			end = start;
			while (str[end] != '\0' && str[end] != '\'' && str[end] != '\"')
				end++;
			split_str[i] = ft_substr(str, start, end - start);
			i++;
			start = end - 1;
		}
		start++;
	}
}

char	**mini_split(char *str)
{
	char	**split_str;
	int		start;
	int		end;
	int		wordcount;

	if (str == NULL)
		return (NULL);
	start = 0;
	end = 0;
	wordcount = define_wordcount(str);
	split_str = malloc(sizeof(char *) * (wordcount + 1));
	if (split_str == NULL)
		return (NULL);
	mini_split_core(start, end, str, split_str);
	split_str[wordcount] = NULL;
	return (split_str);
}

bool	is_there_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	free_infile_outfile(t_cmd *cmd, int mode)
{
	if (mode == 1)
	{
		free(cmd->infile);
		cmd->infile = NULL;
		if (cmd->input > 2)
			close(cmd->input);
	}
	if (mode == 2)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
		if (cmd->output > 2)
			close(cmd->output);
	}
}
