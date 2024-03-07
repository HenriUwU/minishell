/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_ter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:20:37 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 10:11:29 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_infile(t_cmd *cmd, t_env *env, char *str, int old_redir)
{
	if (str[0] == '<' && str[1] != '<')
	{
		cmd->infile = expansion(&str[2], env, 1);
		cmd->infile = quote_removal_bis(cmd->infile);
		return (INPUT);
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		cmd->infile = ft_substr(str, 3, ft_strlen(str) - 3);
		return (HEREDOC);
	}
	if (old_redir != -1)
		return (old_redir);
	return (-1);
}

int	define_outfile(t_cmd *cmd, t_env *env, char *str, int old_redir)
{
	if (str[0] == '>' && str[1] != '>')
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
		cmd->outfile = expansion(&str[2], env, 1);
		cmd->outfile = quote_removal_bis(cmd->outfile);
		return (OUTPUT);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		cmd->outfile = expansion(&str[3], env, 1);
		cmd->outfile = quote_removal_bis(cmd->outfile);
		return (APPEND);
	}
	if (old_redir != -1)
		return (old_redir);
	return (-1);
}

void	open_infile(t_cmd *cmd, int *redir_in, bool *is_file_ok)
{
	if (*redir_in == INPUT)
	{
		cmd->input = open(cmd->infile, O_RDONLY);
		if (cmd->input == -1)
		{
			perror(cmd->infile);
			free(cmd->infile);
			cmd->infile = NULL;
			g_exit_code = 1;
			*is_file_ok = false;
		}
		*redir_in = -1;
	}
}

void	open_outfile(t_cmd *cmd, int *redir_out, bool *is_file_ok)
{
	if (*redir_out == OUTPUT && *is_file_ok == true)
	{
		if (cmd->input != -1)
			cmd->output = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, \
			0644);
		if (cmd->output == -1)
		{
			perror(cmd->outfile);
			free(cmd->outfile);
			cmd->outfile = NULL;
			g_exit_code = 1;
			*is_file_ok = false;
		}
		*redir_out = -1;
	}
	else if (*redir_out == APPEND && *is_file_ok == true)
	{
		cmd->output = open(cmd->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (cmd->output == -1)
		{
			perror(cmd->outfile);
			*is_file_ok = false;
		}
		*redir_out = -1;
	}
}

bool	is_last_redir(char **redir, int type)
{
	int	i;

	i = 1;
	if (type == 1)
	{
		while (redir[i])
		{
			if (redir[i][0] == '<')
				return (false);
			i++;
		}
	}
	else if (type == 2)
	{
		while (redir[i])
		{
			if (redir[i][0] == '>')
				return (false);
			i++;
		}
	}
	return (true);
}
