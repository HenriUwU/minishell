/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:59:07 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 09:28:07 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_access_error(t_cmd *cmd, t_cmd *all, t_env *env, int mode)
{
	if (mode == 1)
		g_exit_code = 127;
	else if (mode == 2)
		g_exit_code = 126;
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit_child(all, env, cmd->pid);
}

void	cmd_not_found(t_env *env, t_cmd *cmd, t_cmd *all)
{
	if (open(cmd->cmd[0], O_DIRECTORY) != -1)
	{
		g_exit_code = 126;
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit_child(all, env, cmd->pid);
	}
	if (ft_strchr(cmd->cmd[0], '/') != NULL
		&& open(cmd->cmd[0], O_RDONLY) == -1)
		print_access_error(cmd, all, env, 1);
	if (ft_strchr(cmd->cmd[0], '/') != NULL && access(cmd->cmd[0], X_OK) != 0)
		print_access_error(cmd, all, env, 2);
	g_exit_code = 127;
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit_child(all, env, cmd->pid);
}

void	close_pipes(int index, int *pipe1, int *pipe2)
{
	if (index % 2 == 0)
	{
		if (pipe1[1] > 2)
		{
			close(pipe1[1]);
			pipe1[1] = 1;
		}
		if (pipe2[0] > 2)
		{
			close(pipe2[0]);
			pipe2[0] = 0;
		}
		return ;
	}
	if (pipe1[0] > 2)
	{
		close(pipe1[0]);
		pipe1[0] = 0;
	}
	if (pipe2[1] > 2)
	{
		close(pipe2[1]);
		pipe2[1] = 1;
	}
}

void	close_input_output(int input, int output)
{
	if (input > 2)
		close(input);
	if (output > 2)
		close(output);
}

void	exit_status(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		wstatus;

	tmp = cmd;
	wstatus = 0;
	while (tmp != NULL)
	{
		if (tmp->pid != -1)
		{
			waitpid(tmp->pid, &wstatus, 0);
			if (WCOREDUMP(wstatus))
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else if (WIFSIGNALED(wstatus))
				ft_putchar_fd('\n', 2);
			if (WIFEXITED(wstatus))
				g_exit_code = WEXITSTATUS(wstatus);
			else
				g_exit_code = 128 + WTERMSIG(wstatus);
		}
		tmp = tmp->next;
	}
}
