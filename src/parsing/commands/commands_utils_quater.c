/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_quater.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:14:22 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 13:44:36 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_redir(char *cmd)
{
	int	i;
	int	nb_redir;

	i = 0;
	nb_redir = 0;
	while (cmd[i] != '\0')
	{
		if (is_charset("<>", cmd[i]) == 1 && is_in_quotes(cmd, &cmd[i]) == 0)
		{
			nb_redir++;
			i += get_redir_len(&cmd[i], " \t\n", 0, 0);
		}
		else
			i++;
	}
	return (nb_redir);
}

char	**get_redir(char *cmd)
{
	int		i;
	int		j;
	char	**redir;

	redir = malloc(sizeof(char *) * (get_nb_redir(cmd) + 1));
	if (redir == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (is_charset("<>", cmd[i]) == 1 && is_in_quotes(cmd, &cmd[i]) == 0)
		{
			redir[j] = ft_substr(cmd, i, get_redir_len(&cmd[i], " \t\n", 0, 0));
			j++;
			i += get_redir_len(&cmd[i], " \t\n", 0, 0);
		}
		else
			i++;
	}
	redir[j] = NULL;
	return (redir);
}

static char	**redir_removal(char **cmd, t_env *env)
{
	char	**final_cmd;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '<' && cmd[i][0] != '>')
			j++;
	}
	final_cmd = malloc(sizeof(char *) * (j + 1));
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '<' && cmd[i][0] != '>')
		{
			final_cmd[j] = expansion(cmd[i], env, 1);
			j++;
		}
	}
	final_cmd[j] = NULL;
	ft_free_taboftab(cmd);
	return (final_cmd);
}

char	**get_cmd(t_env *env, char *command)
{
	char	*expand_cmd;
	char	**split_cmd;
	char	**unredir_cmd;
	char	**unquoted_cmd;

	expand_cmd = expansion(command, env, 0);
	split_cmd = turbo_split(expand_cmd, " \t\n");
	unredir_cmd = redir_removal(split_cmd, env);
	unquoted_cmd = quote_removal(unredir_cmd);
	free(expand_cmd);
	expand_cmd = NULL;
	return (unquoted_cmd);
}
