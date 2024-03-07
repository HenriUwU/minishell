/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:45:25 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 10:02:21 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int index, t_cmd *cmd, t_program *data)
{
	if (index % 2 == 0 && cmd->next != NULL)
		pipe(data->pipe1);
	else if (index % 2 == 1 && cmd->next != NULL)
		pipe(data->pipe2);
}

int	count_nb_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		nb_cmd;

	tmp = cmd;
	nb_cmd = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		nb_cmd++;
	}
	return (nb_cmd);
}

int	exec_builtins(t_program *data, t_env *envp, t_cmd *cmd, t_cmd *all)
{
	if (cmd->next != NULL && cmd->pid != 0)
		return (1);
	if (ft_strncmp(cmd->cmd[0], "echo", ft_strlen(cmd->cmd[0]) + 1) == 0)
		echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", ft_strlen(cmd->cmd[0]) + 1) == 0)
		cd(cmd->cmd, envp);
	else if (ft_strncmp(cmd->cmd[0], "pwd", ft_strlen(cmd->cmd[0]) + 1) == 0)
		pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", ft_strlen(cmd->cmd[0]) + 1) == 0)
		export(envp, cmd->cmd, data);
	else if (ft_strncmp(cmd->cmd[0], "unset", ft_strlen(cmd->cmd[0]) + 1) == 0)
		unset(&envp, data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", ft_strlen(cmd->cmd[0]) + 1) == 0)
		env(envp, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0]) + 1) == 0)
		mini_exit(envp, cmd, all);
	else
		return (1);
	exit_child(all, envp, cmd->pid);
	return (0);
}

static void	exec_cmd(t_program *data, t_env *env, t_cmd *cmd, t_cmd *all)
{
	char	*cmd_path;
	char	**command;

	handle_path(env, cmd, all);
	if (cmd->cmd_path != NULL && access(cmd->cmd_path, X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd->cmd_path);
		command = ft_tabdup(cmd->cmd);
		free_all(env, all);
		if (execve(cmd_path, command, data->env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command[0], 2);
			perror(" ");
			free(cmd_path);
			ft_free_taboftab(command);
			exit(126);
		}
	}
	cmd_not_found(env, cmd, all);
}

void	fork_exec(t_cmd *tmp, t_cmd *cmd, t_program *data, t_env *env)
{
	tmp->pid = fork();
	if (tmp->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (parse_dup2(tmp->index, tmp, data) == 1)
			exit_child(cmd, env, 0);
		else if (exec_builtins(data, env, tmp, cmd) == 1)
			exec_cmd(data, env, tmp, cmd);
	}
}
