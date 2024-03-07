/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:19:44 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/19 15:07:09 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_treatment(t_cmd *cmd, char **redirs, int cmd_index)
{
	int		i;
	char	**new_redirs;

	i = 0;
	new_redirs = quote_removal(redirs);
	if (new_redirs == NULL)
		return ;
	while (cmd_index > 0 && cmd != NULL)
	{
		cmd = cmd->next;
		cmd_index--;
	}
	while (new_redirs[i])
	{
		if (new_redirs[i][1] == '<')
			heredoc(cmd, &new_redirs[i][3]);
		i++;
	}
	ft_free_taboftab(new_redirs);
}

static void	set_redirections(t_cmd *cmd, t_env *env, char **redir)
{
	int		i;
	int		redir_in;
	int		redir_out;
	bool	is_file_ok;

	redir_in = -1;
	redir_out = -1;
	i = 0;
	while (redir[i])
	{
		is_file_ok = true;
		redir_in = define_infile(cmd, env, redir[i], redir_in);
		redir_out = define_outfile(cmd, env, redir[i], redir_out);
		open_infile(cmd, &redir_in, &is_file_ok);
		if ((cmd->input > 2 || cmd->heredoc == 1)
			&& is_last_redir(&redir[i], 1) == false)
			free_infile_outfile(cmd, 1);
		open_outfile(cmd, &redir_out, &is_file_ok);
		if ((cmd->output > 2 && is_last_redir(&redir[i], 2) == false)
			|| cmd->output == -1)
			free_infile_outfile(cmd, 2);
		i++;
	}
	is_file_ok = true;
	ft_free_taboftab(redir);
}

static int	create_cmds_list(char **cmds, char *rwrk_str, t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		rwrk_str = restructure_string(cmds[i]);
		cmd_lstadd_back(cmd, cmd_lstnew());
		heredoc_treatment(*cmd, get_redir(rwrk_str), i);
		if (g_exit_code == 386)
		{
			free(rwrk_str);
			rwrk_str = NULL;
			return (1);
		}
		free(rwrk_str);
		rwrk_str = NULL;
		i++;
	}
	return (0);
}

static void	create_cmds(char **cmds, char *rwrk_str, t_cmd **cmd, t_env *env)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (tmp != NULL && cmds[i] != NULL)
	{
		rwrk_str = restructure_string(cmds[i]);
		tmp->cmd = get_cmd(env, rwrk_str);
		set_redirections(tmp, env, get_redir(rwrk_str));
		tmp = tmp->next;
		free(rwrk_str);
		rwrk_str = NULL;
		i++;
	}
}

void	commands(t_program *data, t_env *env, t_cmd **cmd)
{
	char	**commands;
	char	*rework_str;

	commands = ft_split(data->line, '|');
	free(data->line);
	data->line = NULL;
	rework_str = NULL;
	if (create_cmds_list(commands, rework_str, cmd) == 1)
	{
		ft_free_taboftab(commands);
		return ;
	}
	create_cmds(commands, rework_str, cmd, env);
	ft_free_taboftab(commands);
}
