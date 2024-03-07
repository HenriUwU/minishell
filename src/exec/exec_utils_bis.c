/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:41:17 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 11:14:13 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_dup2(int index, t_cmd *cmd, t_program *data)
{
	if (cmd->heredoc != -42 && cmd->input != -1 && cmd->input < 2)
	{
		cmd->input = open("/tmp/.heredoc", O_RDONLY | O_CREAT);
		unlink("/tmp/.heredoc");
	}
	if (index == 0)
		return (make_dup2_first(cmd, data->pipe1));
	else if (index != 0 && cmd->next != NULL && index % 2 == 0)
		return (make_dup2_within(cmd, data->pipe1, data->pipe2, WITHIN_EVEN));
	else if (index != 0 && cmd->next != NULL && index % 2 == 1)
		return (make_dup2_within(cmd, data->pipe1, data->pipe2, WITHIN_ODD));
	else if (cmd->next == NULL && index % 2 == 0)
		return (make_dup2_last(cmd, data->pipe1, data->pipe2, LAST_EVEN));
	else if (cmd->next == NULL && index % 2 == 1)
		return (make_dup2_last(cmd, data->pipe1, data->pipe2, LAST_ODD));
	return (0);
}

int	exit_child(t_cmd *cmd, t_env *env, int pid)
{
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (cmd->input > 2)
			close(cmd->input);
		if (cmd->output > 2)
			close(cmd->output);
		free_all(env, cmd);
		exit(g_exit_code);
	}
	return (0);
}

static int	check_absolute_path(char *cmd)
{
	char	*absolute_pathname;
	char	*cmd_path;
	char	buf[PATH_MAX];

	cmd_path = NULL;
	if (ft_strchr(cmd, '/') == NULL)
	{
		absolute_pathname = getcwd(buf, sizeof(buf));
		cmd_path = ft_strjoin(ft_strdup(absolute_pathname), cmd);
	}
	if (cmd != NULL && (cmd[0] == '\0' || cmd[ft_strlen(cmd) - 1] == '/'
			|| cmd[ft_strlen(cmd) - 1] == '.'))
	{
		free(cmd_path);
		return (1);
	}
	else if (cmd_path != NULL && access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		return (3);
	}
	else if (cmd != NULL && cmd[0] != '\0' && access(cmd, X_OK) == 0)
		return (2);
	return (0);
}

static char	**get_path(t_env *env)
{
	char	*full_path;
	char	**split_path;

	full_path = NULL;
	while (env != NULL)
	{
		if (ft_strncmp(env->var, "PATH", 5) == 0)
		{
			full_path = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	split_path = NULL;
	if (full_path != NULL)
	{
		split_path = ft_split(full_path, ':');
		free(full_path);
		full_path = NULL;
	}
	return (split_path);
}

void	handle_path(t_env *env, t_cmd *cmd, t_cmd *all)
{
	char	**path;
	int		i;
	char	*tmp;

	if (check_absolute_path(cmd->cmd[0]) == 1)
		cmd_not_found(env, cmd, all);
	path = get_path(env);
	if (check_absolute_path(cmd->cmd[0]) == 2)
		cmd->cmd_path = ft_strdup(cmd->cmd[0]);
	else
	{
		i = 0;
		while (path != NULL && path[i] != NULL)
		{
			tmp = ft_strjoin(ft_strdup(path[i]), "/");
			cmd->cmd_path = ft_strjoin(tmp, cmd->cmd[0]);
			if (access(cmd->cmd_path, X_OK) == 0)
				break ;
			free(cmd->cmd_path);
			cmd->cmd_path = NULL;
			i++;
		}
	}
	ft_free_taboftab(path);
	return ;
}
