/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:47:49 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 10:31:37 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_program *data, t_env *env)
{
	t_cmd	*cmd;

	while (1)
	{
		cmd = NULL;
		rl_event_hook = for_rl_event_hook;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline("❌ AntiShell:~$ ");
		if (data->line == NULL)
		{
			free_list_env(env);
			ctrl_d(0);
		}
		if (data->line[0] != '\0' && g_exit_code != 386)
			add_history(data->line);
		if (syntax(data->line) == 1)
			continue ;
		commands(data, env, &cmd);
		if (g_exit_code != 386)
			exec(data, env, cmd);
		free_all(NULL, cmd);
		if (g_exit_code == 386)
			g_exit_code = 130;
	}
}
