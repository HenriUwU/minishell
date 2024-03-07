/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:52:11 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/09 11:31:57 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_vars(t_program *data, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	data->pipe1[0] = 0;
	data->pipe1[1] = 1;
	data->pipe2[0] = 0;
	data->pipe2[1] = 1;
	tmp = cmd;
	i = 0;
	while (tmp != NULL)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

void	exec(t_program *data, t_env *env, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	init_vars(data, tmp);
	while (tmp != NULL)
	{
		create_pipes(tmp->index, tmp, data);
		if (tmp->cmd[0] != NULL && (count_nb_cmd(cmd) > 1 || tmp->input > 2
				|| tmp->output > 2 || exec_builtins(data, env, tmp, cmd) == 1))
			fork_exec(tmp, cmd, data, env);
		close_pipes(tmp->index, data->pipe1, data->pipe2);
		close_input_output(tmp->input, tmp->output);
		tmp = tmp->next;
	}
	exit_status(cmd);
}
